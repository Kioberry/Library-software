#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sign.h"
#include "user.h"
#include "library.h"
#include "global.h"


void signMenu() {
	printf("\tWelcome to the Library Management System\n");
	printf("\n");
	printf("---------------------------------------------\n");
	printf("\t\t1) Register an account\n");
	printf("\t\t2) Login\n");
	printf("\t\t3) Search for books\n");
	printf("\t\t4) Display all books\n");
	printf("\t\t5) Quit\n");
	printf("\n");
	printf("\tPlease choose an option, press Enter to confirm\n");
	printf("---------------------------------------------\n");
	printf("\n");
	printf("Option: ");
}

//create the node of the linked list(used in registration to create a new account)
User* creatuNode(int numBorrowed, const char* name, const char* username, char password) {
	//dynamically allocate the userList array for storing books
	User* newNode = (User*)malloc(sizeof(User));

	//Assign parameters to the data field of the new node
	newNode->numBorrowed = numBorrowed;
	//use strcpy function with char variables
	strcpy(newNode->name, name);
	strcpy(newNode->username, username);
	strcpy(newNode->password, password);
	newNode->next = NULL;
	return newNode;
}





/*******The registration module*********/


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
void add_user(User* head, int numBorrowed, char name[20], char username[20], char password[20]) {
	//First, create the user node that need to be inserted into the linked list
	User* newNode = creatNode(numBorrowed, name, username, password);
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
			add_user(uhead, 0, name, username, password);
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
int searchUser(FILE* fp, char ufname[50], char fusername[50], char fpassword[50]) {
	int numBorrowed;
	char name[20], username[20], password[20];
	if ((fp = fopen(ufname, 'r')) == NULL) {
		printf("No user exists yet! Please create a new account.");
		getch();
		signCLI();
	}

	for (; !feof(fp);)
	{
		fscanf(fp, "%d%s%s%s", &numBorrowed, &name, &username, &password);
		if (strcmp(fusername, username))
		{
			if (strcmp(fpassword, password) == 0)
				return 1;
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
	char name[20], username[20], password[20], password2[20];
	do {
		printf("Please enter your username: ");
		scanf("%s", &username);
		printf("Press 'Enter' to confirm input, press 'Esc' to re-enter");
		press = getch();
		while (press != 13 && press != 27) {
			press = getch();
		}
	} while (press == 27);

	printf("Please enter your password: ");
	scanf("%s", &password);
	int ret = searchUser(ufile, ufname, username, password);
	if (ret == 1) {
		printf("\nlogged in as: %s", username);
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


void signCLI() {
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
				signSearch();
				break;
			case'4':
				system("cls");
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
