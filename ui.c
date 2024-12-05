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
    char choice[ARRAY_MAX];
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
                takeBook(books, lineCount);
                break;
            case '3':
                returnBook(books, lineCount);
                break;
            case '4':
                listBooks(books, lineCount);
                break;
            case '5':
                modifyMode(books, lineCount);
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
    char choice[ARRAY_MAX];
    unsigned short i = 0;
    system("clear");
    printf("Available books:\n");
    for (i = 0; i < lineCount; i++) {
        printf("ID: %d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
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
    // todo: regex search
    char choice[ARRAY_MAX];
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


void takeBook(Book *books, unsigned short lineCount) {
    char choice[ARRAY_MAX];
    unsigned short i = 0;
    while (1)
    {
        system("clear");
        printf("Available books:\n");
        for (i = 0; i < lineCount; i++) {
            printf("ID: %d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
        }

        printf("\n\nEnter book's ID or 0 to finish: ");
        getUserInput(choice, sizeof(choice));
        if (choice[0] == '0') {
            updateFile(books, lineCount);
            return;
        }
        else {
            for (i = 0; i < lineCount; i++)
            {
                if (books[i].id == atoi(choice) && books[i].id > 0) {
                    printf("You have chosen book with ID and took it: %d. Press Enter to continue...\n", books[i].id);
                    books[i].stock--;
                    getUserInput(choice, sizeof(choice));
                }
            }
        }
    }
}

void returnBook(Book *books, unsigned short lineCount) {
    char choice[ARRAY_MAX];
    unsigned short i = 0;
    while (1)
    {
        system("clear");
        printf("Available books:\n");
        for (i = 0; i < lineCount; i++) {
            printf("ID: %d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
        }

        printf("\n\nEnter book's ID or 0 to finish: ");
        getUserInput(choice, sizeof(choice));
        if (choice[0] == '0') {
            updateFile(books, lineCount);
            return;
        }
        else {
            for (i = 0; i < lineCount; i++)
            {
                if (books[i].id == atoi(choice) && books[i].id > 0) {
                    printf("You have chosen book with ID and returned it: %d. Press Enter to continue...\n", books[i].id);
                    books[i].stock++;
                    getUserInput(choice, sizeof(choice));
                }
            }
        }
    }
}

void modifyMode(Book *books, unsigned short lineCount) {
    char choice[ARRAY_MAX];
    unsigned short i = 0, id = 1;
    while (1)
    {
        system("clear");
        printf("Available books:\n");
        for (i = 0; i < lineCount; i++) {
            printf("ID: %d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
        }

        printf("\n\nEnter book's ID to modify or 0 to finish: ");
        getUserInput(choice, sizeof(choice));
        if (choice[0] == '0') return;
        else {
            id = atoi(choice) - 1;
            while (1) {
                system("clear");
                printf("1. AUTHOR: %s, 2. NAME: %s, 3. PUBLISHED IN: %d, 4. PAGES: %d, 5. ISBN: %s, 6. IN STOCK: %d\n",  books[id].author, books[id].name, books[id].date, books[id].pages, books[id].isbn, books[id].stock);
                printf("Enter what you want to modify or 0 to finish: ");
                getUserInput(choice, sizeof(choice));
                if (choice[0] == '0') return;
                else {
                    switch (choice[0]) {
                        case '1':
                            printf("Enter new author: ");
                            getUserInput(choice, sizeof(choice));
                            strcpy(books[id].author, choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press Enter to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '2':
                            printf("Enter new name: ");
                            getUserInput(choice, sizeof(choice));
                            strcpy(books[id].name, choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press Enter to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '3':
                            printf("Enter new published year: ");
                            getUserInput(choice, sizeof(choice));
                            books[id].date = atoi(choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press Enter to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '4':
                            printf("Enter new number of pages: ");
                            getUserInput(choice, sizeof(choice));
                            books[id].pages = atoi(choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press Enter to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '5':
                            printf("Enter new ISBN: ");
                            getUserInput(choice, sizeof(choice));
                            strcpy(books[id].isbn, choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press Enter to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '6':
                            printf("Enter new number of books in stock: ");
                            getUserInput(choice, sizeof(choice));
                            books[id].stock = atoi(choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press Enter to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        default:
                            printf("Wrong input! Press Enter to show list again.\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                    }
                }
                
            }
        }
    }
}
void changeUser() {
    char choice[ARRAY_MAX];
    system("clear");
    printf("Change user feature coming soon! Press Enter to return.\n");
    getUserInput(choice, sizeof(choice));
}