#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "book_management.h"
#include "global.h"
#include "user.h"
#include "librarian.h"
#include "library.h"




//已改
//完成 可以用booklist 中的length代替？
int numBooks(FILE* file, char Filename[40]) {
	int n = 0;
	int fid = 0; //Book ID
	char ftitle[100]; //book title
	char fauthors[100]; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	int foriginc = 0;
	memset(ftitle, 0, sizeof(ftitle));
	memset(fauthors, 0, sizeof(fauthors));
	file = fopen(Filename, "r");
	if (file == NULL) {
		printf("Library out of stock!Press any key to exit!");
		getch();
		return 0;
	}
	for (n = 0; !feof(file); n++) {
		fscanf(file, "%d|%[^|]|%[^|]|%d|%d|%d", &fid, ftitle, fauthors, &fyear, &fcopies, &foriginc);
	}
	//n--;
	fclose(file);
	return n;

}


/******The core function area******/

//create the linked list of books
Book* createbList() {
	Book* bhead = (Book*)malloc(sizeof(Book));
	bhead->next = NULL;
	return bhead;
}


//create the linked list of users
User* createuList() {
	//dynamically allocate the userList array for storing books
	User* uhead = (User*)malloc(sizeof(User));

	//initializing the string array
	memset(uhead->name, 0, sizeof(uhead->name));
	memset(uhead->username, 0, sizeof(uhead->username));
	memset(uhead->password, 0, sizeof(uhead->password));
	uhead->next = NULL;
	return uhead;
}


//create the node of the linked list
Book* createbNode(int id, char temp1[100], char temp2[100], int year, int copies, int originc) {
	//dynamically allocate the bookList array for storing books
	Book* newNode = (Book*)malloc(sizeof(Book));

	//dynamically allocate the char pointers
	newNode->title = (char*)malloc(strlen(temp1));
	newNode->authors = (char*)malloc(strlen(temp2));
	newNode->id = id;
	strcpy(newNode->title, temp1);
	strcpy(newNode->authors, temp2);
	newNode->year = year;
	newNode->copies = copies;
	newNode->originc = originc;
	newNode->next = NULL;
	return newNode;
}

User* createuNode(int numBorrowed, char name[50], char username[50], char password[50], Book* borrowed) {
	//dynamically allocate the bookList array for storing books
	User* newNode = (User*)malloc(sizeof(User));

	newNode->numBorrowed = numBorrowed;
	strcpy(newNode->name, name);
	strcpy(newNode->username, username);

	newNode->borrowed = (Book*)malloc(sizeof(Book));
	return newNode;
}


//print the linked list of books(some problems with authors)
void display_books(Book* head) {
	if (numBooks(bfile, bfname) == 0) {
		printf("There are no books in the library, please contact the administrator to add books!\n");
		return;
	}
	Book* pMove = (Book*)malloc(sizeof(Book));
	pMove = head->next;
	printf("id\ttitle\tauther\tyear\tcopies\n");
	while (pMove) {
		printf("%d\t%s\t%s\t%d\n", pMove->id, pMove->title, pMove->authors, pMove->year, pMove->copies);
		pMove = pMove->next;
	}
	printf("\n");
}


//calculate the number of books
int calBooks(Book* head) {
	Book* pMove = head->next;
	int n = 0;
	while (pMove) {
		n++;
		pMove = pMove->next;
	}
	return n;
}



//initialize the struct Booklist
BookList* initBooklist(Book* head) {
	int calBooks(head);//需要声明吗？
	BookList* booklist = (BookList*)malloc(sizeof(BookList));
	booklist->list = head;
	booklist->length = calBooks(head);
	return booklist;
}

//The search interface shown on the screen
void searchMenu() {
	printf("\n");
	printf("\tPlease choose an option:\n");
	printf("\t1)Find books by title\n");
	printf("\t2)Find books by authors\n");
	printf("\t3)Find books by year\n");
	printf("\t4)Return to previous menu\n");
	printf("\tOption:");
}

void search_for_books() {
	searchMenu();
	char choice = 0;
	scanf("%c", choice);
	switch (choice) {
		case '1':
		{
			char * title = { '\0' };
			printf("Please enter the title of the book: ");
			scanf("%s", title);
			find_book_by_title(title);
			break;
		}
		case '2':
		{
			char* authors = { '\0' };
			printf("Please enter the author of the book(separate them with commas): ");
			scanf("%s", authors);
			find_book_by_author(authors);
			break;
		}
		case '3':
		{
			int year = 0;
			printf("Please enter the publication of of the book(separate them with commas): ");
			scanf("%s", year);
			find_book_by_year(year);
			break;
		}
		case '4':
			break;
		default:
			printf("Sorry, your option is invalid");		
	}
	getch();
}

void libraryCLI() {
	//已经外部声明的全局变量在main函数里需要重新声明吗？
	//Firstly, initialise the book linked list, user linked list and booklist structure.
	Book* bhead = createbList();
	User* uhead = createuList();
	BookList* booklist = initBooklist(bhead);
	FILE* bfile = NULL;
	signCLI();
}