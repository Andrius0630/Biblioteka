#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booksStruct.h"



void getUserInput(char *buffer, unsigned short size) {
    if (fgets(buffer, size, stdin)) {
        // Check if newline is present and replace it with null terminator
        char *c = strchr(buffer, '\n');
        if (c) *c = '\0'; // Replace newline with null terminator
    } else {
        clearerr(stdin); // Reset input stream if fgets fails
        buffer[0] = '\0'; // Ensure buffer is an empty string
    }
}


void renderMenu(Book *books, unsigned short lineCount) {
    char choice[INPUT_SIZE];
    while (1) {
        system("clear");
        printf("Biblioteka\n\n\n1.Find book\n2.Take book\n3.Return book\n4.List all books available\n\n\n5.Modify mode\n6.Change user\n0.Exit\n\n\n");

        printf("Enter a number: ");
        getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '1':
                findBook(books, lineCount);
                break;
            case '2':
                takeBook();
                break;
            case '3':
                returnBook();
                break;
            case '4':
                listBooks(books, lineCount);
                break;
            case '5':
                modifyMode();
                break;
            case '6':
                changeUser();
                break;
            case '0':
                exit(0);
                break;
            default:
                printf("Wrong input! Press Enter to try again.\n");
                getUserInput(choice, sizeof(choice));
                break;
        }
    }
}

void listBooks(Book *books, unsigned short lineCount) {
    char choice[INPUT_SIZE];
    system("clear");
    printf("Available books:\n");
    for (unsigned short i = 0; i < lineCount; i++) {
        printf("%d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",
               i + 1, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
    }

    printf("\n\n1. Go back\n\n");

    printf("Enter a number: ");
    getUserInput(choice, sizeof(choice));
    while (1)
    {
        switch (choice[0]) {
            case '1':
                return;
            default:
                printf("\nWrong input! Enter a number again: ");
                getUserInput(choice, sizeof(choice));
                break;
        }
    }
}

void findBook(Book *books, unsigned short lineCount) {
    char choice[INPUT_SIZE];
    char found = 0;
    system("clear");
    printf("Enter book's author/name/ISBN:");
    unsigned short i = 0;

    getUserInput(choice, sizeof(choice));
    printf("\nSearch results:\n");
    for (i = 0; i < lineCount; i++) {
        if (strcmp(books[i].author, choice) == 0 || strcmp(books[i].name, choice) == 0 || strcmp(books[i].isbn, choice) == 0) {
                printf("%s,%s,%d,%d,%s,%d\n", books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
                found = 1;
        }
    }
    if(!found) printf("Nothing was found! \n");
    printf("\n\n1. Go back\n\n");

    printf("Enter a number: ");
    getUserInput(choice, sizeof(choice));
    while (1)
    {
        switch (choice[0]) {
            case '1':
                return;
            default:
                printf("Wrong input! Enter a number again: ");
                getUserInput(choice, sizeof(choice));
                break;
        }
    }
    
    
}


void takeBook() {
    char choice[INPUT_SIZE];
    system("clear");
    printf("Take book feature coming soon! Press Enter to return.\n");
    getUserInput(choice, sizeof(choice));
}

void returnBook() {
    char choice[INPUT_SIZE];
    system("clear");
    printf("Return book feature coming soon! Press Enter to return.\n");
    getUserInput(choice, sizeof(choice));
}
void modifyMode() {

    char choice[INPUT_SIZE];
    system("clear");
    printf("Modify mode feature coming soon! Press Enter to return.\n");
    getUserInput(choice, sizeof(choice));
}
void changeUser() {
    char choice[INPUT_SIZE];
    system("clear");
    printf("Change user feature coming soon! Press Enter to return.\n");
    getUserInput(choice, sizeof(choice));
}