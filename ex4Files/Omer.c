/*****
*Omer Hamdi
* 208667113
* 01
* ass04
*****/

#include <stdio.h>
#include <string.h>
#include <math.h>

//value for the size of our game board - REMOVE BEFORE COMPILING
#define SIZE 3
//char definations
#define NEXTLINE '/'
#define SPACE ' '
#define COMMA ','
#define FIRSTCHAR 'a'
//options avialable for actions
#define OPTIONS 3
//options Max Size for Char input
#define OPTIONMAXSIZE 11
//running Styles we have for the soduku game
#define RUNNINGSTYLES 3
//prints error message and returns the void function
#define PRINTERR {printf("Error\n"); return;}

//Declaring the functions
int strCompare(char fullMove[], char moveToCheck[]);
void setActions(char move[], char actions[]);
void addSpacesToBoard(char board[][SIZE * SIZE], int row, int col, int colEnd);
int boardSourceCheck(char str[]);

/******
* Function Name:boardSourceCheck
* Input: char str(the source for our soduku board)
* Output: int (1 or 0) 1 - valid, 0 - invalid.
* Function Operation:	gets the sodoku source char array,make validity checks to the source and returns 1/0 if valid/not.
make sure we don't have too many spaces or not enough lines.
checks for the space indicators ('a' to 'a' + SIZE*SIZE).
******/
int boardSourceCheck(char str[]) {
	int NextLineCounter = 0;
	//a check for the recived source string of the board to make sure we don't get too many chars in any of the rows.
	for (int i = 0, charCounter = 1;str[i] != '\0';i++, charCounter++) {
		//checks if a space indicator is entered and add the charCounter the relevant count
		if (str[i] >= FIRSTCHAR && str[i] <= (FIRSTCHAR + SIZE * SIZE)) {
			charCounter += (str[i] - FIRSTCHAR);
		}
		//check if we got to a space indicator
		if (str[i] == NEXTLINE) {
			NextLineCounter++;
			//checks if the end of the row indicator is valid and if not return 0 (error)
			if ((charCounter > (SIZE * SIZE) + 1)) {
				return 0;
			}
			//resets the charCounter for this row
			charCounter = 0;
		}
	}
	//checks if we have exactly enough nextline indicators
	if (NextLineCounter != (SIZE * SIZE) - 1) {
		return 0;
	}
	return 1;
}

/******
* Function Name:addSpacesToBoard
* Input:	char board(two dimentional char array- indicates the Sudoku board) ,
int row (the current row), int col (the current col), int colEnd (the end coloumn)
* Output: void.
* Function Operation:	gets a pointer to the sodoku board and 3 integers to indicates the current row and col and the end col.
adds spaces in the recived row untill we get to the colEnd.
******/
void addSpacesToBoard(char board[][SIZE * SIZE], int row, int col, int colEnd) {
	while (col < colEnd) {
		board[row][col] = SPACE;
		col++;
	}
}

/******
* Function Name:createBoard
* Input:	char board(two dimentional char array- indicates the Sudoku board),
char str(a char array) - the source string for the soduku board
* Output: void.
* Function Operation:	gets a pointer to the sodoku board and a char with the source we need to fill.
after checking the source char array - add to the board (pointer) the source we got (str).
add spaces as needed when encounter a space char or when got to the end of the line.
******/
void createBoard(char board[][SIZE * SIZE], char str[]) {
	if (boardSourceCheck(str) == 0) PRINTERR;
	//a char to indicate our next char in line everytime
	char nextChar;
	//for loop to loop through the recived str array and fill the board accordingly
	int rowCounter = 0, colCounter = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		nextChar = str[i];
		//if next char is next row indicator - fill the rest of the row (if needed) with spaces.
		if (nextChar == NEXTLINE) {
			//add spaces to the board for the rest of the line
			addSpacesToBoard(board, rowCounter, colCounter, SIZE * SIZE);
			colCounter = SIZE * SIZE;
		}
		//else - fill the board with the appropriate char
		else {
			//checks if the recived Char is a space indicator
			if (nextChar >= FIRSTCHAR && nextChar <= (FIRSTCHAR + SIZE * SIZE))
			{
				//make spaces according to the recived space char
				addSpacesToBoard(board, rowCounter, colCounter, colCounter + nextChar - FIRSTCHAR + 1);
				colCounter += nextChar - FIRSTCHAR;
			}
			else {
				board[rowCounter][colCounter] = nextChar;
			}
		}
		//if we get to the end of the row - go to the next row
		if (colCounter == SIZE * SIZE) {
			colCounter = 0;
			rowCounter++;
		}
		else {
			colCounter++;
		}
	}
	//fill the last spaces if there are any left to fill
	addSpacesToBoard(board, rowCounter, colCounter, SIZE * SIZE);
}

