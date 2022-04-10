#include <stdlib.h>

#include "book_management.h"
#include "user.h"
#include "conio.h"

user* curuser;//the user pointer of the current user logged in

void save_loan(user* userhead)
{
	FILE* fp = fopen("loan.txt", "wb");
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
	store_books(NULL);

	save_user(userhead);
	save_loan(userhead);
}
void load() {
	load_books(NULL);
	system("pause");
	load_user(userhead);
}

// read in a line of text and convert to an integer option
int optionChoice(void) {
	int option = -1;
	char line[80];

	// read in the current line as a string
	fgets(line, 80, stdin);

	// atoi() converts string to integer, returns 0 if could not convert
	option = (int)atoi(line);

	return option;
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
	//unsigned int id; //Book ID
//char* title; //book title
//char* authors; //comma separated list of authors
//unsigned int year; // year of publication
//unsigned int copies; //number of copies the library has
//unsigned int originc;//number of the original copies the library has
	Book* p = a.list;
	printf("ID      Title       Authors year copies\n");
	for (int i0 = 0; i0 < a.length; i0++) {
		/////////////////////////////////
		//printf("id:%d\n",p->id);
		//printf("title:%s\n",p->title);
		//printf("authors:%s\n",p->authors);
		//printf("year:%d\n",p->year);
		//printf("copies:%d\n",p->copies);
		//printf("orignc:%d\n",p->originc);
		//printf("\n");
		printf("%d %s %s %d %d\n", p->id, p->title, p->authors, p->year, p->copies);
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
	getchar();
	int key = optionChoice();
	BookList a;
	if (key == 1)
	{
		char str[40];
		fflush(stdin);
		scanf("%s", str);
		a = find_book_by_title(str);
	}
	if (key == 2)
	{
		char str[40];
		fflush(stdin);
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
		printf("\nReturning to previous menu...\n");
		return;
	}
}



/***Module of the Librarian System****/
//display the librarian menu
void libmenu()
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
	int year = 0;
	int copies = 0;
	int i = 0;
	Book node;
	node.title = (char*)calloc(1, 50 * sizeof(char));
	node.authors = (char*)calloc(1, 50 * sizeof(char));
	//int tag = 1;
	printf("Enter the id of the book you wish to add:");
	scanf("%d", &(node.id));
	printf("Enter the title of the book you wish to add:");
	scanf("%s", node.title); fflush(stdin);
	printf("Enter the authors of the book you wish to add:");
	scanf("%s", node.authors);
	printf("Enter the year of the book you wish to add:");
	getchar();
	year = optionChoice();
	node.year = year;
	printf("Enter the copies of the book you wish to add:");
	getchar();
	copies = optionChoice();
	node.copies = copies;
	if (node.id < 0 || node.year < 0 || node.year>2022 || node.copies < 0) {
		printf("Sorry, you attemped to add an invalid book, please try again.\n");
	}
	for (i = 0; i < strlen(node.authors); i++) {
		if (node.authors[i] <= '9' && node.authors[i] >= '0') {
			printf("Sorry, your attempt to add the authors of the book is invalid");
		}
	}
	//while (tag)
	//{
	//	printf("Enter the id of the book you wish to add:");
	//	tag = 0;
	//	t1 = scanf("%d", &(node.id));
	//	if (node.id < 0)
	//	{
	//		printf("id cannot be negative\n");
	//		tag = 1;
	//	}
	//	if (t1 == 0) {
	//		printf("You have entered an invalid book!");
	//	}
	//}
	//tag = 1;
	//while (tag) {
	//	tag = 0;
	//	printf("Enter the title of the book you wish to add:");
	//	t1 = scanf("%s", node.title);
	//	int i0 = 0;
	//	for (i0 = 0; i0 < strlen(node.title); i0++)
	//	{
	//		if (node.title[i0] <= '9' && node.title[i0] >= '0')
	//		{
	//			printf("error try again\n");
	//			tag = 1;
	//		}
	//		if (t1 == 0) {
	//			printf("You have entered an invalid book!");
	//		}
	//	}
	//}
	//tag = 1;
	//while (tag) {
	//	tag = 0;
	//	printf("Enter the authors of the book you wish to add:");
	//	t1 = scanf("%s", node.authors);
	//	int i0 = 0;
	//	for (i0 = 0; i0 < strlen(node.authors); i0++)
	//	{
	//		//the entered authors' name cannot include numbers
	//		if (node.authors[i0] <= '9' && node.authors[i0] >= '0')
	//		{
	//			printf("error try again\n");
	//			tag = 1;
	//		}
	//		if (t1 == 0) {
	//			printf("You have entered an invalid book!");
	//		}
	//	}
	//}
	//tag = 1;
	//while (tag) {
	//	tag = 0;
	//	printf("Enter the year of the book you wish to add:");
	//	t1 = scanf("%d", &(node.year));
	//	//The year of publication can neither be bigger than this year
	//	//nor smaller than 0
	//	if (t1 == 0) {
	//		printf("You have entered an invalid book!");
	//	}
	//	if (node.year < 0 || node.year>2022) {
	//		printf("error try again\n");
	//		tag = 1;
	//	}
	//}
	//tag = 1;
	//while (tag) {
	//	tag = 0;
	//	printf("Enter the copies of the book you wish to add:");
	//	t1 = scanf("%d", &(node.copies));
	//	if (t1 == 0) {
	//		printf("You have entered an invalid book!");
	//	}
	//	//copies cannot be smaller than 0
	//	if (node.copies < 0) {
	//		printf("error try again\n");
	//		tag = 1;
	//	}
	//}
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
		printf("You have successfully remove a book!\n");
	}
	getch();
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
	int librarianLoggedIn = 1;
	while (librarianLoggedIn) {
		libmenu();
		getchar();
		int key = optionChoice();
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
			librarianLoggedIn = 0;
			printf("\nLogging out...\n");
		}
		else {
			printf("\nUnknown choice\n");
		}
	}
	save();
	getch();
}



