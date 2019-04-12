#ifndef MEMBERS_H_INCLUDED
#define MEMBERS_H_INCLUDED

void filesCheck(); // Creating the necessary files at the first run
void addUser(); // Adding a user to the array
void deleteUser(); // Deleting a user from the array
void editUser();
void printArray(); // Prints the data in the array
void saveToFile(); // Saving the changes made in the array to the file
void fillArray(); // Filling the array with the data in the file at the beginning of the program
void myfgets(char*, int);
int usersInFile(); // Counting how many lines in the file, thus, knowing the number of users
int searchUser(int); // Returns the position of the user in the array of structures or -1 if not found
int searchNationalID(char*);
int natIDverification(char*);

#endif // MEMBERS_H_INCLUDED
