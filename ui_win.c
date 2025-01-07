#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booksStruct.h"
#include <math.h>


void getUserInput(char *buffer, unsigned short size) {
    if (fgets(buffer, size, stdin)) {

        char *c = strchr(buffer, '\n');
        if (c) *c = '\0'; 
    } else {
        clearerr(stdin);
        buffer[0] = '\0'; 
    }
}

void renderLogIn() {
    char choice[ARRAY_MAX];
    while (1) {
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t   Login\\Regsiter\n\n1. Login\n2. Register\n\n\n");
        printf("Select an option (0 to exit): ");
        getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '1':
                loginUser();
                break;
            case '2':
                createUser();
                break;
            case '0':
                system(WIN_CLS);
                return;
            default:
                system(WIN_CLS);
                drawLogo();
                printf("\n\n\n\t\t    No such option available! Press ENTER to try again...\n\n\n");
                getUserInput(choice, sizeof(choice));
                break;
        }
        
    }
}

void renderMainMenuUser(User *users, unsigned short lineCountPasswd, unsigned short userInUse) {
    unsigned short lineCount, lineCountData, i;
    char choice[ARRAY_MAX];
    while (1) {
        lineCount = 0;
        lineCountData = 0;
        i = 0;
        char **buffer = NULL;
        char **usrBookBuffer = NULL;


        readFile(&lineCount, &buffer);
        readFileUsr(&lineCountData, &usrBookBuffer, users, userInUse);

        Book *books = malloc(lineCount * sizeof(Book));
        if (books == NULL) exit(9);

        Data *usrBook = malloc(lineCountData * sizeof(Book));
        if (usrBook == NULL) exit(9);

        initializeBooks(books, buffer, lineCount);
        initializeUsrData(usrBook, usrBookBuffer, lineCountData);
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t     Welcome, %s\n\n1. Find a book\n2. Take a book\n3. Return a book\n4. View all available books\n\n\n5. Manage account\n0. Logout\n\n\n", users[userInUse].name);
        printf("Select an option: ");

        getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '1':
                findBook(books, lineCount);
                break;
            case '2':
                takeBook(usrBook, lineCountData, books, lineCount, users, userInUse);
                break;
            case '3':
                returnBook(usrBook, lineCountData, books, lineCount, users, userInUse);
                break;
            case '4':
                listBooks(books, lineCount);
                break;
            case '5':
                modifyUsrMode(users, lineCountPasswd, userInUse);
                for (i = 0; i < lineCount; i++) {
                    free(buffer[i]);
                }
                free(buffer);
                free(books);

                for (i = 0; i < lineCountData; i++) {
                    free(usrBookBuffer[i]);
                }
                free(usrBookBuffer);
                free(usrBook);
                return;
            case '0':
                for (i = 0; i < lineCount; i++) {
                    free(buffer[i]);
                }
                free(buffer);
                free(books);

                for (i = 0; i < lineCountData; i++) {
                    free(usrBookBuffer[i]);
                }
                free(usrBookBuffer);
                free(usrBook);
                return;
            default:
                system(WIN_CLS);
                drawLogo();
                printf("\n\n\n\t\t    No such option available! Press ENTER to try again...\n\n\n");
                getUserInput(choice, sizeof(choice));
                break;
        }
        for (i = 0; i < lineCount; i++) {
            free(buffer[i]);
        }
        free(buffer);
        free(books);

        for (i = 0; i < lineCountData; i++) {
            free(usrBookBuffer[i]);
        }
        free(usrBookBuffer);
        free(usrBook);
    }
}

