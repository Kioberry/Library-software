#include <stdio.h>

#include "library.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"



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
BookList find_book_by_title(const char* title) {
	FILE* fp;
	int i, isFlag = 0;
	char title[30] = {'\0'};
	int fid = 0; //Book ID
	char* ftitle; //book title
	char* fauthors; //comma separated list of authors
	int fyear = 0; // year of publication
	int fcopies = 0; //number of copies the library has
	if ((fp = fopen("library.txt", "r")) == NULL) {
		printf("\nSorry, the record file does not exist! ");
	}
	printf("Please enter the title of the book: ");
	scanf("%s", title);
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
			printf("%d\t%s\t\t%s\t\t%d\t%d\n", &fid, ftitle, fauthors, &fyear, &fcopies);
			isFlag++;
		}
	}
	if (isFlag == 0) {
		printf("Sorry, your query is invalid.");

	}
	void search_for_books();

}

void mainCLI() {

}