#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#define MAX_BUSES 60
#define MAX_BOOKINGS 100
#define MAX_NAME_LENGTH 50
#define MAX_EMPLOYEES 10
#define NUM_ROUTES 25
#define NUM_ROWS 8
#define NUM_COLUMNS 4

//Struct to represent a bus schedule

typedef struct
{
    char departure[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    int totalSeats;
    int availableSeats;
} BusSchedule;

//Struct to represent an employee

typedef struct
{
    char usernameEmployee[MAX_NAME_LENGTH];
    char passwordEmployee[MAX_NAME_LENGTH];
} Employee;

//All global variables used within the program

int numBuses = 0;
int numBookings = 0;
int numEmployees = 0;
int numRoutes = 25;
char seatChoice[2];
int row, column;
int bookingID = 0;
int totalAmount = 0;
int userAmount = 0;
int choice1;
int choice2;
char departure[MAX_NAME_LENGTH];
char destination[MAX_NAME_LENGTH];
int programRun = 0;
char busVenturaType[MAX_NAME_LENGTH];

//Array to represent all buses routes and their specific cost

char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH] = {
    {"Nairobi", "Kisumu", "1200"},
    {"Nairobi", "Nakuru", "800"},
    {"Nairobi", "Mombasa", "1500"},
    {"Nairobi", "Eldoret", "1000"},
    {"Nairobi", "Meru", "800"},
    {"Kisumu", "Nairobi", "1200"},
    {"Kisumu", "Nakuru", "500"},
    {"Kisumu", "Mombasa", "2500"},
    {"Kisumu", "Eldoret", "300"},
    {"Kisumu", "Meru", "1800"},
    {"Nakuru", "Nairobi", "800"},
    {"Nakuru", "Kisumu", "500"},
    {"Nakuru", "Mombasa", "2000"},
    {"Nakuru", "Eldoret", "300"},
    {"Nakuru", "Meru", "1000"},
    {"Mombasa", "Meru", "2000"},
    {"Mombasa", "Nairobi", "1500"},
    {"Mombasa", "Kisumu", "2500"},
    {"Mombasa", "Eldoret", "2200"},
    {"Mombasa", "Nakuru", "2000"},
    {"Meru", "Nairobi", "800"},
    {"Meru", "Mombasa", "2000"},
    {"Meru", "Nakuru", "1000"},
    {"Meru", "Eldoret", "1500"},
    {"Meru", "Kisumu", "1800"}
};

//Array representing available seats inside a bus

char seatAvailability[NUM_ROWS][2][NUM_COLUMNS] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
};

// Function to add a new bus schedule

void addBusSchedule(char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH]){
    system("cls");

    char destination[MAX_NAME_LENGTH];
    char departure[MAX_NAME_LENGTH];

    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Enter the place of departure: ");
    scanf("%s", departure);
    printf("| Enter the destination: ");
    scanf("%s", destination);
    printf("|----------------------------------------------------------------------------------|\n");

    strcpy(busDetails[NUM_ROUTES][0], departure);
    strcpy(busDetails[NUM_ROUTES][1], destination);

    printf("| New bus schedule added: %s to %s                                                  |\n", departure, destination);

}

// Function to view all bus schedules

