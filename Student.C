#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent() {
    FILE *fptr = fopen("students.txt", "a");
    struct Student s;

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name); // To read string with spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fptr);
    fclose(fptr);
    printf("Student record added successfully.\n");
}

void viewStudents() {
    FILE *fptr = fopen("students.txt", "r");
    struct Student s;

    printf("\nAll Student Records:\n");
    printf("Roll\tName\t\tMarks\n");
    printf("-----------------------------------\n");

    while (fread(&s, sizeof(s), 1, fptr)) {
        printf("%d\t%-15s%.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fptr);
}

void searchStudent() {
    FILE *fptr = fopen("students.txt", "r");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fptr)) {
        if (s.roll == roll) {
            printf("Record Found:\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll);
    }

    fclose(fptr);
}

void deleteStudent() {
    FILE *fptr = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fptr)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Student record deleted successfully.\n");
    else
        printf("Student with Roll Number %d not found.\n", roll);
}

int main() {
    int choice;

    do {
        printf("\n==== Student Management System ====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
