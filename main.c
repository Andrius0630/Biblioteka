#include <stdio.h>
#include <stdlib.h>
#include "booksStruct.h"

int main(void) {
    /*
    char *filename = NULL;
    enterFileName(&filename);
    */

    
    char **bufferPasswd = NULL;
    unsigned short lineCountPasswd = 0, i = 0;
    
    readFilePasswd(&lineCountPasswd, &bufferPasswd);
    
    User *users = malloc(lineCountPasswd * sizeof(User));
    if (users == NULL) exit(9);
    
    /*createFileAuthor(books, lineCount);*/
    initializePasswd(users, bufferPasswd, lineCountPasswd);
    renderLogIn(users, lineCountPasswd);




    
    for (i = 0; i < lineCountPasswd; i++) {
        free(bufferPasswd[i]);
    }

    
    free(bufferPasswd);
    
    free(users);
    /*nufree(filenameUserData);
    free(filenamePasswd);*/


    printf("Done!\n");
    return 0;
}

