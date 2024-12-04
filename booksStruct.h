#define ARRAY_MAX 100
#define ISBN_MAX 14

typedef struct
{
    char author[ARRAY_MAX];
    char name[ARRAY_MAX];
    unsigned short date;
    unsigned short pages;
    char mentioned;
    char isbn[ISBN_MAX];
    unsigned short stock;
}Book;

extern Book *books;

void renderMenu(Book *books, unsigned short lineCount);
void listBooks(Book *books, unsigned short lineCount);
void readFile(char *filename, unsigned short *lineCount, char ***buffer);
void enterFileName(char **filename);
void initializeBooks(Book *books, char **buffer, unsigned short lineCount);
void createFileAuthor(Book *books, unsigned short lineCount);
void clearMem(Book *books, unsigned short lineCount, char *filename, char **buffer);

