#ifndef _USR
#define _USR

#include "stdio.h"
#include "stdlib.h"
#include "book_management.h"
typedef struct User {
	char name[50];
	char password[50];
	int borrow[6];
	int borrow_len;
	struct User* next;
}user;

user* userhead;
void load_user(user* userhead0);
void save_user(user* userhead0);

#endif