int viewAllBusSchedules(char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH]){
    system("cls");
    int i;
    int choice;
    int busnumber;
    
    printf("|----------------------------------------------------------------------------------|\n");
    printf("|                       ALL VENTURA BUSES AVAILABLE                                |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    //for loop that iterates through the busDetails array printing each as a route

    for(i = 0; i < NUM_ROUTES; i++){
        printf("|          Route %d: %s to %s\n", i + 1, busDetails[i][0], busDetails[i][1]);
    }
    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Do you want to book a bus?                                                       |\n");
    printf("| 1. YES                                                                           |\n");
    printf("| 2. NO                                                                            |\n");
    scanf("%d", &choice);
    printf("|----------------------------------------------------------------------------------|\n");

    if (choice == 1)
    {
        printf("| Enter the number of the bus you want to book:                                    |\n");
        scanf("%d", &busnumber);
        printf("|----------------------------------------------------------------------------------|\n");
        system("cls");
        if (busnumber >= 1 && busnumber <= NUM_ROUTES)
        {
            strcpy(departure, busDetails[busnumber - 1][0]);
            strcpy(destination, busDetails[busnumber - 1][1]);

            //Display details of the selected bus

            printf("| Bus Schedule Selected: %s to %s                                          |\n", departure, destination);
            viewAvailableSeats(seatAvailability);
        }
        else
        {
            printf("| Invalid bus number. Please enter a valid bus number.                      |\n");
        }
    }
    return 0;

}

// Function to delete a bus schedule

void deleteBusSchedule(char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH]){
    system("cls");

    int routeIndex;

    printf("-----------------------------Existing Bus Schedules------------------------------:\n");

    //for loop that prints out all bus schedules available

    for (int i = 0; i < numRoutes; ++i){
        printf("%d: %s to %s\n", i + 1, busDetails[i][0], busDetails[i][1]);
    }
    printf("-----------------------------------------------------------------------------------\n");
    printf("Enter the number of the bus schedule to delete: \n");
    scanf("%d", &routeIndex);
    printf("------------------------------------------------------------------------------------\n");

    if (routeIndex >= 1 && routeIndex <= numRoutes)
    {
        // Delete the bus schedule by shifting elements to overwrite the one being deleted

        for (int i = routeIndex - 1; i < numRoutes - 1; ++i)
        {
            strcpy(busDetails[i][0], busDetails[i + 1][0]);
            strcpy(busDetails[i][1], busDetails[i + 1][1]);
        }
        (numRoutes)--; // Decrement the number of routes

        printf("---------------------------------------------------------------------------------\n");
        printf("Bus schedule deleted successfully!\n");
        printf("----------------------------------------------------------------------------------\n");
    }
    else
    {
        printf("----------------------------------------------------------------------------------\n");
        printf("Invalid bus schedule number. No deletions made in the system.\n");
        printf("----------------------------------------------------------------------------------\n");
    }

}

// Function to modify a bus schedule

void modifyBusSchedule(char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH], int numRoutes){
    system("cls");
    int routeIndex;

    printf("----------------------------------------------------------------------------------\n");
    printf("Existing Bus Schedules:\n");
    printf("----------------------------------------------------------------------------------\n");

    //This will print out all bus schedules in place in the current system

    for (int i = 0; i < numRoutes; ++i){
        printf("%d: %s to %s\n", i + 1, busDetails[i][0], busDetails[i][1]);
    }

    printf("----------------------------------------------------------------------------------\n");
    printf("Enter the number of the bus schedule to modify: \n");
    scanf("%d", &routeIndex);
    printf("----------------------------------------------------------------------------------\n");

    if (routeIndex >= 1 && routeIndex <= numRoutes){

        // Modify the bus schedule

        routeIndex--;  // Adjust index to match array index
        printf("Enter the new place of departure: ");
        scanf("%s", busDetails[routeIndex][0]);
        printf("----------------------------------------------------------------------------------\n");
        printf("Enter the new destination: ");
        scanf("%s", busDetails[routeIndex][1]);
        printf("----------------------------------------------------------------------------------\n");
        printf("Bus schedule modified successfully!\n");
        printf("----------------------------------------------------------------------------------\n");
    }
    else{
        printf("----------------------------------------------------------------------------------\n");
        printf("Invalid bus schedule number. No modifications made.\n");
        printf("----------------------------------------------------------------------------------\n");
    }

}

// Function to search for buses based on source and destination

void searchBus(char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH], char seatAvailability[NUM_ROWS][2][NUM_COLUMNS]){
    system("cls");

    int choice;
    bool busFound = false;

    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Enter the place of departure: ");
    scanf("%s", departure);
    printf("| Enter the destination: ");
    scanf("%s", destination);
    system("cls");

    // Iterate through the array to find the bus

    for (int i = 0; i < numRoutes; ++i)
    {
        if (strcmp(busDetails[i][0], departure) == 0 && strcmp(busDetails[i][1], destination) == 0)
        {
            busFound = true;
            break;
        }
    }

    // Display the result to the user

    if (busFound){
        printf("|----------------------------------------------------------------------------------|\n");
        printf("| Bus from %s to %s is available.                                         |\n", departure, destination);
        printf("| Do you want to book this bus?                                                    |\n");
        printf("| 1.YES                                                                            |\n");
        printf("| 2.NO                                                                             |\n");
        scanf("%d", &choice);
        printf("|----------------------------------------------------------------------------------|\n");
        if (choice == 1){
            viewAvailableSeats(seatAvailability);
            return;
        }
        else if (choice == 2){
            return;
        }
        else{
            printf("Invalid option");
        }

    }
    else{
        printf("|----------------------------------------------------------------------------------|\n");
        printf("| Bus from %s to %s is not available.                                              |\n", departure, destination);
        printf("|----------------------------------------------------------------------------------|\n");
    }
}

