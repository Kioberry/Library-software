#include "book_management.h"
#include "user.h"
#include "stdio.h"
#include "stdlib.h"
user* curuser;
char name[3][100];

void save_loan(user* userhead)
{
	FILE* fp = fopen(name[2], "wb");
	user* p = userhead->next;
	while (p)
	{
		int i0 = 0;
		for (i0 = 0; i0 < p->borrow_len; i0++)
		{
			fprintf(fp, "%s %d\n", p->name, p->borrow[i0]);
		}
		p = p->next;
	}
	fclose(fp);
}
void save()
{
	FILE* fp = fopen(name[0], "wb");
	store_books(fp);
	save_user(userhead, name[1]);
	save_loan(userhead);
}
void load() {
	FILE* fp = fopen(name[0], "rb");
	load_books(fp);
	load_user(userhead, name[1]);
}

/****Module of Displaying Books****/
//Display all books in the library
void display()
{
	Book* p = bhead->next;
	printf("ID\ttitle\tauthors\tyear\tcopies\n");
	printf("---------------------------------------------------\n");
	while (p) {
		printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->authors, p->year, p->copies);
		p = p->next;
	}
}
//Display books of the searching result
void displaylist(BookList a)
{
	Book* p = a.list->next;
	printf("ID\ttitle\tauthors\tyear\tcopies\n");
	for (int i0 = 0; i0 < a.length; i0++) {
		printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->authors, p->year, p->copies);
		p = p->next;
	}
}

/***Module of Seaching Books***/
//The search interface shown on the screen
void searchMenu() {
	printf("\n");
	printf("Load search menu...\n");
	printf("---------------------------------------------------\n");
	printf("\t1)Find books by title\n");
	printf("\t2)Find books by authors\n");
	printf("\t3)Find books by year\n");
	printf("\t4)Return to previous menu\n");
	printf("\nPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------------\n");
	printf("\n");
	printf("Option:");
}
//The CLI of the finding books function
void find()
{
	searchMenu();
	int key = 0;
	scanf("%d", &key);
	BookList a;
	if (key == 1)
	{
		char str[40];
		scanf("%s", str);
		a = find_book_by_title(str);
	}
	if (key == 2)
	{
		char str[40];
		scanf("%s", str);
		a = find_book_by_author(str);
	}
	if (key == 3)
	{
		int year;
		scanf("%d", &year);
		a = find_book_by_year(year);
	}
	displaylist(a);
	if (key == 4)
	{
		return;
	}
}


