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

void printBorrowed()
{
    system("cls");
    int i;
    char Keypressed=0;
    if(borrowedNo==0)
    {
        color(12);
        printf("Sorry, No data in our system, yet!\n");
        color(14);
        printf("Press any key to go back to main menu ..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }
    else
    {
        color(15);
        for(i=0; i<borrowedNo; i++)
        {
            color(10);
            printf("Book[%d]",i+1);
            color(15);
            printf("\nBook's ISBN: %s",bBooks[i].bookISBN);
            printf("\nUser's ID: %d",bBooks[i].memberID);
            printf("\nBook's Issued date: %d/%d/%d",bBooks[i].issued.day,bBooks[i].issued.month,bBooks[i].issued.year);
            printf("\nBook's due to return date: %d/%d/%d",bBooks[i].duetoreturn.day,bBooks[i].duetoreturn.month,bBooks[i].duetoreturn.year);
            printf("\nBook's return date: %d/%d/%d\n",bBooks[i].returned.day,bBooks[i].returned.month,bBooks[i].returned.year);
        }
        color(14);
        printf("Press any key to go back to main menu ..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }

}
void load_borrowed()
{
    int n=0;
    FILE *fborrowed = fopen("borrowed.txt","r");
    while(!feof(fborrowed))
    {
        fscanf(fborrowed,"%[^,],",bBooks[n].bookISBN);
        fscanf(fborrowed,"%d,",&bBooks[n].memberID);
        fscanf(fborrowed,"%d/%d/%d,",&bBooks[n].issued.day,&bBooks[n].issued.month,&bBooks[n].issued.year);
        fscanf(fborrowed,"%d/%d/%d,",&bBooks[n].duetoreturn.day,&bBooks[n].duetoreturn.month,&bBooks[n].duetoreturn.year);
        fscanf(fborrowed,"%d/%d/%d\n",&bBooks[n].returned.day,&bBooks[n].returned.month,&bBooks[n].returned.year);
        n++;
    }
    n--;
    borrowedNo=n;
    fclose(fborrowed);
}

void save_borrowed()
{
    FILE *fborrowed;
    fborrowed = fopen("borrowed.txt", "w"); // "w" because every time the array changes the file change with it overwriting the old data
    int n=0;
    for(n=0; n<borrowedNo; n++)
    {
        fprintf(fborrowed,"%s,",bBooks[n].bookISBN);
        fprintf(fborrowed,"%d,",bBooks[n].memberID);
        fprintf(fborrowed,"%d/%d/%d,",bBooks[n].issued.day,bBooks[n].issued.month,bBooks[n].issued.year);
        fprintf(fborrowed,"%d/%d/%d,",bBooks[n].duetoreturn.day,bBooks[n].duetoreturn.month,bBooks[n].duetoreturn.year);
        fprintf(fborrowed,"%d/%d/%d\n",bBooks[n].returned.day,bBooks[n].returned.month,bBooks[n].returned.year);
    }
    fclose(fborrowed);
}
void searchb4Borrow()
{
    searchMenu(3);
}

void Borrow_book(book *temp)
{
    int position=1;
    char Keypressed=0;
    int id;
    color(15);
    printf("Enter your ID: ");
    scanf("%d",&id);
    int j;
    j = userIDverfication(id);
    if(j==-1)
    {
        color(12);
        printf("You can't borrow more than 3 books\n");
        color(14);
        printf("Press any key to go back to main menu ..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }
    while(j==0)
    {
        color(15);
        printf("You've entered a wrong ID.\n");
        system("cls");
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,0);
            arrowHere(1,position);
            printf("1.Enter a new id");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.Back to borrow menu");
            Keypressed=_getch();
            if(Keypressed==(char)224)
            {
                Keypressed = _getch();
                if(Keypressed == (char)80 && position != 2)
                    position++;
                else if(Keypressed == (char)72 && position != 1)
                    position--;
                else
                    position = position;
            }
        }
        if(position==1)
        {
            system("cls");
            color(15);
            printf("Enter your id:");
            scanf("%d",&id);
            j = userIDverfication(id);
            if(j==-1)
            {
                color(15);
                printf("You cant borrow more than 3 books");
                borrowmenu();
            }
        }
        else if(position==2)
            borrowmenu();
    }
    int rDay,rMonth,rYear;
    color(15);
    printf("Enter the date due to return the book (DD/MM/YYYY): ");
    scanf("%d/%d/%d",&rDay,&rMonth,&rYear);
    while(!dateValidation(rDay, rMonth, rYear) || !duetoReturnDateValidation(rDay, rMonth, rYear))
    {
        color(12);
        printf("This is not a valid date , please provide a valid one!\n");
        color(15);
        printf("Date due to return the book: ");
        scanf("%d/%d/%d",&rDay,&rMonth,&rYear);
    }
    bBooks[borrowedNo].duetoreturn.day=rDay;
    bBooks[borrowedNo].duetoreturn.month=rMonth;
    bBooks[borrowedNo].duetoreturn.year=rYear;
    currentDate(&day,&month,&year);
    bBooks[borrowedNo].issued.day=day;
    bBooks[borrowedNo].issued.month=month;
    bBooks[borrowedNo].issued.year=year;
    temp->nBorrowed++;
    temp->available--;
    temp->aBorrows++;
    strcpy(bBooks[borrowedNo].bookISBN,temp->isbn);
    bBooks[borrowedNo].memberID=id;
    bBooks[borrowedNo].returned.day=0;
    bBooks[borrowedNo].returned.month=0;
    bBooks[borrowedNo].returned.year=0;
    borrowedNo++;
}
void borrowmenu()
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
        printf("1.Borrow a book");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Return a book");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Print all borrowed books");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Back");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 4)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(Keypressed==(char)13 && position == 4)
        mainmenu();
    if(position==1)
        searchb4Borrow();
    else if(position==2)
        return_date();
    else if(position==3)
        printBorrowed();
}
