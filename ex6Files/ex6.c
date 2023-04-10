/***********************
* David Shnaiderov
* 209198308
* 01
* EX06
***********************/

#include "ex6.h"
#include "Utils.h"

#define NAME 50
#define SPACE 3
typedef enum { createFamily = 0, addMember = 1 } createOrAdd;
typedef enum { simple = 0, superspreader = 1 } bidudMode;



Trin_Ari* findRoot(Trin_Ari* key) {
	if (key->head == NULL)
		return key;
	return findRoot(key->head);
}
/************************************************************************
* Function Name: quit
* Input: int error (flag incase malloc has falied)
		 Trin_Ari * root (node in the Trin_Ari tree)
* Output Void
* Function Operation: frees all allocated memory and exits the program.
						if root proived is not the absolute root of the
						tree, find it.
************************************************************************/
void vacine(Trin_Ari * vacinated);
void quit(int error, Trin_Ari * root) {
	if (error == ERROR) {
		printf("Malloc Failed!\n");
	}
	if (root->head != NULL)
		root = findRoot(root);
	vacine(root);	
	free(root);
	exit(0);
}

/************************************************************************
* Function Name: getValues
* Input: int* id (pointer to the ID var)
		 char* name (pointer to the name var)
* Output Void
* Function Operation: Gets id and name form user
************************************************************************/
void getValues(int* id, char* name) {
	printf("enter name\n");
	char space = 0;
	scanf("%c\n", &space);

	fgets(name, NAME, stdin);
	strtok(name, "\n");

	printf("enter ID\n");
	scanf("%d", id);
}

/************************************************************************
* Function Name: assignValues
* Input: int id (ID var)
		 char* name (pointer to the name var)
		 Trin_Ari * node (node to assign to)
* Output Void
* Function Operation: Assigns values got from 'getValues'
************************************************************************/
void assignValues(Trin_Ari * node, int id, char* name) {
	node->left = NULL;
	node->middle = NULL;
	node->right = NULL;
	node->name = name;
	node->id = id;
	printf("Hello %s, ID: %d\n", name, id);
}

/************************************************************************
* Function Name: createFamilyNode
* Input: int id (ID var)
		 char* name (pointer to the name var)
		 Trin_Ari * root (node to assign to)
* Output Void
* Function Operation: Creates a root in the family tree
************************************************************************/
Trin_Ari* findMember(Trin_Ari * root, int id);
Trin_Ari* createFamilyNode(int id, char* name, Trin_Ari * root) {
	Trin_Ari* node = malloc(sizeof(Trin_Ari));
	if (node == NULL) {
		quit(ERROR, root);
	}
	assignValues(node, id, name);
	node->head = root;
	return node;
}

/************************************************************************
* Function Name: addToFamilyTree
* Input: int id (ID var)
		 char* name (pointer to the name var)
		 Trin_Ari * root (node to assign to)
* Output Void
* Function Operation: Check which root is free
************************************************************************/
void addToFamilyTree(Trin_Ari * root, int id, char* name) {
	if (root->left == NULL)
		root->left = createFamilyNode(id, name, root);
	else if (root->middle == NULL)
		root->middle = createFamilyNode(id, name, root);
	else if (root->right == NULL)
		root->right = createFamilyNode(id, name, root);
}

/************************************************************************
* Function Name: findMember
* Input: int id (ID var)
		 Trin_Ari * root (node to assign to)
* Output Trin_Ari * (Returns the found root)
* Function Operation: find the root by ID
************************************************************************/
Trin_Ari * findMember(Trin_Ari * root, int id) {
	if (root == NULL)
		return NULL;
	if (root->id == id)
		return root;
	Trin_Ari * temp = findMember(root->left, id);
	if (temp != NULL)
		return temp;
	temp = findMember(root->middle, id);
	if (temp != NULL)
		return temp;
	temp = findMember(root->right, id);
	if (temp != NULL)
		return temp;

	return NULL;
}