void renderMainMenuAdmin() {
    unsigned short lineCount, i;
    char choice[ARRAY_MAX];
    while (1) {
        lineCount = 0;
        i = 0;
        char **buffer = NULL;
        readFile(&lineCount, &buffer);
        Book *books = malloc(lineCount * sizeof(Book));
        if (books == NULL) exit(9);
        initializeBooks(books, buffer, lineCount);
        system(WIN_CLS);
        drawAdminLogo();
        printf("\t\t\t\t     Welcome, %s\n\n1.List all books available\n\n2.Modify or delete mode\n3.Add new book\n\n0.Logout\n\n\n", ADMIN);
        printf("Select an option: ");
       getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '1':
                listBooks(books, lineCount);
                break;
            case '2':
                modifyMode(books, lineCount);
                break;
            case '3':
                addNewMode();
                break;
            case '0':
                return;
            default:
                system(WIN_CLS);
                drawAdminLogo();
                printf("\n\n\n\t\t    No such option available! Press ENTER to try again...\n\n\n");
                getUserInput(choice, sizeof(choice));
                break;
        }
        for (i = 0; i < lineCount; i++) {
            free(buffer[i]);
        }
        free(buffer);
        free(books);
    }
}

void listBooks(Book *books, unsigned short lineCount) {
    char choice[ARRAY_MAX];
    unsigned short i = 0, j = 0;
    int pageCount = 1;
    int linesPrinted = 0;
    double temp = lineCount;
    temp = ceil(temp/3.0);
    system(WIN_CLS);
    drawLogo();
    printf("\t\t\t\t       Book list\n\n\n");
    printf("Currently available books: \n\n");

    printf("PAGE %d\n\n", pageCount);
    while (j <= lineCount) {
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) {
                printf("|----------------------------------------| ");
            } 
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) {
                printf("| ID: %-35d| ", books[i].id);
            } 
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) {
                printf("|----------------------------------------| ");
            } 
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Author: %-31s| ", books[i].author);
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15)  printf("| Name: %-33s| ", books[i].name);
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Published: %-28d| ", books[i].date);
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Pages: %-32d| ", books[i].pages);
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| ISBN: %-33s| ", books[i].isbn);
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Remaining in stock: %-19d| ", books[i].stock);
        }
        printf("\n");
        for (i = j; i < j + 3; i++) {
            if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) {
                printf("|----------------------------------------| ");
            } 
        }

        printf("\n\n");
        linesPrinted++;
        j += 3;

        if (lineCount <= 9) {
            if (linesPrinted == temp) {
                printf("Press ENTER to return...");
                getUserInput(choice, sizeof(choice));
                return;
            }
            continue;
        }
        else if (j % 9 == 0 && pageCount == 1) {
            printf("\n2. Next page\n0. Exit\n");
            getUserInput(choice, sizeof(choice));
            switch (atoi(choice)) {
                case 2:
                    pageCount++;
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t       Book list\n\n\n");
                    printf("Currently available books: \n\n");
                    printf("PAGE %d\n\n", pageCount);
                    break;
                default:
                    return;
            }
        }
        else if (j % 9 == 0) {
            printf("\n1. Previous page\n2. Next page\n0. Exit\n");
            getUserInput(choice, sizeof(choice));
            switch (atoi(choice)) {
                case 1:
                    pageCount--;
                    j -= 18;
                    linesPrinted = j/3;
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t       Book list\n\n\n");
                    printf("Currently available books: \n\n");
                    printf("PAGE %d\n\n", pageCount);
                    break;
                case 2:
                    pageCount++;
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t       Book list\n\n\n");
                    printf("Currently available books: \n\n");
                    printf("PAGE %d\n\n", pageCount);
                    break;
                default:
                    return;
            }
        }
        else if (j >= lineCount) {
            printf("\n1. Previous page\n0. Exit\n");
            getUserInput(choice, sizeof(choice));
            switch (atoi(choice)) {
                case 1:
                    j -= 18 - ((pageCount*9) - ((linesPrinted*3)));
                    pageCount--;
                    linesPrinted = j/3;
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t       Book list\n\n\n");
                    printf("Currently available books: \n\n");
                    printf("PAGE %d\n\n", pageCount);
                    break;
                default:
                    return;
            }
        } 
    }
}

