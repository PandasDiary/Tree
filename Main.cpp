//������� ���������� ������
//������� ������ � �������
//������� ������ � ������
//������� ���������� ������-���� ��-��


/* ��� ��������� ������� �� ����� �������� ������. */
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include<locale.h>
#include<Windows.h>
#include<iostream>

typedef struct Node
{
	struct tree *value;
	struct Node *next;
} Node;
Node *head=NULL;
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
void push(Node **head, struct tree *value)
{
	if (*head == NULL) 
	{
		Node *tmp = (Node*)malloc(sizeof(Node));
		tmp->value = value;
		tmp->next = (*head);
		(*head) = tmp;
	}
	else
	{
		Node *last = getLast(*head);
		Node *tmp = (Node*)malloc(sizeof(Node));
		tmp->value = value;
		tmp->next = NULL;
		last->next = tmp;
	}
}
struct tree* pop(Node **head)
{
	Node* prev = NULL;
	tree *val;
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
			printf("�� ������� ������\n");
			exit(0);
		}
		r->left = NULL;
		r->right = NULL;
		r->info = info;
		if (!root) return r; /* ������ ���� */
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

void deep(struct tree *root) //� �����
{
	if (!root) return;

	if (root->info) printf("%i ", root->info);
	deep(root->left);
	deep(root->right);
} 
void deeppict(struct tree *root, HDC hDC);

void width(struct tree *root)
{
	if (!root)
		return;
	push(&head, root);
	while (head)
	{
		tree *curr=NULL;
		curr = pop(&head);
		printf("%i ", curr->info);
		if (curr->left)
			push(&head, curr->left);
		if (curr->right)
			push(&head, curr->right);
	}
}
struct tree *search_tree(struct tree *root, int key)
{
	//if (!root) return root;  /* ������ ������ */
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

	if (!root) return root; /* ������� �� ������� */

	if (root->info == key) { /* �������� ����� */
							 /* ��� �������� ������ ������ */
		if (root->left == root->right) {
			free(root);
			return NULL;
		}
		/* ��� ���� ���� �� ����������� ������ */
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
		/* ��� ���� ��� ��������� */
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
	int s, N, ox=300, oy=300;
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	system("mode con cols=75 lines=50");
	root = NULL;  /* ������������� ����� ������ */

	scanf("%i", &N);

	for (int i = 0; i < N; i++)
	{
		printf("������� ��������: ");
		scanf_s("%i", &s);
		root = stree(root, root, s);
	}
	deep(root);
	printf("\n");
	width(root);
	printf("\n");
	deeppict(root, hDC);
	system("pause");
	return 0;
}
void deeppict(struct tree *root, HDC hDC)
{
	int s, mainroot;
	static int m = 0;
	if (!root) return;
	s = root->info;
	if (m == 0)
	{
		mainroot = root->info;
		Ellipse(hDC, 10 - 2, 15 - 2, 10 + 2, 15 + 2);
		m++;
		s = root->info;
	}
	if (root->info)
	{
		if (((root->info) < s) && (root->info < mainroot))
		{
			Ellipse(hDC, 10 - 2, 15 - 2, 10 + 2, 15 + 2);
		}
		s = root->info;
	}
	deeppict(root->left, hDC);
	deeppict(root->right, hDC);
}