#ifndef USER_GUARD__H 
#define USER_GUARD__H

#include <stdio.h>

typedef struct _User {
	int numBorrowed;
	char name[20], username[20], password[20];
	struct _USer* next;
}User;

void userMenu();
void userCLI();










#endif