void findBook(Book *books, unsigned short lineCount) {
    char choice[ARRAY_MAX];
    char found = 0;
    system(WIN_CLS);
    drawLogo();
    printf("\t\t\t\t     Find a book\n\n");
    printf("Enter an author, book name or ISBN: ");
    unsigned short i = 0;

    getUserInput(choice, sizeof(choice));
    system(WIN_CLS);
    drawLogo();
    printf("\t\t\t\t     Find a book\n\n");
    printf("\nSearch results for \"%s\":\n\n", choice);

    for (i = 0; i < lineCount; i++) {
        if (strcmp(books[i].author, choice) == 0 || strcmp(books[i].name, choice) == 0 || strcmp(books[i].isbn, choice) == 0) {
            printf("|----------------------------------------| \n");
            printf("| ID: %-35d| \n", books[i].id);
            printf("|----------------------------------------| \n");
            printf("| Author: %-31s| \n", books[i].author);
            printf("| Name: %-33s| \n", books[i].name);
            printf("| Published: %-28d| \n", books[i].date);
            printf("| Pages: %-32d| \n", books[i].pages);
            printf("| ISBN: %-33s| \n", books[i].isbn);
            printf("| Remaining in stock: %-19d| \n", books[i].stock);
            printf("|----------------------------------------| \n\n");
            found = 1;
        } 
    }

    if(!found) printf("Nothing was found!\n");

    printf("\n\n\nPress ENTER to return");
    getUserInput(choice, sizeof(choice));
}

void takeBook(Data *usrBook, unsigned short lineCountData, Book *books, unsigned short lineCount, User *users, unsigned short userInUse) {
    char choice[ARRAY_MAX];
    char pages[ARRAY_MAX];
    char date[ARRAY_MAX];
    char found = 0;
    unsigned short i = 0, id = 0, j = 0;
    system(WIN_CLS);
    drawLogo();
    printf("\t\t\t\t       Taking a book\n\n\n");


    printf("Books available to take:\n\n");
    
    while (j < lineCount) {
            for (i = j; i < j + 3; i++) {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("|----------------------------------------| ");

            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| ID: %-35d| ", books[i].id);
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("|----------------------------------------| ");
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| %-39s| ", books[i].author);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| %-39s| ", books[i].name);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Published: %-28d| ", books[i].date);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Pages: %-32d| ", books[i].pages);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| ISBN: %-33s| ", books[i].isbn);
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("| Amount to return: %-21d| ", books[i].stock);
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (books[i].stock > 0 && books[i].pages > 0 && books[i].date > 0 && books[i].id > 0 && sizeof(books[i].isbn) < 15) printf("|----------------------------------------| ");
            }
            printf("\n\n");
            j += 3;
        }

    
    if (!i) {
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t       Taking a book\n\n\n");
        printf("There are no books available!\n\n\nPress ENTER to return\n");
        getUserInput(choice, sizeof(choice));
        return;
    }
    

    printf("Enter the ID of the book you wish to take. Enter 0 to exit: ");
    getUserInput(choice, sizeof(choice));
    id = atoi(choice);
    if (atoi(choice) == 0) return;
    else {
        for (i = 0; i < lineCount; i++) {
            for (j = 0; j < lineCountData; j++) {
                if (strcmp(books[i].name, usrBook[j].name) == 0 && books[i].id == id && books[i].stock > 0) {
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t       Taking a book\n\n\n");
                    printf("You have taken the book %s. Press ENTER to continue...\n", usrBook[j].name);
                    getUserInput(choice, sizeof(choice));
                    found = 1;
                    books[i].stock--;
                    usrBook[j].stock++;
                    updateFile(books, lineCount);
                    updateUsrData(usrBook, lineCountData, users, userInUse);
                    return;
                }
                
            }
        }
        if (!found && books[id-1].stock > 0)
        {
            system(WIN_CLS);
            drawLogo();
            printf("\t\t\t\t       Taking a book\n\n\n");
            printf("You have taken a book with the ID %d. Press ENTER to continue...\n", id);
            getUserInput(choice, sizeof(choice));
            books[id-1].stock--;
            sprintf(pages, "%d", books[id-1].pages);
            sprintf(date, "%d", books[id-1].date);
            appendToUsr(books[id-1].author, books[id-1].name, date, pages, books[id-1].isbn, "1", users, userInUse);
            updateFile(books, lineCount);
            return;
        }
    }
}

