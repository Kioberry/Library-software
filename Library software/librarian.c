#include <stdio.h>

#include "librarian.h"
#include "library.h"
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
	Book* newNode = creatNode(book.id, book.title, book.authors, book.year, book.copies);
	newNode->next = book.next;
	book.next = newNode;
	return 0;
}