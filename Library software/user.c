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