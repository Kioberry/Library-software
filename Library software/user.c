#include <stdio.h>

#include "user.h"
#include "library.h"
#include "book_management.h"

void userMenu() {
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

//search books by one of the three ways in the user system
void userSearch() {
	searchMenu();
	char choice = 0;
	scanf("%c", choice);
	for (;;) {
		switch (choice) {
		case '1':
		{
			char* title = { '\0' };
			printf("Please enter the title of the book: ");
			scanf("%s", title);
			find_book_by_title(title);
			getch();
			userSearch();
			break;
		}
		case '2':
		{
			char* authors = { '\0' };
			printf("Please enter the author of the book(separate them with commas): ");
			scanf("%s", authors);
			find_book_by_author(authors);
			getch();
			userSearch();
			break;
		}
		case '3':
		{
			int year = 0;
			printf("Please enter the publication of of the book(separate them with commas): ");
			scanf("%s", year);
			find_book_by_year(year);
			getch();
			userSearch();
			break;
		}
		case '4':
			userCLI();
			break;
		default:
			printf("Sorry, your option is invalid");
			getch();
			userSearch();
		}
	}
}


void userCLI() {
	printf("\t(Logged in as: %s)\n", User->name);
}