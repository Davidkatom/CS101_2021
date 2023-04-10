/*************
*Omer Hamdi
* 208667113
* 01
* ass05
*************/
#include "ex6.h"
#include "Utils.h"
#include "queue.h"

//memory checks:
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


/******************
* Function Name:initializeNode
* Input:	Trin_Ari* node(pointer to a node in the tree), char nameInput[](name input to initialize the node),
			int idInput(id input to initialize the node).
* Output:	Result(MEM_ERROR or SUCCESS).
* Function Operation:	initialize the node with the received values and sets the children to NULL.
						if malloc fails for name allocation - return MEM_ERROR else erturn SUCCESS
******************/
Result initializeNode(Trin_Ari* node, char nameInput[], int idInput) {
	node->name = (char*)malloc(sizeof(nameInput) + 1);
	if (node->name == NULL)
		return MEM_ERROR;
	strcpy(node->name, nameInput);
	node->id = idInput;
	node->left = NULL;
	node->middle = NULL;
	node->right = NULL;
	return SUCCESS;
}

/******************
* Function Name:	findInTrinAri.
* Input:	Trin_Ari* root(pointer to a root in the tree),int searchID(id to search).
* Output:	Trin_Ari*(pointer to a tree).
* Function Operation:	searches for the received id in the received root.
						returns NULL if not found.
******************/
Trin_Ari* findInTrinAri(Trin_Ari* root, int searchID) {
	if (root == NULL)
		return NULL;
	if (root->id == searchID)
		return root;
	Trin_Ari* node = findInTrinAri(root->left, searchID);
	if (node != NULL)
		return node;
	node = findInTrinAri(root->middle, searchID);
	if (node != NULL)
		return node;
	node = findInTrinAri(root->right, searchID);
	if (node != NULL)
		return node;
	return NULL;
}

/******************
* Function Name:	isChild.
* Input:	Trin_Ari* root(pointer to a root in the tree),int searchID(id to search).
* Output:	Bool(TRUE or FALSE).
* Function Operation:	checks if the received id is the child of the root.
******************/
Bool isChild(Trin_Ari* root, int searchID) {
	if (root == NULL)
		return FALSE;
	if (root->id == searchID)
		return TRUE;
	return FALSE;
}

/******************
* Function Name:	findParent.
* Input:	Trin_Ari* root(pointer to a root in the tree),int id(id to search).
* Output:	Trin_Ari*(pointer to a tree).
* Function Operation:	if root is NULL return NULL
						check if on of the root's child has the id received.
						else - check if one of it's children is the parent.
						if not found - return NULL, else return the found tree.
******************/
Trin_Ari* findParent(Trin_Ari* root, int id) {
	if (root == NULL)
		return NULL;
	if (isChild(root->left, id) == TRUE || isChild(root->middle, id) == TRUE || isChild(root->right, id) == TRUE)
		return root;
	Trin_Ari* node = findParent(root->left, id);
	if (node != NULL)
		return node;
	node = findParent(root->middle, id);
	if (node != NULL)
		return node;
	node = findParent(root->right, id);
	if (node != NULL)
		return node;
	return NULL;
}

/******************
* Function Name:	printStayHome.
* Input:	Trin_Ari* root(pointer to a root in the tree).
* Output:	void.
* Function Operation:	if received root is not NULL, print the root name and id with STAY HOME!"
******************/
void printStayHome(Trin_Ari* root) {
	if (root != NULL)
		printf("#StayHome! %s %d\n", root->name, root->id);
}

/******************
* Function Name:	bidud.
* Input:	Trin_Ari* head(pointer to a head in the tree).
* Output:	void.
* Function Operation:	get an ID for a suspected member, if id is found:
						put him, his parent and his children in bidud.
						print for all of them stay at home message.
******************/
void bidud(Trin_Ari* head) {
	printf("Enter the ID of the suspected member\n");
	int idInput;
	scanf("%d", &idInput);
	Trin_Ari* node = findInTrinAri(head, idInput);
	if (node == NULL) {
		printf("ID %d does not exist\n", idInput);
		return;
	}
	printStayHome(findParent(head, idInput));
	printStayHome(node);
	printStayHome(node->left);
	printStayHome(node->middle);
	printStayHome(node->right);
}