// Function to view available seats for a bus

int viewAvailableSeats(char seatAvailability[NUM_ROWS][2][NUM_COLUMNS]){

    printf("|---------------------------------------------------------------------------------|\n");
    printf("|          Ventura Bus from %s to %s  Available Seats                     |\n", departure, destination);
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|                             Column                                              |\n");
    printf("|                                                                                 |\n");
    printf("|                         0. 1. 2. 3                                              |\n");
    printf("|                                                                                 |\n");
    printf("|                     0. |%d |%d |%d |%d                                              |\n", *seatAvailability[0][0], *seatAvailability[0][1], *seatAvailability[0][2], *seatAvailability[0][3]);
    printf("|                     1. |%d |%d |%d |%d                                              |\n", *seatAvailability[1][0], *seatAvailability[1][1], *seatAvailability[1][2], *seatAvailability[1][3]);
    printf("|           R         2. |%d |%d |%d |%d                                              |\n", *seatAvailability[2][0], *seatAvailability[2][1], *seatAvailability[2][2], *seatAvailability[2][3]);
    printf("|           O         3. |%d |%d |%d |%d                                              |\n", *seatAvailability[3][0], *seatAvailability[3][1], *seatAvailability[3][2], *seatAvailability[3][3]);
    printf("|           W         4. |%d |%d |%d |%d                                              |\n", *seatAvailability[4][0], *seatAvailability[4][1], *seatAvailability[4][2], *seatAvailability[4][3]);
    printf("|                     5. |%d |%d |%d |%d                                              |\n", *seatAvailability[5][0], *seatAvailability[5][1], *seatAvailability[5][2], *seatAvailability[5][3]);
    printf("|                     6. |%d |%d |%d |%d                                              |\n", *seatAvailability[6][0], *seatAvailability[6][1], *seatAvailability[6][2], *seatAvailability[6][3]);
    printf("|                     7. |%d |%d |%d |%d                                              |\n", *seatAvailability[7][0], *seatAvailability[7][1], *seatAvailability[7][2]);
    printf("|                                                                                 |\n");
    printf("|---------------------------------------------------------------------------------|\n");

    checkSeatAvailability(seatAvailability, busDetails); 
    printBusLayout(seatAvailability);

    return 0;
}

int isSeatAvailable(row, column){
    return seatAvailability[row][0][column] == 0 && seatAvailability[row][1][column] == 0;
}

// Function to book a seat

void bookSeat(row, column){
    seatAvailability[row][0][column] = 1;
    seatAvailability[row][1][column] = 1;
    bookingID++;
    printf("|---------------------------------------------------------------------------------|\n");
    printf("| Booking successful! Your Booking ID is: %d                                       |\n", bookingID);
    printBusLayout(seatAvailability);
    saveReceiptToFile(row, column);
}

void printBusLayout(char seatAvailability[NUM_ROWS][2][NUM_COLUMNS]){
    for (int i = 0; i < NUM_ROWS; i++)
        {
        for (int j = 0; j < NUM_COLUMNS; j++){
            printf("| %d ", seatAvailability[i][0][j] || seatAvailability[i][1][j]);
        }
        printf("                                                                  |\n");
    }
    printf("|---------------------------------------------------------------------------------|\n");
}

