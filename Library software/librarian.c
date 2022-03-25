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
//在else里返回了其他条件还需要吗？
int add_book(Book book) {
	char temp1[100] = '\0', temp2[100] = '\0';
	int n = 0;
	int year, copies = 0;
	int t1, t2, t3, t4 = 0;
	Book* p,* p1,  *newNode;
	load_books(bfile);
	printf("Enter the title of the book you wish to add: ");
	t1 = scanf("%s", temp1);
	printf("Enter the author of the book you wish to add (separate them with commas): ");
	t2 = scanf("%s", temp2);
	printf("Enter the year that the book you wish to add was released: ");
	t3 = scanf("%d", year);
	printf("Enter the number of the copies of the book that you wish to add: ");
	t4 = scanf("%d", copies);
	if (t1 == 0 || t2 == 0 || t3 == 0 || t4 == 0) {
		printf("Sorry, you attempt to add an invalid book, please try again.");
		userCLI();
	}
	if (t1 == -1 || t2 == -1 || t3 == -1 || t4 == -1) {
		printf("End of input stream.");
		userCLI();
	}
	else {
		n = numBooks();
		//booklist->length 什么时候用还是没有搞清楚
		(booklist->length)++;
		book.id = n + 1;
		book.authors = temp1;
		book.title = temp2;
		book.year = year;
		book.copies = copies;
		newNode = &book;
		p = bhead;
		//transverse to get the last node of the linled list
		while (p1) {
			p->next = p1;
			p = p1;
			p1 = p1->next;
		}
		p->next = newNode;
		newNode->next = NULL;
		store_books(bfile);
		printf("\nSave successfully, press any key to return to the previous menu");
		getch();
		printf("\nReturning to previous menu...\n");
		system("pause");
		librarianCLI();
		return 0;
	}

}


//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book) {
	char temp1[100] = '\0';
	int t1 = 0;
	Book* pFront, *p;
	load_books(bfile);
	printf("Enter the title of the book you wish to remove: ");
	t1 = scanf("%s", temp1);
	pFront = bhead;
	p = bhead->next;
	while (strcmp(temp1, p->title)) {
		pFront = p;
		p = p->next;
		if (p == NULL) {
			printf("\nNo book was found to delete, please try again");
			librarianCLI();
		}
	}
	pFront->next = p->next;
	--(booklist->length);
	free(p);
	store_books(bfile);
	printf("\nsave successfully, press any key to return to the previous menu");
	getch();
	printf("\nReturning to previous menu...\n");
	system("pause");
	librarianCLI();
	return 0;
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