/************************************************************************
* Function Name: createFamilyTree
* Input: int addOrCreate (mode of operation)
		 Trin_Ari * root (node to assign to)
* void
* Function Operation: find the root by ID
************************************************************************/
void createFamilyTree(Trin_Ari * root, int addOrCreate) {
	if (strcmp(root->name, INITIALIZE) != 0 && addOrCreate == createFamily) {
		printf("The family has already been created\n");
		return;
	}

	char* name = NULL;
	int id = 0;
	name = (char*)malloc(sizeof(char) * NAME);
	if (name == NULL)
		quit(ERROR, root);
	//gets values from user
	getValues(&id, name);
	//assigns values to node
	assignValues(root, id, name);
}

/************************************************************************
* Function Name: createEncounter
* Input: Trin_Ari * root (node to create an encounter with)
* Output void
* Function Operation: creates an encounter with a family member
					  by adding a root to the Trin_Ari tree
************************************************************************/
void createEncounter(Trin_Ari * root) {
	if (strcmp(root->name, INITIALIZE) == 0) {
		printf("Please create the family first\n");
		return;
	}

	int idToFind;
	char* name = NULL;
	int id = 0;
	name = (char*)malloc(sizeof(char) * NAME);
	if (name == NULL)
		quit(ERROR, root);

	printf("Enter the ID of the person who wants to make an appointment?\n");
	scanf("%d", &idToFind);
	Trin_Ari * member = root;
	Trin_Ari * temp = root;
	//finds the member to create an encounter with 
	member = findMember(root, idToFind);
	if (member == NULL)
		printf("There is no ID %d\n", idToFind);
	else if (member->left != NULL && member->right != NULL && member->middle != NULL)
		printf("%s ID: %d can't meet more than 3 members!\n", member->name, member->id);
	else {
		//keeps prompting the user until a valid ID given
		while (temp != NULL) {
			getValues(&id, name);
			temp = findMember(root, id);
			if (temp != NULL)
				printf("ID %d belongs to %s\n", temp->id, temp->name);
		}
		addToFamilyTree(member, id, name);
		return;
	}
	free(name);
}

/************************************************************************
* Function Name: preOrderPrint
* Input: Trin_Ari * root (tree head node)
* Output void
* Function Operation: prints the tree in preOrder
************************************************************************/
void preOrderPrint(Trin_Ari * root) {
	if (root == NULL)
		return;
	printf("%s ID: %d\n", root->name, root->id);
	preOrderPrint(root->left);
	preOrderPrint(root->middle);
	preOrderPrint(root->right);
}

/************************************************************************
* Function Name: preOrderPrint
* Input: Trin_Ari * root (tree head node)
* Output void
* Function Operation: prints the tree in leftOrder
************************************************************************/
void leftOrderPrint(Trin_Ari * root) {
	if (root == NULL)
		return;
	leftOrderPrint(root->left);
	printf("%s ID: %d\n", root->name, root->id);
	leftOrderPrint(root->middle);
	leftOrderPrint(root->right);
}

/************************************************************************
* Function Name: releaseQueue
* Input: QNode * node (node in linked list)
* Output void
* Function Operation: releases memory in case of memory error
************************************************************************/
void releaseQueue(QNode * node) {
	if (node == NULL)
		return;
	if (node->next != NULL)
		releaseQueue(node->next);
	free(node);
}

/************************************************************************
* Function Name: enQueue
* Input: QNode * node (node in linked list)
		 Trin_Ari * key (node to add to queue)
* Output void
* Function Operation: add a member to queue
************************************************************************/
void enQueue(Queue * queue, Trin_Ari * key) {
	if (queue == NULL || key == NULL)
		return;

	QNode * *node = &queue->front;
	QNode * temp = (QNode*)malloc(sizeof(QNode));
	if (temp == NULL) {
		releaseQueue(*node);
		quit(ERROR, key);
	}
	temp->key = key;
	temp->next = NULL;

	if ((*node) == NULL)
		* node = temp;
	else
	{
		//adds node to front
		while ((*node)->next != NULL)
			node = &(*node)->next;
		(*node)->next = temp;
	}
}

