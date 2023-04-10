//
// Created by Shira Goren on 01/12/2020.
//


#include "ass4.h"
//#include "ass4.c"
#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE
#include <assert.h>
#define SPACE ' '


void func1(char board[][SIZE*SIZE], char testBoard[][SIZE*SIZE]){
    for (int r = 0; r < (SIZE*SIZE); r++){
        for (int c = 0; c < (SIZE*SIZE); c ++){
            assert((board[r][c] == testBoard[r][c]) && "failed test\n");
        }
    }
}

//****************************************************************************************************************
//****************************************************************************************************************

    // tests for SIZE = 1
    //first change in define at top of your file

//****************************************************************************************************************
//****************************************************************************************************************
 int main() {
    //Tests for createBoard
    printf("\033[1;34m");
    printf("###Tests for createBoard###\n");
    printf("\n");

    char board24[SIZE * SIZE][SIZE * SIZE];
    char str24[] = "i/123456789/12a456789/123b6789/1234c89/12345d/12345678*//A23456789";

    char board25[SIZE * SIZE][SIZE * SIZE];
    char str25[] = "i";
    char tBoard25[SIZE * SIZE][SIZE * SIZE] = {'i'};

    char board26[SIZE * SIZE][SIZE * SIZE];
    char str26[] = "a";
    char tBoard26[SIZE * SIZE][SIZE * SIZE] = {' '};

    printf("\033[0;31m");
    printf("Expected for board24:\n");
    printf("\033[0;31m");
    printf("Error\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    createBoard(board24, str24);
    printf("\n");

    createBoard(board25, str25);
    func1(board25, tBoard25);
    printf("\033[0;31m");
    printf("passed test for board20\n");
    printf("\n");

    createBoard(board26, str26);
    func1(board26, tBoard26);
    printf("\033[0;31m");
    printf("passed test for board20\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for createBoard\n");
    printf("\n");
//**************************************************************************************************************
    //Tests for makeMove
    printf("\033[1;34m");
    printf("###Tests for makeMove###\n");
    printf("\n");

    char mm1[] = "replaceAll,i,@";
    char cc1Board[][SIZE * SIZE] = {'@'};
    char mm2[] = "change,0,0,*";
    char cc2Board[][SIZE * SIZE] = {'*'};
    char mm3[] = "delete,0,0";
    char cc3Board[][SIZE * SIZE] = {' '};
    char mm4[] = "add,0,0,1";
    char cc4Board[][SIZE * SIZE] = {'1'};

    makeMove(board25, mm1);
    func1(board25, cc1Board);
    printf("\033[0;31m");
    printf("passed test for replaceAll,1,3\n");
    printf("\n");

    makeMove(board25, mm2);
    func1(board25, cc2Board);
    printf("\033[0;31m");
    printf("passed test for change,0,0,*\n");
    printf("\n");

    makeMove(board25, mm3);
    func1(board25, cc3Board);
    printf("\033[0;31m");
    printf("passed test for delete,0,0\n");
    printf("\n");

    makeMove(board25, mm4);
    func1(board25, cc4Board);
    printf("\033[0;31m");
    printf("passed test for add,0,0,1\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for makeMove\n");
    printf("\n");

//****************************************************************************************************************
    //Tests for printBoard
    printf("\033[1;34m");
    printf("###Tests for printBoard###\n");
    printf("\n");

    printf("\033[0;31m");
    printf("Expected for board 25:\n");
    printf("1\n");
    printf("\n");
    printf("make sure there is a blank line between board and this message\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    printBoard(board25);
    printf("make sure there is a blank line between board and this message\n");


    printf("\033[0;31m");
    printf("passed all tests for printBoard\n");
    printf("\n");
//***********************************************************************************************************
    //Tests for testBoard
    printf("\033[1;34m");
    printf("###Tests for testBoard###\n");
    printf("\n");

    assert(testBoard(board25));
    printf("\033[0;31m");
    printf("passed test for bord25\n");
    printf("\n");

    assert(testBoard(board26));
    printf("\033[0;31m");
    printf("passed test for bord26\n");
    printf("\n");

    char board27[SIZE * SIZE][SIZE * SIZE];
    char str27[] = "i";
    char tBoard27[SIZE * SIZE][SIZE * SIZE] = {'i'};
    createBoard(board27, str27);

    assert(!testBoard(board27));
    printf("\033[0;31m");
    printf("passed test for bord27\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for testBoard\n");
    printf("\n");
//****************************************************************************************************************
    //Tests for isSameBoard
    printf("\033[1;34m");
    printf("###Tests for isSameBoard###\n");
    printf("\n");

    assert(isSameBoard(board25, board25));
    printf("\033[0;31m");
    printf("passed test for bord1 and board1\n");
    printf("\n");


    printf("\033[0;31m");
    printf("Expected for board25 and board27:\n");
    printf("Found inequality on row 0 col 0\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    assert(!isSameBoard(board25, board27));
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for isSameBoard\n");
    printf("\n");


//****************************************************************************************************************
    //Tests for completeBoard
    printf("\033[1;34m");
    printf("###Tests for completeBoard###\n");
    printf("\n");

    completeBoard(board26);
    assert(isSameBoard(board26, board25));
    printf("\033[0;31m");
    printf("passed test for completing board23\n");
    printf("\n");

    printf("\033[0;31m");
    printf("Expected for completeBoard(board27):\n");
    printf("\033[0;31m");
    printf("Error\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    completeBoard(board27);
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for completeBoard\n");
    printf("\n");
    //*******************************
    printf("\n");
    printf("\033[0;31m");
    printf("passed all tests for SIZE = 1\nyou can now change SIZE and run next set of tests\n");
    printf("\n");


//****************************************************************************************************************
//****************************************************************************************************************
    printf("\033[1;34m");
    printf("\n");
    printf("####End of tests####\n");
}