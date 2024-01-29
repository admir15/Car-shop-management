#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    char brand[50];
    int price;
};

struct User {
    char username[50];
    char email[50];
    char password[50];
    struct Car cart[10];
    int cartSize;
};

void displayMenu() {
    
    printf("1. Signup\n");
    printf("2. Login\n");
    printf("3. View Car Brands\n");
    printf("4. View Car Prices\n");
    printf("5. Search Cars\n");
    printf("6. Add to Cart\n");
    printf("7. Display Cart\n");
    printf("8. Buy Now\n");
    printf("9. Exit\n");
    
}

int signup(struct User *users, int numUsers) {
    char username[50];
    char email[50];
    char password[50];

    printf("Enter a new username: ");
    scanf("%s", username);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            return -1;
        }
    }

    printf("Enter your email: ");
    scanf("%s", email);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(email, users[i].email) == 0) {
            printf("Email already exists. Please use a different email.\n");
            return -1;
        }
    }

    printf("Enter a password: ");
    scanf("%s", password);

    strcpy(users[numUsers].username, username);
    strcpy(users[numUsers].email, email);
    strcpy(users[numUsers].password, password);
    users[numUsers].cartSize = 0;

    printf("Signup successful! You can now login.\n");

    return numUsers;
}

int login(struct User *users, int numUsers) {
    char email[50];
    char password[50];

    printf("Enter email: ");
    scanf("%s", email);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(email, users[i].email) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return i;
        }
    }

    printf("Invalid email or password.\n");
    return -1;
}

void viewCarBrands(struct Car *cars, int numCars) {
    printf("\n===== Car Brands =====\n");
    for (int i = 0; i < numCars; i++) {
        printf("%d. %s\n", i + 1, cars[i].brand);
    }
}

void viewCarPrices(struct Car *cars, int numCars) {
    printf("\n===== Car Prices =====\n");
    for (int i = 0; i < numCars; i++) {
        printf("%d. %s - $%d\n", i + 1, cars[i].brand, cars[i].price);
    }
}

void searchCars(struct Car *cars, int numCars) {
    char searchBrand[50];
    printf("Enter the car brand to search: ");
    scanf("%s", searchBrand);

    printf("\n===== Search Results =====\n");
    for (int i = 0; i < numCars; i++) {
        if (strstr(cars[i].brand, searchBrand) != NULL) {
            printf("%s - $%d\n", cars[i].brand, cars[i].price);
        }
    }
}

void addToCart(struct User *user, struct Car *cars, int numCars) {
    int choice;
    printf("Enter the number of the car to add to the cart: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= numCars) {
        if (user->cartSize < 10) {
            user->cart[user->cartSize++] = cars[choice - 1];
            printf("Car added to the cart successfully!\n");
        } else {
            printf("Cart is full. Cannot add more cars.\n");
        }
    } else {
        printf("Invalid car number.\n");
    }
}

void displayCart(struct User *user) {
    printf("\n===== Your Cart =====\n");
    for (int i = 0; i < user->cartSize; i++) {
        printf("%s - $%d\n", user->cart[i].brand, user->cart[i].price);
    }
    printf("======================\n");
}

void buyNow(struct User *user) {
    displayCart(user);

    if (user->cartSize > 0) {
        printf("\n===== Receipt =====\n");
        int total = 0;
        for (int i = 0; i < user->cartSize; i++) {
            printf("%s - $%d\n", user->cart[i].brand, user->cart[i].price);
            total += user->cart[i].price;
        }
        printf("Total: $%d\n", total);

        user->cartSize = 0;
        printf("Purchase successful! Cart is now empty.\n");
    } else {
        printf("Cart is empty. Add cars to the cart first.\n");
    }
}

int main() {
    struct Car cars[] = {{"Toyota", 20000}, {"Honda", 22000}, {"Ford", 18000}, {"Chevrolet", 25000},
                         {"BMW", 35000}, {"Mercedes", 40000}, {"Audi", 30000}, {"Tesla", 50000},
                         {"Nissan", 23000}, {"Hyundai", 19000}};
    int numCars = sizeof(cars) / sizeof(cars[0]);

    struct User users[10];
    int numUsers = 0;

    int currentUserIndex = -1;

    while (1) {
        displayMenu();

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            currentUserIndex = signup(users, numUsers);
            if (currentUserIndex != -1) {
                numUsers++;
            }
            break;
        case 2:
            currentUserIndex = login(users, numUsers);
            break;
        case 3:
            if (currentUserIndex != -1) {
                viewCarBrands(cars, numCars);
            } else {
                printf("Please login first.\n");
            }
            break;
        case 4:
            if (currentUserIndex != -1) {
                viewCarPrices(cars, numCars);
            } else {
                printf("Please login first.\n");
            }
            break;
        case 5:
            searchCars(cars, numCars);
            break;
        case 6:
            if (currentUserIndex != -1) {
                addToCart(&users[currentUserIndex], cars, numCars);
            } else {
                printf("Please login first.\n");
            }
            break;
        case 7:
            if (currentUserIndex != -1) {
                displayCart(&users[currentUserIndex]);
            } else {
                printf("Please login first.\n");
            }
            break;
        case 8:
            if (currentUserIndex != -1) {
                buyNow(&users[currentUserIndex]);
            } else {
                printf("Please login first.\n");
            }
            break;
        case 9:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
