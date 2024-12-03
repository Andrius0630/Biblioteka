#include <stdio.h>
#include <stdlib.h>
#include "booksStruct.h"

/*
+    Iš tekstinio failo nuskaitomos eilutės, kur kiekvienoje eilutėje yra įrašas apie knygą (autorius, pavadinimas, išleidimo data, puslapių skaičius).
+    Išvesti į atskirus failus knygas pagal autorius.
+    Užduočiai reikalingas duomenų struktūras aprašome antraštės faile.
+    Užduočiai reikalingiems masyvams atmintis turi būti išskiriama dinamiškai.
+    Duomenų įvedimas realizuojamas iš tekstinio failo, kurio pavadinimas įvedamas programos veikimo metu arba paduodant jį kaip parametrą paleidžiant programą (turi būti realizuota failo egzistavimo kontrolė).
+    Programą turi sudaryti mažiausiai dvi funkcijos (be main).
*/




int main(void) {    
    char *filename = NULL;
    
    enterFileName(&filename);
    
    char **buffer = NULL;
    unsigned short lineCount = 0;

    readFile(filename, &lineCount, &buffer);
    
    Book *books = malloc(lineCount * sizeof(Book));
    if (books == NULL) exit(1);
    
    initializeBooks(books, buffer, lineCount);
    createFileAuthor(books, lineCount);
    clearMem(books, lineCount, filename, buffer);

    printf("Done!\n");
    return 0;
}

