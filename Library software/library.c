#include <stdio.h>

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


//create the linked list of books
Book* createList() {
	Book* head = (Book*)malloc(sizeof(Book));
	head->next = NULL;
	return head;
}

//create the node of the linked list
Book* creatNode(int id, const char* title, const char* authors, int year, int copies) {
	Book* newNode = (Book*)malloc(sizeof(Book));
	title = 
	newNode->id = id;
	strcpy(newNode->title, title);
	strcpy(newNode->authors, authors);
	newNode->year = year;
	newNode->copies = copies;
	newNode->next = NULL;
}

//print the linked list of books(some problems with authors)
void printList(Book* head) {
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
void initBooklist(Book* head) {
	int calBooks(head);//需要声明吗？
	BookList* booklist = (BookList*)malloc(sizeof(BookList));
	booklist->list = head;
	booklist->length = calBooks(head);
}


//未完成！
BookList find_book_by_title(const char* title) {
	FILE* fp;
	int i, isFlag = 0;
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	if ((fp = fopen("library.txt", "r")) == NULL) {
		printf("\nSorry, the record file does not exist! ");
	}
	int n = numBooks();
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
		
	}
}
//完成
void searchMenu() {
	printf("\n");
	printf("\tPlease choose an option:\n");
	printf("\t1)find books by title\n");
	printf("\t2)find books by author\n");
	printf("\t3)find books by year\n");
	printf("\tOption:\n");
}

void search_for_books() {
	searchMenu();
	char choice = 0;
	scanf("%c", choice);
	switch (choice) {
		case '1':
		{
			char * title[30] = { '\0' };
			printf("Please enter the title of the book: ");
			scanf("%s", title);
			find_book_by_title(title);
			break;
		}
		case '2':
		{

		}
			
	}
}
void mainCLI() {

}