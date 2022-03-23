#ifndef USER_GUARD__H 
#define USER_GUARD__H

#include <stdio.h>

typedef struct _User {
	int numBorrowed;
	char name[50], username[50], password[50];
	struct _USer* next;
}User;

User* uhead;



//function for the operation of User system
void userCLI();

//display the user menu
void userMenu();

//search books by one of the three ways in the user system
void userSearch();

void borrow_book();










#endif