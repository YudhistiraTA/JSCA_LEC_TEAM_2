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

int initialize_database(sqlite3 **db) { // this is a double pointer holds the 'address of db'
  char *err_msg = 0;

  /**
   * Open or create a new SQLite database file
   */
  int rc = sqlite3_open("siswa.db", db); // Then update the 'sqlite3 *db' value
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
    sqlite3_close(*db);
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
  rc = sqlite3_exec(*db, sql, 0, 0, &err_msg); // *db = address of sqlite3
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

void free_student_loc(Student *student) {
  if (student->register_id != NULL) {
    free(student->register_id);
  }
  if (student->name != NULL) {
    free(student->name);
  }
}

void null_database(sqlite3 *db) {
  fprintf(stderr, "Database connection is NULL.\n");
  close_and_exit(&db, EXIT_FAILURE);
}

int add_student(sqlite3 **db) {
  if (*db == NULL) { // address of sqlite3
    null_database(*db);
  }

  Student student;
  student.register_id = (char *)malloc(5 * sizeof(char));
  student.name = (char *)malloc(50 * sizeof(char));

  if (student.register_id == NULL || student.name == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return SQLITE_ERROR;
  }

  printf("Enter register ID: ");
  if (scanf("%4s", student.register_id) != 1) {
    fprintf(stderr, "Invalid input for Registration ID.\n");
    free_student_loc(&student);
    return SQLITE_ERROR;
  }

  printf("Enter name: ");
  if (scanf(" %[^\n]", student.name) != 1) {
    fprintf(stderr, "Invalid input for Name.\n");
    free_student_loc(&student);
    return SQLITE_ERROR;
  }

  printf("Enter age: ");
  if (scanf("%d", &student.age) != 1) {
    printf("Invalid age input. Please enter a valid number.\n");
    while (getchar() != '\n');
    free_student_loc(&student);
    return SQLITE_ERROR;
  }

  const char *insert_query = "INSERT INTO students (register_id, name, age) VALUES (?, ?, ?);";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(*db, insert_query, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(*db));
    free_student_loc(&student);
    return rc;
  }

  sqlite3_bind_text(stmt, 1, student.register_id, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, student.name, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 3, student.age);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Failed to insert student: %s\n", sqlite3_errmsg(*db));
    sqlite3_finalize(stmt);
    free_student_loc(&student);
    return rc;
  }

  sqlite3_finalize(stmt);
  free_student_loc(&student);

  printf("Student added successfully.\n");
  return SQLITE_OK;
}

int find_student(sqlite3 *db) { return 0; }

int delete_student(sqlite3 *db) { return 0; }

void close_loop(int *program_cycle) {
  printf("Exiting...\n");
  *program_cycle = FALSE;
}

int main() {
  sqlite3 *db; // allocate memory for SQLite3 pointer
  if (initialize_database(&db) != SQLITE_OK) { // sent the 'address of db' itself
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
        err = add_student(&db); // give the 'address of db' itself as an argument
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
