#ifndef _USR
#define _USR
#include "stdio.h"
#include "stdlib.h"
#include "book_management.h"
typedef struct User {
	char name[50];//User name
	char password[50];//User Password
	int borrow[6];//the int array to store the id of the books that user borrowed
	int borrow_len;//the number of books user has borrowed
	struct User* next;
}user;

user* userhead;
//loads the database of users from the specified file
void load_user(user* userhead0);
//saves the database of users from the specified file
void save_user(user* userhead0);
#endif










#endif