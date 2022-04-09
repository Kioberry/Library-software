#include "book_management.h"
#include "user.h"
void load_user(user* userhead) {
	FILE* fp = fopen("user.txt", "rb");
	if (fp == NULL)return;
	char name[50];
	char password[50];
	while (1) {
		int tag = fscanf(fp, "%s %s", name, password);
		if (tag == -1)break;
		int i0 = 0;
		for (i0 = 0; i0 < strlen(name); i0++) {
			if (name[i0] == '_')name[i0] = ' ';
		}
		for (i0 = 0; i0 < strlen(password); i0++) {
			if (password[i0] == '_')password[i0] = ' ';
		}
		user* node = (user*)calloc(1, sizeof(user));
		strcpy(node->name, name);
		strcpy(node->password, password);
		node->next = userhead->next;
		userhead->next = node;
	}
	fclose(fp);
}
void save_user(user* userhead) {
	FILE* fp = fopen("user.txt", "wb");
	user* p = userhead->next;
	while (p) {
		int i0 = 0;
		for (i0 = 0; i0 < strlen(p->name); i0++) {
			if (p->name[i0] == ' ')p->name[i0] = '_';
		}
		for (i0 = 0; i0 < strlen(p->password); i0++) {
			if (p->password[i0] == ' ')p->password[i0] = '_';
		}
		fprintf(fp, "%s %s\n", p->name, p->password);
		p = p->next;
	}
	fclose(fp);
}
void load_loans(user* loanhead) {
	FILE* fp = fopen("loans.txt", "rb");
	if (fp == NULL) return;
	int id = 0;
	char username[50];
	while (1) {
		int tag = fscanf(fp, "%d %s", &id, username);
		if (tag == -1) break;
		int i0 = 0;
		for (i0 = 0; i0 < strlen(username); i0++) {
			if (username[i0] == '_')username[i0] = ' ';
		}
		user* node = (user*)calloc(1, sizeof(user));
		node->bolist->id = id;
		strcpy(node->name, username);
		node->next = loanhead->next;
		loanhead->next = node;
	}

}
int add_user(user theUser) {
	user* node = (user*)calloc(1, sizeof(user));
	*node = theUser;
	node->next = NULL;
	user* p = uhead;
	while (p) {
		if (p->next == NULL) {
			p->next = node;
			break;
		}
		p = p->next;
	}
	return 0;
}
int add_ubook(Book book) {
	Book* node = (Book*)calloc(1, sizeof(Book));
	*node = book;
	node->next = NULL;
	Book* p = theUser.bolist;
	while (p) {
		if (p->next == NULL) {
			p->next = node;
			break;
		}
		p = p->next;
	}
	return 0;
}
int bor_book(int id) {
	Book* p = bhead->next;
	//user* lhead = (user*)calloc(1, sizeof(user));
	//load_loans(lhead);
	//user* lp = lhead->next;
	//while (lp) {
	//	if (theUser.name == lp->name && theUser.bolist->id == lp->bolist->id) {
	//		printf("You have already borrowed this book.");
	//		return 1;
	//	}
	//	lp = lp->next;
	//}
	while (p) {
		if (p->id == id && p->copies > 0) {
			printf("You have borrowed the book successfully!");
			Book book;
			book.id = 0;
			book.year = 0;
			book.copies = 0;
			book.originc = 0;
			book.title = (char*)calloc(1, 50 * sizeof(char));
			book.authors = (char*)calloc(1, 50 * sizeof(char));
			book.id = p->id;
			book.year = p->year;
			strcpy(p->authors, book.authors);
			strcpy(p->title, book.title);
			add_ubook(book, theUser);
			return 0;
		}
		else if (p->id == id) {
			printf("This book is out of loan.");
			return 1;
		}
		p = p->next;
	}
	printf("The book id you entered is invalid");
	return -1;
}
int rtrn_book(int id) {
	Book* p = theUser.bolist->next;
	Book* pre = theUser.bolist;
	while (p) {
		if (p->id == id) {
			pre->next = p->next;
			free(p->title);
			free(p->authors);
			free(p);
			return 0;
		}
		p = p->next;
		pre = pre->next;
	}
	printf("No book id could be found to return");
	return 1;
}