/******
* Function Name:printBoard
* Input:	char board(two dimentional char array- indicates the Sudoku board),\
char board1(two dimentional char array- indicates the other Sudoku board)
* Output: int (0 or 1).
* Function Operation:	tests if the two boards are equal - one place at a time.
returns 1 if boards are equal - otherwise 0
******/
void printBoard(char board[][SIZE * SIZE]) {
	char nextChar;
	for (int i = 0, rowIndex = 0; i < (SIZE * SIZE * SIZE * SIZE); i++) {
		nextChar = board[rowIndex][i - (rowIndex * (SIZE * SIZE))];
		printf("%c", nextChar);
		if (((i + 1) % SIZE == 0) && ((i + 1) % (SIZE * SIZE) != 0)) {
			printf(" | ");
		}
		if ((i + 1) % (SIZE * SIZE) == 0) {
			printf("\n");
		}
		//checks if we got to the end of the line
		if (i + 1 >= (SIZE * SIZE) + (rowIndex * SIZE * SIZE)) {
			rowIndex++;
			if ((rowIndex) % SIZE == 0) {
				printf("\n");
			}
		}
	}
}

/******
* Function Name:isSameBoard
* Input:	char board(two dimentional char array- indicates the Sudoku board),
char board1(two dimentional char array- indicates the other Sudoku board)
* Output: int (0 or 1).
* Function Operation:	tests if the two boards are equal - one place at a time.
returns 1 if boards are equal - otherwise 0
******/
int isSameBoard(char board[][SIZE * SIZE], char board1[][SIZE * SIZE]) {
	for (int row = 0; row < SIZE * SIZE; row++) {
		for (int col = 0; col < SIZE * SIZE; col++) {
			//checks for the inequality
			if (board[row][col] != board1[row][col]) {
				printf("Found inequality on row %d col %d.\n", row, col);
				return 0;
			}
		}
	}
	return 1;
}

/******
* Function Name:setActions
* Input:	char move(char array) - pointer to the move text,
char actions(char array) - pointer to the actions supposed to be taken later.
* Output: void.
* Function Operation:	first - reset the actions array.
take the move char array and assign the actions (that come after the first ',') to the actions char.
when there is an error in the actions - put a flag (space ' ') in the first char of actions[0].
******/
void setActions(char move[], char actions[]) {
	//resets the array before entering new chars
	for (int i = 0; i <= OPTIONS; i++) {
		actions[i] = '\0';
	}
	int i = 0;
	int charIndex = 0;
	while (move[i] != '\0') {
		//checks the last char is not ',', checks if there's a '/' char in the str, checks we don't have a space char
		if (((move[i] == COMMA) && (move[i + 1] == '\0')) || move[i + 1] == NEXTLINE || move[i + 1] == SPACE) {
			//flags the actions we have an error
			actions[0] = SPACE;
			return;
		}
		if ((move[i] == COMMA) && (move[i + 1] != '\0')) {
			/*
			//check to make sure we don't have too many actions, and to make sure we don't have more than one char a time.
			also checks for casese we have more than 1 char bewtween ','
			*/
			if (charIndex >= OPTIONS || move[i + 1] == COMMA || (move[i + 2] != COMMA && move[i + 2] != '\0')) {
				//flags the actions we have an error
				actions[0] = SPACE;
				return;
			}
			actions[charIndex] = move[i + 1];
			charIndex++;
			//incase we have a char of ','
			i++;
		}
		i++;
	}
}

