#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booksStruct.h"

void renderMenu(Book *books, unsigned short lineCount) {
    system("clear");
    printf("Biblioteka\n\n\n1.Find book by name\n2.Find book using ISBN\n3.Take book\n4.Return book\n5.List all books available\n\n\n6.Modify mode\n7.Change user\n8.Exit\n\n\n");

    printf("Enter a number: ");
    char choice = getc(stdin);
    switch (choice) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            listBooks(books, lineCount);
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            exit(0);
            break;
        default:
            printf("Wrong input!\n");
            break;
    }
}

void findBook(unsigned short lineCount){
    unsigned short size = 20, i = 0;
    char c = 1;
    char **searchWord = malloc(size * sizeof(char));
    if (*searchWord == NULL) exit(1);
    char *newsearchWord = NULL;
    system("clear");
    printf("Search for...: ");
    while (c)
    {
        c = getc(stdin);
        if(c == '\n' || c == EOF) c = 0;
        if (i >= size) {
            size += 5;
            newsearchWord = realloc(*searchWord, size * sizeof(char));
            if (newsearchWord == NULL)
            {
                free(*searchWord);
                exit(2);
            }
            *searchWord = newsearchWord;
        }
        (*searchWord)[i++] = c;
    }
    (*searchWord)[i - 1] = '\0';

    for (i = 0; i < lineCount; i++)
    {
        if (strcmp(books[i].author, searchWord) == 0 || strcmp(books[i].name, searchWord) == 0) {
            printf("%d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n", i+1, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
        }
    }
    free(searchWord);
    free(*searchWord);
}

void findBookISBN() {

    
}

void takeBook(){
    
}

void returnBook(){
    
}


void listBooks(Book *books, unsigned short lineCount) {
    system("clear");
    printf("Available books:\n");
    unsigned short i = 0;
    for (i = 0; i < lineCount; i++)
    {
        printf("%d. AUTHOR: %s, NAME: %s, PUBLISHED IN: %d, PAGES: %d, ISBN: %s, IN STOCK: %d\n", i+1, books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);

    }
    
}