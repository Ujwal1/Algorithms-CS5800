#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int key; // if the node is a head, then key represents level
	int isHead;
	struct node* right;
	struct node* down;
	struct node* left;
	struct node* up;
}node_t;

// This creates a node with given key and pointers to up, down, left, right set to NULL.
node_t* createNode(int key)
{
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	newnode->key = key;
	newnode->right = NULL;
	newnode->down = NULL;
	newnode->isHead = 0;
	newnode->up = NULL;
	newnode->left = NULL;
	return newnode;
}

// This creates head node with given level and pointers to up, down, left, right set to NULL.
node_t* createHead(int level) 
{
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	newnode->key = level;
	newnode->right = NULL;
	newnode->down = NULL;
	newnode->isHead = 1;
	newnode->up = NULL;
	newnode->left = NULL;
	return newnode;
}

node_t* head0;
node_t* headh;

// used to bring randomness into level selection for any inserted node
int flipCoin() {
	return rand() % 5;
}

// used to split the input buffer by spaces.
int split(char dst[][80], char* str, const char* spl)
{
	int n = 0;
	char* result = NULL;
	result = strtok(str, spl);
	while (result != NULL)
	{
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n;
}

void printList() 
{
	node_t* head = headh;
	
	printf("Skip list current state is: \n");
	while (head != NULL) 
	{
		printf("Level %d :", head->key);
		node_t* tmp = head->right;
		while (tmp != NULL) 
		{
			printf(" %d ", tmp->key);
			tmp = tmp->right;
		}
		printf("\n");
		head = head->down;
	}
	
	printf("\n");
}

// Look up the key, if it exists, return 
// the node; otherwise return the place where it can insert
node_t* find(int key)
{
	printf("Starting to search %d ....\n", key);
	node_t* tmp = headh;//start search the right head to enter
	while (tmp != NULL)
	{
		if (tmp->isHead == 0 && tmp->key == key) 
		{ //if find the node
			while (tmp->down != NULL) 
			{
				printf("Go down\n");
				tmp = tmp->down; // find the lowest one to return
			}
			printf("Found the key\n");
			return tmp;
		}
		if (tmp->right != NULL)
		{ // compare the right node with the key, if right node is larger than key, go down.
			if (tmp->right->key > key)
			{
				if (tmp->down == NULL)
				{ // it is the lowest
					printf("Not found.\n");
					return tmp;//there is no such a key, return the last one
				}
				else
				{
					printf("Go down\n");
					tmp = tmp->down;
				}
			}
			else {
				printf("Go right\n");
				tmp = tmp->right;
			}
		}
		else //If tmp node has no right node
		{
			if (tmp->down == NULL)
			{ // it is the lowest
				printf("Not found.\n");
				return tmp;//there is no such a key
			}
			else
			{
				printf("Go down\n");
				tmp = tmp->down;
			}
		}
	}
	printf("No such key error.\n");
	return tmp;//there is no such a key
}

void insertNewLevel(node_t* tmp) 
{
	node_t* newnode = createNode(tmp->key);
	tmp->up = newnode;
	newnode->down = tmp;

	//find the left node in the upper level
	node_t* leftone = tmp->left;

	while (leftone->up == NULL && leftone->isHead == 0) 
	{
		leftone = leftone->left;
	}
	printf("%d ", leftone->key);

	if(leftone->isHead==1 && leftone->up == NULL)//if is head
	{
		node_t* newhead = createHead(leftone->key + 1);
		leftone->up = newhead;
		newhead->down = leftone;
		newhead->right = newnode;
		newnode->left = newhead;
		headh = newhead;
	}
	else 
	{
		leftone = leftone->up;
		newnode->right = leftone->right;
		leftone->right = newnode;
		if(newnode->right!=NULL)
			newnode->right->left = newnode;
		newnode->left = leftone;
	}
	if (flipCoin() > 1)
	{
		insertNewLevel(newnode);
	}
}

void insert(int key) 
{
	node_t* tmp = find(key);
	if (tmp == NULL) 
	{
		printf("Error!");
		return;
	}
	if (tmp->key == key) {
		printf("Item %d already present in the list.\n", key);
		printList();
		return;
	}
	node_t* newnode = createNode(key);
	newnode->left = tmp;
	
	if (tmp->right != NULL) 
	{
		newnode->right = tmp->right;
		newnode->right->left = newnode;
	}
	tmp->right = newnode;
	
	if (flipCoin() > 1)
	{
		insertNewLevel(newnode);
	}


	printList();
}

void checkHead() 
{
	node_t* tmp = headh;
	while (tmp->right == NULL && tmp->down!=NULL) {
		node_t* tmpdown = tmp->down;
		free(tmp);
		tmp = tmpdown;
	}
	headh = tmp;
}

void delete(int key)
{
	node_t* tmp = find(key);
	if (tmp->key != key) {
		printf("No such Item.\n");
		printList();
		return;
	}
	node_t* tmpup;
	while (tmp != NULL) {
		tmpup = tmp->up;
		tmp->left->right = tmp->right;
		if(tmp->right!=NULL)
			tmp->right->left = tmp->left;
		free(tmp);
		tmp = tmpup;
	}
	checkHead();
	printList();
}

int strToInt(char* string) {
	int i = 0;
	int res = 0;
	while (string[i] != '\0') {
		res = res * 10 + (string[i++] - '0');
	}
	return res;
}

int main()
{	
	head0 = createHead(0); // lowest level head
	headh = head0; //highest level head

	char buf[1024];
	while (1) {

		puts("Enter your command: insert x, delete x, find x, enter quit to exit\n");
		puts("For insert, delete, and find, Format: 'COMMAND_X_Enter'. \n Give a space after the number, and then press enter");
		fgets( buf, sizeof(buf), stdin ); 
		char command[100][80];
		split(command, buf, " ");
		if (!strcmp(command[0], "insert")) 
		{
			insert(strToInt(command[1]));
			printf("\n");
		}
		else if (!strcmp(command[0], "delete")) 
		{
			delete(strToInt(command[1]));
			printf("\n");
		}
		else if (!strcmp(command[0], "find")) 
		{
			find(strToInt(command[1]));
			printf("\n");
		}
		else if (!strcmp(command[0], "quit")) 
		{
			printf("\n");
			break;
		}
		else {
			printf("Please enter a valid command.\n");
		}

	}
	printf("Exit Done");
}

