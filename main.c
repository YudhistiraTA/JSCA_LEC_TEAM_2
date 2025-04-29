#include <stdio.h>
#include <stdlib.h>

#include "sqlite3.h"
#define TRUE 1
#define FALSE 0
#define INVALID -1

typedef struct {
  char *register_id;
  char *name;
  int age;
} Student;

int initialize_database(sqlite3 *db) {
  char *err_msg = 0;

  /**
   * Open or create a new SQLite database file
   */
  int rc = sqlite3_open("siswa.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return rc;
  }

  /**
   * Create Student Table query
   */
  const char *sql =
      "CREATE TABLE IF NOT EXISTS students("
      "register_id TEXT PRIMARY KEY, "
      "name TEXT NOT NULL, "
      "age INT NOT NULL);";
  rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    return rc;
  }

  return SQLITE_OK;
}

void close_and_exit(sqlite3 **db, int EXIT_STATUS) {
  if (*db) {
    sqlite3_close(*db);
    *db = NULL;
  }
  exit(EXIT_STATUS);
}

void prompt_and_input(int *input) {
  printf("1. Add Student\n");
  printf("2. Find Student\n");
  printf("3. Delete Student\n");
  printf("4. Exit\n");
  printf("Enter your choice: ");
  if ((scanf("%d", input) != 1)) {
    *input = -1;
    while (getchar() != '\n');  // Clear the input buffer
  }
};

int add_student(sqlite3 *db) { return 0; }

int find_student(sqlite3 *db) { return 0; }

int delete_student(sqlite3 *db) { return 0; }

void close_loop(int *program_cycle) {
  printf("Exiting...\n");
  *program_cycle = FALSE;
}

int main() {
  sqlite3 *db;
  if (initialize_database(db) != SQLITE_OK) {
    fprintf(stderr, "Failed to initialize database.\n");
    close_and_exit(&db, EXIT_FAILURE);
  }

  int err = FALSE;
  int choice = INVALID;
  int program_cycle = TRUE;
  while (program_cycle) {
    prompt_and_input(&choice);
    switch (choice) {
      case 1:
        err = add_student(db);
        if (err) {
          fprintf(stderr, "Failed to add student.\n");
          close_and_exit(&db, EXIT_FAILURE);
        }
        break;
      case 2:
        err = find_student(db);
        if (err) {
          fprintf(stderr, "Failed to view students.\n");
          close_and_exit(&db, EXIT_FAILURE);
        }
        break;
      case 3:
        err = delete_student(db);
        if (err) {
          fprintf(stderr, "Failed to delete student.\n");
          close_and_exit(&db, EXIT_FAILURE);
        }
        break;
      case 4:
        close_loop(&program_cycle);
        break;
      default:
        printf("Invalid choice. Please try again.\n");
    }
  }

  close_and_exit(&db, EXIT_SUCCESS);
}
