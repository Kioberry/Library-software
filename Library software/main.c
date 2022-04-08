#define _CRT_SECURE_NO_WARNINGS

// Name:Wanrong Xie
// Username:201487690
// Date started:2022.3.15

#include "book_management.h"
#include "user.h"
#include "conio.h"
void menu() {
	printf("\t(Logged in as: librarian)\n");
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("\t1) Add a book\n");
	printf("\t2) Remove a book\n");
	printf("\t3) Search for books\n");
	printf("\t4) Display all books\n");
	printf("\t5) Log out\n");
	printf("\n");
	printf("\tPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------------\n");
	printf("\n");
	printf("Option:");
}
void add() {
	Book node;
	node.title = (char*)calloc(1, 50 * sizeof(char));
	node.authors = (char*)calloc(1, 50 * sizeof(char));
	//unsigned int id; //Book ID
	//char* title; //book title
	//char* authors; //comma separated list of authors
	//unsigned int year; // year of publication
	//unsigned int copies; //number of copies the library has
	//unsigned int originc;//number of the original copies the library has
	printf("id:");
	scanf("%d", &(node.id));
	printf("title:");
	scanf("%s", node.title);
	printf("authors:");
	scanf("%s", node.authors);
	printf("year:");
	scanf("%d", &(node.year));
	printf("copies:");
	scanf("%d", &(node.copies));
	printf("originc:");
	scanf("%d", &(node.originc));
	node.next = 0;
	add_book(node);
}
void del() {
	int id;
	printf("id:");
	scanf("%d", &id);
	Book node;
	node.id = id;
	remove_book(node);
}
void display() {
	Book* p = bhead->next;
	while (p) {
		printf("id:%d\n", p->id);
		printf("title:%s\n", p->title);
		printf("authors:%s\n", p->authors);
		printf("year:%d\n", p->year);
		printf("copies:%d\n", p->copies);
		printf("orignc:%d\n", p->originc);
		printf("\n");
		p = p->next;
	}
}
void displaylist(BookList a) {
	//unsigned int id; //Book ID
//char* title; //book title
//char* authors; //comma separated list of authors
//unsigned int year; // year of publication
//unsigned int copies; //number of copies the library has
//unsigned int originc;//number of the original copies the library has
	Book* p = a.list;
	for (int i0 = 0; i0 < a.length; i0++) {
		/////////////////////////////////
		printf("id:%d\n", p->id);
		printf("title:%s\n", p->title);
		printf("authors:%s\n", p->authors);
		printf("year:%d\n", p->year);
		printf("copies:%d\n", p->copies);
		printf("orignc:%d\n", p->originc);
		printf("\n");
		p = p->next;
	}
}
void find() {
	printf("1.title\n");
	printf("2.name\n");
	printf("3.year\n");
	printf("option:");
	int key = 0;
	scanf("%d", &key);
	BookList a;
	if (key == 1) {
		char str[40];
		scanf("%s", str);
		a = find_book_by_title(str);
	}
	if (key == 2) {
		char str[40];
		scanf("%s", str);
		a = find_book_by_author(str);
	}
	if (key == 3) {
		int year;
		scanf("%s", &year);
		a = find_book_by_year(year);
	}
	displaylist(a);
}
int main() {
	user* userhead = (user*)calloc(1, sizeof(user));
	bhead = (Book*)calloc(1, sizeof(Book));
	load_user(userhead);
	int tag = 1;
	while (tag) {
		char name[50];
		char password[50];
		printf("intput name:");
		scanf("%s", name);
		if (strcmp(name, "librarian") == 0) {
			tag = 1;
			break;
		}
		printf("input password:");
		scanf("%s", password);
		user* p = userhead->next;
		while (p) {
			if (strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0) {
				tag = 1;
				break;
			}
			p = p->next;
		}

		if (tag == 0) {
			printf("try again\n");
		}
	}
	while (1) {
		menu();
		int key = 0;
		scanf("%d", &key);
		switch (key) {
		case 1:add(); break;
		case 2:del(); break;
		case 3:find(); break;
		case 4:display(); break;
		case 5:exit(0);
		default:
			printf("try again\n");
		}
		getch();
	}
	return 0;
}