/***Module of the Librarian System****/
//display the librarian menu
void cmd_menu()
{
	printf("\n(Logged in as: librarian)\n");
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("\t1) Add a book\n");
	printf("\t2) Remove a book\n");
	printf("\t3) Search for books\n");
	printf("\t4) Display all books\n");
	printf("\t5) Log out\n");
	printf("\n");
	printf("Please choose an option, press Enter to confirm\n");
	printf("---------------------------------------------------\n");
	printf("\n");
	printf("Option:");
}
//add books function
void cmd1()
{
	Book node;
	node.title = (char*)calloc(1, 100 * sizeof(char));
	node.authors = (char*)calloc(1, 100 * sizeof(char));
	printf("Enter the id of the book you wish to add:");
	int tag = 1;
	while (tag)
	{
		tag = 0;
		scanf("%d", &(node.id));
		if (node.id < 0)
		{
			printf("error try again\n");
			tag = 1;
		}
	}
	tag = 1;
	while (tag) {
		tag = 0;
		printf("Enter the title of the book you wish to add:");
		scanf("%s", node.title);
		int i0 = 0;
		for (i0 = 0; i0 < strlen(node.title); i0++)
		{
			if (node.title[i0] <= '9' && node.title[i0] >= '0')
			{
				printf("error try again\n");
				tag = 1;
				break;
			}
		}
	}
	tag = 1;
	while (tag) {
		tag = 0;
		printf("Enter the authors of the book you wish to add:");
		scanf("%s", node.authors);
		int i0 = 0;
		for (i0 = 0; i0 < strlen(node.authors); i0++)
		{
			if (node.authors[i0] <= '9' && node.authors[i0] >= '0')
			{
				printf("error try again\n");
				tag = 1;
				break;
			}
		}
	}
	tag = 1;
	while (tag) {
		tag = 0;
		printf("Enter the year of the book you wish to add:");
		char str[50];
		scanf("%s", str);
		for (int i0 = 0; i0 < strlen(str); i0++) {
			if (str[i0] < 'z' && str[i0]>'a') {
				tag = 1;
			}
			if (str[i0] < 'Z' && str[i0]>'A') {
				tag = 1;
			}
		}
		if (tag == 1) {
			printf("try again\n");
		}
		if (tag == 0)
			node.year = atoi(str);
	}
	tag = 1;
	while (tag) {
		tag = 0;
		printf("Enter the number of the book you wish to add:");
		char str[50];
		scanf("%s", str);
		if (node.copies < 0) {
			printf("error try again\n");
			tag = 1;
		}
		if (node.copies >= 'a' && node.copies <= 'z') {
			printf("error try again\n");
			tag = 1;
		}
		if (node.copies >= 'A' && node.copies <= 'Z') {
			printf("error try again\n");
			tag = 1;
		}
		if (tag == 0)
			node.copies = atoi(str);
	}
	node.originc = node.copies;
	printf("You have successfully add a book!\n");
	add_book(node);
}
//remove books function
void cmd2()
{
	int id;
	printf("Enter the id of the book you wish to delete:");
	scanf("%d", &id);
	Book node;
	node.id = id;
	int tag = remove_book(node);
	if (tag == 0) {
		printf("success\n");
	}
	else {
		printf("fail\n");
	}
}
//the searching books function in librarianCLI
void cmd3()
{
	find();
}
//the displaying books function in librarianCLI
void cmd4()
{
	display();
}
//the librarianCLI
void cmd0()
{
	while (1) {
		cmd_menu();
		int key;
		scanf("%d", &key);
		if (key == 1)
		{
			cmd1();
		}
		if (key == 2)
		{
			cmd2();
		}
		if (key == 3)
		{
			cmd3();
		}
		if (key == 4)
		{
			cmd4();
		}
		if (key == 5)
		{
			printf("Logging out...\n");
			break;
		}
		if (key <= 0 || key > 5)
		{
			printf("error try again");
		}
		save();
		getchar();
	}
}

/***Module of the User System****/
//display the user menu
void user_menu()
{
	printf("\n");
	printf("---------------------------------------------\n");
	printf("\t\t1) Borrow a book\n");
	printf("\t\t2) Return a book\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\t\t5) Log out\n");
	printf("\n");
	printf("\tPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------\n");
	printf("\n");
	printf("Option:");
}
//borrow books function
void user1()
{
	printf("Enter the ID number of the book you wish to borrow:");
	int id;
	scanf("%d", &id);
	Book* p = bhead->next;
	while (p)
	{
		if (p->id == id && p->copies > 0 && curuser->borrow_len < 6)
		{
			if (p->copies <= 0)
			{
				printf("error copies=0\n");
				return;
			}
			if (curuser->borrow_len == 6)
			{
				printf("error borrow_len=6\n");
				return;
			}
			p->copies -= 1;
			curuser->borrow[curuser->borrow_len - 1] = id;
			curuser->borrow_len++;
			printf("success\n");
			return;
		}
		p = p->next;
	}
	printf("fail\n");
}
//return books function
void user2()
{
	printf("Below is the list of Books you are currently borrowing:\n");
	printf("ID        Title      Authors     year\n");
	Book* p = bhead->next;
	while (p)
	{
		int i0 = 0;
		for (i0 = 0; i0 < curuser->borrow_len; i0++)
		{
			if (p->id == curuser->borrow[i0])
			{
				printf("%d %s %s %d\n", p->id, p->title, p->authors, p->year);
				break;
			}
		}
		p = p->next;
	}
	printf("Enter the ID number of the book you wish to return:");
	int id = 0;
	scanf("%d", &id);
	p = bhead->next;
	while (p)
	{
		if (p->id == id)
		{
			p->copies++;
			int i0 = 0;
			for (i0 = 0; i0 < curuser->borrow_len; i0++)
			{
				if (p->id == curuser->borrow[i0])
				{
					int i1 = 0;
					for (i1 = i0; i1 < curuser->borrow_len; i1++)
					{
						curuser->borrow[i1] = curuser->borrow[i1 + 1];
					}
					break;
				}
				printf("Returned book successfully\n");
			}
		}
		p = p->next;
	}
}
//the searching books function in userCLI
void user3()
{
	find();
}
//the displaying books function in userCLI
void user4()
{
	display();
}
//the userCLI
void user0()
{
	while (1)
	{
		user_menu();
		int key;
		scanf("%d", &key);
		if (key == 1)
		{
			user1();
		}
		if (key == 2)
		{
			user2();
		}
		if (key == 3)
		{
			user3();
		}
		if (key == 4)
		{
			user4();
		}
		if (key == 5)
		{
			printf("Returning to previous menu...\n");
			break;
		}
		if (key <= 0 || key > 5)
		{
			printf("error try again");
		}
		save();
		getchar();
	}
}


