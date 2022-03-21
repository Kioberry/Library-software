#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sign.h"
#include "library.h"


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


//未完成！
void registration() {
	char press = 0;
	char name[20], username[20], password[20], password2[20];
	FILE* fp;
	if ((fp = fopen("user.txt", 'r')) == NULL) {
		fp = fopen("user.txt", 'w');
		fclose(fp);
	}
	fp = fopen("user.txt", "a+");
	while (1) {
		printf("Please enter your name: ");
		scanf("%s", &name);
		printf("Please enter a username: ");
		scanf("%s", &username);
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
			break;
		}
		fclose(fp);
	}	
}

//未完成！
void login() {
	printf("Please enter your username: ");
	printf("Please enter your password: ");
}

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
			printf("Please enter the publication of of the book(separate them with commas): ");
			scanf("%s", year);
			find_book_by_year(year);
			getch();
			signSearch();
			break;
		}
		case '4':
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

}
