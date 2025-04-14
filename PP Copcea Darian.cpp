#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define RESET   "\033[0m"

#define FILE_NAME "parking_history.txt"


typedef struct {
    char carNumber[20];
    char zone[20];
    char color[10];
    int hours;
    float cost;
} Transaction;


void clearScreen();
void initializeFile();
void addTransaction();
void viewHistory();
void writeTransactionToFile(Transaction t);
void printColoredZone(const char* zone);

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033c");
    #endif
}

int main() {
    initializeFile();
    int choice;
    do {
        clearScreen();
        printf(CYAN "\nOnline Parking Payment System\n" RESET);
        printf("1. Add Parking Transaction\n");
        printf("2. View Parking History\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                viewHistory();
                break;
            case 3:
                clearScreen();
                printf(GREEN "Exiting program.\n" RESET);
                break;
            default:
                printf(RED "Invalid choice, please try again.\n" RESET);
        }
    } while (choice != 3);
    return 0;
}

void initializeFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        file = fopen(FILE_NAME, "w");
        if (file == NULL) {
            printf(RED "Error creating file.\n" RESET);
            exit(1);
        }
        fprintf(file, "Prepopulated Data:\n");
        fprintf(file, "ABC123 - Red Zone - Red - 2 hours - 3.00 RON\n");
        fprintf(file, "XYZ789 - Green Zone - Green - 4 hours - 8.00 RON\n");
        fclose(file);
    } else {
        fclose(file);
    }
}

void addTransaction() {
    clearScreen();
    printf("\n--- Add Parking Transaction ---\n\n");
    Transaction t;

    printf("Car number (e.g., ABC123): ");
    scanf("%s", t.carNumber);
    getchar();


printf("Available Zones:\n");
printf("1. " YELLOW "Yellow Zone" RESET " - 1.00 RON/hour\n");
printf("2. " RED    "Red Zone"    RESET " - 1.50 RON/hour\n");
printf("3. " GREEN  "Green Zone"  RESET " - 2.00 RON/hour\n\n");


while (1) {
    printf("Select parking zone (Yellow, Red, Green): ");
    scanf("%s", t.zone);
    getchar();

    if (strcmp(t.zone, "Yellow") == 0) {
        strcpy(t.color, "Yellow");
        t.cost = 1.0;
        break;
    } else if (strcmp(t.zone, "Red") == 0) {
        strcpy(t.color, "Red");
        t.cost = 1.5;
        break;
    } else if (strcmp(t.zone, "Green") == 0) {
        strcpy(t.color, "Green");
        t.cost = 2.0;
        break;
    } else {
        printf(RED "Invalid zone. Please enter Yellow, Red, or Green.\n" RESET);
    }
}



    while (1) {
        printf("Parking duration in hours (1 or more): ");
        if (scanf("%d", &t.hours) != 1 || t.hours <= 0) {
            printf(RED "Invalid number of hours. Try again.\n" RESET);
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    getchar();

    t.cost *= t.hours;

    writeTransactionToFile(t);

    printf(GREEN "\nTransaction recorded successfully!\n" RESET);
    printf("Press Enter to return to the main menu...");
    getchar();
}

void writeTransactionToFile(Transaction t) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf(RED "Error opening file.\n" RESET);
        return;
    }

    fprintf(file, "%s - %s Zone - %s - %d hours - %.2f RON\n",
            t.carNumber, t.zone, t.color, t.hours, t.cost);
    fclose(file);
}

void viewHistory() {
    clearScreen();
    printf("\n--- Parking History ---\n\n");
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf(RED "No history found.\n" RESET);
    } else {
        char line[256];
        while (fgets(line, sizeof(line), file)) {

            char car[20], zone[20], color[20];
            int hours;
            float cost;

            if (sscanf(line, "%19s - %19s Zone - %19s - %d hours - %f RON",
                       car, zone, color, &hours, &cost) == 5) {

                printf(CYAN "%s" RESET " - ", car);
                printColoredZone(zone);
                printf(" Zone - %s - %d hours - ", color, hours);
                printf(GREEN "%.2f RON\n" RESET, cost);
            } else {
                printf("%s", line);
            }
        }
        fclose(file);
    }

    printf("\nPress Enter to return to the main menu...");
    getchar();
}

void printColoredZone(const char* zone) {
    if (strcmp(zone, "Red") == 0) {
        printf(RED "%s" RESET, zone);
    } else if (strcmp(zone, "Yellow") == 0) {
        printf(YELLOW "%s" RESET, zone);
    } else if (strcmp(zone, "Green") == 0) {
        printf(GREEN "%s" RESET, zone);
    } else {
        printf("%s", zone);
    }
}
