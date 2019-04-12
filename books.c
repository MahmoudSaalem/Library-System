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

void load_books()
{
    FILE* fbook = fopen("Books.txt","r");
    if (fbook==NULL)
    {
        FILE *fbook = fopen("Books.txt", "w");
        fclose(fbook);
        printf("There are no books to display");
        return ;
    }
    fbook = fopen("Books.txt","r");
    int i=0;
    while(!feof(fbook))
    {
        fscanf(fbook,"%d,",&library[i].on);
        if (library[i].on == 1)
        {
            fscanf(fbook,"%[^,],",library[i].title);
            fscanf(fbook,"%[^,],",library[i].author);
            fscanf(fbook,"%[^,],",library[i].publisher);
            fscanf(fbook,"%[^,],",library[i].isbn);
            fscanf(fbook,"%d/%d/%d,",&library[i].dateofpublication.day,&library[i].dateofpublication.month,&library[i].dateofpublication.year);
            fscanf(fbook,"%d,",&library[i].copies);
            fscanf(fbook,"%d,",&library[i].available);
            fscanf(fbook,"%[^,],",library[i].category);
            fscanf(fbook,"%d,",&library[i].nBorrowed);
            fscanf(fbook,"%d\n",&library[i].aBorrows);
            i++;
        }
    }
    i--;
    BooksNO=i;
    fclose(fbook);
}
void save_books()
{
    FILE *fbook;
    int n;
    fbook = fopen("Books.txt", "w"); // "w" because every time the array changes the file change with it overwriting the old data
    for(n=0; n<=BooksNO; n++)
    {
        if (library[n].on==1)
        {
            fprintf(fbook,"%d,",library[n].on);
            fprintf(fbook,"%s,",library[n].title);
            fprintf(fbook,"%s,",library[n].author);
            fprintf(fbook,"%s,",library[n].publisher);
            fprintf(fbook,"%s,",library[n].isbn);
            fprintf(fbook,"%d/%d/%d,",library[n].dateofpublication.day,library[n].dateofpublication.month,library[n].dateofpublication.year);
            fprintf(fbook,"%d,",library[n].copies);
            fprintf(fbook,"%d,",library[n].available);
            fprintf(fbook,"%s,",library[n].category);
            fprintf(fbook,"%d,",library[n].nBorrowed);
            fprintf(fbook,"%d\n",library[n].aBorrows);
        }
    }
    fclose(fbook);
}
int already_exist(book input)
{
    int i,flag=0;
    for (i=0; i<=BooksNO; i++)
    {
        if (library[i].on == 1)
        {
            if ( atoll(library[i].isbn) == atoll(input.isbn) )
            {
                search_results[0] = &library[i];
                flag=1;
                break;
            }
        }
    }
    if (flag) return 1;
    else return 0;
}
void insert_book()
{
    system("CLS");
    int position=1;
    char Keypressed=0;
    char x[100];
    book input;
    input.on = 1;
    color(15);
    printf("Enter the book title: ");
    fflush(stdin);
    myfgets(x, sizeof(x));
    while(!stringValidation(x)) // Handling Error
    {
        color(12);
        printf("Invalid input! Please enter only alphabets\n");
        color(15);
        printf("Your input: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
    }
    strcpy(input.title,x);
    color(15);
    printf("Enter the Book ISBN: ");
    fflush(stdin);
    strcpy(input.isbn, isbnValidation());
    if(already_exist(input)==1)
    {
        system("cls");
        setcoordinates(0,0);
        color(10);
        printf("Book already exists");
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.Back to book management");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.Back to main menu");
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
            booksmenu();
        else if(position==2)
            mainmenu();
    }
    color(15);
    printf("Enter the author's name: ");
    fflush(stdin);
    myfgets(x, sizeof(x));
    while(!stringValidation(x)) // Handling Error
    {
        color(12);
        printf("Invalid input! Please enter only alphabets\n");
        color(15);
        printf("Your input: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
    }
    strcpy(input.author, x);
    color(15);
    printf("Enter the category of the book: ");
    fflush(stdin);
    myfgets(x, sizeof(x));
    while(!stringValidation(x)) // Handling Error
    {
        color(12);
        printf("Invalid input! Please enter only alphabets\n");
        color(15);
        printf("Your input: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
    }
    strcpy(input.category, x);
    color(15);
    printf("Enter the book publisher: ");
    fflush(stdin);
    myfgets(x, sizeof(x));
    while(!stringValidation(x)) // Handling Error
    {
        color(12);
        printf("Invalid input! Please enter only alphabets\n");
        color(15);
        printf("Your input: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
    }
    strcpy(input.publisher, x);
    color(15);
    printf("Enter the book date of publication(day/month/20xx): ");
    fflush(stdin);
    scanf("%d/%d/%d",&input.dateofpublication.day,&input.dateofpublication.month,&input.dateofpublication.year);
    while(!dateValidation(input.dateofpublication.day,input.dateofpublication.month,input.dateofpublication.year) || !publicationDate(input.dateofpublication.day,input.dateofpublication.month,input.dateofpublication.year))
    {
        color(12);
        printf("This is not a valid date, Please provide a valid one.\n");
        color(15);
        printf("Book Date of Publication: ");
        scanf("%d/%d/%d",&input.dateofpublication.day,&input.dateofpublication.month,&input.dateofpublication.year);
    }
    color(15);
    printf("Enter the available number of copies: ");
    fflush(stdin);
    char copies[100];
    myfgets(copies,sizeof(copies));
    while(!numberValid(copies)||atoi(copies)<1)
    {
        color(12);
        printf("This is not a valid number! Please enter a valid one\n");
        color(15);
        printf("Your input: ");
        fflush(stdin);
        myfgets(copies,sizeof(copies));
    }
    input.copies = atoi(copies);
    input.available = input.copies;
    input.nBorrowed = 0;
    input.aBorrows=0;
    system("CLS");
    setcoordinates(0,0);
    color(10);
    printf("Do you want to save the input book?");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.YES");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.NO");
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
        BooksNO++;
        library[BooksNO].on = input.on;
        library[BooksNO].aBorrows=input.aBorrows;
        strcpy(library[BooksNO].title, input.title);
        strcpy(library[BooksNO].isbn, input.isbn);
        strcpy(library[BooksNO].author, input.author);
        strcpy(library[BooksNO].category, input.category);
        strcpy(library[BooksNO].publisher, input.publisher);
        library[BooksNO].dateofpublication.day = input.dateofpublication.day;
        library[BooksNO].dateofpublication.month = input.dateofpublication.month;
        library[BooksNO].dateofpublication.year = input.dateofpublication.year;
        library[BooksNO].copies = input.copies;
        library[BooksNO].available = input.available;
        library[BooksNO].nBorrowed = input.nBorrowed;
        system("cls");
        setcoordinates(0,0);
        color(10);
        printf("Your book was added successfully.\n");
        position=1;
        Keypressed=0;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.Back to book management menu");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.Back to main menu");
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
            booksmenu();
        else if(position==2)
            mainmenu();
    }
    else
    {
        system("cls");
        color(10);
        printf("Book discarded.\n");
        position=1;
        Keypressed=0;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.Back to book management menu");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.Back to main menu");
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
            booksmenu();
        else if(position==2)
            mainmenu();
    }
}
void searchMenu(int mode)
{
    system("CLS");
    int position =1;
    char Keypressed=0;
    setcoordinates(0,0);
    color(10);
    printf("Use arrows");
    if(mode==1||mode==2||mode==3||mode==4)
    {
        setcoordinates(0,1);
        printf("YOU MUST SEARCH FOR THE BOOK FIRST");
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,2);
            arrowHere(1,position);
            printf("1.Search by ISBN");
            setcoordinates(0,3);
            arrowHere(2,position);
            printf("2.Search by book title");
            setcoordinates(0,4);
            arrowHere(3,position);
            printf("3.Search by author's name");
            setcoordinates(0,5);
            arrowHere(4,position);
            printf("4.Search by category");
            setcoordinates(0,6);
            arrowHere(5,position);
            printf("5.Search by Publisher");
            setcoordinates(0,7);
            arrowHere(6,position);
            printf("6.Multi Search");
            setcoordinates(0,8);
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
    }
    else
    {
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.Search by ISBN");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.Search by book title");
            setcoordinates(0,3);
            arrowHere(3,position);
            printf("3.Search by author's name");
            setcoordinates(0,4);
            arrowHere(4,position);
            printf("4.Search by category");
            setcoordinates(0,5);
            arrowHere(5,position);
            printf("5.Search by publisher");
            setcoordinates(0,6);
            arrowHere(6,position);
            printf("6.Multi Search");
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
    }
    if(Keypressed==(char)13 && position==7)
        booksmenu();
    if(position==1)
        isbn_search(mode);
    else if(position==2)
        string_search(mode,0,library[0].title);
    else if(position==3)
        string_search(mode,0,library[0].author);
    else if(position==4)
        string_search(mode,0,library[0].category);
    else if(position==5)
        string_search(mode,0,library[0].publisher);
    else if(position==6)
        multisearchmenu(mode);
}
void multisearchmenu(int mode)
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
        printf("1.Title + Author");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Title + Category");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Title + Publisher");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Author + Category");
        setcoordinates(0,5);
        arrowHere(5,position);
        printf("5.Author + publisher");
        setcoordinates(0,6);
        arrowHere(6,position);
        printf("6.Category + Publisher");
        setcoordinates(0,7);
        arrowHere(7,position);
        printf("7.Title + Author + Category");
        setcoordinates(0,8);
        arrowHere(8,position);
        printf("8.Title + Author + Publisher");
        setcoordinates(0,9);
        arrowHere(9,position);
        printf("9.Title + Category + Publisher");
        setcoordinates(0,10);
        arrowHere(10,position);
        printf("10.Author + Category + Publisher");
        setcoordinates(0,11);
        arrowHere(11,position);
        printf("11.Title + Author + Category + Publisher");
        setcoordinates(0,12);
        arrowHere(12,position);
        printf("12.Back");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 12)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(Keypressed==(char)13 && position==12)
        searchMenu(mode);
    if(position==1)
        string_search(mode,1,library[0].title); // 3rd parameter has no effect hear
    if(position==2)
        string_search(mode,2,library[0].title); // 3rd parameter has no effect hear
    if(position==3)
        string_search(mode,3,library[0].title); // 3rd parameter has no effect hear
    if(position==4)
        string_search(mode,4,library[0].title); // 3rd parameter has no effect hear
    if(position==5)
        string_search(mode,5,library[0].title); // 3rd parameter has no effect hear
    if(position==6)
        string_search(mode,6,library[0].title); // 3rd parameter has no effect hear
    if(position==7)
        string_search(mode,7,library[0].title); // 3rd parameter has no effect hear
    if(position==8)
        string_search(mode,8,library[0].title); // 3rd parameter has no effect hear
    if(position==9)
        string_search(mode,9,library[0].title); // 3rd parameter has no effect hear
    if(position==10)
        string_search(mode,10,library[0].title); // 3rd parameter has no effect hear
    if(position==11)
        string_search(mode,11,library[0].title); // 3rd parameter has no effect hear
}
void isbn_search(int mode)
{
    char Keypressed = 0;
    system("cls");
    setcoordinates(0,0);
    color(15);
    printf("Enter Book ISBN:");
    fflush(stdin);
    bosearch=0;
    book x;
    strcpy(x.isbn, isbnValidation());
    color(7);
    int i,flag=13;
    for (i=0; i<=BooksNO; i++)
    {
        if (library[i].on == 1)
        {
            if ( atoll(library[i].isbn) == atoll(x.isbn) )
            {
                search_results[0] = &library[i];
                flag=0;
                break;
            }
        }
    }
    if (flag)
    {
        color(12);
        printf("\nBook Not Found.\n");
    }
    else
    {
        system("cls");
        color(10);
        printf("Book Found Successfully!\n\n");
        for (i=0; i<=bosearch; i++)
        {
            color(10);
            printf("Book[%d]",i+1);
            color(15);
            printf("\nBook title: %s",search_results[i]->title);
            printf("\nBoo ISBN: %s",search_results[i]->isbn);
            printf("\nBook Author: %s",search_results[i]->author);
            printf("\nBook Category: %s",search_results[i]->category);
            printf("\nBook Publisher: %s",search_results[i]->publisher);
            printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
            printf("\nBook Copies: %d",search_results[i]->copies);
            printf("\nBook available Copies: %d",search_results[i]->available);
            printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
        }
        fflush(stdin);
        if (mode != 0)
        {
            color(11);
            printf("Enter the index of the book you want to apply changes to: ");
            color(15);
            fflush(stdin);
            myfgets(numTest, 20);
            while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
            {
                color(12);
                printf("Invalid Input!\n");
                fflush(stdin);
                color(11);
                printf("Enter the index of the target book in the list: ");
                color(15);
                myfgets(numTest, 20);
            }
            bofound = atoi(numTest)-1;
        }
        /**/
    }
    if (mode==1) // ADD NEW COPIES FUNCTION
    {
        color(15);
        int new_copies;
        printf("Enter the number of new copies to be added:");
        scanf("%d",&new_copies);
        fflush(stdin);
        while (new_copies<1)
        {
            color(12);
            printf("Invalid Input!\n");
            fflush(stdin);
            printf("Enter a positive number: ");
            scanf("%d", &new_copies);
        }
        search_results[bofound]->copies+=new_copies;
        search_results[bofound]->available+=new_copies;
        color(10);
        printf("Copies added successfully!");
        color(15);
        printf("\nNumber of copies: %d",search_results[bofound]->copies);
        printf("\nNumber of available copies: %d",search_results[bofound]->available);
        color(15);
    }
    else if (mode==2) // DELETE BOOK
    {
        system("cls");
        if (search_results[bofound]->nBorrowed>0)
        {
            setcoordinates(0,0);
            color(12);
            printf("This book is already borrowed by %d users. You Can't Delete it.\n",search_results[bofound]->nBorrowed);
            color(14);
            fflush(stdin);
            printf("\nPress any key to go back to main menu..");
            Keypressed=_getch();
            if(Keypressed)
            mainmenu();
        }
        else
        {
            setcoordinates(0,0);
            color(12);
            printf("Are you sure you want to delete the targeted book?");
            char Keypressed=0;
            int position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,1);
                arrowHere(1,position);
                printf("1.YES");
                setcoordinates(0,2);
                arrowHere(2,position);
                printf("2.NO");
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
            if (position==1)
            {
                search_results[bofound]->on=0;
                color(10);
                printf("\nBook Deleted successfully!\n");
            }
            else if(position==2)
            {
                system("cls");
                Keypressed=0;
                position=1;
                while(Keypressed!=(char)13)
                {
                    setcoordinates(0,0);
                    arrowHere(1,position);
                    printf("1.Back to main menu");
                    setcoordinates(0,1);
                    arrowHere(2,position);
                    printf("2.Back to books menu");
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
                    mainmenu();
                else if(position==2)
                    booksmenu();
            }
            }
    }
    else if(mode==3) //BORROW BOOK
    {
        system("CLS");
        setcoordinates(0,0);
        color(10);
        printf("Borrowing Section\n");
        Borrow_book(search_results[bofound]);
    }
    else if (mode==4) //EDIT BOOK
    {
        system("CLS");
        setcoordinates(0,0);
        color(10);
        printf("Edit book\n");
        edit_book(search_results[bofound]);
    }
    color(14);
    fflush(stdin);
    printf("\nPress any key to go back to main menu..");
    Keypressed=_getch();
    if(Keypressed)
        mainmenu();
}
void string_search(int mode, int search_type, char* y)
{
    char Keypressed=0;
    system("cls");
    setcoordinates(0,0);
    color(15);
    if (search_type==0) // SINGLE SEARCH KEY
    {
        char x[100];
        printf("Enter Search Key:");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        bosearch=-1;
        char* pt=y;
        int a,b,f1;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0;
                for (a=0; a<strlen(pt); a++)
                {
                    if (pt[a]==x[0] || pt[a]==x[0]+32 || pt[a]==x[0]-32)
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (pt[a]==x[b] || pt[a]==x[b]+32 || pt[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (pt[a]==x[0] || pt[a]==x[0]+32 || pt[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                        if (f1)
                        {
                            break;
                        }
                    }
                }
                if (f1)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            pt+=sizeof(book);

        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(15);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }
    /////////////////********************************Start Multi-Search********************************/////////////////
    ////////////////////////////// DOUBLE MULTI SEARCH //////////////////////////////
    else if (search_type==1) //SEACH KEYS: TITLE & AUTHOR
    {
        char x[100],y[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book title: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter Author name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].author;
        int a,b,f1,f2;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                if (f1!=0 && f2!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }
    else if (search_type==2) //SEARCH KEYS : TITLE & CATEGORY
    {
        char x[100],y[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].category;
        int a,b,f1,f2;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                if (f1!=0 && f2!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
        {
            color(14);
            printf("Enter the index of the book you want to apply changes to: ");
            fflush(stdin);
            color(15);
            myfgets(numTest, 20);
            while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
            {
                color(12);
                printf("Invalid Input!\n");
                color(15);
                printf("Enter the index of the target book in the list: ");
                fflush(stdin);
                myfgets(numTest, 20);
            }
            bofound = atoi(numTest)-1;
        }

        }
    }
    else if (search_type==3) //SEARCH KEYS : TITLE & PUBLISHER
    {
        char x[100],y[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter Publisher name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].publisher;
        int a,b,f1,f2;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                if (f1!=0 && f2!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
        {
            color(14);
            printf("Enter the index of the book you want to apply changes to: ");
            fflush(stdin);
            color(15);
            myfgets(numTest, 20);
            while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
            {
                color(12);
                printf("Invalid Input!\n");
                color(15);
                printf("Enter the index of the target book in the list: ");
                fflush(stdin);
                myfgets(numTest, 20);
            }
            bofound = atoi(numTest)-1;
        }

        }
        }

    else if (search_type==4) //SEARCH KEYS : AUTHOR & CATEGORY
    {
        char x[100],y[100];
        printf("Enter author name: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book category: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        bosearch=-1;
        char* p1=library[0].author;
        char* p2=library[0].category;
        int a,b,f1,f2;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                if (f1!=0 && f2!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
        }
        if (flag)
        {
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            printf("Book Found!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
        {
            color(14);
            printf("Enter the index of the book you want to apply changes to: ");
            fflush(stdin);
            color(15);
            myfgets(numTest, 20);
            while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
            {
                color(12);
                printf("Invalid Input!\n");
                color(15);
                printf("Enter the index of the target book in the list: ");
                fflush(stdin);
                myfgets(numTest, 20);
            }
            bofound = atoi(numTest)-1;
        }

        }
        }

    else if (search_type==5) //SEARCH KEYS : AUTHOR & PUBLISHER
    {
        char x[100],y[100];
        printf("Enter author name: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter publisher name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        bosearch=-1;
        char* p1=library[0].author;
        char* p2=library[0].publisher;
        int a,b,f1,f2;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                if (f1!=0 && f2!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    else if (search_type==6) //SEARCH KEYS : CATEGORY & PUBLISHER
    {
        char x[100],y[100];
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter publisher name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        bosearch=-1;
        char* p1=library[0].author;
        char* p2=library[0].category;
        int a,b,f1,f2;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                if (f1!=0 && f2!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    ////////////////////////////// TRIPLE MULTI SEARCH //////////////////////////////
    else if (search_type==7) //SEARCH KEYS : TITLE & AUTHOR & CATEGORY
    {
        char x[100],y[100],z[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter author name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(z, sizeof(z));
        while(!stringValidation(z)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book category: ");
            fflush(stdin);
            myfgets(z, sizeof(z));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].author;
        char* p3=library[0].category;
        int a,b,f1,f2,f3;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0,f3=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p3); a++)
                {
                    if ( (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32) && !f3 )
                    {
                        a++;
                        f3=1;
                        for (b=1; b<strlen(z); b++)
                        {
                            if (p3[a]==z[b] || p3[a]==z[b]+32 || p3[a]==z[b]-32)
                            {
                                a++;
                            }
                            else if (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f3=0;
                                a++;
                                break;
                            }
                        }
                    }

                }
                if (f1!=0 && f2!=0 && f3!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
            p3+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    else if (search_type==8) //SEARCH KEYS : TITLE & AUTHOR & PUBLISHER
    {
        char x[100],y[100],z[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book title: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter author name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        printf("Enter publisher name: ");
        fflush(stdin);
        myfgets(z, sizeof(z));
        while(!stringValidation(z)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Publisher name: ");
            fflush(stdin);
            myfgets(z, sizeof(z));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].author;
        char* p3=library[0].publisher;
        int a,b,f1,f2,f3;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0,f3=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p3); a++)
                {
                    if ( (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32) && !f3 )
                    {
                        a++;
                        f3=1;
                        for (b=1; b<strlen(z); b++)
                        {
                            if (p3[a]==z[b] || p3[a]==z[b]+32 || p3[a]==z[b]-32)
                            {
                                a++;
                            }
                            else if (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f3=0;
                                a++;
                                break;
                            }
                        }
                    }

                }
                if (f1!=0 && f2!=0 && f3!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
            p3+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    else if (search_type==9) //SEARCH KEYS : TITLE & CATEGORY & PUBLISHER
    {
        char x[100],y[100],z[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book title: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book category: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        printf("Enter publisher name: ");
        fflush(stdin);
        myfgets(z, sizeof(z));
        while(!stringValidation(z)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Publisher name: ");
            fflush(stdin);
            myfgets(z, sizeof(z));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].category;
        char* p3=library[0].publisher;
        int a,b,f1,f2,f3;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0,f3=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p3); a++)
                {
                    if ( (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32) && !f3 )
                    {
                        a++;
                        f3=1;
                        for (b=1; b<strlen(z); b++)
                        {
                            if (p3[a]==z[b] || p3[a]==z[b]+32 || p3[a]==z[b]-32)
                            {
                                a++;
                            }
                            else if (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f3=0;
                                a++;
                                break;
                            }
                        }
                    }

                }
                if (f1!=0 && f2!=0 && f3!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
            p3+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    else if (search_type==10) //SEARCH KEYS : AUTHOR & CATEGORY & PUBLISHER
    {
        char x[100],y[100],z[100];
        printf("Enter author name: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book category: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        printf("Enter publisher name: ");
        fflush(stdin);
        myfgets(z, sizeof(z));
        while(!stringValidation(z)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Publisher name: ");
            fflush(stdin);
            myfgets(z, sizeof(z));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].author;
        char* p3=library[0].category;
        int a,b,f1,f2,f3;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0,f3=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p3); a++)
                {
                    if ( (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32) && !f3 )
                    {
                        a++;
                        f3=1;
                        for (b=1; b<strlen(z); b++)
                        {
                            if (p3[a]==z[b] || p3[a]==z[b]+32 || p3[a]==z[b]-32)
                            {
                                a++;
                            }
                            else if (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f3=0;
                                a++;
                                break;
                            }
                        }
                    }

                }
                if (f1!=0 && f2!=0 && f3!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
            p3+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    ////////////////////////////// QUADRIPLE MULTI SEARCH //////////////////////////////
    else if (search_type==11) //SEARCH KEYS : TITLE & AUTHOR & CATEGORY & PUBLISHER
    {
        char x[100],y[100],z[100],l[100];
        printf("Enter book title: ");
        fflush(stdin);
        myfgets(x, sizeof(x));
        while(!stringValidation(x)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book title: ");
            fflush(stdin);
            myfgets(x, sizeof(x));
        }
        printf("Enter author name: ");
        fflush(stdin);
        myfgets(y, sizeof(y));
        while(!stringValidation(y)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(y, sizeof(y));
        }
        printf("Enter book category: ");
        fflush(stdin);
        myfgets(z, sizeof(z));
        while(!stringValidation(z)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book category: ");
            fflush(stdin);
            myfgets(z, sizeof(z));
        }
        printf("Enter publisher name: ");
        fflush(stdin);
        myfgets(l, sizeof(l));
        while(!stringValidation(l)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Publisher name: ");
            fflush(stdin);
            myfgets(l, sizeof(l));
        }
        bosearch=-1;
        char* p1=library[0].title;
        char* p2=library[0].author;
        char* p3=library[0].category;
        char* p4=library[0].publisher;
        int a,b,f1,f2,f3,f4;
        int i,flag=1;
        for (i=0; i<=BooksNO; i++)
        {
            if (library[i].on == 1)
            {
                f1=0,f2=0,f3=0,f4=0;
                for (a=0; a<strlen(p1); a++)
                {
                    if ( (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32) && !f1 )
                    {
                        a++;
                        f1=1;
                        for (b=1; b<strlen(x); b++)
                        {
                            if (p1[a]==x[b] || p1[a]==x[b]+32 || p1[a]==x[b]-32)
                            {
                                a++;
                            }
                            else if (p1[a]==x[0] || p1[a]==x[0]+32 || p1[a]==x[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f1=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p2); a++)
                {
                    if ( (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32) && !f2 )
                    {
                        a++;
                        f2=1;
                        for (b=1; b<strlen(y); b++)
                        {
                            if (p2[a]==y[b] || p2[a]==y[b]+32 || p2[a]==y[b]-32)
                            {
                                a++;
                            }
                            else if (p2[a]==y[0] || p2[a]==y[0]+32 || p2[a]==y[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f2=0;
                                a++;
                                break;
                            }
                        }
                    }
                }
                for (a=0; a<strlen(p3); a++)
                {
                    if ( (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32) && !f3 )
                    {
                        a++;
                        f3=1;
                        for (b=1; b<strlen(z); b++)
                        {
                            if (p3[a]==z[b] || p3[a]==z[b]+32 || p3[a]==z[b]-32)
                            {
                                a++;
                            }
                            else if (p3[a]==z[0] || p3[a]==z[0]+32 || p3[a]==z[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f3=0;
                                a++;
                                break;
                            }
                        }
                    }

                }
                for (a=0; a<strlen(p4); a++)
                {
                    if ( (p4[a]==l[0] || p4[a]==l[0]+32 || p4[a]==l[0]-32) && !f4 )
                    {
                        a++;
                        f4=1;
                        for (b=1; b<strlen(l); b++)
                        {
                            if (p4[a]==l[b] || p4[a]==l[b]+32 || p4[a]==l[b]-32)
                            {
                                a++;
                            }
                            else if (p4[a]==l[0] || p4[a]==l[0]+32 || p4[a]==l[0]-32)
                            {
                                b=2;
                                a++;
                            }
                            else
                            {
                                f4=0;
                                a++;
                                break;
                            }
                        }
                    }

                }
                if (f1!=0 && f2!=0 && f3!=0 && f4!=0)
                {
                    bosearch++;
                    search_results[bosearch]=&library[i];
                    flag=0;
                }
            }
            p1+=sizeof(book);
            p2+=sizeof(book);
            p3+=sizeof(book);
            p4+=sizeof(book);
        }
        if (flag)
        {
            color(12);
            printf("\nBook Not Found...\n");
        }
        else
        {
            system("cls");
            color(10);
            printf("Book Found Successfully!\n");
            for (i=0; i<=bosearch; i++)
            {
                color(10);
                printf("Book[%d]",i+1);
                color(15);
                printf("\nBook title: %s",search_results[i]->title);
                printf("\nBoo ISBN: %s",search_results[i]->isbn);
                printf("\nBook Author: %s",search_results[i]->author);
                printf("\nBook Category: %s",search_results[i]->category);
                printf("\nBook Publisher: %s",search_results[i]->publisher);
                printf("\nBook Date of publication: %d/%d/%d",search_results[i]->dateofpublication.day,search_results[i]->dateofpublication.month,search_results[i]->dateofpublication.year);
                printf("\nBook Copies: %d",search_results[i]->copies);
                printf("\nBook available Copies: %d",search_results[i]->available);
                printf("\nBook borrows: %d\n",search_results[i]->nBorrowed);
            }
            if (mode != 0)
            {
                color(14);
                printf("Enter the index of the book you want to apply changes to: ");
                fflush(stdin);
                color(15);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)>bosearch+1)
                {
                    color(12);
                    printf("Invalid Input!\n");
                    color(15);
                    printf("Enter the index of the target book in the list: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                bofound = atoi(numTest)-1;
            }
        }
    }

    /////////////////********************************End Multi-Search********************************/////////////////
    if (mode==1) // ADD NEW COPIES FUNCTION
    {
        color(10);
        int new_copies;
        printf("Enter the number of new copies to be added:");
        scanf("%d",&new_copies);
        fflush(stdin);
        while (new_copies<1)
        {
            color(12);
            printf("Invalid Input!\n");
            fflush(stdin);
            color(15);
            printf("Enter a positive number:");
            scanf("%d", &new_copies);
        }
        search_results[bofound]->copies+=new_copies;
        search_results[bofound]->available+=new_copies;
        color(10);
        printf("Copies added successfully!");
        printf("\nNew number of copies: %d",search_results[bofound]->copies);
        printf("\nNew number of available copies: %d",search_results[bofound]->available);
        color(15);
    }
    else if (mode==2) // DELETE BOOK
    {
        system("cls");
        if (search_results[bofound]->nBorrowed>0)
        {
            setcoordinates(0,0);
            color(12);
            printf("This book is already borrowed by %d users. You Can't Delete it.\n",search_results[bofound]->nBorrowed);
            color(14);
            fflush(stdin);
            printf("\nPress any key to go back to main menu..");
            Keypressed=_getch();
            if(Keypressed)
            mainmenu();
        }
        else
        {
            setcoordinates(0,0);
            color(12);
            printf("Are you sure you want to delete the targeted book?");
            char Keypressed=0;
            int position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,1);
                arrowHere(1,position);
                printf("1.YES");
                setcoordinates(0,2);
                arrowHere(2,position);
                printf("2.NO");
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
            if (position==1)
            {
                search_results[bofound]->on=0;
                color(10);
                printf("\nBook Deleted successfully!\n");
            }
            else if(position==2)
            {
                system("cls");
                Keypressed=0;
                position=1;
                while(Keypressed!=(char)13)
                {
                    setcoordinates(0,0);
                    arrowHere(1,position);
                    printf("1.Back to main menu");
                    setcoordinates(0,1);
                    arrowHere(2,position);
                    printf("2.Back to books menu");
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
                    mainmenu();
                else if(position==2)
                    booksmenu();
            }
        }
    }
    else if(mode==3)//BORROW BOOK
    {
        system("CLS");
        setcoordinates(0,0);
        color(10);
        printf("Borrowing Section\n");
        Borrow_book(search_results[bofound]);
    }
    else if (mode==4)// EDIT BOOK
    {
        system("CLS");
        setcoordinates(0,0);
        color(10);
        printf("Edit book\n");
        edit_book(search_results[bofound]);
    }
    color(14);
    fflush(stdin);
    printf("\nPress any key to go back to main menu..");
    Keypressed=_getch();
    if(Keypressed)
        mainmenu();
}
void edit_book(book* target)
{
    int position=1;
    char Keypressed=0;
    while (Keypressed!=(char)13)
    {
        color(15);
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Book Title");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Book ISBN");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Book Author");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Book Category");
        setcoordinates(0,5);
        arrowHere(5,position);
        printf("5.Book Publisher");
        setcoordinates(0,6);
        arrowHere(6,position);
        printf("6.Date of publication");
        setcoordinates(0,7);
        arrowHere(7,position);
        printf("7.Number of Copies");
        setcoordinates(0,8);
        arrowHere(8,position);
        printf("8.Back to book management");
        Keypressed = _getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 8)
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
        char c[100];
        color(15);
        printf("Enter new book title: ");
        fflush(stdin);
        myfgets(c, sizeof(c));
        while(!stringValidation(c)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book title: ");
            fflush(stdin);
            myfgets(c, sizeof(c));
        }
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            strcpy(target->title,c);
            color(10);
            setcoordinates(0,5);
            printf("Title edited successfully!\n");
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    else if(position == 2)
    {
        system("cls");
        char c[100];
        color(15);
        printf("Enter new book ISBN: ");
        fflush(stdin);
        myfgets(c, sizeof(c));
        while(!stringValidation(c)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book ISBN: ");
            fflush(stdin);
            myfgets(c, sizeof(c));
        }
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            strcpy(target->isbn,c);
            color(10);
            setcoordinates(0,5);
            printf("ISBN edited successfully!\n");
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    else if(position == 3)
    {
        system("cls");
        char c[100];
        color(15);
        printf("Enter new Author name: ");
        fflush(stdin);
        myfgets(c, sizeof(c));
        while(!stringValidation(c)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Author name: ");
            fflush(stdin);
            myfgets(c, sizeof(c));
        }
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            strcpy(target->author,c);
            color(10);
            setcoordinates(0,5);
            printf("Author name edited successfully!\n");
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    else if(position == 4)
    {
        system("cls");
        char c[100];
        color(15);
        printf("Enter new book category: ");
        fflush(stdin);
        myfgets(c, sizeof(c));
        while(!stringValidation(c)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Your input: ");
            fflush(stdin);
            myfgets(c, sizeof(c));
        }
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            strcpy(target->category,c);
            color(10);
            setcoordinates(0,5);
            printf("Category edited successfully!\n");
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    else if(position == 5)
    {
        system("cls");
        char c[100];
        color(15);
        printf("Enter book publisher: ");
        fflush(stdin);
        myfgets(c, sizeof(c));
        while(!stringValidation(c)) // Handling Error
        {
            color(12);
            printf("Invalid input! Please enter only alphabets\n");
            color(15);
            printf("Book publishe: ");
            fflush(stdin);
            myfgets(c, sizeof(c));
        }
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            strcpy(target->publisher,c);
            color(10);
            setcoordinates(0,5);
            printf("Publisher edited successfully!\n");
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    else if(position == 6)
    {
        system("cls");
        int dd,mm,yy;
        color(15);
        printf("Enter the date of publication(DD/MM/YYYY): ");
        fflush(stdin);
        scanf("%d/%d/%d",&dd,&mm,&yy);
        while(!dateValidation(dd,mm,yy))
        {
            color(12);
            printf("Invalid date please provide a valid one");
            color(15);
            printf("Enter the date of publication (DD/MM/YYYY)");
            scanf("%d/%d/%d",&dd,&mm,&yy);
        }
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            target->dateofpublication.day=dd;
            target->dateofpublication.month=mm;
            target->dateofpublication.year=yy;
            color(10);
            setcoordinates(0,5);
            printf("Date of publication edited successfully!\n");
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    else if(position == 7)
    {
        system("cls");
        int x;
        color(15);
        printf("Enter new number of copies: ");
        fflush(stdin);
        char input[100];
        myfgets(input,sizeof(input));
        while(!numberValid(input)||atoi(input)>bosearch+1)
        {
            color(12);
            printf("Invalid Input!\n");
            fflush(stdin);
            color(15);
            printf("Enter the index of the target book in the list:");
            myfgets(input,sizeof(input));
        }
        x = atoi(input);
        system("cls");
        color(12);
        setcoordinates(0,0);
        printf("Are you sure you want to edit?");
        char Keypressed=0;
        int position=1;
        while(Keypressed!=(char)13)
        {
            setcoordinates(0,1);
            arrowHere(1,position);
            printf("1.YES");
            setcoordinates(0,2);
            arrowHere(2,position);
            printf("2.NO");
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
        if (position==1)
        {
            if (x < target->nBorrowed)
            {
                color(12);
                setcoordinates(0,10);
                printf("Invalid number of copies!There are already %d books borrowed",target->nBorrowed);
                setcoordinates(0,11);
                printf("You can't reduce the number of copies");
            }
            else
            {
                target->copies = x;
                target->available = x - target->nBorrowed;
                color(10);
                setcoordinates(0,5);
                printf("Number of copies edited successfully!\n");
            }
        }
        else if(position==2)
        {
            system("cls");
            Keypressed=0;
            position=1;
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,0);
                arrowHere(1,position);
                printf("1.Back to main menu");
                setcoordinates(0,1);
                arrowHere(2,position);
                printf("2.Back to books menu");
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
                mainmenu();
            else if(position==2)
                booksmenu();
        }
    }
    if(position==8)
    {
        booksmenu();
    }
}
void return_date()
{
    system("cls");
    int ID, posInArray;
    char Keypressed=0;
    char numTest[20];
    strcpy(numTest, "a");
    color(15);
    printf("Enter User ID: ");
    fflush(stdin);
    myfgets(numTest, 20);
    while(!numberValid(numTest))
    {
        color(12);
        printf("This is not a valid ID, please provide a valid one.\n");
        color(15);
        printf("Enter User ID: ");
        fflush(stdin);
        myfgets(numTest, 20);
    }
    ID = atoi(numTest);
    posInArray=searchUser(ID);
    if(posInArray < 0)
    {
        color(12);
        printf("User Doesn't Exist!\n");
        color(14);
        printf("Press any key to go back to main menu ..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }
    else
    {
        if(users[posInArray].booksBorrowed<1)
        {
            color(12);
            printf("\nThis user doesn't have any borrowed books.\n");
            color(14);
            printf("Press any key to go back to main menu ..");
            Keypressed=_getch();
            if(Keypressed)
                mainmenu();
        }
        else
        {
            color(15);
            printf("Enter Book ISBN:");
            fflush(stdin);
            book x;
            strcpy(x.isbn, isbnValidation());
            color(15);
            int i,posInLibrary,j;
            int day,year,month;
            for (i=0; i<=borrowedNo; i++)
            {
                if(bBooks[i].returned.day==0&&bBooks[i].returned.year==0&&bBooks[i].returned.year==0)
                  {
                        if ( atoll(bBooks[i].bookISBN) == atoll(x.isbn) )
                        {
                            Isbnsearch[i] = &bBooks[i];
                            if(Isbnsearch[i]->memberID==ID)
                            {
                                color(15);
                                printf("The user borrowed this book");
                                color(10);
                                printf("\nBook[%d]",i);
                                color(15);
                                printf("\nBook's ISBN: %s",Isbnsearch[i]->bookISBN);
                                printf("\nUser's ID: %d",Isbnsearch[i]->memberID);
                                printf("\nBook's Issued date: %d/%d/%d",Isbnsearch[i]->issued.day,Isbnsearch[i]->issued.month,Isbnsearch[i]->issued.year);
                                printf("\nBook's due to return date: %d/%d/%d",Isbnsearch[i]->duetoreturn.day,Isbnsearch[i]->duetoreturn.month,Isbnsearch[i]->duetoreturn.year);
                                currentDate(&day,&month,&year);
                                Isbnsearch[i]->returned.day=day;
                                Isbnsearch[i]->returned.month=month;
                                Isbnsearch[i]->returned.year=year;
                                printf("\nBook's return date: %d/%d/%d\n",Isbnsearch[i]->returned.day,Isbnsearch[i]->returned.month,Isbnsearch[i]->returned.year);
                            }
                        }
                  }

            }
            users[posInArray].booksBorrowed--;
            for(j=0; j<=BooksNO; j++)
            {
                if(atoll(library[j].isbn)==atoll(x.isbn))
                    posInLibrary=j;
            }
            library[posInLibrary].nBorrowed--;
            library[posInLibrary].available++;
            color(10);
            printf("Book Returned successfully");
            color(14);
            printf("\nPress any key to go back to main menu ..");
            Keypressed=0;
            Keypressed=_getch();
            if(Keypressed)
                mainmenu();
        }
    }
}
void popular_books()
{
    system("cls");
    int i,pass,sorted=0;
    char Keypressed = 0;
    book hold;
    if(BooksNO<0)
    {
        color(12);
        printf("There are no books in the system.\n");
        color(14);
        printf("Press any key to go back to main menu..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }
    for (pass=0; pass<BooksNO && !sorted; pass++)
    {
        sorted = 1;
        for (i=0; i<BooksNO-pass; i++)
        {
            if (library[i].aBorrows<library[i+1].aBorrows)
            {
                hold = library[i];
                library[i] = library[i+1];
                library[i+1] = hold;
                sorted = 0;
            }
        }
    }
    if (BooksNO<4)
    {
        for (i=0; i<=BooksNO; i++)
        {
            color(10);
            printf("Book[%d]",i);
            color(15);
            printf("\nBook title: %s",library[i].title);
            printf("\nBoo ISBN: %s",library[i].isbn);
            printf("\nBook Author: %s",library[i].author);
            printf("\nBook Category: %s",library[i].category);
            printf("\nBook Publisher: %s",library[i].publisher);
            printf("\nBook Date of publication: %d/%d/%d",library[i].dateofpublication.day,library[i].dateofpublication.month,library[i].dateofpublication.year);
            printf("\nBook Copies: %d",library[i].copies);
            printf("\nBook available Copies: %d",library[i].available);
            printf("\nCurrent book borrows: %d",library[i].nBorrowed);
            printf("\nAll time borrows: %d\n",library[i].aBorrows);
        }
    }
    else
    {
        for (i=0; i<5; i++)
        {
            color(10);
            printf("Book[%d]",i+1);
            color(15);
            printf("\nBook title: %s",library[i].title);
            printf("\nBoo ISBN: %s",library[i].isbn);
            printf("\nBook Author: %s",library[i].author);
            printf("\nBook Category: %s",library[i].category);
            printf("\nBook Publisher: %s",library[i].publisher);
            printf("\nBook Date of publication: %d/%d/%d",library[i].dateofpublication.day,library[i].dateofpublication.month,library[i].dateofpublication.year);
            printf("\nBook Copies: %d",library[i].copies);
            printf("\nBook available Copies: %d",library[i].available);
            printf("\nBook borrows: %d",library[i].nBorrowed);
            printf("\nAll time borrows: %d\n",library[i].aBorrows);


        }
    }
    color(14);
    printf("Press any key to go back to main menu ..");
    Keypressed=0;
    Keypressed=_getch();
    if(Keypressed)
        mainmenu();
}
void overdueBooks()
{
    system("cls");
    int i,k;
    char Keypressed=0;
    if(borrowedNo<=0)
    {
        color(12);
        printf("There are no borrowed books.\n");
        color(14);
        printf("Press any key to go back to main menu..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }
    for(i=0;i<borrowedNo;i++)
    {
        if(bBooks[i].returned.day==0 && bBooks[i].returned.month==0 && bBooks[i].returned.year==0)
        {
            k = returnDateValidation(bBooks[i].duetoreturn.day,bBooks[i].duetoreturn.month,bBooks[i].duetoreturn.year);
            if(k)
            {
                color(14);
                printf("Overdue Books");
                color(10);
                printf("\nBook[%d]",i);
                color(15);
                printf("\nBook's ISBN: %s",bBooks[i].bookISBN);
                printf("\nUser's ID: %d",bBooks[i].memberID);
                printf("\nBook's Issued date: %d/%d/%d",bBooks[i].issued.day,bBooks[i].issued.month,bBooks[i].issued.year);
                printf("\nBook's due to return date: %d/%d/%d\n",bBooks[i].duetoreturn.day,bBooks[i].duetoreturn.month,bBooks[i].duetoreturn.year);
                color(14);
                printf("Press any key to go back to main menu..");
                Keypressed=_getch();
                if(Keypressed)
                    mainmenu();
            }
            if(k==0)
            {
                color(12);
                printf("There are no overdue books\n");
                color(14);
                printf("Press any key to go back to main menu..");
                Keypressed=_getch();
                if(Keypressed)
                    mainmenu();
            }
        }
        else
        {
            color(12);
            printf("There are no overdue books\n");
            color(14);
            printf("Press any key to go back to main menu..");
            Keypressed=_getch();
            if(Keypressed)
                mainmenu();
        }
    }
}
void print_books()
{
    system("cls");
    int i;
    char Keypressed=0;
    if(BooksNO<0)
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
        for(i=0; i<=BooksNO; i++)
        {
            color(10);
            printf("Book[%d]",i+1);
            color(15);
            printf("\nBook title: %s",library[i].title);
            printf("\nBoo ISBN: %s",library[i].isbn);
            printf("\nBook Author: %s",library[i].author);
            printf("\nBook Category: %s",library[i].category);
            printf("\nBook Publisher: %s",library[i].publisher);
            printf("\nBook Date of publication: %d/%d/%d",library[i].dateofpublication.day,library[i].dateofpublication.month,library[i].dateofpublication.year);
            printf("\nBook Copies: %d",library[i].copies);
            printf("\nBook available Copies: %d",library[i].available);
            printf("\nBook borrows: %d\n",library[i].nBorrowed);
        }
        color(14);
        printf("Press any key to go back to main menu ..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
    }
}
