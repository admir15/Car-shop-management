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

    printf("1. Sign up\n");
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

    printf("Sign up successful! You can now login.\n");

    return numUsers;
}