/************************************************************************
* Function Name: deQueue
* Input: QNode * node (node in linked list)
		 Trin_Ari * key (node to add to queue)
* Output void
* Function Operation: removes a member from queue and prints the next node
************************************************************************/
void printStayHome(Trin_Ari * bidud);
void deQueue(Queue * *queue, bidudMode mode) {
	QNode* front = (*queue)->front;
	//superspreader mode
	if (mode == superspreader)
		printStayHome(front->key);
	else
		//normal print mode
		printf("%s %d\n", front->key->name, front->key->id);
	//remove node from queue
	front = front->next;
	free((*queue)->front);
	(*queue)->front = front;
}

/************************************************************************
* Function Name: createQueue
* Input: Trin_Ari * root (a root in the Trin_Ari family tree)
* Output Queue (initialized queue)
* Function Operation: removes a member from queue and prints the next node
************************************************************************/
Queue* createQueue(Trin_Ari * root) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL)
		quit(ERROR, root);
	queue->front = NULL;
	return queue;
}

/************************************************************************
* Function Name: bfsPrint
* Input: Trin_Ari * root (root in the Trin_Ari family tree)
		 bidudMode mode (print simple or Supserspreader)
* Output void
* Function Operation: prints the family in a Breadth-first search order
************************************************************************/
void bfsPrint(Trin_Ari * root, bidudMode mode) {
	if (root == NULL)
		return;
	Queue * queue = createQueue(root);
	//add root to queue
	enQueue(queue, root);

	do {
		if (queue->front != NULL) {
			enQueue(queue, queue->front->key->left);
			enQueue(queue, queue->front->key->middle);
			enQueue(queue, queue->front->key->right);
		}
		deQueue(&queue, mode);
	} while (queue->front != NULL);
	free(queue);
}

/************************************************************************
* Function Name: printFamilyMenu
* Input: Trin_Ari * root (root of the tree)
		 int menuType (full or reduced menu)
* Output void
* Function Operation: prints the print menue and promts the user for an option
************************************************************************/
void menu(int menuType, Trin_Ari * root);
void printFamilyMenu(Trin_Ari * root) {
	printf("Please select an operation:\n"
		"	0. Return to the main menu.\n"
		"	1. Print Trin-Ari family.\n"
		"	2. Print Pre-order.\n"
		"	3. Print Left-order.\n"
		"	4. Print BFS.\n");
	char choice = '\0';
	scanf(" %c", &choice);

	switch (choice) {
	case '0':
		break;
	case '1':
		if (strcmp(root->name, INITIALIZE) != 0)
			print2DUtil(root, SPACE);
		break;
	case '2':
		if (strcmp(root->name, INITIALIZE) != 0)
			preOrderPrint(root);
		break;
	case '3':
		if (strcmp(root->name, INITIALIZE) != 0)
			leftOrderPrint(root);
		break;
	case '4':
		if (strcmp(root->name, INITIALIZE) != 0)
			bfsPrint(root, simple);
		break;
	default:
		printf("Error: unrecognized operation.\n");
		printFamilyMenu(root);
		return;
		break;
	}
	menu(fullMenu, root);
}

/************************************************************************
* Function Name: printStayHome
* Input: Trin_Ari * bidud (member to print)
* Output void
* Function Operation: print "stayHome" for the recived member
************************************************************************/
void printStayHome(Trin_Ari * bidud) {
	if (bidud != NULL)
		printf("#StayHome! %s %d\n", bidud->name, bidud->id);
}

/************************************************************************
* Function Name: stayHome
* Input: Trin_Ari * infected (the infected member)
* Output void
* Function Operation: calls 'printStayHome' for the required members
************************************************************************/
void stayHome(Trin_Ari * infected) {
	printStayHome(infected);
	printStayHome(infected->left);
	printStayHome(infected->middle);
	printStayHome(infected->right);
}

