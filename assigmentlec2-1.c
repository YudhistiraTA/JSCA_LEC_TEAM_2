#include <stdio.h>
#include <stdlib.h>

int main() {
    int *grades;
    int numStudents, i;

    printf("Enter number of students: ");
    scanf("%d", &numStudents);

    grades = malloc(numStudents * sizeof(int));  

    if (grades == NULL) {
        printf("Memory allocation failed.\n");
        return 1; 
    }

    for (i = 0; i < numStudents; i++) {
        printf("Enter grade for student %d: ", i + 1);
        scanf("%d", &grades[i]);
    }

    printf("\nList of Grades:\n");
    for (i = 0; i < numStudents; i++) {
        printf("Student %d: %d\n", i + 1, grades[i]);
    }

    free(grades);
    return 0;
}