#ifndef LIBRARY_GUARD__H 
#define LIBRARY_GUARD__H

#include <stdio.h>





//main function of the Library management system
void libraryCLI();

//Display the search menu
void searchMenu();

//calculate the number of books(method 1)
int numBooks();

//create the linked list of books
Book* createbList();

//create the linked list of users
User* createuList();

//create the node of the linked list
Book* creatbNode(int id, const char* title, const char* authors, int year, int copies);

//print the linked list of books(some problems with authors)
void printbList(Book* head);

//calculate the number of books(method 2)
int calBooks(Book* head);



#endif