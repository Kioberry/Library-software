#include "book_management.h"
#include "user.h"
#include "conio.h"

//display the librarian menu
void libmenu() {
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
void mainmenu() {
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
void usermenu() {
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
//The search interface shown on the screen
void searchMenu() {
	printf("\n");
	printf("\n");
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

//showing the clues for librarian to add a book and perform the add_book() function
void add() {
	int t1, t2, t3, t4, t5 = 0;
	Book node;
	node.id = 0;
	node.copies = 0;
	node.year = 0;
	node.originc = 0;
	node.title = (char*)calloc(1, 50 * sizeof(char));
	node.authors = (char*)calloc(1, 50 * sizeof(char));
	//unsigned int id; //Book ID
	//char* title; //book title
	//char* authors; //comma separated list of authors
	//unsigned int year; // year of publication
	//unsigned int copies; //number of copies the library has
	//unsigned int originc;//number of the original copies the library has
	printf("id:");
	t1 = scanf("%d", &(node.id));
	printf("title:");
	t2 = scanf("%s", node.title);
	printf("authors:");
	t3 = scanf("%s", node.authors);
	printf("year:");
	t4 = scanf("%d", &(node.year));
	printf("copies:");
	t5 = scanf("%d", &(node.copies));
	if (t1 == 0 || t2 == 0 || t3 == 0 || t4 == 0 || t5 == 0) {
		printf("Sorry, you attempt to add an invalid book, please try again.");
		return;
	}
	if (node.year > 2022 || node.year < 0 || node.copies < 0) {
		printf("Sorry, you attempt to add an invalid book, please try again.");
		return;
	}
	node.originc = node.copies;
	node.next = 0;
	add_book(node);
}

//showing the clues for librarian to delete a book and perform the remove_book() function
void del() {
	int id;
	printf("Enter the id of the book you want to remove:");
	scanf("%d", &id);
	Book node;
	node.id = id;
	remove_book(node);
}

void bor() {
	int id = 0;
	printf("ID:");
	scanf("%d", &id);
	getchar();
	bor_book(id);
}

void rtrn() {
	int id = 0;
	Book* node = (Book*)calloc(1, sizeof(Book));
	node = theUser.bolist->next;
	printf("ID\ttitle\tauthers\tyear\n");
	printf("---------------------------------------------------\n");
	while (node) {
		printf("%d\t%s\t%s\t%d\n", node->id, node->title, node->authors, node->year);
		node = node->next;
	}

	printf("Enter the id of the book you want to return: ");
	scanf("%d", &id);
	rtrn_book(id);
}
//display all the books in the library
void display() {
	Book* p = bhead->next;
	printf("ID\ttitle\tauthors\tyear\tcopies\n");
	printf("---------------------------------------------------\n");
	while (p) {
		printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->authors, p->year, p->copies);
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
	int i0 = 0;
	for (i0 = 0; i0 < a.length; i0++) {
		/////////////////////////////////
		printf("id:%d\n", p->id);
		printf("title:%s\n", p->title);
		printf("authors:%s\n", p->authors);
		printf("year:%d\n", p->year);
		printf("copies:%d\n", p->copies);
		printf("\n");
		p = p->next;
	}
}
//The interface of search for books
void find() {
	searchMenu();
	int key = 0;
	scanf("%d", &key);
	BookList a;
	switch (key) {
	case 1: {
		char str[40];
		printf("Enter the title of the book you want to search: ");
		scanf("%s", str);
		a = find_book_by_title(str);
		if (a.list != NULL) {
			displaylist(a);
		}
		break;
	}
	case 2: {
		char str1[40];
		printf("Enter the authors of the book(separate with commas): ");
		scanf("%s", str1);
		a = find_book_by_author(str1);
		if (a.list != NULL) {
			displaylist(a);
		}
		break;
	}
	case 3: {
		int year;
		printf("Enter the year of the book you want to search: ");
		scanf("%d", &year);
		a = find_book_by_year(year);
		if (a.list != NULL) {
			displaylist(a);
		}
		break;
	}
	default:
		printf("error");
	}


}
void reg() {
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
		user* p = uhead->next;
		while (p) {
			if (strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0) {
				tag = 1;
				break;
			}
			p = p->next;
		}

		if (tag == 2) {
			printf("You have registered into the system successfully!\n");
			user rUser;
			strcpy(rUser.name, name);
			strcpy(rUser.password, password);
			rUser.bolist = (Book*)calloc(1, sizeof(Book));
			add_user(rUser);
			return;
		}
	}
	if (tag == 1) {
		printf("Sorry, registration unsuccessful, the username you entered already exist\n");
		return;
	}

}
void log() {
	int tag = 1;
	char name[50];
	char password[50];
	theUser.bolist = (Book*)calloc(1, sizeof(Book));
	while (tag == 1) {
		printf("intput name:");
		scanf("%s", name);
		printf("input password:");
		scanf("%s", password);
		if (strcmp(name, "librarian") == 0 && strcmp(password, "librarian") == 0) {
			tag = 3;
			break;
		}
		user* p = uhead->next;
		while (p) {
			if (strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0) {
				tag = 2;
				strcpy(p->name, theUser.name);
				strcpy(p->password, theUser.password);
				Book* b = p->bolist;
				b->id = theUser.bolist->id;
				break;
			}
			p = p->next;
		}
		if (tag == 1) {
			printf("The username or password is not true, try again\n");
			return;
		}

	}
	if (tag == 3) {
		while (1) {
			libmenu();
			int key = 0;
			scanf("%d", &key);
			getchar();
			switch (key) {
			case 1:add(); break;
			case 2:del(); break;
			case 3:find(); break;
			case 4:display(); break;
			case 5:mainCLI();
			default:
				printf("try again\n");
			}
			getch();
		}
	}
	if (tag == 2) {
		while (1) {
			printf("\n(Logged in as: %s)\n", name);
			usermenu();
			int key = 0;
			scanf("%d", &key);
			getchar();
			switch (key) {
			case 1:bor(); break;
			case 2:rtrn(); break;
			case 3:find(); break;
			case 4:display(); break;
			case 5:exit(0);
			default:
				printf("try again\n");
			}
			getch();
		}
	}
}

mainCLI() {
	while (1) {
		mainmenu();
		int key = 0;
		scanf("%d", &key);
		getchar();
		switch (key) {
		case 1:reg(); break;
		case 2:log(); break;
		case 3:find(); break;
		case 4:display(); break;
		case 5:exit(0);
		default:
			printf("try again\n");
		}
		getch();
	}
}
int main() {
	uhead = (user*)calloc(1, sizeof(user));
	bhead = (Book*)calloc(1, sizeof(Book));
	load_user(uhead);
	//FILE* bfile = NULL;
	//load_books(bfile);
	mainCLI();
	return 0;
}