int checkSeatAvailability(char seatAvailability[NUM_ROWS][2][NUM_COLUMNS], char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH]){
    int choice;

    userAmount = 0;
    totalAmount = 0;

    printf("| Enter row number (0 to 7): ");
    scanf("%d", &row);
    printf("| Enter column number (0 to 3): ");
    scanf("%d", &column);
    printf("|---------------------------------------------------------------------------------|\n");

    if (row >= 0 && row < NUM_ROWS && column >= 0 && column < NUM_COLUMNS)
    {
        if (isSeatAvailable(row, column))
        {
            totalAmount = calculateTotalAmount(busDetails);
            printf("| Seat at row %d, column %d is available!                                           |\n", row, column);
            printf("| Amount to pay is %d, Do you wish to proceed to pay?                        |\n", totalAmount);
            printf("| 1.YES                                                                           |\n");
            printf("| 2.NO                                                                            |\n");
            scanf("%d", &choice);

            if (choice == 1){
                printf("|---------------------------------------------------------------------------------|\n");
                printf("| Enter the amount to pay: sh");
                scanf("%d", &userAmount);

                if(userAmount == totalAmount){
                    system("cls");
                    bookSeat(row, column);
                    printf("| Seat at row %d, column %d has been booked.                                        |\n", row, column);
                    printf("|---------------------------------------------------------------------------------|\n");
                    printRecipt(userAmount, row);
                    saveReceiptToFile(userAmount, row);
                }
                else
                {
                    printf("Incorrect amount. Booking failed.\n");
                }
            }
            else if (choice == 2){
                return 1;
            }
            else{
                printf("Invalid choice");
            }
        }
        else{
            printf("Invalid seat number.\n");
        }
    }
    return 0;
}



int calculateTotalAmount(char busDetails[NUM_ROUTES][3][MAX_NAME_LENGTH]){
    int seatCost = atoi(busDetails[row][2]);
    return seatCost;
}

int checkBookingStatus(int row, int column){
    if (isSeatAvailable(row, column))
    {
        return 0; // Booking failed
    }
    else
    {
        return 1; // Booking successful
    }
    return 0;
}

// Function to issue a receipt
void printRecipt(int checkSeatAvailability, char seatAvailability[NUM_ROWS][2][NUM_COLUMNS]){
    if (strcmp(departure, "Nairobi") == 0) {
        strcpy(busVenturaType, "VenturaA");
    } else if (strcmp(destination, "Kisumu") == 0) {
        strcpy(busVenturaType, "VenturaB");
    } else if (strcmp(destination, "Mombasa") == 0) {
        strcpy(busVenturaType, "VenturaC");
    } else if (strcmp(destination, "Nakuru") == 0) {
        strcpy(busVenturaType, "VenturaD");
    } else if (strcmp(destination, "Meru") == 0) {
        strcpy(busVenturaType, "VenturaE");
    } else {
        // Default label if no match
        return "VenturaX";
    }
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|                          Booking Successful!                                    |\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|                              Receipt:                                           |\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("| Booking ID:  |%d%d|\n", bookingID, programRun);
    printf("| Bus ID:      %s\n", busVenturaType);
    printf("| Seat Number: Row |%d|, Column |%d\n", row, column);
    printf("| Amount Paid: %d ksh\n", userAmount);
    printf("| %s to %s\n", departure, destination);
    printf("|----------------------------------------------------------------------------------|\n");
    programRun++;
    mainMenu();
}
//function to save booking history in a file

void saveReceiptToFile(char seatAvailability[NUM_ROWS][2][NUM_COLUMNS], int checkSeatAvailability){

    FILE *file = fopen("receipt.txt", "a");

    if (file != NULL){
        fprintf(file, "\nBooking ID: %d%d", bookingID, programRun);
        fprintf(file, "%s ", busVenturaType);
        fprintf(file, "Seat Number: Row %d, Column %d", row, column);
        fprintf(file, "Amount Paid: %d ksh", userAmount);
        fprintf(file, "%s to %s \n", departure, destination);
        fclose(file);
    }
    else{
        printf("Error: Unable to open the file for writing.\n");
    }
    fclose(file);
}


// Function to cancel a booking

