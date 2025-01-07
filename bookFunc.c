#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booksStruct.h"

/*void enterFileName(char **filename) {
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
}*/

void readFile(unsigned short *lineCount, char ***buffer) {
    unsigned short i = 0, size = READ_SIZE;
    char c = 1;
    char *tmp = NULL;
    char *line = NULL;
    FILE *fptr = fopen(BOOKS_FILE, "r");
    if (fptr == NULL) {printf("Error! File %s is not found.\n", BOOKS_FILE);exit(3);}
    while (1) {
        size = READ_SIZE;
        i = 0;
        line = malloc(size * sizeof(char));
        if (line == NULL) {
            fclose(fptr);
            exit(4);
        }
        while ((c = fgetc(fptr)) != '\n' && c != EOF) {
            if(i >= size) {
                size += 10;
                tmp = realloc(line, size * sizeof(char));
                if(tmp == NULL) {free(line); fclose(fptr); exit(5);}
                line = tmp;
            }
            line[i++] = c;
        }
        line[i] = '\0';
        if (i == 0) {free(line); if (c == EOF) break; continue;}
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
        if (buffer[i][0] == '\0') continue;
        books[i].id = i+1;
        token = strtok(buffer[i], ",");
        strncpy(books[i].author, token, ARRAY_MAX - 1);
        books[i].author[ARRAY_MAX - 1] = '\0';


        token = strtok(NULL, ",");
        strncpy(books[i].name, token, ARRAY_MAX - 1);
        books[i].name[ARRAY_MAX - 1] = '\0';

        books[i].date = atoi(strtok(NULL, ","));
        books[i].pages = atoi(strtok(NULL, ","));
        books[i].mentioned = 0;
        token = strtok(NULL, ",");
        strncpy(books[i].isbn, token, ISBN_MAX);
        books[i].isbn[ARRAY_MAX - 1] = '\0';
        books[i].stock = atoi(strtok(NULL, ","));
    }
}



/*void createFileAuthor(Book *books, unsigned short lineCount) {
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
}*/

void readFileUsr(unsigned short *lineCountData, char ***usrBuffer, User *users, unsigned short userInUse) {
    char filename[ARRAY_MAX];
    strcpy(filename, "userFiles/");
    strcat(filename, users[userInUse].name);
    unsigned short i = 0, size = READ_SIZE;
    char c = 1;
    char *tmp = NULL;
    char *line = NULL;
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        /*printf("Error! File %s is not found.\n", filename);*/
        FILE *fptr2 = fopen(filename, "w");
        fclose(fptr2);
        fptr = fopen(filename, "r");
    }
    while (1) {
        size = READ_SIZE;
        i = 0;
        line = malloc(size * sizeof(char));
        if (line == NULL) {
            fclose(fptr);
            exit(4);
        }
        while ((c = fgetc(fptr)) != '\n' && c != EOF) {
            if(i >= size) {
                size += 10;
                tmp = realloc(line, size * sizeof(char));
                if(tmp == NULL) {free(line); fclose(fptr); exit(5);}
                line = tmp;
            }
            line[i++] = c;
        }
        line[i] = '\0';
        if (i == 0) {free(line); if (c == EOF) break; continue;}
        *usrBuffer = realloc(*usrBuffer, sizeof(char*) * (*lineCountData + 1));
        if (*usrBuffer == NULL) {free(line); fclose(fptr); exit(7);}
        (*usrBuffer)[*lineCountData] = line;
        (*lineCountData)++;
        if(c == EOF) break;
    }
    fclose(fptr);
}

void initializeUsrData(Data *usrBook, char **usrBuffer, unsigned short lineCountData) {
    unsigned short i = 0;
    char *token;
    for (i = 0; i < lineCountData; i++) {
        if (usrBuffer[i][0] == '\0') continue;
        usrBook[i].id = i+1;
        token = strtok(usrBuffer[i], ",");
        strncpy(usrBook[i].author, token, ARRAY_MAX - 1);
        usrBook[i].author[ARRAY_MAX - 1] = '\0';


        token = strtok(NULL, ",");
        strncpy(usrBook[i].name, token, ARRAY_MAX - 1);
        usrBook[i].name[ARRAY_MAX - 1] = '\0';

        usrBook[i].date = atoi(strtok(NULL, ","));
        usrBook[i].pages = atoi(strtok(NULL, ","));
        token = strtok(NULL, ",");
        strncpy(usrBook[i].isbn, token, ISBN_MAX);
        usrBook[i].isbn[ARRAY_MAX - 1] = '\0';
        usrBook[i].stock = atoi(strtok(NULL, ","));
    }
}

