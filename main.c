#include <stdio.h>
#include <stdlib.h>
#include "booksStruct.h"

int main(void) {
    char *filename = "books.txt";
    
    /*
    char *filename = NULL;
    enterFileName(&filename);
    */
    
    char **buffer = NULL;
    unsigned short lineCount = 0;

    readFile(filename, &lineCount, &buffer);
    
    Book *books = malloc(lineCount * sizeof(Book));
    if (books == NULL) exit(9);
    
    initializeBooks(books, buffer, lineCount);
    createFileAuthor(books, lineCount);

    renderMenu(books, lineCount);
    printf("\n");




    clearMem(books, lineCount, filename, buffer);

    printf("Done!\n");
    return 0;
}

