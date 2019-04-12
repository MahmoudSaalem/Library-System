#ifndef BOOKS_H_INCLUDED
#define BOOKS_H_INCLUDED

void load_books();
void save_books();
int already_exist(book);
void insert_book();
void searchMenu(int);
void multisearchmenu(int);
void isbn_search(int);
void string_search(int, int, char*);
void edit_book(book*);
void return_date();
void popular_books();
void overdueBooks();
void print_books();



#endif // BOOKS_H_INCLUDED
