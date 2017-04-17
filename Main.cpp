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

void deep(struct tree *root) //В глубь
{
	if (!root) return;

	if (root->info) printf("%i ", root->info);
	deep(root->left);
	deep(root->right);
} 

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

void GoToXY(short x, short y)
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(StdOut, coord);
}

void print(tree * root, short x, short y, short a, char c)
{
	if (root)
	{
		if (a>0 && c != 'k')
		{
			if (c == 'l')
				x -= 10;
			else
				x += 10;
		}
		else
			if (c != 'k')
				if (c == 'l')
					x -= 4;
				else
					x += 4;

		GoToXY(x, y += 2);

		a--;

		printf("%5d", root->info);
		print(root->left, x, y, a, 'l');
		print(root->right, x, y, a, 'r');
	}
}

void LEVEL(tree *koren_d, int &i, int &max_level)//считает количество уровней в деревке моём :)(нужно для вывода деревка,чтобы знать на сколько уровней погружаться рекурсией)
{
	if (koren_d->left != NULL)
	{
		i++;
		if (max_level < i)
			max_level = i;
		LEVEL(koren_d->left, i, max_level);
		i--;
	}
	if (koren_d->right != NULL)
	{
		i++;
		if (max_level < i)
			max_level = i;
		LEVEL(koren_d->right, i, max_level);
		i--;
	}
}

void display_level(tree *koren_d, int &i, int level)//выводит уровень № level у деревка :)
{
	if (i == level)
		printf("%d ", koren_d->info);
	if (koren_d->left != NULL)
	{
		i++;
		display_level(koren_d->left, i, level);
		i--;
	}
	if (koren_d->right != NULL)
	{
		i++;
		display_level(koren_d->right, i, level);
		i--;
	}
}

void display_all(tree *koren)
{
	int i = 0;//нужна для сквозной нумерации уровня в рекурсиях.(по крайней мере моя башка не придумала ничего лучше этого костыля)
	int max_level = 0;
	LEVEL(koren, i, max_level); //---узнаю максимальный уровень дерева
	for (int level = 0; level <= max_level; level++) //--цикл поочереди выводит каждый уровень девера, начиная с корняж
	{
		if (level == 0)
			printf("[ Корень ] : ");
		else
			printf("[%d уровень] : ", level);
		display_level(koren, i, level);//--функция вывода 1 уровня  дерева  
		printf("\n");
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	int s, N, kol;
	system("mode con cols=75 lines=50");
	root = NULL;  /* инициализация корня дерева */
	do
	{
		printf("Выберите опцию: ");
		scanf("%i", &N);
		switch(N)
		{
		case 1:
			printf("Сколько элементов вы хотите добавить? ");
			scanf("%i", &kol);
			for (int i = 0; i < kol; i++)
			{
				printf("Введите значение: ");
				scanf_s("%i", &s);
				root = stree(root, root, s);
			}
			break;
		case 2:
			system("cls");
			printf("Дерево в глубину:");
			deep(root);
			printf("\n");
			break;
		case 3:
			system("cls");
			printf("Дерево в ширину:");
			width(root);
			printf("\n");
			break;
		case 4:
			system("cls");
			printf("Дерево по уровням:");
			display_all(root);
			break;
		case 5:
			system("cls");
			print(root, 31, 2, 2, 'k');
			GoToXY(0, 0);
			break;
		}
	}while(N!=6);
	return 0;
}