void cancelBooking(FILE *receiptFile){
    system("cls");
    char ch;
    int i = 0;
    char password[20]; // Password for authentication
    char inputPassword[20]; // User input for password

    // Set the correct password
    strcpy(password, "ventura"); // Replace "your_password" with the actual password

    printf("Enter password to cancel the booking: ");
    while((ch = getch())!= 13){
        inputPassword[i] = ch;
        i++;
        printf("*");
    }
    inputPassword[i] = '\0';
    i = 0;

    // Compare the input password with the correct password
    if (strcmp(inputPassword, password) == 0){
        // Authentication successful, allow cancellation
        printf("Authentication successful!\n");
        FILE *tempFile = fopen("temp.txt", "w");

        if (tempFile == NULL){
            printf("Error: Unable to open files for processing.\n");
            return;
        }

        char line[100];
        int bookingFound = 0;

        //rewind the file to the beginning
        rewind(receiptFile);

        printf("Enter the booking ID to cancel the booking: ");
        scanf("%d", &bookingID);

        while (fgets(line, sizeof(line), receiptFile)){
            int currentBookingID;
            if (sscanf(line, "Booking ID: %d", &currentBookingID) == 1 && currentBookingID == bookingID){
                bookingFound = 1;
                continue;
            }
            fprintf(tempFile, "%s", line);
        }

        fclose(receiptFile);
        fclose(tempFile);

        //remove the original file and rename the temporary file
        remove("receipt.txt");
        rename("temp.txt", "receipt.txt");

        if (bookingFound){
            printf("Booking information removed.\n");
        }
        else{
            printf("Booking information not found.\n");
        }
    }
    else
    {
        // Authentication failed
        printf("Incorrect password. Booking cancellation failed.\n");
    }

}

