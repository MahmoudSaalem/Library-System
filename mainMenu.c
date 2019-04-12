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
extern int arrayCount;
extern int currentID;
extern char numTest[20];
extern int NumOfUser;
extern int runs;
extern user users[MaxNumOfUsers];

extern book library[MaxNumOfUsers];
extern int BooksNO;
extern int bosearch;
extern int bofound;
extern FILE *fbook;
extern book *search_results[10];

extern Borrowed bBooks[MaxNumOfUsers];
extern int borrowedNo;
extern int day,month,year;
extern FILE *fborrowed;
extern Borrowed *Isbnsearch[MaxNumOfUsers];

void arrowHere(int realposition, int arrowposition)
{
    if ( realposition == arrowposition)
    {
        color(15);
    }
    else
    {
        color(8);
    }
}
void mainmenu()
{
    system("CLS");
    setcoordinates(60,1);
    color(14);
    currentDate(&day,&month,&year);
    printf("Current date: %d/%d/%d",day,month,year);
    int position=1;
    char Keypressed=0;
    setcoordinates(0,0);
    color(10);
    printf("Use arrows");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Book Management");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Member Management");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Borrow Management");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Administrative actions");
        setcoordinates(0,5);
        arrowHere(5,position);
        printf("5.Save Changes");
        setcoordinates(0,6);
        arrowHere(6,position);
        printf("6.Exit");
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 6)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(position==1)
        booksmenu();
    else if(position == 2)
        membersmenu();
    else if(position == 3)
        borrowmenu();
    else if(position == 4)
        administrativemenu();
    else if(position ==5)
    {
        save_books();
        saveToFile();
        save_borrowed();
        mainmenu();
    }
    else if(position == 6)
        exitmenu();
}
void booksmenu()
{
    system("CLS");
    int position =1;
    char Keypressed=0;
    setcoordinates(0,0);
    color(10);
    printf("Use arrows");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Insert a new book");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Search for a book");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Add new copy");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Edit book");
        setcoordinates(0,5);
        arrowHere(5,position);
        printf("5.Delete book");
        setcoordinates(0,6);
        arrowHere(6,position);
        printf("6.Show all books");
        setcoordinates(0,7);
        arrowHere(7,position);
        printf("7.Back");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 7)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(Keypressed==(char)13 && position == 7)
        mainmenu();
    if(position==1)
        insert_book();
    else if(position==2)
        searchMenu(0);
    else if(position==3)
        searchMenu(1);
    else if(position==4)
        searchMenu(4);
    else if(position==5)
        searchMenu(2);
    else if(position==6)
        print_books();
}
void membersmenu()
{
    system("CLS");
    int position = 1;
    char Keypressed=0;
    setcoordinates(0,0);
    color(10);
    printf("Use arrows");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Registration");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Remove member");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Edit member");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Print all Data");
        setcoordinates(0,5);
        arrowHere(5,position);
        printf("5.Back");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 5)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(Keypressed==(char)13 && position == 5)
        mainmenu();
    if(position==1)
        addUser();
    else if(position==2)
        deleteUser();
    else if(position==3)
        editUser();
    else if(position==4)
        printArray();
}
void administrativemenu()
{
    system("CLS");
    int position = 1;
    char Keypressed=0;
    setcoordinates(0,0);
    color(10);
    printf("Use arrows");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Overdue Books");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Popular books");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Back");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 3)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(Keypressed==(char)13 && position == 3)
        mainmenu();
    if(position==2)
        popular_books();
    else if(position==1)
        overdueBooks();
}
void exitmenu()
{
    system("CLS");
    int position = 1;
    char Keypressed=0;
    setcoordinates(0,0);
    color(10);
    printf("Use arrows");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Save and Exit");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Exit without saving");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Back");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 3)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(Keypressed==(char)13 && position == 3)
        mainmenu();
    if(position==2)
        exit(0);
    else if(position==1)
    {
        saveToFile();
        save_books();
        save_borrowed();
        exit(0);
    }
}
