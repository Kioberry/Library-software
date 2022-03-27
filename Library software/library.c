#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "library.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"
#include "global.h"




//完成 可以用booklist 中的length代替？
int numBooks() {
	FILE* fp;
	int n = 0;
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	
	if (fp = fopen(bfname, "rb") == NULL) {
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
	if (numBooks() == 0) {
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


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE* file) {
	file = fopen(bfname, "w");
	if (file == NULL) {
		printf("Failed to open the file, press any key to exit!");
		getch();
		exit(0);
	}
	Book* pMove = bhead->next;
	while (pMove)
	{
		//格式需要注意？
		fprintf(file, "%d%s%s%d%d%d",pMove->id, pMove->title, pMove->authors, pMove->year, pMove->copies, pMove->originc);
		pMove = pMove->next;
	}
	fclose(file);
}


//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE* file) {
	int n, i, m = 0;
	int fid, fyear, fcopies, foriginc = 0;
	char temp1[100], temp2[100];
	Book* p, *newNode;
	memset(temp1, 0, sizeof(temp1));
	memset(temp2, 0, sizeof(temp2));
	createbList();
	if ((file = fopen(bfname, "r")) == NULL) {
		printf("Library out of stock! Press any key to exit!");
		getch();
		exit(0);
	}
	else {
		n = numBooks();
		for (i = 0; i < n; i++) {
			fscanf(file, "%d%s%s%d%d%d", &fid, temp1, temp2, &fyear, &fcopies, &foriginc);
			m++;
			if (m == 1)
			{
				//create a new node that needs to
				//be inserted into the linked list
				p = newNode = createbNode(fid, temp1, temp2, fyear, fcopies, foriginc);
				bhead->next = p;
			}
			else {
				p->next = newNode;
				p = newNode;
				newNode = createbNode(fid, temp1, temp2, fyear, fcopies, foriginc);
			}
			
		}
		if (m == 0) {
			bhead = NULL;
		}
		else
		{
			p->next = newNode;
			newNode->next = NULL;
			fclose(file);
		}
	}
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
	int fcopies, foriginc = 0; //number of copies the library has
	//BookList* booklist = initBooks(bhead);
	if ((fp = fopen(bfile, "r")) == NULL) {//二进制数据会影响到数据读取吗？
		printf("\nSorry, the record file does not exist! ");
	}
	//int n = numBooks();
	int n = booklist->length;
	for (i = 0; i < n; i++) {
		fscanf("%d%s%s%d%d%d", &fid, ftitle, fauthors, &fyear, &fcopies, &foriginc);
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
	int fcopies, foriginc = 0; //number of copies the library has
	BookList* booklist = initBooks(bhead);
	if ((fp = fopen(bfile, "r")) == NULL) {//二进制数据会影响到数据读取吗？
		printf("\nSorry, the record file does not exist! ");
	}
	//int n = numBooks();
	int n = booklist->length;
	for (i = 0; i < n; i++) {
		fscanf("%d%s%s%d%d%d", &fid, ftitle, fauthors, &fyear, &fcopies, &foriginc);
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
	int fcopies, foriginc = 0; //number of copies the library has
	BookList* booklist = initBooks(bhead);
	if ((fp = fopen(bfile, "r")) == NULL) {//二进制数据会影响到数据读取吗？
		printf("\nSorry, the record file does not exist! ");
	}
	//int n = numBooks();
	int n = booklist->length;
	for (i = 0; i < n; i++) {
		fscanf("%d%s%s%d%d%d", &fid, ftitle, fauthors, &fyear, &fcopies, &foriginc);
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

int main(void) {
	//已经外部声明的全局变量在main函数里需要重新声明吗？
	//Firstly, initialise the book linked list, user linked list and booklist structure.
	Book* bhead = createbList();
	User* uhead = createuList();
	BookList* booklist = initBooklist(bhead);
	return 0;
}