#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 31
#define MAX_DEPT_LENGTH 101
#define MAX_RECORDS 100

struct Record
{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    int phone;
    char department[MAX_DEPT_LENGTH];
};

struct Record phonebook[MAX_RECORDS];
int recordCount = 0;

void loadRecords()
{
    FILE *file = fopen("phonebook.txt", "r");
    if (file == NULL)
    {
        printf("No existing file found, starting fresh.\n");
        return;
    }

    recordCount = 0;
    while (fscanf(file, "%s %s %d %s",
                  phonebook[recordCount].name,
                  phonebook[recordCount].surname,
                  &phonebook[recordCount].phone,
                  phonebook[recordCount].department) == 4)
    {
        recordCount++;
        if (recordCount >= MAX_RECORDS)
            break;
    }

    fclose(file);
}

void saveRecords()
{
    FILE *file = fopen("phonebook.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < recordCount; i++)
    {
        fprintf(file, "%s %s %d %s\n",
                phonebook[i].name,
                phonebook[i].surname,
                phonebook[i].phone,
                phonebook[i].department);
    }

    fclose(file);
}

int addRecord()
{
    if (recordCount >= MAX_RECORDS)
    {
        printf("No more places to save.\n");
        return 0;
    }

    struct Record newRecord;

    printf("Name: ");
    scanf("%s", newRecord.name);
    printf("Surname: ");
    scanf("%s", newRecord.surname);
    printf("PhoneNumber: ");
    scanf("%d", &newRecord.phone);
    printf("Department: ");
    scanf("%s", newRecord.department);

    for (int i = 0; i < recordCount; i++)
    {
        if (strcmp(phonebook[i].name, newRecord.name) == 0 &&
            strcmp(phonebook[i].surname, newRecord.surname) == 0 &&
            phonebook[i].phone == newRecord.phone &&
            strcmp(phonebook[i].department, newRecord.department) == 0)
        {
            printf("Record already exists.\n");
            return 0;
        }
    }

    phonebook[recordCount] = newRecord;
    recordCount++;

    printf("Record successfully added.\n");

    return 1;
}

int searchRecord()
{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    int phone;
    char department[MAX_DEPT_LENGTH];
    int matchCount = 0;

    printf("Search criteria:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Surname: ");
    scanf("%s", surname);
    printf("PhoneNumber: ");
    scanf("%d", &phone);
    printf("Department: ");
    scanf("%s", department);

    for (int i = 0; i < recordCount; i++)
    {
        if ((strlen(name) == 0 || strcmp(phonebook[i].name, name) == 0) &&
            (strlen(surname) == 0 || strcmp(phonebook[i].surname, surname) == 0) &&
            (phone == 0 || phonebook[i].phone == phone) &&
            (strlen(department) == 0 || strcmp(phonebook[i].department, department) == 0))
        {
            printf("Name: %s\n", phonebook[i].name);
            printf("Surname: %s\n", phonebook[i].surname);
            printf("PhoneNumber: %d\n", phonebook[i].phone);
            printf("Department: %s\n", phonebook[i].department);
            printf("------------------------\n");
            matchCount++;
        }
    }

    if (matchCount == 0)
    {
        printf("No results found.\n");
    }
    else
    {
        printf("%d results found.\n", matchCount);
    }

    return 1;
}

int updateRecord()
{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    int phone;
    char department[MAX_DEPT_LENGTH];

    printf("Search criteria for the record you want to change:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Surname: ");
    scanf("%s", surname);
    printf("PhoneNumber: ");
    scanf("%d", &phone);
    printf("Department: ");
    scanf("%s", department);

    for (int i = 0; i < recordCount; i++)
    {
        if (strcmp(phonebook[i].name, name) == 0 &&
            strcmp(phonebook[i].surname, surname) == 0 &&
            phonebook[i].phone == phone &&
            strcmp(phonebook[i].department, department) == 0)
        {
            printf("Enter new data:\n");
            printf("Name: ");
            scanf("%s", phonebook[i].name);
            printf("Surname: ");
            scanf("%s", phonebook[i].surname);
            printf("PhoneNumber: ");
            scanf("%d", &phonebook[i].phone);
            printf("Department: ");
            scanf("%s", phonebook[i].department);

            printf("Record successfully updated.\n");

            return 1;
        }
    }

    printf("No records found.\n");

    return 0;
}

int deleteRecord()
{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    int phone;
    char department[MAX_DEPT_LENGTH];

    printf("Search criteria for the record you want to delete:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Surname: ");
    scanf("%s", surname);
    printf("PhoneNumber: ");
    scanf("%d", &phone);
    printf("Department: ");
    scanf("%s", department);

    for (int i = 0; i < recordCount; i++)
    {
        if (strcmp(phonebook[i].name, name) == 0 &&
            strcmp(phonebook[i].surname, surname) == 0 &&
            phonebook[i].phone == phone &&
            strcmp(phonebook[i].department, department) == 0)
        {
            for (int j = i; j < recordCount - 1; j++)
            {
                phonebook[j] = phonebook[j + 1];
            }

            recordCount--;

            printf("Record successfully deleted.\n");

            return 1;
        }
    }

    printf("No records found.\n");

    return 0;
}

void listRecords()
{
    if (recordCount == 0)
    {
        printf("No record.\n");
        return;
    }

    printf("All Records:\n");
    for (int i = 0; i < recordCount; i++)
    {
        printf("Name: %s\n", phonebook[i].name);
        printf("Surname: %s\n", phonebook[i].surname);
        printf("PhoneNumber: %d\n", phonebook[i].phone);
        printf("Department: %s\n", phonebook[i].department);
        printf("---------------------------------\n");
    }
}

int main()
{
    int choice;

    loadRecords();

    do
    {
        printf("\n1. Add a record\n");
        printf("2. Search by\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. List\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (addRecord()) saveRecords();
                break;
            case 2:
                searchRecord();
                break;
            case 3:
                if (updateRecord()) saveRecords();
                break;
            case 4:
                if (deleteRecord()) saveRecords();
                break;
            case 5:
                listRecords();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
    while (choice != 6);

    return 0;
}