/******************
* Function Name:printBFS
* Input: Trin_Ari* root(pointer to a root in the tree), BFSPrintStyle style( PRINT_ONLY or PRINT_STAY_HOME).
* Output: Result(SUCCESS, FAILURE or MEM_ERROR).
* Function Operation:	This function gets a pointer to a root and a printing style
						if root is NULL - return Failure
						create new Queue and allocate memory for it.
						add the first root to the queue, then loop through the queue:
						for each member - add his lines to the queue and deQueu him(print and free from queue)
						free the allocation for Queue head
******************/
Result printBFS(Trin_Ari* root, BFSPrintStyle style) {
	if (root == NULL)
		return FAILURE;
	Queue* queue = createQueue();
	if (queue == NULL)
		return MEM_ERROR;
	if (enQueue(queue, root) == MEM_ERROR)
		return MEM_ERROR;
	do {
		if (queue->front != NULL)
		{
			if (enQueue(queue, queue->front->key->left) == MEM_ERROR)
				return MEM_ERROR;
			if (enQueue(queue, queue->front->key->middle) == MEM_ERROR)
				return MEM_ERROR;
			if (enQueue(queue, queue->front->key->right) == MEM_ERROR)
				return MEM_ERROR;
		}
		deQueue(&queue, style);
	} while (queue->front != NULL);
	free(queue);
	return SUCCESS;
}

/******************
* Function Name:superSpreader
* Input: Trin_Ari* head(pointer to a head in the tree).
* Output: Result(SUCCESS, FAILURE or MEM_ERROR).
* Function Operation:	get input from user for suspected Super Spreader
						if received ID not exists - print error and return
						else, print stay home for parent and all nodes beneath the spreader
						user printBFS to print in BFS search.
******************/
Result superSpreader(Trin_Ari* head) {
	printf("Enter the ID of the suspected Superspreader\n");
	int idInput;
	scanf("%d", &idInput);
	Trin_Ari* node = findInTrinAri(head, idInput);
	if (node == NULL) {
		printf("ID %d does not exist\n", idInput);
		return FAILURE;
	}
	printStayHome(findParent(head, idInput));
	return printBFS(node, PRINT_STAY_HOME);
}

/******************
* Function Name:vaccinePostOrder
* Input: Trin_Ari* node(pointer to a node in the tree).
* Output: void.
* Function Operation:	prints survived in post order (left, middle, right and head)
						frees all the allocated memory for the survivors
						if received node is NULL, return and do nothing
******************/
void vaccinePostOrder(Trin_Ari* node) {
	if (node == NULL)
		return;
	vaccinePostOrder(node->left);
	vaccinePostOrder(node->middle);
	vaccinePostOrder(node->right);
	printf("%s ID: %d Survived!\n", node->name, node->id);
	//free the node upon survival:
	free(node->name);
	free(node);
}

/******************
* Function Name:vaccine
* Input: Trin_Ari** head(pointer to pointer to a head in the tree), int idInput(input ID).
* Output: void.
* Function Operation:	get an id for vaccinated member - if not found return.
						otherwise: vaccine and print relevant message for the survivors.
						remove the survivors from our tree and close the edges neatly.
******************/
void vaccine(Trin_Ari** head, int idInput) {
	if (idInput == 0) {
		printf("Who got vaccinated (ID)?\n");
		scanf("%d", &idInput);
	}
	Trin_Ari* node = findInTrinAri(*head, idInput);
	if (node == NULL) {
		printf("There is no ID %d\n", idInput);
		return;
	}
	Trin_Ari* nodeParent = findParent(*head, idInput);
	ChildDirection direction = LEFT;
	if (nodeParent != NULL) {
		if (nodeParent->middle->id == idInput)
			direction = MIDDLE;
		if (nodeParent->right->id == idInput)
			direction = RIGHT;
	}
	vaccinePostOrder(findInTrinAri(*head, idInput));
	if (nodeParent != NULL) {
		if (direction == LEFT)
			nodeParent->left = NULL;
		if (direction == MIDDLE)
			nodeParent->middle = NULL;
		if (direction == RIGHT)
			nodeParent->right = NULL;
	}
	else {
		*head = NULL;
	}
}

