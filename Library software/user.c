#include "user.h"

void save_user(user* userhead, char* name)
{
	FILE* fp = fopen(name, "wb");
	user* p = userhead->next;
	while (p) {
		fprintf(fp, "%s %s %d %d %d %d %d %d %d\n", p->name, p->password, p->borrow_len, (p->borrow[0]), (p->borrow[1]), (p->borrow[2]), (p->borrow[3]), (p->borrow[4]), (p->borrow[5]));
		//int i0 = 0;
		//for (i0 = 0; i0 < 6; i0++)
		//{
		//	fprintf(fp, "%d ", p->borrow[i0]);
		//}
		/*fprintf(fp, "\n");*/
		p = p->next;
	}
	fclose(fp);
}
void load_user(user* userhead, char* name)
{
	FILE* fp = fopen(name, "rb");
	if (fp == NULL)return;
	char name0[50];
	char password[50];
	int len;
	int arr[6];
	while (1)
	{
		int tag = fscanf(fp, "%s %s %d %d %d %d %d %d %d\n", name0, password, &len, &(arr[0]), &(arr[1]), &(arr[2]), &(arr[3]), &(arr[4]), &(arr[5]));

		if (tag == -1)
			break;
		user* node = (user*)calloc(1, sizeof(user));
		strcpy(node->name, name0);
		strcpy(node->password, password);
		node->borrow_len = len;
		for (int i0 = 0; i0 < 6; i0++)
		{
			node->borrow[i0] = arr[i0];
		}
		node->next = userhead->next;
		userhead->next = node;
	}
	fclose(fp);
}