/***Module of the Login System****/
//display the main menu
void log_menu()
{
	printf("\nWelcome to the Library Management System\n");
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("\t1) Register an account\n");
	printf("\t2) Login\n");
	printf("\t3) Search for books\n");
	printf("\t4) Display all books\n");
	printf("\t6) Quit\n");
	printf("\n");
	printf("Please choose an option, press Enter to confirm\n");
	printf("---------------------------------------------------\n");
	printf("\n");
	printf("Option: ");

}
//user registration function
void log1()
{
	int tag = 2;
	while (tag == 2) {
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

		if (tag == 2) {
			printf("Registered successfully!\n");
			user* node = (user*)calloc(1, sizeof(user));
			strcpy(node->name, name);
			strcpy(node->password, password);
			node->next = userhead->next;
			userhead->next = node;
			return;
		}
	}
	if (tag == 1) {
		printf("Sorry, registration unsuccessful, the username you entered already exist\n");
		return;
	}


}
//user login function
void log2()
{
	int tag = 1;
	char name[50];
	char password[50];
	while (tag == 1) {
		printf("intput name:");
		scanf("%s", name);
		printf("input password:");
		scanf("%s", password);
		if (strcmp(name, "librarian") == 0 && strcmp(password, "librarian") == 0) {
			tag = 3;
			break;
		}
		user* p = userhead->next;
		while (p) {
			if (strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0) {
				tag = 2;
				curuser = p;
			}
			p = p->next;
		}
		if (tag == 1) {
			printf("The username or password is not true, try again\n");
			return;
		}

	}
	if (tag == 3) {
		cmd0();
	}
	if (tag == 2) {
		user0();
	}
}
//the searching books function in logCLI
void log3()
{
	find();
}
//the displaying books function in logCLI
void log4()
{
	display();
}
//the displayment of manuls
void log5() {
	printf("manual\n");
	printf("log\n");
	printf("\t\t1) Register an account\n");
	printf("\t\t2) Login\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\t\t5) System Manual\n");
	printf("user\n");
	printf("\t\t1) Borrow a book\n");
	printf("\t\t2) Return a book\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("cmd\n");
	printf("\t\t1) Add a book\n");
	printf("\t\t2) Remove a book\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\n\n");
}
//the logCLI
void log0()
{
	while (1)
	{
		log_menu();
		int key;
		scanf("%d", &key);
		if (key == 1)
		{
			log1();
		}
		if (key == 2)
		{
			log2();
		}
		if (key == 3)
		{
			log3();
		}
		if (key == 4)
		{
			log4();
		}
		if (key == 5) {
			log5();
		}
		if (key == 6) {
			printf("Thank you for using the library system!\n");
			printf("Goodbye!\n");
			break;
		}
		if (key < 0 || key>6)
		{
			printf("error try again\n");
		}
		save();
		getchar();
	}
}


int main(int argc, char* argv[])
{
	//// check that correct number of command line arguments are entered    
	//if (argc < 4)
	//{
	//	printf("The arguments you enteres is not enough.Use default file.\n");
	//	exit(1);
	//}
	//// assign command line value to filename string
	//if (argc > 1)  strcpy(name[0], argv[1]);
	//if (argc > 2)  strcpy(name[1], argv[2]);
	//if (argc > 3)  strcpy(name[2], argv[3]);
	strcpy(name[0], "books.txt");
	strcpy(name[1], "users.txt");
	strcpy(name[2], "loans.txt");
	userhead = (user*)calloc(1, sizeof(user));
	bhead = (Book*)calloc(1, sizeof(Book));
	load();
	

	log0();
	return 0;
}