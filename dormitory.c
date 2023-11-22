#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct Student
{
    char name[100];
    char dorm[100];
    char class[100];
    int on_leave; // 0 for on campus, 1 for on leave
};

void printMenu()
{
    time_t now;

    time(&now);

    printf("\n");

    printf("\t\t\t\t\t\t       %s", ctime(&now)); // current time and date will be appear at the top
    printf("\n\t\t\t\t\t******** Student Accommodation System ********\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Modify Student\n");
    printf("4. Query Student\n");
    printf("5. Print All Students\n");
    printf("6. Print Students On Leave\n");
    printf("7. Exit\n\n");

    printf("Enter your choice: ");
}

void addStudent(struct Student students[], int *numStudents)
{

    struct Student s;

    printf("Enter new student name: ");
    scanf("%s", s.name);
    printf("Enter dorm (dorm#-bed#): ");
    scanf("%s", s.dorm);
    printf("Enter class: ");
    scanf("%s", s.class);

    printf("On campus (0) or on leave(1)?: ");
    scanf("%d", &s.on_leave);

    students[(*numStudents)++] = s;

    printf("New student added successfully!\n");
}

void deleteStudent(struct Student students[], int *numStudents)
{

    char name[100];

    printf("Enter name of student to delete: ");
    scanf("%s", name);

    for (int i = 0; i < *numStudents; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            for (int j = i; j < *numStudents - 1; j++)
            {
                students[j] = students[j + 1];
            }
            (*numStudents)--;
            printf("Student record deleted successfully!\n");
            return;
        }
    }

    printf("Student with name %s not found!\n", name);
}

void modifyStudent(struct Student students[], int numStudents)
{

    char name[100];

    printf("Enter name of student to modify: ");
    scanf("%s", name);

    for (int i = 0; i < numStudents; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {

            printf("Enter updated dorm (dorm#-bed#): ");
            scanf("%s", students[i].dorm);
            printf("Enter updated class: ");
            scanf("%s", students[i].class);

            printf("Updated on campus(0) or on leave(1)?: ");
            scanf("%d", &students[i].on_leave);

            printf("Student record modified successfully!\n");
            return;
        }
    }

    printf("Student with name %s not found!\n", name);
}

void queryStudent(struct Student students[], int numStudents)
{

    char name[100];

    printf("Enter name of student to query: ");
    scanf("%s", name);

    for (int i = 0; i < numStudents; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            printf("Name: %s\n", students[i].name);
            printf("Dorm: %s\n", students[i].dorm);
            printf("Class: %s\n", students[i].class);

            if (students[i].on_leave)
            {
                printf("On Leave\n");
            }
            else
            {
                printf("On Campus\n");
            }

            return;
        }
    }

    printf("Student with name %s not found!\n", name);
}

void printStudents(struct Student students[], int numStudents)
{

    printf("All Students\n");

    for (int i = 0; i < numStudents; i++)
    {
        printf("Name: %s\n", students[i].name);
        printf("Dorm: %s\n", students[i].dorm);
        printf("Class: %s\n", students[i].class);

        if (students[i].on_leave)
        {
            printf("On Leave\n\n");
        }
        else
        {
            printf("On Campus\n\n");
        }
    }
}

void printOnLeave(struct Student students[], int numStudents)
{

    printf("Students On Leave\n");

    for (int i = 0; i < numStudents; i++)
    {
        if (students[i].on_leave)
        {
            printf("Name: %s\n", students[i].name);
            printf("Dorm: %s\n", students[i].dorm);
            printf("Class: %s\n", students[i].class);
            printf("On Leave\n\n");
        }
    }
}
void saveToFile(struct Student studs[], int count);

int main()
{
    system("color 0b");
    struct Student students[100];
    int numStudents = 0;
    // Load saved data
    FILE *fp = fopen("students.dat", "r");

    if (fp)
    {
        struct Student s;
        while (fread(&s, sizeof(struct Student), 1, fp))
        {
            students[numStudents++] = s;
        }
        fclose(fp);
    }

    int choice;

    do
    {
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent(students, &numStudents);
            break;
        case 2:
            deleteStudent(students, &numStudents);
            break;
        case 3:
            modifyStudent(students, numStudents);
            break;
        case 4:
            queryStudent(students, numStudents);
            break;
        case 5:
            printStudents(students, numStudents);
            break;
        case 6:
            printOnLeave(students, numStudents);
            break;
        case 7:
            saveToFile(students, numStudents);
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice\n");
        }

    } while (choice != 7);

    return 0;
}
// Rest of functions
void saveToFile(struct Student studs[], int count)
{

    FILE *fp = fopen("students.dat", "w");

    if (!fp)
    {
        printf("File open failed\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fwrite(&studs[i], sizeof(struct Student), 1, fp);
    }

    fclose(fp);
    printf("Data saved to file!\n");
}