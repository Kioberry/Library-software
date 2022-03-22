#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "library.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"


//未完成！
void libraryCLI() {
	void librarianCLI();
	void userCLI();
	char choice;
	mainMenu();
	scanf("%c", &choice);
	switch (choice) {
		case '1':

	}

}


//完成 可以用booklist 中的length代替？
int numBooks() {
	FILE* fp;
	int n = 0;
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	
	if (fp = fopen("library.txt", "r") == NULL) {
		printf("Sorry, the record file does not exist!");
		return 0;
	}
	for (n = 0; !feof(fp); n++) {
		fscanf("%d%s%s%d%d", &fid, ftitle, fauthors, &fyear, &fcopies);
	}
	n--;
	fclose(fp);
	return n;
	
}


/******The core function area******/

//create the linked list of books
Book* createbList() {
	Book* head = (Book*)malloc(sizeof(Book));
	head->next = NULL;
	return head;
}


//create the linked list of users
User* createuList() {
	User* head = (User*)malloc(sizeof(User));
	head->next = NULL;
	return head;
}

//saves the database of books in the specified file
int store_books(FILE* file) {

}


//create the node of the linked list
Book* creatbNode(int id, const char* title, const char* authors, int year, int copies) {
	//dynamically allocate the bookList array for storing books
	Book* newNode = (Book*)malloc(sizeof(Book));

	//dynamically allocate the char pointers
	newNode->title = (char*)malloc(sizeof(char)*20);
	newNode->authors = (char*)malloc(sizeof(char) * 50);
	newNode->id = id;
	newNode->title =  title;
	newNode->authors = authors;
	newNode->year = year;
	newNode->copies = copies;
	newNode->next = NULL;
	return newNode;
}


//print the linked list of books(some problems with authors)
void printbList(Book* head) {
	Book* pMove = head->next;
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



//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title(const char* title) {
	FILE* fp;
	int i, isFlag = 0;
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	BookList* booklist = initBooks(bhead);
	if ((fp = fopen("library.bin", "rb")) == NULL) {//二进制数据会影响到数据读取吗？
		printf("\nSorry, the record file does not exist! ");
	}
	//int n = numBooks();
	int n = booklist->length;
	for (i = 0; i < n; i++) {
		fscanf("%d%s%s%d%d", &fid, ftitle, fauthors, &fyear, &fcopies);
		if (!strcmp(title, ftitle)) {
			if (isFlag == 0) {
				printf("here is the searching result.\n");
				printf("\n");
				printf("ID\tTitle\t\tAuthor\t\tYear of Publication\tCopies\n");
				printf("------------------------------------------------------------------------\n");
			}
			printf("%d\t%s\t\t%s\t\t%d\t%d\n", fid, ftitle, fauthors, fyear, fcopies);
			isFlag++;
		}
	}
	if (isFlag == 0) {
		printf("Sorry, your query is invalid.");
		return ;//有问题吗？
	}
	//close the file
	fclose(fp);
	return *booklist;
}


//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author(const char* author) {
	FILE* fp;
	int i, isFlag = 0;
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	BookList* booklist = initBooks(bhead);
	if ((fp = fopen("library.bin", "rb")) == NULL) {//二进制数据会影响到数据读取吗？
		printf("\nSorry, the record file does not exist! ");
	}
	//int n = numBooks();
	int n = booklist->length;
	for (i = 0; i < n; i++) {
		fscanf("%d%s%s%d%d", &fid, ftitle, fauthors, &fyear, &fcopies);
		if (!strcmp(author, fauthors)) {
			if (isFlag == 0) {
				printf("here is the searching result.\n");
				printf("\n");
				printf("ID\tTitle\t\tAuthor\t\tYear of Publication\tCopies\n");
				printf("------------------------------------------------------------------------\n");
			}
			printf("%d\t%s\t\t%s\t\t%d\t%d\n", fid, ftitle, fauthors, fyear, fcopies);
			isFlag++;
		}
	}
	if (isFlag == 0) {
		printf("Sorry, your query is invalid.");
		return;//有问题吗？
	}
	//close the file
	fclose(fp);
	return *booklist;
}


//finds books published in the given year.
BookList find_book_by_year(unsigned int year) {
	FILE* fp;
	int i, isFlag = 0;
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	BookList* booklist = initBooks(head);
	if ((fp = fopen("library.bin", "rb")) == NULL) {//二进制数据会影响到数据读取吗？
		printf("\nSorry, the record file does not exist! ");
	}
	//int n = numBooks();
	int n = booklist->length;
	for (i = 0; i < n; i++) {
		fscanf("%d%s%s%d%d", &fid, ftitle, fauthors, &fyear, &fcopies);
		if (year == fyear) {
			if (isFlag == 0) {
				printf("here is the searching result.\n");
				printf("\n");
				printf("ID\tTitle\t\tAuthor\t\tYear of Publication\tCopies\n");
				printf("------------------------------------------------------------------------\n");
			}
			printf("%d\t%s\t\t%s\t\t%d\t%d\n", fid, ftitle, fauthors, fyear, fcopies);
			isFlag++;
		}
	}
	if (isFlag == 0) {
		printf("Sorry, your query is invalid.");
		return;//有问题吗？
	}
	//close the file
	fclose(fp);
	return *booklist;//什么时候free？
}


//完成
void searchMenu() {
	printf("\n");
	printf("\tPlease choose an option:\n");
	printf("\t1)Find books by title\n");
	printf("\t2)Find books by authors\n");
	printf("\t3)Find books by year\n");
	printf("\t4)Return to previous menu\n");
	printf("\tOption:\n");
}


//未完成！
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
