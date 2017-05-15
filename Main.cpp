#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include<locale.h>
#include<Windows.h>
#include<iostream>

//Организация очереди//
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
///////////////////////

struct tree {
	int info;
	struct tree *left;
	struct tree *right;
}*root;

struct tree *stree(struct tree *root, struct tree *r, int info)  //Функция построения дерева
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

void deep(struct tree *root) //Обход дерева в глубину
{
	if (!root) return;

	if (root->info) printf("%i ", root->info);
	deep(root->left);
	deep(root->right);
} 

void width(struct tree *root)  // Обход дерева в ширину
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
struct tree *search_tree(struct tree *root, int key) // Нахождение элемента в дереве
{
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

struct tree *dtree(struct tree *root, int key) // Удаление элемента из дерева (По значению)
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

void GoToXY(short x, short y) // Перевод курсора к координатам x, y
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(StdOut, coord);
}

void print(tree * root, short x, short y, short a, char c)  // Рисование дерева
{
	if (root)
	{
		if (a>0 && c != 'k')
		{
			if (c == 'l')
				x -= 15;
			else
				x += 15;
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

void LEVEL(tree *koren_d, int &i, int &max_level)//считает количество уровней в дереве
{
	if (koren_d)
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
}

void display_level(tree *koren_d, int &i, int level)  // Отображение всех элементов выбранного уровня
{
	if (koren_d)
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
}

void display_all(tree *koren)  // Отображение всего дерева по уровням
{
	int i = 0;//нужна для сквозной нумерации уровня в рекурсиях.
	int max_level = 0;
	LEVEL(koren, i, max_level); //---узнаю максимальный уровень дерева
	for (int level = 0; level <= max_level; level++) //--цикл поочереди выводит каждый уровень девера, начиная с корня
	{
		if (level == 0)
			printf("[ Корень ] : ");
		else
			printf("[%d уровень] : ", level);
		display_level(koren, i, level);//--функция вывода 1 уровня  дерева  
		printf("\n");
	}
}

struct tree *deletelement(struct tree *root, int key) // Вспомогательная функция для удаления всего дерева
{
	if (!root) return root;
	if (root->info == key)
	{
		free(root);
		return NULL;
	}
	if (root->info < key) root->right = deletelement(root->right, key);
	else root->left = deletelement(root->left, key);
	return root;
}

void delalltree(struct tree *root) // Удаление всего дерева
{
	if (!root) return;
	delalltree(root->left);
	delalltree(root->right);
	root = deletelement(root, root->info);
}

int listnumber(struct tree *root, int &i, int &p, int level) //Нахождение количества листов на n-ом уровне
{
	if (root)
	{
		if (i == level)
		{
			if (root->left == root->right)
			p++;
		}
		if (root->left != NULL)
		{
			i++;
			listnumber(root->left, i, p, level);
			i--;
		}
		if (root->right != NULL)
		{
			i++;
			listnumber(root->right, i, p, level);
			i--;
		}
	}
	return p;
}

int summa(struct tree *root, int &i, int &sum, int k) //Нахождение суммы не листов на n-ом уровне
{
	if (root)
	{
		if (i == k)
		{
			if (root->left != root->right)
				sum = sum + root->info;
		}
		if (root->left != NULL)
		{
			i++;
			summa(root->left, i, sum, k);
			i--;
		}
		if (root->right != NULL)
		{
			i++;
			summa(root->right, i, sum, k);
			i--;
		}
	}
	return sum;
}


int main()
{
	setlocale(LC_ALL, "rus");
	int s, N, kol, l, f = 0, p = 0, i = 0, sum = 0;
	system("mode con cols=125 lines=100");
	root = NULL;
	do
	{
		printf("1 - Добавление элементов в дерево\n");
		printf("2 - Вывод дерева в глубину\n");
		printf("3 - Вывод дерева в ширину\n");
		printf("4 - Вывод дерева по уровням\n");
		printf("5 - Нарисовать дерево\n");
		printf("6 - Удалить элемент из дерева\n");
		printf("7 - Найти кол-во листьев на n-ом уровне\n");
		printf("8 - Найти сумму не листьев на n-ом уровне\n");
		printf("9 - Удалить всё дерево и выйти из программы\n");
		printf("Выберите опцию: ");
		scanf("%i", &N);
		switch (N)
		{
		case 1:
			printf("Сколько элементов вы хотите добавить? ");
			scanf("%i", &kol);
			for (int i = 0; i < kol; i++)
			{
				printf("Введите значение: ");
				scanf("%i", &s);
				root = stree(root, root, s);
			}
			break;
		case 2:
			system("cls");
			printf("Дерево в глубину:");
			deep(root);
			printf("\n\n");
			break;
		case 3:
			system("cls");
			printf("Дерево в ширину:");
			width(root);
			printf("\n\n");
			break;
		case 4:
			system("cls");
			printf("Дерево по уровням:");
			display_all(root);
			printf("\n\n");
			break;
		case 5:
			system("cls");
			print(root, 31, 2, 2, 'k');
			GoToXY(0, 0);
			system("pause");
			system("cls");
			break;
		case 6:
			printf("Введите значение элемента, который хотите удалить:");
			scanf("%i", &l);
			root = dtree(root, l);
			break;
		case 7:
			system("cls");
			int m;
			printf("Введите уровень: ");
			scanf("%i", &m);
			printf("%i\n\n", listnumber(root, f, p, m));
			p = 0;
			break;
		case 8:
			system("cls");
			int k;
			printf("Введите уровень: ");
			scanf("%i", &k);
			printf("%i\n\n", summa(root, i, sum, k));
			sum = 0;
			break;
		case 9:
			system("cls");
			delalltree(root);
			break;
		default:
			printf("Нет такой опции!\n");
		}
	}while(N!=9);
	return 0;
}