void returnBook(Data *usrBook, unsigned short lineCountData, Book *books, unsigned short lineCount, User *users, unsigned short userInUse) {
    char choice[ARRAY_MAX];
    char pages[ARRAY_MAX];
    char date[ARRAY_MAX];
    char found = 0;
    unsigned short i = 0, id = 0, j = 0;
    system(WIN_CLS);
    drawLogo();
    printf("\t\t\t\t       Returning a book\n\n\n");
    printf("Currently available books to return: \n\n");
    if (!lineCountData)
    {
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t       Returning a book\n\n\n");
        printf("\nYou have no books to return!\n\nPress ENTER to return...\n");
        getUserInput(choice, sizeof(choice));
        return;
    } else {
        while (j < lineCountData) {
            for (i = j; i < j + 3; i++) {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("|----------------------------------------| ");

            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| ID: %-35d| ", usrBook[i].id);
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("|----------------------------------------| ");
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| Author: %-31s| ", usrBook[i].author);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| Name: %-33s| ", usrBook[i].name);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| Published: %-28d| ", usrBook[i].date);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| Pages: %-32d| ", usrBook[i].pages);
            }
            printf("\n");
            for (i = j; i < j + 3; i++)
            {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| ISBN: %-33s| ", usrBook[i].isbn);
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("| Amount to return: %-21d| ", usrBook[i].stock);
            }
            printf("\n");
            for (i = j; i < j + 3; i++) {            
                if (usrBook[i].stock > 0 && usrBook[i].pages > 0 && usrBook[i].date > 0 && usrBook[i].id > 0 && sizeof(usrBook[i].isbn) < 15) printf("|----------------------------------------| ");
            }
            printf("\n\n");
            j += 3;
        }
    }
    

    printf("\n\nEnter the ID of the book you wish to return. Enter 0 to exit: ");
    getUserInput(choice, sizeof(choice));
    id = atoi(choice);
    if (atoi(choice) == 0) return;
    else {
        for (i = 0; i < lineCountData; i++) {
            for (j = 0; j < lineCount; j++) {
                if (strcmp(books[j].name, usrBook[i].name) == 0 && usrBook[i].stock > 0 && usrBook[i].id == id) {
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t       Returning a book\n\n\n");
                    printf("You have returned the book with the ID: %d. Press ENTER to continue...\n", id);
                    getUserInput(choice, sizeof(choice));
                    found = 1;
                    books[j].stock++;         
                    usrBook[i].stock--;
                    updateFile(books, lineCount);
                    updateUsrData(usrBook, lineCountData, users, userInUse);
                }
            }
        }
        if (!found && usrBook[id-1].stock > 0) {
            system(WIN_CLS);
            drawLogo();
            printf("\t\t\t\t       Returning a book\n\n\n");
            printf("You have returned the book with the ID: %d. Press ENTER to continue...\n", id);
            getUserInput(choice, sizeof(choice));
            usrBook[id-1].stock--;
            sprintf(pages, "%d", usrBook[id-1].pages);
            sprintf(date, "%d", usrBook[id-1].date);
            appendToFile(usrBook[id-1].author, usrBook[id-1].name, date, pages, usrBook[id-1].isbn, "1");
            updateUsrData(usrBook, lineCountData, users, userInUse);
        }
        
    }
}

