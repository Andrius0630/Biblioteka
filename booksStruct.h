#define ARRAY_MAX 100
#define ISBN_MAX 14
#define READ_SIZE 50
#define BOOKS_FILE "books.txt"
#define PASSWD_FILE "passwd"

typedef struct
{
    unsigned short id;
    char author[ARRAY_MAX];
    char name[ARRAY_MAX];
    unsigned short date;
    unsigned short pages;
    char mentioned;
    char isbn[ISBN_MAX];
    unsigned short stock;
}Book;

typedef struct
{
    unsigned short id;
    char author[ARRAY_MAX];
    char name[ARRAY_MAX];
    char isbn[ISBN_MAX];
    unsigned short stock;
}Data;

typedef struct
{
    char name[ARRAY_MAX];
    char passwd[ARRAY_MAX];
}User;

void renderMainMenuAdmin(User *users, unsigned short userInUse);
void renderMainMenuUser(User *users, unsigned short userInUse);
void getUserInput(char *buffer, unsigned short size);

void findBook(Book *books, unsigned short lineCount);
void takeBook(Book *books, unsigned short lineCount);
void returnBook(Book *books, unsigned short lineCount);
void listBooks(Book *books, unsigned short lineCount);

void renderLogIn(User *users, unsigned short lineCountPasswd);
void loginUser(User *users, unsigned short lineCountPasswd);
void modifyMode(Book *books, unsigned short lineCount);
void addNewMode();
void createUser();





void readFile(unsigned short *lineCount, char ***buffer);
void readFilePasswd(unsigned short *lineCountPasswd, char ***bufferPasswd);
void initializePasswd(User *users, char **bufferPasswd, unsigned short lineCountPasswd);
/*void enterFileName(char **filename);*/
void initializeBooks(Book *books, char **buffer, unsigned short lineCount);
/*void createFileAuthor(Book *books, unsigned short lineCount);*/
void updateFile(Book *books, unsigned short lineCount);
void appendToFile(char *author, char *name, char *date, char *pages, char *isbn, char *stock);