/***Module of the User System****/
//display the user menu
void usermenu()
{
	printf("\n");
	printf("---------------------------------------------------\n");
	printf("\t1) Borrow a book\n");
	printf("\t2) Return a book\n");
	printf("\t3) Display all books\n");
	printf("\t4) Logged out\n\n");
	printf("Please choose an option, press Enter to confirm\n");
	printf("---------------------------------------------------\n");
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
				printf("This book is out of loan, borrowing book unsuccessfully\n");
				return;
			}
			if (curuser->borrow_len == 6)
			{
				printf("You have already 6 books! You must return a book before borrowing\n");
				return;
			}
			//the changes when the user has successfully borrowed the book
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
			//If book can be returned successfully, the copies will increase 1
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
	int userLoggedIn = 1;
	while (userLoggedIn)
	{
		usermenu();
		getchar();
		int key = optionChoice();
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
			userLoggedIn = 0;
			printf("\nLogging out...\n");
		}
		else {
			printf("\nUnknown Choice");
		}
		save();
		getch();
	}
}



/***Module of the Login System****/
//display the main menu
void mainmenu()
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
			printf("You have registered into the system successfully!\n");
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

	/*char name[50];
	char password[50];
	printf("Please enter your username:");
	scanf("%s", name);
	printf("please enter your password:");
	scanf("%s", password);
	user* node = (user*)calloc(1, sizeof(user));
	strcpy(node->name, name);
	strcpy(node->password, password);
	node->next = userhead->next;
	userhead->next = node;
	printf("success\n");*/
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
				//strcpy(p->name, theUser.name);
				//strcpy(p->password, theUser.password);
				//Book* b = p->bolist;
				//b->id = theUser.bolist->id;
				//break;
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
	//char name[50];
	//char password[50];
	//printf("Please enter your username:");
	//scanf("%s", name);
	//printf("please enter your password:");
	//scanf("%s", password);
	//user* p = userhead->next;
	//while (p)
	//{
	//	if (strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0)
	//	{
	//		if (strcmp(name, "librarian") == 0)
	//		{
	//			curuser = p;
	//			cmd0();
	//		}
	//		else
	//		{
	//			curuser = p;
	//			user0();
	//		}
	//	}
	//	p = p->next;
	//}
	//printf("The username or password is not true, try again\n");
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
//show all the menu in the system for users
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
	int libraryOpen = 1;
	while (libraryOpen)
	{
		mainmenu();
		int key = optionChoice();
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
			libraryOpen = 0;
			printf("Thank you for using the Library!\n");
			printf("Goodbye!");

		}
		else {
			printf("\nUnknown option\n");
		}
	}
	save();
	getch();
}


int main()
{
	//load();
	userhead = (user*)calloc(1, sizeof(user));
	bhead = (Book*)calloc(1, sizeof(Book));
	log0();
	return 0;
}