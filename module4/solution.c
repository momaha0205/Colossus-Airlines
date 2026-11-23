
#include <stdio.h>
#include <string.h>

#define TOTAL_SEATS 128
#define TOTAL_FLIGHTS 4

// Structure to store information about each seat
struct Seat {
    int seatNumber;
    int isAssigned;
    char firstName[50];
    char lastName[50];
};

// Array of flight numbers
int flightNumbers[TOTAL_FLIGHTS] = {101, 102, 201, 202};

// Store 128 seats for each of the 4 flights
struct Seat seats[TOTAL_FLIGHTS][TOTAL_SEATS];

// Clear invalid input from the keyboard
void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// Read a menu choice
char readChoice() {
    char choice;

    if (scanf(" %c", &choice) != 1) {
        return '\0';
    }

    clearInput();
    return choice;
}

void initializeSeats();


// Save all flight reservations to a binary file
void saveReservations() {
    FILE *file = fopen("reservations.dat", "wb");

    if (file == NULL) {
        printf("Error: Could not save reservations.\n");
        return;
    }

    if (fwrite(seats, sizeof(seats), 1, file) != 1) {
        printf("Error: Could not write reservation data.\n");
    }

    fclose(file);
}

// Load existing reservations from a binary file
void loadReservations() {
    FILE *file = fopen("reservations.dat", "rb");

    if (file == NULL) {
        printf("No saved reservations found. Starting fresh.\n");
        return;
    }

    if (fread(seats, sizeof(seats), 1, file) == 1) {
        printf("Saved reservations loaded successfully.\n");
    } else {
        printf("Error reading reservation data. Starting fresh.\n");
        initializeSeats();
    }

    fclose(file);
}

// Initialize all seats as empty
void initializeSeats() {
    for (int i = 0; i < TOTAL_FLIGHTS; i++) {
        for (int j = 0; j < TOTAL_SEATS; j++) {
            seats[i][j].seatNumber = j + 1;
            seats[i][j].isAssigned = 0;
            strcpy(seats[i][j].firstName, "");
            strcpy(seats[i][j].lastName, "");
        }
    }
}

// Count and display the number of empty seats
void showEmptySeatCount(int flightIndex) {
    int emptyCount = 0;

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[flightIndex][i].isAssigned == 0) {
            emptyCount++;
        }
    }

    printf("\nNumber of empty seats: %d\n", emptyCount);
}

// Display all available seat numbers
void showEmptySeats(int flightIndex) {
    printf("\nAvailable seats for Flight %d:\n",
           flightNumbers[flightIndex]);

    int count = 0;

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[flightIndex][i].isAssigned == 0) {
            printf("%4d", seats[flightIndex][i].seatNumber);
            count++;

            if (count % 10 == 0) {
                printf("\n");
            }
        }
    }

    if (count == 0) {
        printf("No empty seats available.");
    }

    printf("\n");
}

// Assign a customer to an available seat
void assignSeat(int flightIndex) {
    int seatNumber;
    char firstName[50];
    char lastName[50];

    printf("\n=== Assign a Seat ===\n");
    printf("Enter seat number (1-128), or 0 to cancel: ");

    if (scanf("%d", &seatNumber) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    clearInput();

    if (seatNumber == 0) {
        printf("Seat assignment canceled.\n");
        return;
    }

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
        printf("Invalid seat number. Please choose 1-128.\n");
        return;
    }

    int seatIndex = seatNumber - 1;

    if (seats[flightIndex][seatIndex].isAssigned == 1) {
        printf("This seat is already assigned.\n");
        return;
    }

    printf("Enter first name (or 0 to cancel): ");

    if (scanf("%49s", firstName) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    clearInput();

    if (strcmp(firstName, "0") == 0) {
        printf("Seat assignment canceled.\n");
        return;
    }

    printf("Enter last name (or 0 to cancel): ");

    if (scanf("%49s", lastName) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    clearInput();

    if (strcmp(lastName, "0") == 0) {
        printf("Seat assignment canceled.\n");
        return;
    }

    strcpy(seats[flightIndex][seatIndex].firstName, firstName);
    strcpy(seats[flightIndex][seatIndex].lastName, lastName);
    seats[flightIndex][seatIndex].isAssigned = 1;
    saveReservations();

    printf("\nSeat %d successfully assigned to %s %s.\n",
           seatNumber, firstName, lastName);
}

// Delete an existing seat assignment
void deleteSeat(int flightIndex) {
    int seatNumber;

    printf("\n=== Delete a Seat Assignment ===\n");
    printf("Enter seat number (1-128), or 0 to cancel: ");

    if (scanf("%d", &seatNumber) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    clearInput();

    if (seatNumber == 0) {
        printf("Seat deletion canceled.\n");
        return;
    }

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
        printf("Invalid seat number. Please choose 1-128.\n");
        return;
    }

    int seatIndex = seatNumber - 1;

    if (seats[flightIndex][seatIndex].isAssigned == 0) {
        printf("This seat is already empty.\n");
        return;
    }

    printf("Deleting reservation for %s %s.\n",
           seats[flightIndex][seatIndex].firstName,
           seats[flightIndex][seatIndex].lastName);

    seats[flightIndex][seatIndex].isAssigned = 0;
    saveReservations();
    strcpy(seats[flightIndex][seatIndex].firstName, "");
    strcpy(seats[flightIndex][seatIndex].lastName, "");

    printf("Seat %d is now available.\n", seatNumber);
}

// Display assigned passengers in alphabetical order
void showAlphabeticalList(int flightIndex) {
    struct Seat assignedSeats[TOTAL_SEATS];
    int count = 0;

    // Copy assigned seats into a temporary array
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[flightIndex][i].isAssigned == 1) {
            assignedSeats[count] = seats[flightIndex][i];
            count++;
        }
    }

    if (count == 0) {
        printf("\nNo seats are currently assigned.\n");
        return;
    }

    // Sort by last name, then first name
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int comparison = strcmp(
                assignedSeats[i].lastName,
                assignedSeats[j].lastName
            );

            if (comparison > 0 ||
                (comparison == 0 &&
                 strcmp(assignedSeats[i].firstName,
                        assignedSeats[j].firstName) > 0)) {

                struct Seat temp = assignedSeats[i];
                assignedSeats[i] = assignedSeats[j];
                assignedSeats[j] = temp;
            }
        }
    }

    printf("\n=== Alphabetical Passenger List ===\n");
    printf("%-8s %-20s %-20s\n",
           "Seat", "Last Name", "First Name");

    for (int i = 0; i < count; i++) {
        printf("%-8d %-20s %-20s\n",
               assignedSeats[i].seatNumber,
               assignedSeats[i].lastName,
               assignedSeats[i].firstName);
    }
}

