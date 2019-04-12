#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct address
{
    int buildingNum;
    char city[20];
    char street[30];
} address;

typedef struct user
{
    char fName[20];
    char lName[20];
    int ID;
    int age;
    int booksBorrowed;
    char phone[20];
    char nationalID[15];
    char mail[50];
    address add;
} user;
typedef struct
{
    int day;
    int month;
    int year;
} Date;
typedef struct book
{
    int copies, available, on, nBorrowed,aBorrows;
    char title[100], isbn[14], author[100], category[30], publisher[100];
    Date dateofpublication;
} book;
typedef struct Borrowed
{
    int memberID;
    char bookISBN[14];
    Date issued;
    Date duetoreturn;
    Date returned;
} Borrowed;

#endif // STRUCT_H_INCLUDED
