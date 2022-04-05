#include <stdio.h>

#include "user.h"
#include "library.h"
#include "book_management.h"
#include "global.h"


//The user interface shown on the screen
void userMenu() {
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

int numUsers() {
	FILE* fp;
	int n = 0;
	int fnumBorrowed = 0; //Book ID
	char fname[50] = {'\0'}, fusername[50] = { '\0' }, fpassword[50] = { '\0' };
	char* fborrowed[4];
	if (fp = fopen(ufname, "r") == NULL) {
		printf("Sorry, the record file does not exist!");
		return 0;
	}
	for (n = 0; !feof(fp); n++) {
		fscanf("%d%s%s%s%s", &fnumBorrowed, fname, fusername, fpassword, fborrowed);
	}
	n--;
	fclose(fp);
	return n;

}

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
store_users(FILE* file) {
	file = fopen(ufname, "w");
	if (file == NULL) {
		printf("Failed to open the file, press any key to exit!");
		getch();
		exit(0);
	}
	User* pMove = uhead->next;
	while (pMove)
	{
		fprintf(file, "%d%s%s%s%s", pMove->numBorrowed, pMove->name, pMove->username, pMove->password, pMove->borrowed);
		pMove = pMove->next;
	}
	fclose(file);
}




//borrow a copy of a book from the library
void borrow_book(User* theUser) {
	// TO DO : 
	int i, fid = 0;
	int isFlag, ocopies = 0;
	Book* bp, *up, *up1, *newNode;


	load_books(bfile);
	if (theUser->numBorrowed >= maxBorrowed) {
		// check that the user can borrow a book
		printf("You have to return a book before you can borrow another\n");
		// For any error message you should return to the menu
		return;
	}
	else {
		// request the choice of book 
		// message
		printf("Enter the ID number of the book you want to borrow:");
		scanf("%d", &fid);
		// check that the choice is valid 
		bp = bhead->next;
		for (;bp != NULL;) {
			if (!strcmp(bp->id, fid)) {
				isFlag = 1;
				ocopies = bp->copies;
				(bp->copies)--;
			}
			bp = bp->next;
		}
		if (isFlag && ocopies > 0) {
			store_books(bfile);
			theUser->numBorrowed++;
			up = theUser->borrowed;
			newNode = creatbNode(bp->id, bp->title, bp->authors, bp->year, bp->copies);
			while (up1) {
				up->next = up1;
				up = up1;
				up1 = up1->next;
			}
			up->next = newNode;
			newNode->next = NULL;
			store_users(ufile);
			printf("You have successfully borrowed the book!");
		}
		else {
			if (ocopies == 0) {
				printf("Sorry that all copies of this book has been borrowed, press any key to return");
			}
			else {
				printf("This book cannot be found, press any key to return");
			}
		}
		getch();
		userCLI();
		
	}

	return;
}


//display all the borrowed books of a user 
// it is used in the return_books() to allow 
// users choose the ID of the book to return
void display_borrowed_books(User* theUser) {
	Book* pMove = (Book*)malloc(sizeof(Book));
	pMove = theUser->borrowed->next;
	printf("ID\ttitle\tauther\tyear\t");
	while (pMove) {
		printf("%d\t%s\t%s\t%d\n", pMove->id, pMove->title, pMove->authors, pMove->year);
		pMove = pMove->next;
	}
	printf("\n");
}

void return_book(User* theUser) {
	int rid = 0;
	Book* p, *pFront;
	Book* b;
	if (theUser->numBorrowed == 0) {
		printf("You haven't borrowed any books yet, press any key to return");
	}
	else {
		display_borrowed_books(theUser);
		printf("Enter the ID number of the book you want to return:");
		scanf("%d", rid);
		pFront = theUser->borrowed;
		p = theUser->borrowed->next;
		while (strcmp(rid, p->id)) {
			pFront = p;
			p = p->next;
			if (p == NULL) {
				printf("\nInvalid ID of borrowed books, please try again");
				userCLI();
			}
		}
		pFront->next = p->next;
		free(p);
		b = bhead->next;
		while (b) {
			if (!strcmp(rid, b->id)) {
				b->copies++;
			}
			b = b->next;
		}
		store_users(ufile);
		store_books(bfile);
		printf("You have successfully borrowed the book!");
	}
	getch();
	userCLI();
}

//search books by one of the three ways in the user system
void userSearch() {
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
			userSearch();
			break;
		}
		case '2':
		{
			char* authors = { '\0' };
			printf("Please enter the author of the book(separate them with commas): ");
			scanf("%s", authors);
			find_book_by_author(authors);
			getch();
			userSearch();
			break;
		}
		case '3':
		{
			int year = 0;
			printf("Please enter the publication of of the book(separate them with commas): ");
			scanf("%s", year);
			find_book_by_year(year);
			getch();
			userSearch();
			break;
		}
		case '4':
			printf("\nReturning to previous menu...\n");
			system("pause");
			userCLI();
			break;
		default:
			printf("Sorry, your option is invalid");
			getch();
			userSearch();
		}
	}
}


void userCLI() {
	char choice = 0;
	printf("\nlogged in as: %s", t_username);
	userMenu();
	scanf("%c", choice);
	switch (choice) {
		case'1':
			borrow_book(theUser);
			break;
		case'2':
			return_book(theUser);
			break;
		case'3':
			printf("\nLoading search menu...\n");
			system("pause");
			userSearch();
			break;
		case'4':
			display_books(bhead);
			break;
		case'5':
			printf("\nLogging out...\n");
			system("pause");
			signCLI();
			break;
		default:
			printf("\nSorry, the option you entered was invalid, please try again.\n");
			system("pause");
			userCLI();
	}
}