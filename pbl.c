#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100
#define FILENAME "heart_transplant_data.txt"

// Structure to represent a person (either a patient or a donor)
struct Person {
    char name[50];
    int age;
    char bloodGroup[4];
    // Add more attributes as needed
};

// Structure to represent a record in the database
struct Record {
    struct Person patient;
    struct Person donor;
    // Add more attributes as needed
};

// Database array to store records
struct Record database[MAX_RECORDS];

// Function to save the database to a file
void saveToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < MAX_RECORDS; i++) {
        if (database[i].patient.age != 0) {
            fprintf(file, "%s %d %s %s %d %s\n", 
                    database[i].patient.name, database[i].patient.age, database[i].patient.bloodGroup,
                    database[i].donor.name, database[i].donor.age, database[i].donor.bloodGroup);
        }
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}

// Function to load the database from a file
void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    for (int i = 0; i < MAX_RECORDS; i++) {
        if (fscanf(file, "%s %d %s %s %d %s", 
                   database[i].patient.name, &database[i].patient.age, database[i].patient.bloodGroup,
                   database[i].donor.name, &database[i].donor.age, database[i].donor.bloodGroup) != EOF) {
            // Incremental read, assuming data is stored in a space-separated format
        } else {
            break;  // Reached the end of file
        }
    }

    fclose(file);
    printf("\nData loaded from file successfully.\n");
}

// Function to add a new record to the database
void addRecord() {
    // Check if there is space in the database
    int i = 0;
    while (database[i].patient.age != 0 && i < MAX_RECORDS) {
        i++;
    }
    if (i == MAX_RECORDS) {
        printf("Database is full. Cannot add more records.\n");
        return;
    }

    // ... (user input for patient and donor details)

    // Add the new record to the database
    printf("Enter patient name: ");
    scanf("%s", database[i].patient.name);
    printf("Enter patient age: ");
    scanf("%d", &database[i].patient.age);
    printf("Enter patient blood group: ");
    scanf("%s", database[i].patient.bloodGroup);

    printf("Enter donor name: ");
    scanf("%s", database[i].donor.name);
    printf("Enter donor age: ");
    scanf("%d", &database[i].donor.age);
    printf("Enter donor blood group: ");
    scanf("%s", database[i].donor.bloodGroup);

    printf("Record added successfully.\n");
}

// Function to find a suitable donor for a given patient
void findDonor() {
    char patientBloodGroup[4];
    int patientAge;

    // Input patient details
    printf("Enter patient blood group: ");
    scanf("%s", patientBloodGroup);
    printf("Enter patient age: ");
    scanf("%d", &patientAge);

    // Search for a suitable donor
    printf("Matching donors:\n");
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (strcmp(database[i].donor.bloodGroup, patientBloodGroup) == 0 &&
            database[i].donor.age >= patientAge) {
            printf("Donor Name: %s, Age: %d, Blood Group: %s\n",
                   database[i].donor.name, database[i].donor.age, database[i].donor.bloodGroup);
        }
    }
}

// Main function
int main() {
    // Load data from file at the beginning
    loadFromFile();

    int choice;

    do {
        // Display menu
        printf("\nHeart Transplant Database Management System\n");
        printf("1. Add a new record\n");
        printf("2. Find a suitable donor\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform action based on user's choice
        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                findDonor();
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    // Save data to file before exiting
    saveToFile();

    return 0;
}
