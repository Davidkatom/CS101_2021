/************
*David Shnaiderov
*209198308
*01
*ass04
************/
#include <math.h>
#include <stdio.h>
#include <string.h>

#define SPACE ' '
#define NEXT_LINE '/'
//number of marameters
#define PARAMS 3
//number of marameters
#define MAX_LENGTH 11

/******************************************************************************************
* Function Name: checkStr
* Function Input: char str[] (string for creating a board)
* Output: (int 0-1)
* Function Operation: checks if the string provided Is a legal string for creating a baord
******************************************************************************************/
int checkStr(char str[]) {
	int col = 0;
	int row = 0;
	for (unsigned int i = 0; i < strlen(str); i++) {
		//Checks if not enaough space in line
		if (str[i] >= 'a' && str[i] - 'a' < SIZE * SIZE) {
			col = col + (str[i] - 'a');
		}
		//Next Line
		else if (str[i] != NEXT_LINE) {
			col++;
		}

		if (col > SIZE * SIZE) {
			printf("Error\n");
			return 0;
		}

		if (str[i] == NEXT_LINE) {
			row++;
			col = 0;
		}

	}
	//checks if there aren't too many raws and characters
	if (row >= SIZE * SIZE || row < SIZE * SIZE - 1) {
		printf("Error\n");
		return 0;
	}
	return 1;
}
/************************************************************************
* Function Name: createBoard
* Function Input:	char board[][] (2D array to save the board to)
				char str[] (string for creating a board)
* Function Operation: creates a Sudoku board based on the string provided
					  and saves it in board
************************************************************************/
void createBoard(char board[][SIZE * SIZE], char str[]) {
	if (checkStr(str) == 0)
		return;
	int col = 0;
	int row = 0;

	for (unsigned int i = 0; i < strlen(str); i++) {
		//Adds spaces
		if (str[i] >= 'a' && str[i] - 'a' < SIZE * SIZE) {
			for (int j = 0; j <= str[i] - 'a'; j++) {
				board[row][col] = SPACE;
				col++;
			}
		}
		//Next Line
		else if (str[i] == NEXT_LINE) {
			for (int j = col; j < SIZE * SIZE; j++) {
				board[row][col] = SPACE;
				col++;
			}
			row++;
			col = 0;
		}
		//random char
		else {
			board[row][col] = str[i];
			col++;
		}
	}
	//Fills spaces in the board
	if (row < SIZE * SIZE) {
		for (int j = col; j < SIZE * SIZE; j++) {
			board[row][col] = SPACE;
			col++;
		}
	}
}

/************************************************************************
* Function Name: printBoard
* Function Inputchar board[][] (2D array)				
* Function Operation: prints the soduku board
************************************************************************/
void printBoard(char board[][SIZE * SIZE]) {
	for (int row = 0; row < SIZE * SIZE; row++) {
		if (row % SIZE == 0 && row != 0)
			printf("\n");

		for (int col = 0; col < SIZE * SIZE; col++)
		{
			if (col % SIZE == 0 && col != 0) {
				printf(" | ");
			}
			printf("%c", board[row][col]);
		}
		printf("\n");
	}
	printf("\n");
}
/************************************************************************
* Function Name: isSameBoard
* Function Input: char board[][] (2D array) char board1[][] (2D array)
* Function Operation: compares the two boards and prints inequalities
************************************************************************/
int isSameBoard(char board[][SIZE * SIZE], char board1[][SIZE * SIZE]) {
	for (int row = 0; row < SIZE * SIZE; row++)
	{
		for (int col = 0; col < SIZE * SIZE; col++)
		{
			if (board[row][col] != board1[row][col]) {
				printf("Found inequality on row %d col %d.\n", row, col);
				return 0;
			}
		}
	}
	return 1;
}