/******************
* Function Name:createTree
* Input: Trin_Ari** head(pointer to pointer to a head in the tree), Trin_Ari** rootPTR(pointer to pointer to a root in the tree).
* Output: Result (FAILURE, SUCCESS, MEM_ERROR).
* Function Operation:	create a tree in the received rootPTR.
						if family was not created already - get input from user.
						make sure id not exists already in the main tree (head).
						allocate memory for new node/family and allocate memory for name too.
						print relevant message if SUCCESSFULL, else return error type.
******************/
Result createTree(Trin_Ari** head, Trin_Ari** rootPTR) {
	if (*rootPTR != NULL) {
		printf("The family has already been created\n");
		return FAILURE;
	}
	//Trin_Ari* root = *rootPTR;
	int idInput = 0;
	Bool idBelongsToOther;
	char nameInput[INPUT_TREE_NAME] = { 0 };
	char garbage = 0;
	do {
		idBelongsToOther = EMPTY;
		printf("enter name\n");
		scanf("%c%[^\n]", &garbage, &nameInput);
		printf("enter ID\n");
		scanf("%d", &idInput);
		if (findInTrinAri(*head, idInput) != NULL) {
			printf("ID %d belongs to %s\n", idInput, findInTrinAri(*head, idInput)->name);
			idBelongsToOther = TRUE;
		}
	} while (idBelongsToOther == TRUE || findInTrinAri(*rootPTR, idInput) != NULL);
	//Allocate memory for the new family root
	Trin_Ari* root = (Trin_Ari*)malloc(sizeof(Trin_Ari));
	if (root == NULL)
		return MEM_ERROR;
	//if name allocation failed - free the root we created
	if (initializeNode(root, nameInput, idInput) == MEM_ERROR) {
		free(root);
		root = NULL;
		return MEM_ERROR;
	}
	//if input is Valid:
	*rootPTR = root;
	printf("Hello %s, ID: %d\n", root->name, root->id);
}

/******************
* Function Name:meetingCounter
* Input: rin_Ari* root(pointer to the tree root).
* Output: int (number of meetings someone was assigned to).
* Function Operation:	for each child of the received root
						if child exists(!=NULL) add 1 to the count
						return the total amount.
******************/
int meetingCounter(Trin_Ari* root) {
	int count = 0;
	if (root->left != NULL)
		count++;
	if (root->middle != NULL)
		count++;
	if (root->right != NULL)
		count++;
	return count;
}

/******************
* Function Name:nextMeetingSpot
* Input: rin_Ari* root(pointer to a tree root).
* Output: Trin_Ari* root(pointer to a tree root).
* Function Operation:	return next meeting spot or "free spot" available for the received root.
						if all is taken - return NULL, else pointer to the place for the new meeting.
******************/
Trin_Ari* nextMeetingSpot(Trin_Ari* root) {
	if (root->left == NULL)
		return root->left;
	if (root->middle == NULL)
		return root->middle;
	if (root->right == NULL)
		return root->right;
	return NULL;
}

/******************
* Function Name:add member
* Input: Trin_Ari** head(pointer to the head pointer of our family tree)
* Output: Result(MEM ERROR or SUCESS or FAILURE).
* Function Operation:	get input for a member to add to the tree.
						make sure ID already exists and no more then 2 meetings are alraedy signed.
						add the new root with the relevant information.
						if allocation error occurred - return MEM_ERRO else SUCCES.
******************/
Result addMember(Trin_Ari** head) {
	char nameInput[INPUT_TREE_NAME] = { 0 };
	int idInput;
	printf("Enter the ID of the person who wants to make an appointment?\n");
	scanf("%d", &idInput);
	Trin_Ari* parentMember = findInTrinAri(*head, idInput);
	if (parentMember == NULL) {
		printf("There is no ID %d\n", idInput);
		return FAILURE;
	}
	if (meetingCounter(parentMember) == MEETINGS_MAX) {
		printf("%s ID: %d can't meet more than 3 members!\n", parentMember->name, parentMember->id);
		return FAILURE;
	}
	Trin_Ari* newRoot = nextMeetingSpot(parentMember);
	//if result is MEM_ERROR return MEM_ERROR accordingly
	if (createTree(head, &newRoot) == MEM_ERROR)
		return MEM_ERROR;
	if (parentMember->left == NULL) {
		parentMember->left = newRoot;
	}
	else if (parentMember->middle == NULL) {
		parentMember->middle = newRoot;
	}
	else if (parentMember->right == NULL) {
		parentMember->right = newRoot;
	}
	return SUCCESS;
}

