#include <stdio.h>

#include "librarian.h"
#include "book_management.h"

void librarianMenu() {
	printf("\t(Logged in as: librarian)\n");
	printf("\n");
	printf("---------------------------------------------\n");
	printf("\t\t1) Add a book\n");
	printf("\t\t2) Remove a book\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\t\t5) Log out\n");
	printf("\n");
	printf("\tPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------\n");
	printf("\n");
}