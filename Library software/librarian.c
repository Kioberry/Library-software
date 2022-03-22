#include <stdio.h>

#include "librarian.h"
#include "library.h"
#include "user.h"
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


//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book) {
	
}

//display the linked list of users(new feature)
void displayUsers(User* head) {
	User* pMove = head->next;
	printf("numBorrowed\tname\tusername\tpassword");
	while (pMove) {
		printf("%d\t%s\t%s\t%s\n", pMove->numBorrowed, pMove->name, pMove->username, pMove->password);
		pMove = pMove->next;
	}
	printf("\n");
}

void librarianSearch() {
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
			getchar();
			librarianSearch();
			break;
		}
		case '2':
		{
			char* authors = { '\0' };
			printf("Please enter the author of the book(separate them with commas): ");
			scanf("%s", authors);
			find_book_by_author(authors);
			getchar();
			librarianSearch();
			break;
		}
		case '3':
		{
			int year = 0;
			printf("Please enter the publication of of the book(separate them with commas): ");
			scanf("%s", year);
			find_book_by_year(year);
			getchar();
			librarianSearch();
			break;
		}
		case '4':
			librarianCLI();
			break;
		default:
			printf("Sorry, your option is invalid");
			getchar();
			librarianSearch();
		}
	}
}