// Function to view booking history
void viewBookingHistory() {
    system("cls");
    int choice;
    FILE *file;

    printf("|----------------------------------------------------------------------------------|\n");
    printf("|                             Choose an option:                                    |\n");
    printf("| 1. View all the bookings ever made                                               |\n");
    printf("| 2. View all current bookings                                                     |\n");
    scanf("%d", &choice);
    printf("|----------------------------------------------------------------------------------|\n");

    if (choice == 1) {
        file = fopen("receipt.txt", "r");
    } else if (choice == 2) {
        file = fopen("temp.txt", "r");
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (file == NULL) {
        printf("Error: Unable to open the selected file.\n");
        return;
    }

    char line[200];

    printf("|                           Booking History:                                       |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    // Display booking history from the selected file

    while (fgets(line, sizeof(line), file)) {
        printf("| %s", line);
    }

    fclose(file);
}


// Function to register a new employee

void signUp(FILE *credential){
    char username[50];
    char password[50];
    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Enter a username: ");
    scanf("%s", username);
    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Enter a password: ");
    scanf("%s", password);
    printf("|----------------------------------------------------------------------------------|\n");

    fprintf(credential, "%s %s\n", username, password);
    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Registration successful!\n");
    printf("|----------------------------------------------------------------------------------|\n");
    system("cls");
}

// Function to validate employee login

int login(FILE *credential){
    char username[50];
    char password[50];
    char ch;
    int i = 0;
    char fileUsername[50];
    char filePassword[50];

    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Enter your username: ");
    scanf("   %s", username);
    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Enter your password: ");
    while((ch = getch())!= 13){
        password[i] = ch;
        i++;
        printf("*");
    }
    password[i] = '\0';
    i = 0;
    
    rewind(credential); // Reset file pointer to the beginning

    while (fscanf(credential, "%s %s", fileUsername, filePassword) != EOF){
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0){
            printf("|----------------------------------------------------------------------------------|\n");
            printf("| Login successful!                                                                |\n");
            printf("|----------------------------------------------------------------------------------|\n");
            return 1;
        }
    }
    printf("|----------------------------------------------------------------------------------|\n");
    printf("| Login unsuccessful. Please check your credentials.\n                             |");
    printf("|----------------------------------------------------------------------------------|\n");
    return 0;
}

void programRunCounterPrint(){
    FILE *programRunfile;
    programRunfile = fopen("programRunfile", "a+");
    fprintf(programRunfile, "%d", programRun);
    fclose(programRunfile);
}

void programRunCounterRead(FILE *programRunfile){
    fscanf(programRunfile, "%d", programRun);
}

void mainMenu(){
    FILE *credential;
    credential = fopen("credentials.txt", "a+"); // Open or create the credentials file
    FILE *receipt;
    receipt = fopen("receipt.txt", "a+");
    FILE *programRunfile;
    programRunfile = fopen("programRunfile.txt", "a+");
    FILE *temp;
    temp = fopen("temp.txt", "a+");
    programRunCounterPrint();
    programRunCounterRead(programRunfile);


    if (credential == NULL){
        printf("|----------------------------------------------------------------------------------|\n");
        printf("|Error: Could not open the credentials file.                                       |\n");
        printf("|----------------------------------------------------------------------------------|\n");
        return 1;
    }

    while (1){
        printf("|----------------------------------------------------------------------------------|\n");
        printf("|                        CHOOSE AN OPTION:                                         |\n");
        printf("|----------------------------------------------------------------------------------|\n");
        printf("|                      1. Add bus schedule                                         |\n");
        printf("|                      2. View bus schedule                                        |\n");
        printf("|                      3. Delete bus schedule                                      |\n");
        printf("|                      4. Modify bus schedule                                      |\n");
        printf("|                      5. Search bus                                               |\n");
        printf("|                      6. Cancel a booking                                         |\n");
        printf("|                      7. View booking history                                     |\n");
        printf("|                      8. Back to Signup/login                                     |\n");
        printf("|                      9. Exit                                                     |\n");
        printf("|----------------------------------------------------------------------------------|\n");
        scanf("   %d", &choice2);
        printf("|----------------------------------------------------------------------------------|\n");
        switch (choice2){
        case 1:
            addBusSchedule(busDetails);
            break;
        case 2:
            viewAllBusSchedules(busDetails);
            break;
        case 3:
            deleteBusSchedule(busDetails);
            break;
        case 4:
            modifyBusSchedule(busDetails, numRoutes);
            break;
        case 5:
            searchBus(busDetails, seatAvailability);
            break;
        case 6:
            cancelBooking(receipt);
            fclose(receipt);
            break;
        case 7:
            viewBookingHistory(temp);
            break;
        case 8:
            main();
        case 9:
            printf("|**************8*************THANKYOU AND GOODBYE**********8***********************|\n");
            printf("|----------------------------------------------------------------------------------|\n");
            return 0;
        }
    }
    fclose(credential);
    fclose(receipt);
    fclose(programRunfile);
    fclose(temp);
}


int main(){
    programRun ++;
    FILE *credential;
    credential = fopen("credentials.txt", "a+"); // Open or create the credentials file
    FILE *receipt;
    receipt = fopen("receipt.txt", "a+");
    FILE *programRunfile;
    programRunfile = fopen("programRunfile.txt", "a+");


    if (credential == NULL){
        printf("|----------------------------------------------------------------------------------|\n");
        printf("|Error: Could not open the credentials file.                                       |\n");
        printf("|----------------------------------------------------------------------------------|\n");
        return 1;
    }

    printf("|----------------------------------------------------------------------------------|\n");
    printf("|*************************WELCOME TO THE VENTURA BUS BOOKING SYSTEM****************|\n");
    printf("|----------------------------------------------------------------------------------|\n");
    printf("|         ______________________________________________/                          |\n");
    printf("|       /  _____   ________    _______       _______   |                           |\n");
    printf("|      /  /    |   |      |    |     |       |     |  |                            |\n");
    printf("|     /  /_____|   |______|    |_____|       |_____|  |                            |\n");
    printf("|    |      VENTURA  SPACE BUS Travel in style        |                            |\n");
    printf("|    |________________________________________________|                            |\n");
    printf("|              OOOOO                OOOOO  OOOOO                                   |\n");
    printf("|----------------------------------------------------------------------------------|\n");
    while (1){
        printf("|                              Select:                                             |\n");
        printf("|----------------------------------------------------------------------------------|\n");
        printf("| 1. Sign Up                                                                       |\n");
        printf("| 2. Login                                                                         |\n");
        printf("| 3. Exit                                                                          |\n");
        scanf("%d", &choice1);                                                                     
        printf("|----------------------------------------------------------------------------------|\n");
        switch (choice1){
        case 1:
            signUp(credential);
            break;
        case 2:
            if (login(credential)){
                system("cls");
                mainMenu();
                break;
            case 3:
                printf("***************bye**************");
                fclose(credential);
                fclose(receipt);
                fclose(programRunfile);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
            }
        }
    }
    return 0;
}