/************************************************************************
* Function Name: bidud
* Input: Trin_Ari * root (root in the Trin_Ari family tree)
		 bidudMode mode (simple or Superspreader)
* Output void
* Function Operation: recives an infected member and decides who needs
					  to stay home
************************************************************************/
void bidud(Trin_Ari * root, bidudMode mode) {
	if (strcmp(root->name, INITIALIZE) == 0) {
		printf("Please create the family first\n");
		return;
	}
	int id;
	if (mode == superspreader)
		printf("Enter the ID of the suspected Superspreader\n");
	else
		printf("Enter the ID of the suspected member\n");
	scanf("%d", &id);
	Trin_Ari * infected = findMember(root, id);
	if (infected == NULL) {
		printf("ID %d does not exist\n", id);
		return;
	}
	printStayHome(infected->head);
	if (mode == simple)
		stayHome(infected);
	else if (mode == superspreader) {
		bfsPrint(infected, superspreader);
	}
}

/************************************************************************
* Function Name: vacine
* Input: Trin_Ari * vacinated (the member who got vacinated)
* Output void
* Function Operation: removes from the member who got vacinated and his children
************************************************************************/
void vacine(Trin_Ari * vacinated) {
	if (vacinated == NULL || strcmp(vacinated->name, INITIALIZE) == 0)
		return;
	vacine(vacinated->left);
	vacine(vacinated->middle);
	vacine(vacinated->right);
	printf("%s ID: %d Survived!\n", vacinated->name, vacinated->id);

	free(vacinated->name);
	if (vacinated->head == NULL)
		vacinated->name = INITIALIZE;
	else {		
		free(vacinated);
		vacinated = NULL;
	}
}

/************************************************************************
* Function Name: clearHead
* Input: Trin_Ari * vacinated (the member who got vacinated)
* Output void
* Function Operation: sets to NULL the child who got vacinated
************************************************************************/
void clearHead(Trin_Ari * vacinated) {
	if (vacinated->head == NULL)
		return;
	if (vacinated->head->left == vacinated)
		vacinated->head->left = NULL;
	if (vacinated->head->middle == vacinated)
		vacinated->head->middle = NULL;
	if (vacinated->head->right == vacinated)
		vacinated->head->right = NULL;
}

/************************************************************************
* Function Name: whoVacinated
* Input: Trin_Ari * vacinated (the root of the tree)
* Output void
* Function Operation: starts the procces of removing vacinated members
					  from the tree
************************************************************************/
void whoVacinated(Trin_Ari * root) {
	if (strcmp(root->name, INITIALIZE) == 0) {
		printf("Please create the family first\n");
		return;
	}
	int id;
	printf("Who got vaccinated (ID)?\n");
	scanf("%d", &id);
	Trin_Ari* vacinated = findMember(root, id);
	if (vacinated == NULL) {
		printf("There is no ID %d\n", id);
		return;
	}
	clearHead(vacinated);
	vacine(vacinated);
}

/************************************************************************
* Function Name: menu
* Input: Trin_Ari * root (root of the tree)
		 int menuType (full or reduced menu)
* Output void
* Function Operation: prints the menue and promts the user for an option
************************************************************************/
void menu(int menuType, Trin_Ari * root) {
	if (menuType == fullMenu) {
		printf("Please select an operation:\n""	0. Exit.\n"	"	1. Create family.\n"
			"	2. Add family member.\n"	"	3. Print Family-Tree.\n"	"	4. Bidud.\n"
			"	5. Superspreader.\n"	"	6. Vaccine.\n"	"	7. Print the menu.\n");
	}
	else
		printf("Select the next operation (insert 7 for the entire menu):\n");
	char choice = '\0';
	scanf(" %c", &choice);
	switch (choice) {
	case '0':
		quit(0, root);
		break;
	case '1':
		createFamilyTree(root, createFamily);
		break;
	case '2':
		createEncounter(root);
		break;
	case '3':
		printFamilyMenu(root);
		break;
	case '4':
		bidud(root, simple);
		break;
	case '5':
		bidud(root, superspreader);
		break;
	case '6':
		whoVacinated(root);
		break;
	case '7':
		menu(fullMenu, root);
		break;
	default:
		printf("Error: unrecognized operation.\n");
		break;
	}
}