/************************************************************************
* Function Name: makeMove
* Input:char:	char board[][] (2D array) char move[] (command)
* Function Operation: makes a move on the recived board.
						The moves are: replaceAll, change, add, delete
************************************************************************/
void makeMove(char board[][SIZE * SIZE], char move[]) {
	//recives move// 	
	int len = strlen(move) - 1;
	enum optionsIndex { replaceAll, change, add, delete };
	char options[][MAX_LENGTH] = { "replaceAll", "change", "add", "delete" };
	char param[3];
	int numOfParams = 0;
	int command = 0;
	//checks for string legality 
	if (move[len - 1] != ',') {
		printf("Error\n");
		return;
	}
	for (int i = 0; i <= len; i++) {
		if (move[i] == ',')
			numOfParams++;
		if (move[i] == SPACE || move[i] == NEXT_LINE) {
			printf("Error\n");
			return;
		}
	}	

	if (strstr(move, options[replaceAll]) != NULL && numOfParams == 2 &&
		strlen(move) == strlen(options[replaceAll]) + numOfParams*2)
		command = replaceAll;
	else if (strstr(move, options[change]) != NULL && numOfParams == 3 &&
		strlen(move) == strlen(options[change]) + numOfParams * 2)
		command = change;
	else if (strstr(move, options[add]) != NULL && numOfParams == 3 &&
		strlen(move) == strlen(options[add]) + numOfParams * 2)
		command = add;
	else if (strstr(move, options[delete]) != NULL && numOfParams == 2 &&
		strlen(move) == strlen(options[delete]) + numOfParams * 2)
		command = delete;
	else {
		printf("Error\n");
		return;
	}

	int index = strlen(options[command]) + 1;
	for (int i = 0; index <= len; i++) {
		param[i] = move[index];
		index = index + 2;
	}

	//execute move
	int charOnBoard = 0;
	for (int i = 0; i < numOfParams; i++) {
		if (param[i] >= 'a' && param[i] - 'a' < SIZE * SIZE) {
			printf("Error\n");
			return;
		}
	}
	if (command == replaceAll) {
		
		for (int row = 0; row < SIZE * SIZE; row++) {
			for (int col = 0; col < SIZE * SIZE; col++) {
				if (board[row][col] == param[0]) {
					board[row][col] = param[1];
					charOnBoard = 1;
				}
			}
		}
		if (charOnBoard == 0) {
			printf("Error\n");			
		}
		return;
	}
	int col = param[1] - '0';
	int row = param[0] - '0';
	
	if (row < 0 || col < 0 || row > SIZE*SIZE || col > SIZE*SIZE) {
		printf("Error\n");
		return;
	}

	if (command == change) {
		if (board[row][col] != SPACE)
			board[row][col] = param[2];
		else {
			printf("Error\n");			
		}
		return;
	}
	else if (command == add) {
		if (board[row][col] == SPACE)
			board[row][col] = param[2];
		else {
			printf("Error\n");
		}
		return;
	}
	else if (command == delete) {
		if (board[row][col] != SPACE)
			board[row][col] = SPACE;
		else {
			printf("Error\n");
			return;
		}
	}
}

/************************************************************************
* Function Name: testBoard
* Input:char:	char board[][] (2D array)
* Function Operation: checks if the board layout is legal and there 
					  are no wrong characters
************************************************************************/
int testBoard(char board[][SIZE * SIZE]) {
	//check for invalid chars
	for (int row = 0; row < SIZE * SIZE; row++) {
		for (int col = 0; col < SIZE * SIZE; col++) {
			if (board[row][col] <= '0' || board[row][col] > '0' + SIZE * SIZE) {
				if(board[row][col] != SPACE)
					return 0;
			}
		}
	}
	//check columns and rows
	for (int row = 0; row < SIZE * SIZE; row++)
	{
		for (int col = 0; col < SIZE * SIZE; col++)
		{
			if (board[row][col] == SPACE)
				continue;
			for (int i = 0; i < SIZE * SIZE; i++)
			{
				if ((board[row][col] == board[row][i] && col != i) ||
					(board[row][col] == board[i][col] && row != i)) {
					return 0;
				}
			}
		}
	}
	//check in squares
	char square[SIZE * SIZE];
	int arrayIndex = 0;
	for (int squareIndex = 0; squareIndex < SIZE * SIZE; squareIndex++) {
		//create square
		arrayIndex = 0;
		for (int row = (squareIndex / SIZE) * SIZE; row < (squareIndex / SIZE) * SIZE + SIZE; row++)
		{
			for (int col = (squareIndex * SIZE) % (SIZE*SIZE);
				col < (squareIndex * SIZE) % (SIZE * SIZE) + SIZE; col++)
			{
				square[arrayIndex] = board[row][col];
				arrayIndex++;
			}
		}
		//check if numbers repeat
		for (int row = 0; row < SIZE; row++)
		{
			if (square[row] == SPACE)
				continue;
			for (int i = 0; i < SIZE * SIZE; i++) {
				if (square[row] == square[i] && row != i) {
					return 0;
				}
			}
		}
	}
	return 1;
}

/************************************************************************
* Function Name: completeBoard
* Input:char:	char board[][] (2D array)
* Function Operation: completes the board by the standart Sudoku rules
************************************************************************/
void completeBoard(char board[][SIZE * SIZE]) {
	if (testBoard(board) == 0) {
		printf("Error\n");
		return;
	}
	int sum = 0;
	int x;
	int y;
	int maxSum = 0;
	for (int i = 1; i <= SIZE * SIZE; i++) {
		maxSum = maxSum + i;
	}
	//set to one if more then one number missing
	int flag = 0;
	for (int row = 0; row < SIZE * SIZE; row++) {
		flag = 0;
		x = 0;
		y = 0;
		sum = 0;
		for (int col = 0; col < SIZE * SIZE; col++) {
			if (board[row][col] == SPACE) {
				flag++;
				x = col;
				y = row;
				if (flag == 2) {
					printf("Error\n");
					return;
				}
			}			
			else {
				sum = sum + (board[row][col] - '0');				
			}

		}
		if(flag == 1)
			board[y][x] = maxSum - sum + '0';
	}
}