// Display the third-level reservation menu
void displayReservationMenu(int flightIndex) {
    char choice;

    do {
        printf("\n=== Flight %d Reservation Menu ===\n",
               flightNumbers[flightIndex]);

        printf("a. Show number of empty seats\n");
        printf("b. Show list of empty seats\n");
        printf("c. Show alphabetical list of seats\n");
        printf("d. Assign a customer to a seat\n");
        printf("e. Delete a seat assignment\n");
        printf("f. Return to Main Menu\n");
        printf("Enter your choice: ");

        choice = readChoice();

        switch (choice) {
            case 'a':
                showEmptySeatCount(flightIndex);
                break;

            case 'b':
                showEmptySeats(flightIndex);
                break;

            case 'c':
                showAlphabeticalList(flightIndex);
                break;

            case 'd':
                assignSeat(flightIndex);
                break;

            case 'e':
                deleteSeat(flightIndex);
                break;

            case 'f':
                printf("\nReturning to Main Menu.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 'f' && choice != '\0');
}

// Display the second-level menu for flight selection
void displayFlightMenu(int direction) {
    char choice;
    int flightNumber;
    int startIndex;

    if (direction == 0) {
        startIndex = 0;
    } else {
        startIndex = 2;
    }

    do {
        if (direction == 0) {
            printf("\n=== Outbound Flights ===\n");
        } else {
            printf("\n=== Inbound Flights ===\n");
        }

        printf("Available flight numbers: %d, %d\n",
               flightNumbers[startIndex],
               flightNumbers[startIndex + 1]);

        printf("a. Flight Number\n");
        printf("b. Back to Main\n");
        printf("Enter your choice: ");

        choice = readChoice();

        switch (choice) {
            case 'a':
                printf("Enter flight number: ");

                if (scanf("%d", &flightNumber) != 1) {
                    clearInput();
                    printf("\nInvalid flight number.\n");
                    break;
                }
                clearInput();

                if (flightNumber == flightNumbers[startIndex]) {
                    displayReservationMenu(startIndex);
                    return;
                } else if (flightNumber == flightNumbers[startIndex + 1]) {
                    displayReservationMenu(startIndex + 1);
                    return;
                } else {
                    printf("\nInvalid flight number. Please try again.\n");
                }
                break;

            case 'b':
                printf("\nReturning to main menu.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 'b' && choice != '\0');
}

// Display the main menu
void displayMainMenu() {
    printf("\n=== Colossus Airlines Reservation System ===\n");
    printf("a. Outbound Flight\n");
    printf("b. Inbound Flight\n");
    printf("c. Quit\n");
    printf("Enter your choice: ");
}

int main() {
    char choice;

    initializeSeats();
    loadReservations();

    do {
        displayMainMenu();
        choice = readChoice();

        switch (choice) {
            case 'a':
                displayFlightMenu(0);
                break;

            case 'b':
                displayFlightMenu(1);
                break;

            case 'c':
                printf("\nExiting reservation system.\n");
                break;

            case '\0':
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 'c' && choice != '\0');

    return 0;
}
