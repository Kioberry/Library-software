#ifndef LIBRARY_GUARD__H 
#define LIBRARY_GUARD__H

#include <stdio.h>



//calculate the number of books(method 1)
int numBooks();

//create the linked list of books
Book* createbList();

//create the linked list of users
User* createuList();

//create the node of the book linked list
Book* creatbNode(int id, const char* title, const char* authors, int year, int copies);

//create the node of the user linked list
User* createuNode(int numBorrowed, char name[50], char username[50], char password[50], Book* borrowed);

//print the linked list of books(some problems with authors)
void display_books(Book* head);

//calculate the number of books(method 2)
int calBooks(Book* head);

//initialize the struct Booklist
BookList* initBooklist(Book* head);

//Display the search menu
void searchMenu();

void search_for_books();
#endif