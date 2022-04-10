#ifndef _USR
#define _USR
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct User {
	char name[50];
	char password[50];
	Book* bolist;
	struct User* next;
}user;
user* uhead;
user theUser;
void load_user(user* userhead);
void save_user(user* userhead);
int add_user(user theUser);
int bor_book(int id);
int rtrn_book(int id);
#endif










#endif