/******************
* Function Name:freeMenu
* Input: char* menu[](menu to free), int amount(listing amounts in menu)
* Output: void.
* Function Operation:	frees all the menu options (chars) in the received menu.
******************/
void freeMenu(char* menu[], int amount) {
	for (int i = 0; i < amount; i++) {
		free(menu[i]);
	}
}

/******************
* Function Name:initializeChar
* Input: char* menuIntiall[](menu of our operations), int index(index to set),char operations(operation to allocate)
* Output: void.
* Function Operation:	this function allocates memory for the operation received
						save it into the menuIntiall[] in the received index with the received operation.
******************/
void initializeChar(char* menuIntiall[], int index, char operation[]) {
	menuIntiall[index] = (char*)malloc(sizeof(char) * (strlen(operation) + 1));
	if (!menuIntiall[index])
		return;
	strcpy(menuIntiall[index], operation);
}

/******************
* Function Name:declareMenu
* Input: char* opers[](menu of our options)
* Output: Result(if allocation was successful or not).
* Function Operation:	this function sets the options into the general menu.
******************/
Result declareMenu(char* generalMenu[MENU_OPTIONS]) {
	initializeChar(generalMenu, 0, "0. Exit.");
	initializeChar(generalMenu, 1, "1. Create family.");
	initializeChar(generalMenu, 2, "2. Add family member.");
	initializeChar(generalMenu, 3, "3. Print Family-Tree.");
	initializeChar(generalMenu, 4, "4. Bidud.");
	initializeChar(generalMenu, 5, "5. Superspreader.");
	initializeChar(generalMenu, 6, "6. Vaccine.");
	initializeChar(generalMenu, 7, "7. Print the menu.");
	for (int i = 0; i < MENU_OPTIONS; i++) {
		if (generalMenu[i] == NULL)
			return MEM_ERROR;
	}
	return SUCCESS;
}

/******************
* Function Name:declareMenu
* Input: char* opers[](menu of our options)
* Output: Result(if allocation was successful or not).
* Function Operation:	this function sets the options into the general menu.
******************/
Result declareSubMenu(char* subMenu[SUB_MENU_OPTIONS]) {
	initializeChar(subMenu, 0, "0. Return to the main menu.");
	initializeChar(subMenu, 1, "1. Print Trin-Ari family.");
	initializeChar(subMenu, 2, "2. Print Pre-order.");
	initializeChar(subMenu, 3, "3. Print Left-order.");
	initializeChar(subMenu, 4, "4. Print BFS.");
	for (int i = 0; i < SUB_MENU_OPTIONS; i++) {
		if (subMenu[i] == NULL)
			return MEM_ERROR;
	}
	return SUCCESS;
}

/******************
* Function Name:printMenu
* Input: char* opers[](menu of our operations), int options(amount of options in the menu)
* Output: void.
* Function Operation:	this function gets a pointer to a char array.
						prints all the char in the array (from the first one to the options num received).
******************/
void printMenu(char* MenuOptions[], int options) {
	printf("Please select an operation:\n");
	for (int i = 0; i < options; i++) {
		if (MenuOptions[i])
			printf("\t%s\n", MenuOptions[i]);
	}
}

/******************
* Function Name:printPreOrder
* Input: Trin_Ari* node(pointer to a node in the tree).
* Output: void.
* Function Operation:	this function prints in PreOrder the nodes in the received tree
******************/
void printPreOrder(Trin_Ari* node) {
	if (node == NULL)
		return;
	printf("%s ID: %d\n", node->name, node->id);
	printPreOrder(node->left);
	printPreOrder(node->middle);
	printPreOrder(node->right);
}

/******************
* Function Name:printLeftOrder
* Input: Trin_Ari* node(pointer to a node in the tree).
* Output: void.
* Function Operation:	this function prints in LeftOrder the nodes in the received tree
******************/
void printLeftOrder(Trin_Ari* node) {
	if (node == NULL)
		return;
	printLeftOrder(node->left);
	printf("%s ID: %d\n", node->name, node->id);
	printLeftOrder(node->middle);
	printLeftOrder(node->right);
}

/******************
* Function Name:createQueue
* Input: none.
* Output: Queue*(a new Queue).
* Function Operation:	this function allocates memory for a new Queue 
						if failed - return NULL.
******************/
Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q == NULL)
		return NULL;
	q->front = NULL;
	return q;
}

