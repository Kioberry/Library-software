#include <stdio.h>

#include "user.h"
#include "book_management.h"

void userMenu() {
	printf("\t(Logged in as: %s)\n", User->name);
	printf("\n");
	printf("---------------------------------------------\n");
	printf("\t\t1) Borrow a book\n");
	printf("\t\t2) Return a book\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\t\t5) Log out\n");
	printf("\n");
	printf("\tPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------\n");
	printf("\n");
}

void userCLI() {

}