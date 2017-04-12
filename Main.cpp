//Функция построения дерева
//Функция поиска в глубину
//Функция поиска в ширину
//Функция нахождения какого-либо эл-та


/* Эта программа выводит на экран двоичное дерево. */
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include<locale.h>
#include<Windows.h>
#include<iostream>

typedef struct Node
{
	int value;
	struct Node *next;
} Node;
Node *head;
Node* getLast(Node *head)
{
	if (head == NULL)
	{
		return NULL;
	}
	while (head->next)
	{
		head = head->next;
	}
	return head;
}
void push(Node *head, int value)
{
	Node *last = getLast(head);
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = NULL;
	last->next = tmp;
}

int pop(Node **head)
{
	Node* prev = NULL;
	int val;
	if (head == NULL)
	{
		exit(-1);
	}
	prev = (*head);
	val = prev->value;
	(*head) = (*head)->next;
	free(prev);
	return val;
}



struct tree {
	int info;
	struct tree *left;
	struct tree *right;
}*root;

struct tree *stree(struct tree *root, struct tree *r, int info)
{

	if (!r) {
		r = (struct tree *) malloc(sizeof(struct tree));
		if (!r) {
			printf("Не хватает памяти\n");
			exit(0);
		}
		r->left = NULL;
		r->right = NULL;
		r->info = info;
		if (!root) return r; /* первый вход */
		if (info < root->info) root->left = r;
		else root->right = r;
		return r;
	}

	if (info < r->info)
		stree(r, r->left, info);
	else
		stree(r, r->right, info);

	return root;
}

void preorder(struct tree *root) //В глубь
{
	if (!root) return;

	if (root->info) printf("%i ", root->info);
	preorder(root->left);
	preorder(root->right);
} 

void postorder(struct tree *root) //В ширину
{
	if (!root) return;

	
	postorder(root->left);
	postorder(root->right);
	if (root->info) printf("%i ", root->info);
}

void printspisok(struct tree *root)
{
	if (!root)
		return;
	push(head, root->info);
	while (head)
	{
		tree *curr=NULL;
		curr->info = pop(&head);
		printf("%d", curr->info);
		if (curr->left)
			push(head, curr->left->info);
		if (curr->right)
			push(head, curr->right->info);
	}
}
struct tree *search_tree(struct tree *root, int key)
{
	//if (!root) return root;  /* пустое дерево */
	while (root) {
		if (root->info < key)
		{
			root = root->right;
			continue;
		}
		else if (root->info > key)
		{
			root = root->left;
			continue;
		}
		else return root;
	}
	return NULL;
}

struct tree *dtree(struct tree *root, char key)
{
	struct tree *p, *p2;

	if (!root) return root; /* вершина не найдена */

	if (root->info == key) { /* удаление корня */
							 /* это означает пустое дерево */
		if (root->left == root->right) {
			free(root);
			return NULL;
		}
		/* или если одно из поддеревьев пустое */
		else if (root->left == NULL) {
			p = root->right;
			free(root);
			return p;
		}
		else if (root->right == NULL) {
			p = root->left;
			free(root);
			return p;
		}
		/* или есть оба поддерева */
		else {
			p2 = root->right;
			p = root->right;
			while (p->left) p = p->left;
			p->left = root->left;
			free(root);
			return p2;
		}
	}
	if (root->info < key) root->right = dtree(root->right, key);
	else root->left = dtree(root->left, key);
	return root;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int s, N;

	root = NULL;  /* инициализация корня дерева */

	scanf("%i", &N);

	for (int i = 0; i < N; i++)
	{
		printf("Введите значение: ");
		scanf_s("%i", &s);
		root = stree(root, root, s);
	}
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	printspisok(root);
	system("pause");
	return 0;
}

