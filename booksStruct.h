#define ARRAY_MAX 100

typedef struct
{
    char author[ARRAY_MAX];
    char name[ARRAY_MAX];
    unsigned short date;
    unsigned short pages;
    char mentioned;
}Book;

void readFile(char *filename, unsigned short *lineCount, char ***buffer);
void enterFileName(char **filename);
void initializeBooks(Book *books, char **buffer, unsigned short lineCount);
void createFileAuthor(Book *books, unsigned short lineCount);
void clearMem(Book *books, unsigned short lineCount, char *filename, char **buffer);

