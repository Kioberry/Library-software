#ifndef LIBRARY_GUARD__H 
#define LIBRARY_GUARD__H

#include <stdio.h>

int numBooks();
void libraryCLI();
void searchMenu();
Book* createList();
Book* creatNode(int id, const char* title, const char* authors, int year, int copies);




#endif