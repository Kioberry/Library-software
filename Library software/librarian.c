#include <stdio.h>

#include "librarian.h"
#include "library.h"
#include "user.h"
#include "book_management.h"
#include "global.h"

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
	char temp1[100] = '\0', temp2[100] = '\0';
	int year, copies = 0;
	printf("Enter the title of the book you wish to add: ");
	scanf("%s", temp1);
	printf("Enter the author of the book you wish to add (separate them with commas): ");
	scanf("%s", temp2);
	printf("Enter the year that the book you wish to add was released: ");
	scanf("%d", year);
	printf("Enter the number of the copies of the book that you wish to add: ");
	scanf("%d", copies);

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

//search books by one of the three ways in the user system
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
			getch();
			librarianSearch();
			break;
		}
		case '2':
		{
			char* authors = { '\0' };
			printf("Please enter the author of the book(separate them with commas): ");
			scanf("%s", authors);
			find_book_by_author(authors);
			getch();
			librarianSearch();
			break;
		}
		case '3':
		{
			int year = 0;
			printf("Please enter the publication of year: ");
			scanf("%s", year);
			find_book_by_year(year);
			getch();
			librarianSearch();
			break;
		}
		case '4':
			printf("\nReturning to previous menu...\n");
			librarianCLI();
			break;
		default:
			printf("Sorry, your option is invalid");
			getch();
			librarianSearch();
		}
	}
}

int main(void) {
	 
}