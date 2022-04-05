#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sign.h"
#include "user.h"
#include "library.h"
#include "global.h"
#include "book_management.h"

//The login interface shown on the screen
void signMenu() {
	printf("\tWelcome to the Library Management System\n");
	printf("\n");
	printf("---------------------------------------------\n");
	printf("\t\t1) Register an account\n");
	printf("\t\t2) Login\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\t\t5) System Manual\n");
	printf("\t\t6) Quit\n");
	printf("\n");
	printf("\tPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------\n");
	printf("\n");
	printf("Option: ");
}


/*******The registration module*********/

//create the node of the linked list(used in registration to create a new account)
User* creatuNode(const char* name, const char* username, char password) {
	//dynamically allocate the userList array for storing books
	User* newNode = (User*)malloc(sizeof(User));
	newNode->next = NULL;

	//Assign parameters to the data field of the new node
	newNode->numBorrowed = 0;
	//use strcpy function with char variables
	strcpy(newNode->name, name);
	strcpy(newNode->username, username);
	strcpy(newNode->password, password);

	//initialize the borrowed book linked list of the user
	newNode->borrowed = (Book*)malloc(sizeof(Book));
	newNode->borrowed->next = NULL;

	return newNode;
}


//loads the database of users from the specified file
//the file must have been generated by a previous call to store_users()
//returns 0 if books were loaded correctly, or an error code otherwise
load_users(FILE* file) {
	int n, i, m = 0;
	int fnumBorrowed = 0;
	char fname[50] = { '\0' }, fusername[50] = { '\0' }, fpassword[50] = { '\0' };
	FILE* fp;
	Book* fborrowed;
	User* p, * newNode;
	createuList();
	if ((file = fopen(ufname, "r")) == NULL) {
		fp = fopen(ufname, 'w');
		add_user(uhead, "librarian", "librarian", "0000");
		User* p = uhead->next;
		fprintf(fp, "%d%s%s%s", p->numBorrowed, p->name, p->username, p->password);
		Book* bp = p->borrowed->next;

		fprintf(file, "%d%s%s%d%d%d", bp->id, bp->title, bp->authors, bp->year, bp->copies, bp->originc);
		//getch();
		fclose(fp);
	}
	else {
		n = numUsers();
		for (i = 0; i < n; i++) {
			fscanf(file, "%d%s%s%s%s", &fnumBorrowed, fname, fusername, fpassword, fborrowed);
			m++;
			if (m == 1)
			{
				//create a new node that needs to
				//be inserted into the linked list
				p = newNode = createuNode(fnumBorrowed, fname, fusername, fpassword, fborrowed);
				bhead->next = p;
			}
			else {
				p->next = newNode;
				p = newNode;
				newNode = createuNode(fnumBorrowed, fname, fusername, fpassword, fborrowed);
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


//transverse the linked list
User* searchUsername(const char* username) {
	User* pMove = uhead->next;
	while (pMove) {
		if (!strcmp(pMove->username, username)) {
			return pMove;
		}
		pMove = pMove->next;
	}
	return NULL;
}

//add a new user in the user linked list
void add_user(User* head, char name[50], char username[50], char password[50]) {
	//First, create the user node that need to be inserted into the linked list
	User* newNode = creatNode(name, username, password);
	//perform the operation of inserting the node
	newNode->next = head->next;
	head->next = newNode;
	return 0;
}

//注意要在主函数里设置命令行参数输入！
//registration of a new user.
void registration(FILE* fp, char ufname[50]) {
	char press = 0;
	char name[50], username[50], password[50], password2[50];
	if ((fp = fopen(ufname, 'r')) == NULL) {
		fp = fopen(ufname, 'w');
		fclose(fp);
	}
	fp = fopen(ufname, "a");
	while (1) {
		printf("Please enter your name: ");
		scanf("%s", &name);
		printf("Please enter a username: ");
		scanf("%s", &username);
		if (searchUsername(username) != NULL) {
			printf("Sorry, registration unsuccessful, the username you entered already exists."); \
			break;
		}
		printf("Please enter a password(No more than 20 characters): ");
		scanf("%s", &password);
		printf("Please enter your password again to confirm: ");
		scanf("%s", &password2);
		if (strcmp(password, password2) != 0) {
			printf("Sorry, the new password and confirming password disagree!\n");
			printf("Press 'Enter' to continue or 'ESC' to log out:");
			if ((press = getch()) == 27) {
				signCLI();
			}
			scanf("%s", password2);
		}
		else {
			fprintf(fp, "%s %s %s\n", name, username, password);
			add_user(uhead, name, username, password);
			break;
		}
		fclose(fp);
	}	
}


/***********The Login module*******/


//transverse the userlist to varify the username and password.
//returns 1 if both username and password can be matched, returns 0 if
//username couldn't be matched and returns -1 if username can be matched 
// while password is incorrect.
//需要被删除
int searchUser(FILE* fp, char ufname[50], char fusername[50], char fpassword[50]) {
	int numBorrowed;
	char name[20], username[20], password[20];
	Book* borrowed;
	if ((fp = fopen(ufname, 'r')) == NULL) {
		//printf("No user exists yet! Please create a new account.");
		fp = fopen(ufname, 'w');
		add_user(uhead, "librarian", "librarian", "0000");
		User* p = uhead->next;
		fprintf(fp, "%d%s%s%s%s", p->numBorrowed, p->name, p->username, p->password, p->borrowed);
		//getch();
		fclose(fp);
		//signCLI();
	}
	fopen(ufname, 'r');
	for (; !feof(fp);)
	{
		fscanf(fp, "%d%s%s%s%s", &numBorrowed, name, username, password, borrowed);
		if (strcmp(fusername, username))
		{
			if (strcmp(fpassword, password) == 0) {
				theUser = (User*)malloc(sizeof(User));
				theUser->numBorrowed = numBorrowed;
				strcpy(theUser->name, name);
				strcpy(theUser->username, username);
				strcpy(theUser->password, password);
				//可以吗？
				theUser->borrowed = borrowed;
				return 1;
			}	
			else
			{
				return -1;
			}
		}
	}
	return 0;
}


//function to allow authentic users to log in
void login() {
	int press, ret;
	char name[20], password[20], password2[20];
	do {
		printf("Please enter your username: ");
		scanf("%s", &t_username);
		printf("Press 'Enter' to confirm input, press 'Esc' to re-enter");
		press = getch();
		while (press != 13 && press != 27) {
			press = getch();
		}
	} while (press == 27);

	printf("Please enter your password(The initial password of librarian is 0000): ");
	scanf("%s", &password);
	int ret = searchUser(ufile, ufname, t_username, password);
	if (ret == 1) {
		userCLI();
	}
	else if (ret == 0) {
		printf("The username does not exist.");
		getch();
		signCLI();
	}
	else if (ret == -1) {
		printf("Sorry, the password is incorrect.");
		getch();
		login();
	}
	
}


/*********Search for books********/

//search books by one of the three ways in the Login system
void signSearch() {
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
			signSearch();
			break;
		}
		case '2':
		{
			char* authors = { '\0' };
			printf("Please enter the author of the book(separate them with commas): ");
			scanf("%s", authors);
			find_book_by_author(authors);
			getch();
			signSearch();
			break;
		}
		case '3':
		{
			int year = 0;
			printf("Please enter the publication of year: ");
			scanf("%s", year);
			find_book_by_year(year);
			getch();
			signSearch();
			break;
		}
		case '4':
			printf("\nReturning to previous menu...\n");
			signCLI();
			break;
		default:
			printf("Sorry, your option is invalid");
			getch();
			signSearch();
		}
	}
}

//The main function to deal with the Login system
void signCLI() {
	User* theUser;
	signMenu();
	char choice = 0;
	scanf("%c", choice);
	while (1) {
		switch (choice) {
			case'1':
				registration(ufile, ufname);
			    break;
			case'2':
				login();
				break;
			case'3':
				printf("\nLoading search menu...\n");
				system("pause");
				signSearch();
				break;
			case'4':
				display_books(bhead);
				break;
			case'5':
				printf("--------------------------------------\n");
				printf("Initial librarian account: librarian\n");
				printf("Initial password: 0000");
				printf("--------------------------------------\n");
				break;
			case'6':
				printf("Thank you for using the library!\nGoodbye!");
				break;
			default:
				printf("\nSorry, the option you entered was invalid, please try again.\n");
				system("pause");
			//对不对？
			getch();
			exit(0);
			system("cls");
			break;
		}
	}
}
