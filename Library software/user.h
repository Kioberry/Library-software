#ifndef USER_GUARD__H 
#define USER_GUARD__H

#include <stdio.h>

typedef struct _User {
	int numBorrowed;
	char name[50], username[50], password[50];
	Book* borrowed;
	struct _User* next;
}User;

extern User* uhead;

extern User* theUser;

//function for the operation of User system
void userCLI();

//display the user menu
void userMenu();

//search books by one of the three ways in the user system
void userSearch();

void borrow_book();










#endif