void modifyMode(Book *books, unsigned short lineCount) {
    char choice[ARRAY_MAX];
    unsigned short i = 0, id = 1;
    while (1)
    {
        system(WIN_CLS);
        printf("Available books:\n");
        for (i = 0; i < lineCount; i++) {
            printf("ID: %d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
        }

        printf("\n\nEnter book's ID to modify or 0 to finish: ");
        getUserInput(choice, sizeof(choice));
        if (atoi(choice) == 0) return;
        else {
            id = atoi(choice) - 1;
            while (1) {
                system(WIN_CLS);
                printf("1. AUTHOR: %s, 2. NAME: %s, 3. PUBLISHED IN: %d, 4. PAGES: %d, 5. ISBN: %s, 6. IN STOCK: %d\n",  books[id].author, books[id].name, books[id].date, books[id].pages, books[id].isbn, books[id].stock);
                printf("Enter what you want to modify or 0 to finish: ");
                getUserInput(choice, sizeof(choice));
                if (atoi(choice) == 0) return;
                else {
                    switch (choice[0]) {
                        case '1':
                            printf("Enter new author: ");
                            getUserInput(choice, sizeof(choice));
                            strcpy(books[id].author, choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press ENTER to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '2':
                            printf("Enter new name: ");
                            getUserInput(choice, sizeof(choice));
                            strcpy(books[id].name, choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press ENTER to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '3':
                            printf("Enter new published year: ");
                            getUserInput(choice, sizeof(choice));
                            books[id].date = atoi(choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press ENTER to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '4':
                            printf("Enter new number of pages: ");
                            getUserInput(choice, sizeof(choice));
                            books[id].pages = atoi(choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press ENTER to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '5':
                            printf("Enter new ISBN: ");
                            getUserInput(choice, sizeof(choice));
                            strcpy(books[id].isbn, choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press ENTER to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        case '6':
                            printf("Enter new number of books in stock: ");
                            getUserInput(choice, sizeof(choice));
                            books[id].stock = atoi(choice);
                            updateFile(books, lineCount);
                            printf("Changes saved! Press ENTER to continue...\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                        default:
                            printf("Wrong input! Press ENTER to show list again.\n");
                            getUserInput(choice, sizeof(choice));
                            break;
                    }
                }
                
            }
        }
    }
}

void addNewMode() {
    char author[ARRAY_MAX];
    char name[ARRAY_MAX];
    char date[ARRAY_MAX];
    char pages[ARRAY_MAX];
    char isbn[ARRAY_MAX];
    char stock[ARRAY_MAX];
    char choice[ARRAY_MAX];
    system(WIN_CLS);
    drawAdminLogo();
    printf("\t\t\t\t     Adding new book\n\n");
    printf("Enter author: ");
    getUserInput(author, sizeof(author));

    printf("Enter name: ");
    getUserInput(name, sizeof(name));
    
    printf("Enter year when it was published: ");
    getUserInput(date, sizeof(date));

    printf("Enter page count: ");
    getUserInput(pages, sizeof(pages));
    
    printf("Enter ISBN: ");
    getUserInput(isbn, sizeof(isbn));

    printf("Enter how many books will be in stock: ");
    getUserInput(stock, sizeof(stock));


    system(WIN_CLS);
    drawAdminLogo();
    printf("\t\t\t\t     Adding new book\n\n");
    printf("\n\t\t\tSuccess!. Press ENTER to continue...");
    getUserInput(choice, sizeof(choice));

    appendToFile(author, name, date, pages, isbn, stock);
}

void loginUser() {
    char **bufferPasswd = NULL;
    char username[ARRAY_MAX];
    char passwd[ARRAY_MAX];
    unsigned short i = 0, lineCountPasswd = 0;
    char found = 0, attempts = 4;

    readFilePasswd(&lineCountPasswd, &bufferPasswd);
    User *users = malloc(lineCountPasswd * sizeof(User));
    if (users == NULL) exit(9);
    initializePasswd(users, bufferPasswd, lineCountPasswd);

    while (attempts > 0)
    {
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t\t   Login\n");

        printf("\n\n\t\t\t\t   Name: ");
        getUserInput(username, sizeof(username));
        printf("\t\t\t\t   Password: ");
        getUserInput(passwd, sizeof(passwd));
        
        if (strcmp(username, ADMIN) == 0 && strcmp(username, ADMIN_PASSWD) == 0) {
            renderMainMenuAdmin();
            for (i = 0; i < lineCountPasswd; i++) {
                free(bufferPasswd[i]);
            }
            free(bufferPasswd);
            free(users);
            return;
        } else {
            encrypt(username, 0xFACE);
            encrypt(passwd, 0xFACE);
        }
        
        for (i = 0; i < lineCountPasswd; i++) {
            if (strcmp(users[i].name, username) == 0 && strcmp(users[i].passwd, passwd) == 0) {
                found = 1;
                decrypt(users[i].name, 0xFACE);
                renderMainMenuUser(users, lineCountPasswd, i);
                for (i = 0; i < lineCountPasswd; i++) {
                    free(bufferPasswd[i]);
                }
                free(bufferPasswd);
                free(users);
                return;
            }
        }
        if (!found) 
        {
            attempts--;
            system(WIN_CLS);
            drawLogo();
            printf("\t\t\t\t\t   Login\n");
            printf("\n\n\n\t    Invalid username or password, please try again. %d attempts remaining.\n\t\t\t\tPress ENTER to try again\n", attempts);
            getUserInput(passwd, sizeof(passwd));
        }
            
    }

    for (i = 0; i < lineCountPasswd; i++) {
        free(bufferPasswd[i]);
    }
    free(bufferPasswd);
    free(users);

}

void createUser() {
    char **bufferPasswd = NULL;
    char choice[ARRAY_MAX];
    char name[ARRAY_MAX];
    char passwd[ARRAY_MAX];
    char passwd2[ARRAY_MAX];
    char success = 0, nameExists = 0;

    unsigned short lineCountPasswd = 0, i = 0;
    readFilePasswd(&lineCountPasswd, &bufferPasswd);
    User *users = malloc(lineCountPasswd * sizeof(User));
    if (users == NULL) exit(9);
    initializePasswd(users, bufferPasswd, lineCountPasswd);

    while (!success) {
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t\t Register\n");
        printf("\n\n\t\t\t\t   Username: ");
        getUserInput(name, sizeof(name));
        encrypt(name, 0xFACE);
        nameExists = 0;
        for (i = 0; i < lineCountPasswd; i++) {
            if (strcmp(users[i].name, name) == 0) {
                system(WIN_CLS);
                drawLogo();
                printf("\t\t\t\t\t Register\n");
                printf("\n\n\t\t\t  Username already exists! Press ENTER to try again...\n");
                getUserInput(choice, sizeof(choice));
                nameExists = 1;
                break;
            }
        }
        if (nameExists) continue;

        printf("\t\t\t\t   Password: ");
        getUserInput(passwd, sizeof(passwd));

        printf("\t\t\t\t   Confirm password: ");
        getUserInput(passwd2, sizeof(passwd2));

        if (strcmp(passwd, passwd2) != 0) {
            system(WIN_CLS);
            drawLogo();
            printf("\t\t\t\t\t Register\n");
            printf("\n\n\t\t\t  Passwords do not match! Press ENTER to try again...\n");
            getUserInput(choice, sizeof(choice));
            continue;
        }

        encrypt(passwd, 0xFACE);
        appendToPasswd(name, passwd);

        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t\t Register\n");
        printf("\n\n\t\t\t\tUser created successfully! Press ENTER to continue...\n");
        getUserInput(choice, sizeof(choice));
        success = 1;
    }

    for (i = 0; i < lineCountPasswd; i++) {
        free(bufferPasswd[i]);
    }
    free(bufferPasswd);
    free(users);
}    
    
void modifyUsrMode(User *users, unsigned short lineCountPasswd, unsigned short userInUse) {
    char choice[ARRAY_MAX];
    char passwd[ARRAY_MAX];
    unsigned short i = 0;
    char nameExists = 0;
    while (1)
    {
        nameExists = 0;
        system(WIN_CLS);
        drawLogo();
        printf("\t\t\t\t   Account management\n\n\n");
        printf("Currently logged in as: %s\n\n", users[userInUse].name);
        encrypt(users[userInUse].name, 0xFACE);
        printf("1. Change username\n2. Change password\n3. Delete account\n");
        printf("\n\n\nSelect an option (0 to exit): ");
        getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '0':
                decrypt(users[userInUse].name, 0xFACE);
                return;
            case '1':
                system(WIN_CLS);
                drawLogo();
                printf("\t\t\t\t   Account management\n\n");
                printf("\n\n\t\t\t\t  Enter new username: ");
                getUserInput(choice, sizeof(choice));
                if (strcmp(choice, ADMIN) != 0) {
                    encrypt(choice, 0xFACE);
                    for (i = 0; i < lineCountPasswd; i++) {
                        if (strcmp(users[i].name, choice) == 0) {
                            nameExists = 1;
                            system(WIN_CLS);
                            drawLogo();
                            printf("\t\t\t\t   Account management\n\n\n");
                            printf("\n\t\t\t  Username already exists! Press ENTER to try again...\n");
                            getUserInput(choice, sizeof(choice));
                            decrypt(users[userInUse].name, 0xFACE);
                            break;
                        }
                    }
                } else {
                    nameExists = 1;
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t   Account management\n\n\n");
                    printf("\n\t\t\t  Username already exists! Press ENTER to try again...\n");
                    getUserInput(choice, sizeof(choice));
                    decrypt(users[userInUse].name, 0xFACE);
                }
                
                if (nameExists == 1) break;
                else {
                    strcpy(users[userInUse].name, choice);
                    updateFileUser(users, lineCountPasswd);
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t   Account management\n\n\n");
                    printf("\t\t\tChanges saved! Press ENTER to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    decrypt(users[userInUse].name, 0xFACE);
                    break;
                }
            case '2':
                system(WIN_CLS);
                drawLogo();
                printf("\t\t\t\t   Account management\n\n");
                printf("\n\n\t\t\t\t  Enter new password: ");
                getUserInput(choice, sizeof(choice));

                printf("\t\t\t\t  Confirm new password: ");
                getUserInput(passwd, sizeof(passwd));


                if (strcmp(passwd, choice) != 0) {
                    system(WIN_CLS);
                    drawLogo();
                    printf("\n\n\t\t\t  Passwords do not match! Press ENTER to try again...\n");
                    getUserInput(choice, sizeof(choice));
                    decrypt(users[userInUse].name, 0xFACE);
                    break;
                } else {
                    encrypt(choice, 0xFACE);
                    strcpy(users[userInUse].passwd, choice);
                    updateFileUser(users, lineCountPasswd);
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t   Account management\n\n\n");
                    printf("\t\t\tChanges saved! Press ENTER to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    decrypt(users[userInUse].name, 0xFACE);
                    break;
                }
            case '3':
                system(WIN_CLS);
                drawLogo();
                printf("\t\t\t\t   Account management\n\n\n");
                printf("\t\tAre you sure you want to delete this account? (y/n): ");
                getUserInput(choice, sizeof(choice));
                if (choice[0]=='y')
                {
                    users[userInUse].deleted = 1;
                    updateFileUser(users, lineCountPasswd);
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t   Account management\n\n\n");
                    printf("\t\t   Account has been deleted! Press ENTER to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    decrypt(users[userInUse].name, 0xFACE);
                    return;
                } else {
                    system(WIN_CLS);
                    drawLogo();
                    printf("\t\t\t\t   Account management\n\n\n");
                    printf("\t\tAccount deletion canceled! Press ENTER to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    decrypt(users[userInUse].name, 0xFACE);
                    break;
                }
            default:
                system(WIN_CLS);
                drawLogo();
                printf("\t\t\t\t   Account management\n\n\n");
                printf("\n\n\n\t\t    No such option available! Press ENTER to try again...\n\n\n");
                getUserInput(choice, sizeof(choice));
                decrypt(users[userInUse].name, 0xFACE);
                break;
        }
    }
}