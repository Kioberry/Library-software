#include "user.h"

void save_user(user* userhead)
{
	FILE* fp = fopen("user.txt", "wb");
	user* p = userhead->next;
	while (p) {
		fprintf(fp, "%s %s %d ", p->name, p->password, p->borrow_len);
		int i0 = 0;
		for (i0 = 0; i0 < 6; i0++)
		{
			fprintf(fp, "%d ", p->borrow[i0]);
		}
		fprintf(fp, "\n");
		p = p->next;
	}
	fclose(fp);
}
void load_user(user* userhead)
{
	FILE* fp = fopen("user.txt", "rb");
	if (fp == NULL)return;
	char name[50];
	char password[50];
	int len;
	int arr[6];
	while (1)
	{
		int tag = fscanf(fp, "%s %s %d %d %d %d %d %d %d\n", name, password, &len, &(arr[0]), &(arr[1]), &(arr[2]), &(arr[3]), &(arr[4]), &(arr[5]));
		if (tag == -1)
			break;
		user* node = (user*)calloc(1, sizeof(user));
		strcpy(node->name, name);
		strcpy(node->password, password);
		node->borrow_len = len;
		for (int i0 = 0; i0 < 6; i0++)
		{
			node->borrow[i0] = arr[i0];
		}
	}
	fclose(fp);
}