#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN 10

struct tnode
{
	struct tnode *left;
	struct tnode *right;
	int isleaf;
	char symbol;
};

struct code
{
	int symbol;
	char strcode[MAX_LEN];
};

struct tnode *root = NULL;

struct tnode *talloc()
{
	struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
	if (p != NULL)
	{
		p->left = p->right = NULL;
		p->symbol = 0;
		p->isleaf = 0;
	}
	return p;
}

void build_tree(FILE *fp)
{
	char symbol;
	char strcode[MAX_LEN];
	int items_read;
	int i, len;
	struct tnode *curr = NULL;

	while (!feof(fp))
	{
		items_read = fscanf(fp, "%c %s\n", &symbol, strcode);
		if (items_read != 2)
			break;
		curr = root;
		len = strlen(strcode);
		for (i = 0; i < len; i++)
		{
			if (strcode[i] == '0')
			{
				if (curr->left == NULL)
					curr->left = talloc();
				curr = curr->left;
			}
			else if (strcode[i] == '1')
			{
				if (curr->right == NULL)
					curr->right = talloc();
				curr = curr->right;
			}
			else
			{
				printf("Invalid code detected!\n");
				return;
			}
		}
		/*assign code*/
		curr->isleaf = 1;
		curr->symbol = symbol;
		printf("inserted symbol:%c\n", symbol);
	}
}

void decode(FILE *fin, FILE *fout)
{
	char c;
	struct tnode *curr = root;
	while ((c = getc(fin)) != EOF)
	{
		if (c == '0')
		{
			if (curr->left != NULL)
				curr = curr->left;
		}
		else if (c == '1')
		{
			if (curr->right != NULL)
				curr = curr->right;
		}

		if (curr->isleaf)
		{
			printf("%c", curr->symbol);
			putc(curr->symbol, fout);

			curr = root;
		}
	}
}

void freetree(struct tnode *root)
{
	if (root == NULL)
		return;
	freetree(root->right);
	freetree(root->left);
	free(root);
}

int main()
{
	const char *IN_FILE = "encoded.txt";
	const char *CODE_FILE = "code.txt";
	const char *OUT_FILE = "decoded.txt";
	FILE *fout;
	FILE *fin;

	root = talloc();
	fin = fopen(CODE_FILE, "r");
	build_tree(fin);
	fclose(fin);

	fin = fopen(IN_FILE, "r");
	fout = fopen(OUT_FILE, "w");
	decode(fin, fout);
	fclose(fin);
	fclose(fout);

	freetree(root);

	return 0;
}
