#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booksStruct.h"

void enterFileName(char **filename) {
    unsigned short size = 10, i = 0;
    char c = 1;
    *filename = malloc(size * sizeof(char));
    if(*filename == NULL) exit(1);
    char *newFilename = NULL;
    
    printf("Please enter filename: ");
    while(c) {
        c = getc(stdin);
        if(c == '\n' || c == EOF) c = 0;
        if(i >= size) {
            size += 5;
            newFilename = realloc(*filename, size * sizeof(char));
            if(newFilename == NULL) {
                free(*filename);
                exit(2);
            }
            *filename = newFilename;
        }
        (*filename)[i++] = c;
    }
    (*filename)[i - 1] = '\0';
}

void readFile(char *filename, unsigned short *lineCount, char ***buffer) {
    unsigned short i = 0, size = 50;
    char c = 1;
    char *tmp = NULL;
    char *line = NULL;
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {printf("Error! File %s is not found.\n", filename); free(filename); exit(3);}
    while (1) {
        size = 50;
        i = 0;
        line = malloc(size * sizeof(char));
        if (line == NULL) {
            fclose(fptr);
            exit(4);
        }
        while ((c = fgetc(fptr)) != '\n' && c != EOF) {
            if(i > size) {
                size += 10;
                tmp = realloc(line, size * sizeof(char));
                if(tmp == NULL) {free(line); fclose(fptr); exit(5);}
                line = tmp;
            }
            line[i++] = c;
        }
        line[i] = '\0';
        if(c == EOF && i == 0) {free(line); exit(6);}
        *buffer = realloc(*buffer, sizeof(char*) * (*lineCount + 1));
        if (*buffer == NULL) {free(line); fclose(fptr); exit(7);}
        (*buffer)[*lineCount] = line;
        (*lineCount)++;
        if(c == EOF) break;
    }
    fclose(fptr);
}

void initializeBooks(Book *books, char **buffer, unsigned short lineCount) {
    unsigned short i = 0;
    char *token;
    for (i = 0; i < lineCount; i++) {
        token = strtok(buffer[i], ",");
        strncpy(books[i].author, token, ARRAY_MAX - 1);

        token = strtok(NULL, ",");
        strncpy(books[i].name, token, ARRAY_MAX - 1);


        books[i].date = atoi(strtok(NULL, ","));
        books[i].pages = atoi(strtok(NULL, ","));
        books[i].mentioned = 0;
        token = strtok(NULL, ",");
        strncpy(books[i].isbn, token, ISBN_MAX);
        books[i].stock = atoi(strtok(NULL, ","));
    }
}



void createFileAuthor(Book *books, unsigned short lineCount) {
    unsigned short i = 0, j = 0;
    for (i = 0; i < lineCount; i++) {
        for (j = 0; j < lineCount; j++) {
            if (strcmp(books[i].author, books[j].author) == 0 && strcmp(books[i].name, books[j].name) == 0 && books[i].mentioned == 0) {
                FILE *fptr = fopen(books[i].author, "a");
                if (fptr != NULL) {
                    fprintf(fptr, "%s,%s,%d,%d,%s,%d\n", books[j].author, books[j].name, books[j].date, books[j].pages, books[j].isbn, books[j].stock);
                    fclose(fptr);
                    books[i].mentioned = 1;
                } else exit(8);
            } else continue;
        }
    }
    
}

void clearMem(Book *books, unsigned short lineCount, char *filename, char **buffer) {
    unsigned short i = 0;
    for (i = 0; i < lineCount; i++) {
        free(buffer[i]);
    }
    free(buffer);
    free(books);
    /*free(filename);*/
}