/******************
* Function Name:enQueue
* Input: Queue* q(pointer to Queue), Trin_Ari* (a key pointer to a tree)
* Output: Result(SUCCESSS, FAILURE or MEM_ERROR).
* Function Operation:	this function allocates new memory for the new node and add it
						in order to the Queue with the key element (pointer to tree).
						if memory allocation fails - return accordingly, else return success.
******************/
Result enQueue(Queue* q, Trin_Ari* key) {
	if (q == NULL || key == NULL)
		return FAILURE;
	QNode* temp = (QNode*)malloc(sizeof(QNode));
	if (temp == NULL)
		return MEM_ERROR;
	temp->key = key;
	temp->next = NULL;

	QNode** node = &q->front;
	if ((*node) == NULL) {
		(*node) = temp;
	}
	else {
		while ((*node)->next != NULL) {
			node = &(*node)->next;
		}
		(*node)->next = temp;
	}
	return SUCCESS;
}

/******************
* Function Name:deQueue
* Input: Queue** q(pointer to pointer to Queue), BFSPrintStyle style(style to print)
* Output: void.
* Function Operation:	this function removes a listing from the Queue
						prints message according to the PrintStyle received
						frees the removed memory.
******************/
void deQueue(Queue** q, BFSPrintStyle style) {
	QNode* front = (*q)->front;
	if (style == PRINT_ONLY)
		printf("%s %d\n", front->key->name, front->key->id);
	if (style == PRINT_STAY_HOME)
		printf("#StayHome! %s %d\n", (*q)->front->key->name, (*q)->front->key->id);
	front = front->next;
	free((*q)->front);
	(*q)->front = front;
}



//check if needed to be Result or void
Result secoundMenu(char* subMenu[], Trin_Ari* head) {
	printMenu(subMenu, SUB_MENU_OPTIONS);
	char option;
	do
	{
		scanf(" %c", &option);
		switch (option)
		{
		case '0':
			break;
		case '1':
			print2DUtil(head, PRINT_TREE_SPACE);
			return SUCCESS;
			break;
		case '2':
			printPreOrder(head);
			return SUCCESS;
			break;
		case '3':
			printLeftOrder(head);
			return SUCCESS;
			break;
		case '4':
			if (printBFS(head, PRINT_ONLY) == MEM_ERROR)
				return MEM_ERROR;
			return SUCCESS;
			break;
		default:
			printf("Error: unrecognized operation.\n");
			printMenu(subMenu, SUB_MENU_OPTIONS);
			break;
		}
	} while (option != '0');
	return SUCCESS;
}

Result familyCreated(Trin_Ari* head) {
	if (head == NULL) {
		printf("Please create the family first\n");
		return FAILURE;
	}
	return SUCCESS;
}


void mainMenu(char* generalMenu[MENU_OPTIONS], char* subMenu[MENU_OPTIONS], Result* RST) {
	Trin_Ari* head = NULL;
	printMenu(generalMenu, MENU_OPTIONS);
	char option;
	do {
		if (*RST == MEM_ERROR) {
			//OMER CHECK - move it to main.c ???
			printf("Malloc Failed!\n");
			return;
		}
		scanf(" %c", &option);
		switch (option)
		{
		case '0':
			break;
		case '1':
			createTree(&head, &head);
			if (head == NULL)
				*RST = MEM_ERROR;
			break;
		case '2':
			if (familyCreated(head) == SUCCESS)
				addMember(&head);
			break;
		case '3':
			*RST = secoundMenu(subMenu, head);
			printMenu(generalMenu, MENU_OPTIONS);
			break;
		case '4':
			if (familyCreated(head) == SUCCESS)
				bidud(head);
			break;
		case '5':
			if (familyCreated(head) == SUCCESS)
				*RST = superSpreader(head);
			break;
		case '6':
			if (familyCreated(head) == SUCCESS)
				vaccine(&head, 0);
			break;
		case '7':
			printMenu(generalMenu, MENU_OPTIONS);
			break;
		default:
			printf("Error: unrecognized operation.\n");
			break;
		}
		if (option != '0' && option != '7' && option != '3')
			printf("Select the next operation (insert 7 for the entire menu):\n");
	} while (option != '0');
	if (head != NULL)
		vaccine(&head, head->id);
}