void updateUsrData(Data *usrBook, unsigned short lineCountData, User *users, unsigned short userInUse) {
    char filename[ARRAY_MAX];
    strcpy(filename, "userFiles/");
    strcat(filename, users[userInUse].name);
    unsigned short i = 0;
    FILE *fptr = fopen(filename, "w");
    if (fptr != NULL) {
        for (i = 0; i < lineCountData; i++) {
            if (usrBook[i].stock > 0) fprintf(fptr, "%s,%s,%d,%d,%s,%d\n", usrBook[i].author, usrBook[i].name, usrBook[i].date, usrBook[i].pages, usrBook[i].isbn, usrBook[i].stock);
        }    
        fclose(fptr);
    } else exit(8);
}

void updateFile(Book *books, unsigned short lineCount) {
    unsigned short i = 0;
    FILE *fptr = fopen(BOOKS_FILE, "w");
    if (fptr != NULL) {
        for (i = 0; i < lineCount; i++) {
            if (books[i].stock > 0) fprintf(fptr, "%s,%s,%d,%d,%s,%d\n", books[i].author, books[i].name, books[i].date, books[i].pages, books[i].isbn, books[i].stock);
        }
    } else exit(8);
    fclose(fptr);
}

void updateFileUser(User *users, unsigned short lineCountPasswd) {
    unsigned short i = 0;
    FILE *fptr = fopen(PASSWD_FILE, "w");
    if (fptr != NULL) {
        for (i = 0; i < lineCountPasswd; i++) {
            if (users[i].deleted != 1) fprintf(fptr, "%s,%s\n", users[i].name, users[i].passwd);
        }
    } else exit(8);
    fclose(fptr);
}

void appendToFile(char *author, char *name, char *date, char *pages, char *isbn, char *stock) {
    FILE *fptr = fopen(BOOKS_FILE, "a");
    
    if (fptr != NULL) {
        if (atoi(stock) > 0) {
            fprintf(fptr, "\n%s,%s,%s,%s,%s,%s", author, name, date, pages, isbn, stock);
        } 
    } else exit(8);
    fclose(fptr);
}

void appendToUsr(char *author, char *name, char *date, char *pages, char *isbn, char *stock, User *users, unsigned short userInUse) {
    char filename[ARRAY_MAX];
    strcpy(filename, "userFiles/");
    strcat(filename, users[userInUse].name);
    FILE *fptr = fopen(filename, "a");
    
    
    if (fptr != NULL) {
        if (atoi(stock) > 0) {
            fprintf(fptr, "\n%s,%s,%s,%s,%s,%s", author, name, date, pages, isbn, stock);
        } 
    } else exit(8);
    fclose(fptr);
}

void appendToPasswd(char *name, char *passwd) {
    FILE *fptr = fopen(PASSWD_FILE, "a");
    
    if (fptr != NULL) {
        fprintf(fptr, "%s,%s\n", name, passwd);
    } else exit(8);
    fclose(fptr);
}

void readFilePasswd(unsigned short *lineCountPasswd, char ***bufferPasswd) {
    unsigned short i = 0, size = READ_SIZE;
    char c = 1;
    char *tmp = NULL;
    char *line = NULL;
    FILE *fptr = fopen(PASSWD_FILE, "r");
    if (fptr == NULL) {printf("Error! File %s is not found.\n", PASSWD_FILE); exit(3);}
    while (1) {
        size = READ_SIZE;
        i = 0;
        line = malloc(size * sizeof(char));
        if (line == NULL) {
            fclose(fptr);
            exit(4);
        }
        while ((c = fgetc(fptr)) != '\n' && c != EOF) {
            if(i >= size) {
                size += 10;
                tmp = realloc(line, size * sizeof(char));
                if(tmp == NULL) {free(line); fclose(fptr); exit(5);}
                line = tmp;
            }
            line[i++] = c;
        }
        line[i] = '\0';
        if (i == 0) {free(line); if (c == EOF) break; continue;}
        *bufferPasswd = realloc(*bufferPasswd, sizeof(char*) * (*lineCountPasswd + 1));
        if (*bufferPasswd == NULL) {free(line); fclose(fptr); exit(7);}
        (*bufferPasswd)[*lineCountPasswd] = line;
        (*lineCountPasswd)++;
        if(c == EOF) break;
    }
    fclose(fptr);
}

void initializePasswd(User *users, char **bufferPasswd, unsigned short lineCountPasswd) {
    unsigned short i = 0;
    char *token;
    for (i = 0; i < lineCountPasswd; i++) {
        if (bufferPasswd[i][0] == '\0') continue;
        token = strtok(bufferPasswd[i], ",");
        strncpy(users[i].name, token, ARRAY_MAX - 1);
        users[i].name[ARRAY_MAX - 1] = '\0';

        token = strtok(NULL, ",");
        strncpy(users[i].passwd, token, ARRAY_MAX - 1);
        users[i].passwd[ARRAY_MAX - 1] = '\0';
        users[i].deleted = 0;
    }
}

void encrypt(char *password, short key) {
    unsigned char i = 0;
    for (i = 0; i < strlen(password); i++) {
        password[i] -= key;
    }
}
void decrypt(char *password, short key) {
    unsigned char i = 0;
    for (i = 0; i < strlen(password); i++) {
        password[i] += key;
    }
}