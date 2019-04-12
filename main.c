#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "struct.h"
#include "members.h"
#include "books.h"
#include "borrows.h"
#include "validation.h"
#include "mainMenu.h"
#include "Consfunctions.h"
#define MaxNumOfUsers 100

/// Global Variables
int arrayCount=0;
int currentID=1;
char numTest[20];
int NumOfUser;
int runs=0;
user users[MaxNumOfUsers];

book library[MaxNumOfUsers];
int BooksNO=-1;
int bosearch=-1;
int bofound;
FILE *fbook;
book *search_results[10];

Borrowed bBooks[MaxNumOfUsers];
int borrowedNo=0;
int day,month,year;
FILE *fborrowed;
Borrowed *Isbnsearch[MaxNumOfUsers];

char input_receiver[MaxNumOfUsers]; // Receive inputs and Enter a series of validation functions to return a valid input
char validISBN[14];

int main()
{
    filesCheck();
    fillArray();
    load_books();
    load_borrowed();
    system("title Library System");
    cursor(0);
    mainmenu();
    return 0;
}
