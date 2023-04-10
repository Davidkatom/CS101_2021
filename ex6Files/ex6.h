/***********************
* David Shnaiderov
* 209198308
* 01
* EX06
***********************/

#ifndef _EX6_H_
#define _EX6_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define INITIALIZE "~"
#define ERROR 1

struct Trin_Ari {
	int id;
	char * name;
	struct Trin_Ari *left;
	struct Trin_Ari *middle;
	struct Trin_Ari *right;
	struct Trin_Ari *head;
};
typedef struct Trin_Ari Trin_Ari;
typedef enum { fullMenu = 1, shortMenu = 0 } printMenu;
typedef enum { true = 1, false = 0 } bool;

typedef struct QNode {
	Trin_Ari* key;
	struct QNode* next;
}QNode;

typedef struct Queue {
	struct QNode* front, * rear;
}Queue;

void menu(int menuType, Trin_Ari* root);
void quit(int error, Trin_Ari* root);
#endif