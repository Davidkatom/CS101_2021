/***********************
* David Shnaiderov
* 209198308
* 01
* EX06
***********************/

#include "ex6.h"
int main() {	
	Trin_Ari* root = NULL;
	root = malloc(sizeof(Trin_Ari));
	if (root == NULL)
		quit(ERROR, root);
	root->name = INITIALIZE;
	root->head = NULL;
	menu(fullMenu, root);
	//loops until the user exits the program
	while (1)
		menu(shortMenu, root);
	return 0;
}