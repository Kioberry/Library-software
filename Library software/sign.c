#include <stdio.h>

#include "sign.h"


void signMenu() {
	printf("\tWelcome to the Library Management System\n");
	printf("\n");
	printf("---------------------------------------------\n");
	printf("\t\t1) Rigister an account\n");
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

void rigister() {
	char press = 0;
	char name[20], username[20], password[20], password2[20];
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
			
			break;
		}
	}
	


}

void login() {
	printf("Please enter your username: ");
	printf("Please enter your password: ");
}
void signCLI() {

}
