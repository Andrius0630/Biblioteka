#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booksStruct.h"

/*
    todo: 
        1. login/signIn menu
        2. regex search
        3. add and delete books
    bruh 💀💀💀
*/

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
        system("clear");
        printf("Registration/Login Menu \n\n\n1.Login\n2.Register new user\n\n0.Exit\n\n\n");
        printf("Choose an option: ");
        getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '1':
                loginUser();
                break;
            case '2':
                createUser();
                break;
            case '0':
                system("clear");
                return;
            default:
                printf("Wrong input! Press Enter to try again.\n");
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

        system("clear");
        printf("Biblioteka\n\nWelcome back, %s\n\n1.Find book\n2.Take book\n3.Return book\n4.List all books available\n\n\n5.Modify account or delete\n0.Logout\n\n\n", users[userInUse].name);
        printf("Choose an option: ");
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
                printf("Wrong input! Press Enter to try again.\n");
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

void renderMainMenuAdmin(User *users, unsigned short userInUse) {
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
        system("clear");
        printf("Biblioteka\n\nWelcome back, %s\n\n1.List all books available\n\n2.Modify or delete mode\n3.Add new book\n\n0.Logout\n\n\n", users[userInUse].name);

        printf("Choose an option: ");
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
                printf("Wrong input! Press Enter to try again.\n");
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
    unsigned short i = 0;
    system("clear");
    printf("Available books:\n");
    for (i = 0; i < lineCount; i++) {
        if (books[i].stock > 0) printf("ID: %d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
    }

    printf("\n\n0. Go back\n\n");

    printf("Choose an option: ");
    getUserInput(choice, sizeof(choice));
    while (1)
    {
        switch (choice[0]) {
            case '0':
                return;
            default:
                printf("\nWrong input! Choose an option again: ");
                getUserInput(choice, sizeof(choice));
                break;
        }
    }
}

void findBook(Book *books, unsigned short lineCount) {
    /* todo: regex search */
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
    printf("\n\n0. Go back\n\n");

    printf("Choose an option: ");
    getUserInput(choice, sizeof(choice));
    while (1)
    {
        switch (choice[0]) {
            case '0':
                return;
            default:
                printf("Wrong input! Choose an option again: ");
                getUserInput(choice, sizeof(choice));
                break;
        }
    }
}

void takeBook(Data *usrBook, unsigned short lineCountData, Book *books, unsigned short lineCount, User *users, unsigned short userInUse) {
    char choice[ARRAY_MAX];
    char pages[ARRAY_MAX];
    char date[ARRAY_MAX];
    char found = 0;
    unsigned short i = 0, id = 0, j = 0;
    system("clear");
    printf("Your books:\n");
    for (i = 0; i < lineCount; i++) {
        if (books[i].stock > 0) printf("ID: %d. AUTHOR: %s, NAME: %s, ISBN: %s, IN STOCK: %d\n",  books[i].id, books[i].author, books[i].name, books[i].isbn, books[i].stock);
        else continue;
    }
    if (!i)
    {
        printf("\nThere is no books to take!\n\nPress Enter to return...\n");
        getUserInput(choice, sizeof(choice));
        return;
    }
    

    printf("\n\nEnter book's ID or 0 to finish: ");
    getUserInput(choice, sizeof(choice));
    id = atoi(choice);
    if (atoi(choice) == 0) return;
    else {
        for (i = 0; i < lineCount; i++) {
            for (j = 0; j < lineCountData; j++) {
                if (strcmp(books[i].name, usrBook[j].name) == 0 && books[i].id == id && books[i].stock > 0) {
                    printf("You have chosen book with ID and took it: %s. Press Enter to continue...\n", usrBook[j].name);
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
            printf("You have chosen book with ID and took it: %d. Press Enter to continue...\n", id);
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
    system("clear");
    printf("Your books:\n");
    for (i = 0; i < lineCountData; i++) {
        if (usrBook[i].stock > 0) printf("ID: %d. AUTHOR: %s, NAME: %s, ISBN: %s, IN STOCK: %d\n",  usrBook[i].id, usrBook[i].author, usrBook[i].name, usrBook[i].isbn, usrBook[i].stock);
        else continue;
    }
    if (!i)
    {
        printf("\nYou have no books to return!\n\nPress Enter to return...\n");
        getUserInput(choice, sizeof(choice));
        return;
    }
    

    printf("\n\nEnter book's ID or 0 to finish: ");
    getUserInput(choice, sizeof(choice));
    id = atoi(choice);
    if (atoi(choice) == 0) return;
    else {
        for (i = 0; i < lineCountData; i++) {
            for (j = 0; j < lineCount; j++) {
                if (strcmp(books[j].name, usrBook[i].name) == 0 && usrBook[i].stock > 0 && usrBook[i].id == id) {
                    printf("You have chosen book with ID and returned it: %d. Press Enter to continue...\n", id);
                    getUserInput(choice, sizeof(choice));
                    found = 1;
                    books[j].stock++;         
                    usrBook[i].stock--;
                    updateFile(books, lineCount);
                    updateUsrData(usrBook, lineCountData, users, userInUse);
                }
            }
        }
        if (!found && usrBook[id-1].stock > 0)
        {
            printf("You have chosen book with ID and returned it: %d. Press Enter to continue...\n", id);
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
        system("clear");
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
                system("clear");
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

void addNewMode() {
    char author[ARRAY_MAX];
    char name[ARRAY_MAX];
    char date[ARRAY_MAX];
    char pages[ARRAY_MAX];
    char isbn[ARRAY_MAX];
    char stock[ARRAY_MAX];
    char choice[ARRAY_MAX];
    system("clear");
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

    printf("\nSuccess!. Press Enter to continue...");
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
        system("clear");
        printf("Enter name: ");
        getUserInput(username, sizeof(username));

        printf("Enter password: ");
        getUserInput(passwd, sizeof(passwd));
        for (i = 0; i < lineCountPasswd; i++) {
            if (strcmp(users[i].name, username) == 0 && strcmp(users[i].passwd, passwd) == 0 && strcmp(users[i].name, "admin") == 0) {
                found = 1;
                renderMainMenuAdmin(users, i);
                return;
            }
            if (strcmp(users[i].name, username) == 0 && strcmp(users[i].passwd, passwd) == 0 && strcmp(users[i].name, "admin") != 0) {
                found = 1;
                renderMainMenuUser(users, lineCountPasswd, i);
                return;
            }
        }
        if (!found) 
        {
            attempts--;
            printf("\nInvalid username or password, %d attempts left. Press Enter to try again.\n", attempts);
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
        system("clear");
        printf("Enter new name: ");
        getUserInput(name, sizeof(name));
        nameExists = 0;
        for (i = 0; i < lineCountPasswd; i++) {
            if (strcmp(users[i].name, name) == 0) {
                printf("Username already exists! Try again.\n");
                getUserInput(choice, sizeof(choice));
                nameExists = 1;
                break;
            }
        }
        if (nameExists) continue;

        printf("Enter new password: ");
        getUserInput(passwd, sizeof(passwd));

        printf("Confirm new password: ");
        getUserInput(passwd2, sizeof(passwd2));

        if (strcmp(passwd, passwd2) != 0) {
            printf("Passwords do not match! Try again.\n");
            getUserInput(choice, sizeof(choice));
            continue;
        }
        appendToPasswd(name, passwd);

        printf("User created successfully!\n");
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
        system("clear");
        printf("1. CURRENT NAME: %s, 2. CURRENT PASSWORD: %s 3. DELETE USER\n",  users[userInUse].name, users[userInUse].passwd);
        printf("Enter what you want to do or 0 to finish: ");
        getUserInput(choice, sizeof(choice));
        switch (choice[0]) {
            case '0':
                return;
            case '1':
                printf("Enter new name: ");
                getUserInput(choice, sizeof(choice));
                for (i = 0; i < lineCountPasswd; i++) {
                    if (strcmp(users[i].name, choice) == 0) {
                        printf("Username already exists! Try again.\n");
                        getUserInput(choice, sizeof(choice));
                        nameExists = 1;
                        break;
                    }
                }
                if (nameExists == 1) break;
                else {
                    strcpy(users[userInUse].name, choice);
                    updateFileUser(users, lineCountPasswd);
                    printf("Changes saved! Press Enter to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    break;
                }
            case '2':
                printf("Enter new password: ");
                getUserInput(choice, sizeof(choice));

                printf("Confirm new password: ");
                getUserInput(passwd, sizeof(passwd));

                if (strcmp(passwd, choice) != 0) {
                    printf("Passwords do not match! Try again.\n");
                    getUserInput(choice, sizeof(choice));
                    break;
                } else {
                    strcpy(users[userInUse].passwd, choice);
                    updateFileUser(users, lineCountPasswd);
                    printf("Changes saved! Press Enter to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    break;
                }
            case '3':
                printf("Are you really want to delete user? (y/n): ");
                getUserInput(choice, sizeof(choice));
                if (choice[0]=='y')
                {
                    users[userInUse].deleted = 1;
                    updateFileUser(users, lineCountPasswd);
                    printf("Changes saved! Press Enter to logout...\n");
                    getUserInput(choice, sizeof(choice));
                    return;
                } else {
                    printf("Deletion canceled! Press Enter to continue...\n");
                    getUserInput(choice, sizeof(choice));
                    break;
                }
            default:
                printf("Wrong input! Press Enter to try again.\n");
                getUserInput(choice, sizeof(choice));
                break;
        }
    }
}