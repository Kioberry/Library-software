#pragma once
#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>

/*You can extend the structs (Book and BookList) defined in this head file;
  However, you may not change the function prototypes.
  You are also free to add additional head files and data structures as needed.
*/
//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE* file) {
	FILE* fp = fopen("book.txt", "wb");
	Book* p = bhead->next;
	while (p) {
		fscanf(fp, "%d|%[^|]|%[^|]|%d|%d|%d\n", &(p->id), p->title, p->authors, &(p->year), &(p->copies), &(p->originc));
		p = p->next;
	}
	fclose(fp);
}

void add_bookhead(Book* node)
{
	Book* p = bhead;
	while (p) {
		if (p->next == NULL) {
			p->next = node;
		}
		p = p->next;
	}
}
//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE* file) {
	file = fopen("books.txt", "rb");
	if (file == NULL) {
		printf("error");
	}
	int id;
	char title[100];
	char authors[100];
	int year;
	int cop;
	int ori;
	while (1) {
		int tag = fscanf(file, "%d|%[^|]|%[^|]|%d|%d|%d", &id, title, authors, &year, &cop, &ori);
		if (tag == -1)break;
		Book* node = (Book*)calloc(1, sizeof(Book));
		node->title = (char*)calloc(1, 50 * sizeof(char));
		node->authors = (char*)calloc(1, 50 * sizeof(char));
		node->id = id;
		strcpy(node->title, title);
		strcpy(node->authors, authors);
		node->year = year;
		node->copies = cop;
		node->originc = ori;
		add_bookhead(node);
	}
	fclose(file);
	return 0;
}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book) {
	//printf("id:%d\n", book.id);
	//printf("title:%s\n", book.title);
	//printf("authors:%s\n", book.authors);
	//printf("year:%d\n", book.year);
	//printf("copies:%d\n", book.copies);
	//printf("orignc:%d\n", book.originc);
	//getch();
	Book* node = (Book*)calloc(1, sizeof(Book));
	*node = book;
	node->next = NULL;
	Book* p = bhead;
	while (p) {
		if (p->next == NULL) {
			p->next = node;
			break;
		}
		p = p->next;
	}
	return 0;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book) {
	Book* p = bhead->next;
	Book* pre = bhead;
	while (p) {
		if (p->id == book.id && p->copies == p->originc) {
			printf("You have removed the book successfully!");
			pre->next = p->next;
			free(p->title);
			free(p->authors);
			free(p);
			return 0;
		}
		else if (p->id == book.id) {
			printf("Some users are still borrowing copies of the book, unable to delete.");
			return 2;
		}
		p = p->next;
		pre = pre->next;
	}
	printf("No book id could be found to remove");
	return 1;
}

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title(const char* title) {
	Book* p = bhead;
	BookList list0;
	list0.list = (Book*)calloc(1, sizeof(Book));
	list0.length = 0;
	while (p) {
		if (strcmp(p->title, title) == 0) {
			//copy the book into the newly created booklist
			list0.length++;
			Book* node = (Book*)calloc(1, sizeof(Book));
			*node = *p;
			node->next = NULL;
			if (list0.length == 0) {
				list0.list = node;
			}
			else {
				Book* q = list0.list;
				while (q) {
					if (q->next == NULL) {
						q->next = node;

					}
					q = q->next;
				}
			}
		}
		p = p->next;
	}
	return list0;
}

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author(const char* author) {
	Book* p = bhead->next;
	BookList list0;
	list0.list = (Book*)calloc(1, sizeof(Book));
	list0.length = 0;
	while (p) {
		if (strcmp(p->authors, author) == 0) {
			//copy the book into the newly created booklist
			list0.length++;
			Book* node = (Book*)calloc(1, sizeof(Book));
			*node = *p;
			node->next = NULL;
			if (list0.length == 0) {
				list0.list = node;
			}
			else {
				Book* q = list0.list;
				while (q) {
					if (q->next == NULL) {
						q->next = node;

					}
					q = q->next;
				}
			}
		}
		p = p->next;
	}
	//return the newly created booklist so that it can
	//be easily displayed on the screen latter
	return list0;
}

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year(unsigned int year) {
	Book* p = bhead->next;
	BookList list0;
	list0.list = (Book*)calloc(1, sizeof(Book));
	list0.length = 0;
	while (p) {
		if (p->year == year) {
			//copy the book into the newly created booklist
			Book* node = (Book*)calloc(1, sizeof(Book));
			node->title = (char*)calloc(1, 50 * sizeof(char));
			node->authors = (char*)calloc(1, 50 * sizeof(char));
			//*node = *p;
			node->id = p->id;
			strcpy(node->authors, p->authors);
			strcpy(node->title, p->title);
			node->year = p->year;
			node->copies = p->copies;
			node->originc = p->originc;
			if (list0.length == 0) {
				list0.list->next = node;
				node->next = NULL;
			}
			else {
				Book* q = list0.list->next;
				while (q) {
					if (q->next == NULL) {
						q->next = node;
						node->next = NULL;
					}
					q = q->next;
				}
			}
			list0.length++;
		}
		p = p->next;
	}
	printf("The year you entered is invalid.");
	return list0;
}