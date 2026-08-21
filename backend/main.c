#include <stdio.h>
#include <string.h>

#define MAX_EVS 10

struct EV {
    int id;
    char model[50];
    char brand[30];
    char type[30];
    float pricePerDay;
    int batteryRange;
    int available;
};

struct Rental {
    int rentalId;
    int evId;
    char customerName[50];
    char phone[15];
    int days;
    float totalAmount;
    int active;
};

struct EV evs[MAX_EVS] = {
    {101, "NexonEV", "Tata", "SUV", 1200, 325, 1},
    {102, "CometEV", "MG", "Hatchback", 900, 230, 1},
    {103, "TiagoEV", "Tata", "Hatchback", 800, 250, 1},
    {104, "ZSEV", "MG", "SUV", 1500, 461, 1},
    {105, "eC3", "Citroen", "Hatchback", 850, 320, 1}
};

struct Rental rentals[MAX_EVS];

int rentalCount = 0;

void displayEVs() {

    printf("\n================ AVAILABLE EVs ================\n");

    for (int i = 0; i < MAX_EVS; i++) {

        if (evs[i].available) {

            printf("\nID            : %d", evs[i].id);
            printf("\nModel         : %s", evs[i].model);
            printf("\nBrand         : %s", evs[i].brand);
            printf("\nType          : %s", evs[i].type);
            printf("\nPrice/Day     : Rs. %.2f", evs[i].pricePerDay);
            printf("\nBattery Range : %d km\n", evs[i].batteryRange);
        }
    }
}

void searchEV() {

    char model[50];

    printf("\nEnter EV model to search: ");
    scanf("%s", model);

    for (int i = 0; i < MAX_EVS; i++) {

        if (strcasecmp(evs[i].model, model) == 0) {

            printf("\nEV Found!");
            printf("\nID: %d", evs[i].id);
            printf("\nModel: %s", evs[i].model);
            printf("\nBrand: %s", evs[i].brand);
            printf("\nPrice/Day: Rs. %.2f\n", evs[i].pricePerDay);

            return;
        }
    }

    printf("\nEV not found.\n");
}

void rentEV() {

    int id;
    int days;

    printf("\nEnter EV ID: ");
    scanf("%d", &id);

    int index = -1;

    for (int i = 0; i < MAX_EVS; i++) {

        if (evs[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nInvalid EV ID.\n");
        return;
    }

    if (!evs[index].available) {
        printf("\nThis EV is already rented.\n");
        return;
    }

    printf("Enter Customer Name: ");
    scanf("%s", rentals[rentalCount].customerName);

    printf("Enter Phone Number: ");
    scanf("%s", rentals[rentalCount].phone);

    printf("Enter Number of Days: ");
    scanf("%d", &days);

    rentals[rentalCount].rentalId = 1001 + rentalCount;
    rentals[rentalCount].evId = id;
    rentals[rentalCount].days = days;
    rentals[rentalCount].totalAmount =
        evs[index].pricePerDay * days;
    rentals[rentalCount].active = 1;

    evs[index].available = 0;

    printf("\n========== BOOKING CONFIRMED ==========\n");
    printf("Rental ID   : %d\n", rentals[rentalCount].rentalId);
    printf("Customer    : %s\n", rentals[rentalCount].customerName);
    printf("EV          : %s\n", evs[index].model);
    printf("Days        : %d\n", days);
    printf("Total       : Rs. %.2f\n",
           rentals[rentalCount].totalAmount);

    saveRental(rentals[rentalCount]);

rentalCount++;
}

void returnEV() {

    int rentalId;

    printf("\nEnter Rental ID: ");
    scanf("%d", &rentalId);

    for (int i = 0; i < rentalCount; i++) {

        if (rentals[i].rentalId == rentalId &&
            rentals[i].active) {

            for (int j = 0; j < MAX_EVS; j++) {

                if (evs[j].id == rentals[i].evId) {
                    evs[j].available = 1;
                    break;
                }
            }

            rentals[i].active = 0;

            printf("\nEV returned successfully!\n");
            return;
        }
    }

    printf("\nInvalid Rental ID.\n");
}

void displayRentals() {

    printf("\n================ RENTALS ================\n");

    for (int i = 0; i < rentalCount; i++) {

        printf("\nRental ID : %d", rentals[i].rentalId);
        printf("\nCustomer  : %s", rentals[i].customerName);
        printf("\nEV ID     : %d", rentals[i].evId);
        printf("\nDays      : %d", rentals[i].days);
        printf("\nAmount    : Rs. %.2f", rentals[i].totalAmount);
        printf("\nStatus    : %s\n",
               rentals[i].active ? "Active" : "Returned");
    }
}

void saveRental(struct Rental rental) {

    FILE *file;

    file = fopen("backend/data/rentals.txt", "a");

    if (file == NULL) {
        printf("Error opening rental file.\n");
        return;
    }

    fprintf(file,
            "%d|%d|%s|%s|%d|%.2f|%d\n",
            rental.rentalId,
            rental.evId,
            rental.customerName,
            rental.phone,
            rental.days,
            rental.totalAmount,
            rental.active);

    fclose(file);

    printf("Rental saved successfully.\n");
}

int main() {

    int choice;

    while (1) {

        printf("\n\n============================================\n");
        printf("          EV RENTAL MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1. View Available EVs\n");
        printf("2. Search EV\n");
        printf("3. Rent EV\n");
        printf("4. Return EV\n");
        printf("5. View Rentals\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayEVs();
                break;

            case 2:
                searchEV();
                break;

            case 3:
                rentEV();
                break;

            case 4:
                returnEV();
                break;

            case 5:
                displayRentals();
                break;

            case 6:
                printf("\nThank you!\n");
                return 0;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}