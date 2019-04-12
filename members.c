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

void filesCheck()
{
    int f;
    f = (int)fopen("usersFile.txt", "r");
    if(!f)
    {
        FILE *usersFile;
        usersFile = fopen("usersFile.txt", "w");
        fprintf(usersFile, "%d\n", currentID);
        fclose(usersFile);
    }
    f = (int)fopen("Books.txt", "r");
    if(!f)
    {
        FILE *fbook;
        fbook = fopen("Books.txt", "w");
        fclose(fbook);
    }
    f = (int)fopen("borrowed.txt", "r");
    if(!f)
    {
        FILE *fborrowed;
        fborrowed = fopen("borrowed.txt", "w");
        fclose(fborrowed);
    }
}
void addUser()
{
    char keypressed=0;
    system("cls");
    NumOfUser = usersInFile()+runs; // to know the position of the user being added
    color(15);
    printf("Please Enter User's \n");
    printf("First Name: ");
    fflush(stdin);
    myfgets(users[NumOfUser].fName, 20);
    while(!stringValidation(users[NumOfUser].fName)) // Handling Error
    {
        color(12);
        printf("This is not a valid Name, please provide a valid one.\n");
        color(15);
        printf("First Name: ");
        fflush(stdin);
        myfgets(users[NumOfUser].fName, 20);
    }

    printf("Last Name: ");
    fflush(stdin);
    myfgets(users[NumOfUser].lName, 20);
    while(!stringValidation(users[NumOfUser].lName))
    {
        color(12);
        printf("This is not a valid Name, please provide a valid one.\n");
        color(15);
        printf("Last Name: ");
        fflush(stdin);
        myfgets(users[NumOfUser].lName, 20);
    }

    users[NumOfUser].ID = currentID; // The ID of each user is his order in the system

    strcpy(numTest, "a"); // For making sure that the validation will refuse it
    printf("Age: ");
    fflush(stdin);
    myfgets(numTest, 20);
    while(!numberValid(numTest) || atoi(numTest)<6 || atoi(numTest) >110)
    {
        color(12);
        printf("This is not a valid age, please provide a valid one.\n");
        color(15);
        printf("Age: ");
        fflush(stdin);
        myfgets(numTest, 20);
    }
    users[NumOfUser].age = atoi(numTest);

    strcpy(numTest, "a");
    printf("Phone Number: +2");
    fflush(stdin);
    myfgets(numTest, 20);
    while(phoneNumValidation(numTest)!=5)
    {
        int x = phoneNumValidation(numTest);
        switch(x)
        {
        case 0:
            color(12);
            printf("This is not a valid Phone Number, please provide a valid one.\n");
            color(15);
            printf("Phone Number: +2");
            fflush(stdin);
            myfgets(numTest, 20);
            break;
        case 1:
            color(12);
            printf("This is not a valid Phone Number, A phone number should contain exactly 11 digits.\n");
            color(15);
            printf("Phone Number: +2");
            fflush(stdin);
            myfgets(numTest, 20);
            break;
        case 2:
            color(12);
            printf("This is not a valid Phone Number, A phone number should be in the form (+201)234567890.\n");
            color(15);
            printf("Phone Number: +2");
            fflush(stdin);
            myfgets(numTest, 20);
            break;
        }
    }
    strcpy(users[NumOfUser].phone, numTest);

    strcpy(numTest, "a");
    printf("National ID: ");
    fflush(stdin);
    myfgets(numTest, 20);
    while(!numberValid(numTest) || strlen(numTest)!=14 || !natIDverification(numTest))
    {
        color(12);
        printf("This is not a valid national ID, please provide a valid one.\n");
        color(15);
        printf("National ID: ");
        fflush(stdin);
        myfgets(numTest, 20);
    }
    strcpy(users[NumOfUser].nationalID, numTest);
    while(searchNationalID(numTest)!=1)
    {
        color(12);
        printf("User already exists.\n");
        color(14);
        printf("Press any key to go back to main menu ..");
        keypressed=_getch();
        if(keypressed)
            mainmenu();
    }

    printf("E-Mail: ");
    fflush(stdin);
    myfgets(users[NumOfUser].mail, 50);
    while(!mailVaildation(users[NumOfUser].mail))
    {
        color(12);
        printf("This is not a valid email address, please provide a valid one.\n");
        color(15);
        printf("E-mail: ");
        fflush(stdin);
        myfgets(users[NumOfUser].mail, 50);
    }

    strcpy(numTest, "a");
    printf("Building Number: ");
    fflush(stdin);
    myfgets(numTest, 20);
    while(!numberValid(numTest))
    {
        color(12);
        printf("This is not a valid Building Number, please provide a valid one.\n");
        color(15);
        printf("Building Number: ");
        fflush(stdin);
        myfgets(numTest, 20);
    }
    users[NumOfUser].add.buildingNum = atoi(numTest);

    printf("Street Name: ");
    fflush(stdin);
    myfgets(users[NumOfUser].add.street, 30);
    while(!stringValidation(users[NumOfUser].add.street))
    {
        color(12);
        printf("This is not a valid Street Name, please provide a valid one.\n");
        color(15);
        printf("Street Name: ");
        fflush(stdin);
        myfgets(users[NumOfUser].add.street, 30);
    }

    printf("City Name: ");
    fflush(stdin);
    myfgets(users[NumOfUser].add.city, 20);
    while(!stringValidation(users[NumOfUser].add.city))
    {
        color(12);
        printf("This is not a valid City Name, please provide a valid one.\n");
        color(15);
        printf("City Name: ");
        fflush(stdin);
        myfgets(users[NumOfUser].add.city, 20);
    }

    system("cls");
    printf("User Added Successfully!\n");
    printf("User ID is %d\n", users[NumOfUser].ID);
    currentID++;
    runs++;
    arrayCount++;
    users[NumOfUser].booksBorrowed = 0;
    int position=1;
    char Keypressed=0;
        while(Keypressed!=(char)13)
    {
        setcoordinates(0,2);
        arrowHere(1,position);
        printf("1.Back to members menu");
        setcoordinates(0,3);
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
            membersmenu();
        else if(position==2)
            mainmenu();
    }
void deleteUser()
{
    system("cls");
    int i, ID, posInArray;
    char Keypressed=0;
    if(arrayCount==0)
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
        else if(users[posInArray].booksBorrowed!=0)
        {
            color(12);
            printf("Member must return the books he borrowed first before leaving the system!\n");
            color(14);
            printf("Press any key to go back to main menu ..");
            Keypressed=_getch();
            if(Keypressed)
                mainmenu();
        }
        else
        {
            for(i=0; i<arrayCount; i++) // Shifting the elements in the array
            {
                if(i==posInArray)
                {
                    for(; i<arrayCount; i++)
                        users[i]=users[i+1];
                    break;
                }

            }
            color(10);
            printf("User Deleted Successfully!\n");
            arrayCount--; // decreasing the size of the array's counter
            runs--;
            color(14);
            printf("Press any key to go back to main menu ..");
            Keypressed=_getch();
            if(Keypressed)
                mainmenu();
        }
    }
}
void editUser()
{
    char keypressed=0;
    system("cls");
    int ID, posInArray;
    char Keypressed=0;
    if(arrayCount==0)
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
            system("CLS");
            int position = 2;
            char Keypressed=0;
            setcoordinates(0,0);
            color(10);
            printf("Use arrows\n");
            printf("User Found Successfully!");
            while(Keypressed!=(char)13)
            {
                setcoordinates(0,2);
                arrowHere(2,position);
                printf("First Name: %s\n", users[posInArray].fName);
                setcoordinates(0,3);
                arrowHere(3,position);
                printf("Last Name: %s\n", users[posInArray].lName);
                setcoordinates(0,4);
                arrowHere(4,position);
                printf("Age: %d\n", users[posInArray].age);
                setcoordinates(0,5);
                arrowHere(5,position);
                printf("Mobile: %s\n", users[posInArray].phone);
                setcoordinates(0,6);
                arrowHere(6,position);
                printf("National ID: %s\n", users[posInArray].nationalID);
                setcoordinates(0,7);
                arrowHere(7,position);
                printf("E-Mail: %s\n", users[posInArray].mail);
                setcoordinates(0,8);
                arrowHere(8,position);
                printf("Building Number: %d\n", users[posInArray].add.buildingNum);
                setcoordinates(0,9);
                arrowHere(9,position);
                printf("Street: %s\n", users[posInArray].add.street);
                setcoordinates(0,10);
                arrowHere(10,position);
                printf("City: %s\n\n", users[posInArray].add.city);
                setcoordinates(0,11);
                arrowHere(11,position);
                printf("Back to main menu");
                Keypressed = _getch();
                if(Keypressed==(char)224)
                {
                    Keypressed = _getch();
                    if(Keypressed == (char)80 && position != 11)
                        position++;
                    else if(Keypressed == (char)72 && position != 2)
                        position--;
                    else
                        position = position;
                }
            }
            if(Keypressed==(char)13 && position == 11)
                mainmenu();
            if(position==2)
            {
                system("cls");
                color(15);
                printf("New First Name: ");
                fflush(stdin);
                myfgets(users[posInArray].fName, 20);
                while(!stringValidation(users[posInArray].fName)) // Handling Error
                {
                    color(12);
                    printf("This is not a valid name, please provide a valid one.\n");
                    color(15);
                    printf("New First Name: ");
                    fflush(stdin);
                    myfgets(users[posInArray].fName, 20);
                }
            }
            else if(position==3)
            {
                system("cls");
                color(15);
                printf("New Last Name: ");
                fflush(stdin);
                myfgets(users[posInArray].lName, 20);
                while(!stringValidation(users[posInArray].lName)) // Handling Error
                {
                    color(12);
                    printf("This is not a valid name, please provide a valid one.\n");
                    color(15);
                    printf("New Last Name: ");
                    fflush(stdin);
                    myfgets(users[posInArray].lName, 20);
                }
            }
            else if(position==4)
            {
                system("cls");
                color(15);
                strcpy(numTest, "a"); // For making sure that the validation will refuse it
                printf("New Age: ");
                fflush(stdin);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || atoi(numTest)<6 || atoi(numTest) >100)
                {
                    color(12);
                    printf("This is not a valid age, please provide a valid one.\n");
                    color(15);
                    printf("New Age: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                users[posInArray].age = atoi(numTest);
            }
            else if(position==5)
            {
                system("cls");
                color(15);
                strcpy(numTest, "a");
                printf("New Phone Number: +2");
                fflush(stdin);
                myfgets(numTest, 20);
                while(phoneNumValidation(numTest)!=5)
                {
                    int x = phoneNumValidation(numTest);
                    switch(x)
                    {
                    case 0:
                        color(12);
                        printf("This is not a valid Phone Number, please provide a valid one.\n");
                        color(15);
                        printf("New Phone Number: +2");
                        fflush(stdin);
                        myfgets(numTest, 20);
                        break;
                    case 1:
                        color(12);
                        printf("This is not a valid Phone Number, A phone number should contain exactly 11 digits.\n");
                        color(15);
                        printf("New Phone Number: +2");
                        fflush(stdin);
                        myfgets(numTest, 20);
                        break;
                    case 2:
                        color(12);
                        printf("This is not a valid Phone Number, A phone number should be in the form (+201)234567890.\n");
                        color(15);
                        printf("New Phone Number: +2");
                        fflush(stdin);
                        myfgets(numTest, 20);
                        break;
                    }
                }
                strcpy(users[posInArray].phone, numTest);
            }
            else if(position==6)
            {
                system("cls");
                color(15);
                strcpy(numTest, "a");
                printf("New National ID: ");
                fflush(stdin);
                myfgets(numTest, 20);
                while(!numberValid(numTest) || strlen(numTest)!=14 || !natIDverification(numTest))
                {
                    color(12);
                    printf("This is not a valid national ID, please provide a 'valid' 14-digit one.\n");
                    color(15);
                    printf("New National ID: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                strcpy(users[NumOfUser].nationalID, numTest);
                while(searchNationalID(users[posInArray].nationalID)!=1)
                {
                    color(12);
                    printf("User already exists.\n");
                    color(14);
                    printf("Press any key to go back to main menu ..");
                    keypressed=_getch();
                    if(keypressed)
                        mainmenu();
                }
            }
            else if(position==7)
            {
                system("cls");
                color(15);
                printf("New E-Mail: ");
                fflush(stdin);
                myfgets(users[posInArray].mail, 50);
                while(!mailVaildation(users[posInArray].mail))
                {
                    color(12);
                    printf("This is not a valid email address, please provide a valid one.\n");
                    color(15);
                    printf("New E-mail: ");
                    fflush(stdin);
                    myfgets(users[posInArray].mail, 50);
                }
            }
            else if(position==8)
            {
                system("cls");
                color(15);
                strcpy(numTest, "a");
                printf("New Building Number: ");
                fflush(stdin);
                myfgets(numTest, 20);
                while(!numberValid(numTest))
                {
                    color(12);
                    printf("This is not a valid Building Number, please provide a valid one.\n");
                    color(15);
                    printf("New Building Number: ");
                    fflush(stdin);
                    myfgets(numTest, 20);
                }
                users[posInArray].add.buildingNum = atoi(numTest);
            }
            else if(position==9)
            {
                system("cls");
                color(15);
                printf("New Street Name: ");
                fflush(stdin);
                myfgets(users[posInArray].add.street, 30);
                while(!stringValidation(users[posInArray].add.street))
                {
                    color(12);
                    printf("This is not a valid Street Name, please provide a valid one.\n");
                    color(15);
                    printf("New Street Name: ");
                    fflush(stdin);
                    myfgets(users[posInArray].add.street, 30);
                }
            }
            else if(position==10)
            {
                system("cls");
                color(15);
                printf("New City Name: ");
                fflush(stdin);
                myfgets(users[posInArray].add.city, 20);
                while(!stringValidation(users[posInArray].add.city))
                {
                    color(12);
                    printf("This is not a valid City Name, please provide a valid one.\n");
                    color(15);
                    printf("New City Name: ");
                    fflush(stdin);
                    myfgets(users[posInArray].add.city, 20);
                }
            }
            color(10);
            printf("User Edited Successfully!\n");
            color(14);
            printf("Press any key to go back to main menu ..");
            Keypressed=_getch();
            if(Keypressed)
                mainmenu();
        }
    }
}
void printArray()
{
    system("cls");
    int i;
    char Keypressed=0;
    if(arrayCount==0)
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
        FILE *usersFile;
        usersFile = fopen("usersFile.txt", "r");
        for(i=0; i<arrayCount; i++)
        {
            color(10);
            printf("User [%d]\n", i+1);
            color(15);
            printf("Name: %s %s!\n", users[i].fName, users[i].lName);
            printf("ID: %d\n", users[i].ID);
            printf("Age: %d\n", users[i].age);
            printf("Mobile: %s\n", users[i].phone);
            printf("National ID: %s\n", users[i].nationalID);
            printf("E-Mail: %s\n", users[i].mail);
            printf("Books Borrowed: %d\n", users[i].booksBorrowed);
            printf("Address: %d, %s, %s\n\n", users[i].add.buildingNum, users[i].add.street, users[i].add.city);
        }
        color(14);
        printf("Press any key to go back to main menu ..");
        Keypressed=_getch();
        if(Keypressed)
            mainmenu();
        fclose(usersFile);
    }
}
void saveToFile()
{
    int n;
    FILE *usersFile;
    usersFile = fopen("usersFile.txt", "w"); // "w" because every time the array changes the file change with it overwriting the old data
    fprintf(usersFile, "%d\n", currentID); // Used in generating new IDs for new users
    for(n=0; n<arrayCount; n++)
    {
        fprintf(usersFile, "%s,%s,", users[n].fName, users[n].lName);
        fprintf(usersFile, "%d,", users[n].ID);
        fprintf(usersFile, "%d,", users[n].age);
        fprintf(usersFile, "%s,", users[n].phone);
        fprintf(usersFile, "%s,", users[n].nationalID);
        fprintf(usersFile, "%s,", users[n].mail);
        fprintf(usersFile, "%d,", users[n].booksBorrowed);
        fprintf(usersFile, "%d,%s,%s\n", users[n].add.buildingNum, users[n].add.street, users[n].add.city);
    }
    fclose(usersFile);
    fillArray();
    runs=0;
}
int usersInFile()
{
    int currentChar=0, count=0;
    FILE *usersFile;
    usersFile = fopen("usersFile.txt", "r");
    while((currentChar = fgetc(usersFile)) != EOF)
    {
        if(currentChar == '\n')
            count++;
    }
    fclose(usersFile);
    return count-1; // Returns count=1 because the first line is ID..
}
void fillArray()
{
    int i;
    FILE *usersFile;
    usersFile = fopen("usersFile.txt", "r");
    fscanf(usersFile, "%d\n", &currentID); // The first line in the fie contains the ID of the user that will be added
    for(i=0; i<usersInFile(); i++)
    {
        fscanf(usersFile, "%[^,],%[^,],", users[i].fName, users[i].lName);
        fscanf(usersFile, "%d,", &users[i].ID);
        fscanf(usersFile, "%d,", &users[i].age);
        fscanf(usersFile, "%[^,],", users[i].phone);
        fscanf(usersFile, "%[^,],", users[i].nationalID);
        fscanf(usersFile, "%[^,],", users[i].mail);
        fscanf(usersFile, "%d,", &users[i].booksBorrowed);
        fscanf(usersFile, "%d,%[^,],%[^\n]\n", &users[i].add.buildingNum, users[i].add.street, users[i].add.city);
    }
    arrayCount=i;
    fclose(usersFile);
}
int searchUser(int ID)
{
    int i;
    for(i=0; i<=arrayCount; i++)
    {
        if(users[i].ID==ID)
            return i;
    }
    return -1;
}
int searchNationalID(char *ID)
{
    int i, flag=0;
    for(i=0; i<=arrayCount; i++)
    {
        if(!strcmp(users[i].nationalID, ID))
            flag++;
    }
    return flag;
}
int natIDverification(char *ID)
{
    int dy, mnth, yr;
    dy = (int)(ID[5]-48)*10+(int)(ID[6]-48);
    mnth = (int)(ID[3]-48)*10+(int)(ID[4]-48);
    yr = (int)(ID[1]-48)*10+(int)(ID[2]-48);
    if(yr>17)
        yr+=1900;
    else
        yr+=2000;
    if(dateValidation(dy, mnth, yr))
        return 1;
    else
        return 0;
}
void myfgets(char *input, int n)
{
    int i;
    fgets(input, n, stdin);
    for(i=0; input[i]!='\0'; i++);
    if(input[i-1]=='\n')
        input[i-1]='\0';
}