/******
* Function Name:strCompare
* Input:	char fullMove(char array) - pointer to the fullMove text,
char moveToCheck (char array) - pointer to the move we need to check
* Output: int (0 or 1).
* Function Operation:	checks if the movetocheck char array is inside the beggining of full move.
*						return 0 when found and 1 otherwise
******/
int strCompare(char fullMove[], char moveToCheck[]) {
	int i = 0;
	//checks for boundrys and loops untill getting to the boundry of one of the moves
	while (fullMove[i] != '\0' && fullMove[i] != COMMA && moveToCheck[i] != '\0') {
		if (fullMove[i] != moveToCheck[i]) {
			return 1;
		}
		i++;
	}
	//make sure the len of the movetocheck is the same as the compared chars
	if (strlen(moveToCheck) == (i + 1)) {
		return 0;
	}
	return 1;
}

/******
* Function Name:makeMove
* Input:	char board(two dimentional char array) - a pointer to the Sudoku board,
char move (array of chars) - a pointer to the move we ned to take
* Output: void.
* Function Operation:	gets a soduko board and a move and do the following:
*						make sure the move is valid.
*						make sure there are not too many moves or invalid chars.
*						go inside replaceAll/Change/Add according to what's requested - make special validity checks if needed.
*						if non of the validity checks failed - make the selected move.
*						if no move was made - print an error.
******/
void makeMove(char board[][SIZE * SIZE], char move[]) {
	char actions[OPTIONS + 1];
	setActions(move, actions);
	//checks if a flag was raised during the creating of the actions
	if (actions[0] == SPACE)PRINTERR;
	//checks we don't have space chars as one of our inputs (never valid)
	for (int i = 0; i < OPTIONS; i++)
	{
		if (actions[i] >= FIRSTCHAR && actions[i] <= (FIRSTCHAR + SIZE * SIZE + SIZE * SIZE)) PRINTERR;
	}
	char nextChar;
	if (strCompare(move, "replaceAll,") == 0) {
		//checks for move-specific invalid inputs - no third action is valid and second action is a must
		if (actions[2] != '\0' || actions[1] == '\0') PRINTERR;
		int totalReplacments = 0, row = 0;
		//loops through the board and make the selected changes
		for (int i = 0; i < (SIZE * SIZE * SIZE * SIZE);i++) {
			//get the next char (place) in the sequence
			nextChar = board[row][(int)i % (SIZE * SIZE)];
			//if the next char is same as the search one, replace it in board with the char2 and add to the counter
			if (nextChar == actions[0]) {
				board[row][i % (SIZE * SIZE)] = actions[1];
				totalReplacments++;
			}
			//when we got to the end of the row - go to the next one
			if ((i + 1) % (SIZE * SIZE) == 0) row++;
		}
		//make sure there were any replacements - otherwise prints an error
		if (totalReplacments == 0) PRINTERR;
	}
	else {
		//validity checks for out of boundry locations
		if (actions[0] > ('0' + SIZE * SIZE) || actions[0] < '0') PRINTERR;
		if (actions[1] > ('0' + SIZE * SIZE) || actions[1] < '0') PRINTERR;
		//vars for the locations of the actions
		int locationRow = actions[0] - '0', locationCol = actions[1] - '0';
		if (strCompare(move, "change,") == 0 && locationRow < (SIZE * SIZE) && locationCol < (SIZE * SIZE)) {
			//checks for move-specific invalid inputs - can't change space
			if (board[locationRow][locationCol] == SPACE) PRINTERR;
			//validity checks of the actions
			for (int i = 0; i < OPTIONS; i++)
			{
				if (actions[i] == '\0') PRINTERR;
			}
			//changes the board in the recived location.
			board[locationRow][locationCol] = actions[2];
		}
		else if (strCompare(move, "add,") == 0 && locationRow < (SIZE * SIZE) && locationCol < (SIZE * SIZE)) {
			//checks for move-specific invalid inputs - can't add to filled place
			if (board[locationRow][locationCol] != SPACE) PRINTERR;
			board[locationRow][locationCol] = actions[2];
		}
		else if (strCompare(move, "delete,") == 0 && locationRow < (SIZE * SIZE) && locationCol < (SIZE * SIZE)) {
			//checks for move-specific invalid inputs - can't delete a space, can never have a third action.
			if (board[locationRow][locationCol] == SPACE || actions[2] != '\0') PRINTERR;
			board[locationRow][locationCol] = SPACE;
		}
		//when no action was executed - print error message
		else PRINTERR;
	}
}

/******
* Function Name:testBoard
* Input: char board(two dimentional char array) - a pointer to the Sudoku board
* Output: int (0 or 1).
* Function Operation:	tests if the board is valid in the following ways:
*						checks we don't have numbers outside our boundries (space is okay)
*						checks we don't have the same number is the same row/colum/cube.
*						returns 1 if board is valid - otherwise 0
******/
int testBoard(char board[][SIZE * SIZE]) {
	//validity check for smallest size case (either a space or a '1')
	if (SIZE == (SIZE * SIZE) && board[0][0] != '1' && board[0][0] != SPACE)return 0;
	//outsideRunner running for the first row/col/cube and so on and the outside runner is running for the subcubes
	for (int outterRunner = 0; outterRunner < (SIZE * SIZE); outterRunner++)
	{
		//the inside runner for the subrunning - for rows it will be cols, for cols rows and for cubes it will be calculate
		for (int insideRunner = 0; insideRunner < (SIZE * SIZE) - 1; insideRunner++) {
			//if the index points at a space ignore it specifically
			if (board[outterRunner][insideRunner] != SPACE) {
				//make sure the current place in the board is a valid number inside our boundaries
				if (board[outterRunner][insideRunner] < '1' || board[outterRunner][insideRunner] > '0' + SIZE * SIZE)return 0;
				/*
				for each place in our matrix: checks if in the future places have another show of the current char
				returns 0 (error) if we found more than one show of the same char in the sequence (checks for row, col and cube)
				*/
				for (int pos = (insideRunner + 1); pos < (SIZE * SIZE); pos++) {
					//rows check:
					if (board[outterRunner][insideRunner] == board[outterRunner][pos])return 0;
					//cols check:
					if (board[insideRunner][outterRunner] == board[pos][outterRunner]) return 0;
					//calcs for the rows and the cols checks for cube case
					int rowCalc = (outterRunner % SIZE) * SIZE + (insideRunner % SIZE);
					int colCalc = (outterRunner / SIZE) * SIZE + (insideRunner / SIZE);
					int rowPos = (outterRunner % SIZE) * SIZE + ((pos) % SIZE);
					int colPos = (outterRunner / SIZE) * SIZE + ((pos) / SIZE);
					//cubes check:
					if (board[rowCalc][colCalc] == board[rowPos][colPos]) return 0;
				}
			}
		}
	}
	return 1;
}

/******
* Function Name:completeBoard
* Input: char board(two dimentional char array) - a pointer to the Sudoku board
* Output: void.
* Function Operation:	the functions gets the soduku board and solve it if there is at most one missing solution in each line.
*						if the board is invalid or unsolvable ny the rules mentioned above - print an error.
******/
void completeBoard(char board[][SIZE * SIZE]) {
	//a char of the missing numbers while [] indicates which row the miising number needs to fill.
	char missingNumbers[SIZE * SIZE] = { "" };
	if (testBoard(board) == 0)PRINTERR;
	for (int row = 0; row < SIZE * SIZE; row++) {
		//loops throuh all the numbers that supposed to show up in the soduku
		for (int num = 1; num <= SIZE * SIZE; num++) {
			//checks all the positions in the current row to find the curr num, if not - add it to our 'missingNums' array
			for (int pos = 0; pos < SIZE * SIZE;pos++) {
				if (board[row][pos] == num + '0') {
					//if the number was found - great we can continue to the next number
					break;
				}
				if ((pos + 1) == (SIZE * SIZE)) {
					//make sure we didn't found a missing numbers alredy.
					if (missingNumbers[row] == 0) {
						missingNumbers[row] = (num + '0');
					}
					else PRINTERR;
				}
			}
		}
	}
	//after we have all the missing numbers and no multiple spaces found in any of the rows - fill them!
	for (int row = 0; row < SIZE * SIZE; row++) {
		for (int col = 0; col < SIZE * SIZE;col++) {
			if (board[row][col] == SPACE) {
				board[row][col] = missingNumbers[row];
			}
		}
	}
}