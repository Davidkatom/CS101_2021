//
// Created by Shira Goren on 01/12/2020.
//
//**************************************************************************************************************
#include "ass4.h"
//#include "ass4.c"
//**************************************************************************************************************

#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 2
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

    //tests for SIZE = 2
    //first change in define at top of your file

//****************************************************************************************************************
//****************************************************************************************************************
int main() {
    //Tests for createBoard
    printf("\033[1;34m");
    printf("###Tests for createBoard###\n");
    printf("\n");

    // tests for SIZE = 2:
    char board19[SIZE * SIZE][SIZE * SIZE];
    char str19[] = "i/123456789/12a456789/123b6789/1234c89/12345d/12345678*//A23456789";

    char board20[SIZE * SIZE][SIZE * SIZE];
    char str20[] = "i/1234/12a4/d";
    char tBoard20[SIZE * SIZE][SIZE * SIZE] = {'i', ' ', ' ', ' ', '1', '2', '3', '4', '1', '2', ' ', '4', ' ', ' ', ' ', ' '};

    char board21[SIZE * SIZE][SIZE * SIZE];
    char str21[] = "1234/4321/2413/3142";
    char tBoard21[SIZE * SIZE][SIZE * SIZE] = {'1', '2', '3', '4', '4', '3', '2', '1', '2', '4', '1', '3', '3', '1', '4', '2'};

    char board22[SIZE * SIZE][SIZE * SIZE];
    char str22[] = "1534/4521/2413/3142";
    char tBoard22[SIZE * SIZE][SIZE * SIZE] = {'1', '5', '3', '4', '4', '5', '2', '1', '2', '4', '1', '3', '3', '1', '4', '2'};

    //this board has valid input, will pass testBoard, but is unsolvable
    char boardS1[SIZE * SIZE][SIZE * SIZE];
    char strS1[] = "431a/1a23/32a1/a134";
    char tBoardS1[SIZE * SIZE][SIZE * SIZE] = {'4', '3', '1', ' ', '1', ' ', '2', '3', '3', '2', ' ', '1', ' ', '1', '3', '4'};

    printf("\033[0;31m");
    printf("Expected for board19:\n");
    printf("\033[0;31m");
    printf("Error\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    createBoard(board19, str19);
    printf("\n");

    createBoard(board20, str20);
    func1(board20, tBoard20);
    printf("\033[0;31m");
    printf("passed test for board20\n");
    printf("\n");

    createBoard(board21, str21);
    func1(board21, tBoard21);
    printf("\033[0;31m");
    printf("passed test for board21\n");
    printf("\n");

    createBoard(board22, str22);
    func1(board22, tBoard22);
    printf("\033[0;31m");
    printf("passed test for board22\n");
    printf("\n");

    createBoard(boardS1, strS1);
    func1(boardS1, tBoardS1);
    printf("\033[0;31m");
    printf("passed test for boardS1\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for createBoard\n");
    printf("\n");
    //******************************
    //Tests for makeMove
    printf("\033[1;34m");
    printf("###Tests for makeMove###\n");
    printf("\n");


    char m1[] = "replaceAll,1,3";
    char c1Board20[SIZE * SIZE][SIZE * SIZE] = {'i', ' ', ' ', ' ', '3', '2', '3', '4', '3', '2', ' ',
                                                '4', ' ', ' ', ' ', ' '};
    char m2[] = "change,5,3,*";
    char m3[] = "change,1,3,*";
    char c2Board20[SIZE * SIZE][SIZE * SIZE] = {'i', ' ', ' ', ' ', '3', '2', '3', '*', '3', '2', ' ',
                                                '4', ' ', ' ', ' ', ' '};
    char m4[] = "add,0,3,*";
    char c4Board20[SIZE * SIZE][SIZE * SIZE] = {'i', ' ', ' ', '*', '3', '2', '3', '*', '3', '2', ' ',
                                                '4', ' ', ' ', ' ', ' '};
    char m5[] = "delete,1,3";
    char c3Board20[SIZE * SIZE][SIZE * SIZE] = {'i', ' ', ' ', '*', '3', '2', '3', ' ', '3', '2', ' ',
                                                '4', ' ', ' ', ' ', ' '};

    makeMove(board20, m1);
    func1(board20, c1Board20);
    printf("\033[0;31m");
    printf("passed test for replaceAll,1,3\n");
    printf("\n");

    printf("\033[0;31m");
    printf("Expected for %s:\n", m2);
    printf("\033[0;31m");
    printf("Error\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    makeMove(board20, m2);
    printf("\n");

    makeMove(board20, m3);
    func1(board20, c2Board20);
    printf("\033[0;31m");
    printf("passed test for change,1,3,*\n");
    printf("\n");

    makeMove(board20, m4);
    func1(board20, c4Board20);
    printf("\033[0;31m");
    printf("passed test for change,1,3,*\n");
    printf("\n");

//    printf("\033[0;31m");
//    printf("Expected for %s:\n", m4);
//    printf("\033[0;31m");
//    printf("Error\n");
//    printf("\n");
//    printf("\033[1;32m");
//    printf("Got:\n");
//    printf("\033[0m");
//    makeMove(board20, m4);
//    printf("\n");

    makeMove(board20, m5);
    func1(board20, c3Board20);
    printf("\033[0;31m");
    printf("passed test for add,1,3\n");
    printf("\n");
    printf("\033[0;31m");
    printf("passed all tests for makeMove\n");
    printf("\n");
    //**************************************

    //Tests for printBoard
    printf("\033[1;34m");
    printf("###Tests for printBoard###\n");
    printf("\n");

//    {'i', ' ', ' ', '*', '3', '2', '3', ' ', '3', '2', ' ','4', ' ', ' ', ' ', ' '};

    printf("\033[0;31m");
    printf("Expected for board 20:\n");
    printf("i  |  *\n32 | 3 \n\n32 |  4 \n   |   \n");
    printf("\n");
    printf("make sure there is a blank line between board and this message\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    printBoard(board20);
    printf("make sure there is a blank line between board and this message\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for printBoard\n");
    printf("\n");
    //*********************************************

    //Tests for testBoard
    printf("\033[1;34m");
    printf("###Tests for testBoard###\n");
    printf("\n");

    assert(!testBoard(board20));
    printf("\033[0;31m");
    printf("passed test for bord20\n");
    printf("\n");

    assert(testBoard(board21));
    printf("\033[0;31m");
    printf("passed test for bord21\n");
    printf("\n");

    assert(!testBoard(board22));
    printf("\033[0;31m");
    printf("passed test for bord22\n");
    printf("\n");

    assert(testBoard(boardS1));
    printf("\033[0;31m");
    printf("passed test for bordS1\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for testBoard\n");
    printf("\n");
    //****************************************
    //Tests for isSameBoard
    printf("\033[1;34m");
    printf("###Tests for isSameBoard###\n");
    printf("\n");

    assert(isSameBoard(board20, board20));
    printf("\033[0;31m");
    printf("passed test for bord1 and board1\n");
    printf("\n");


    printf("\033[0;31m");
    printf("Expected for board21 and board22:\n");
    printf("Found inequality on row 0 col 1\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    assert(!isSameBoard(board21, board22));
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for isSameBoard\n");
    printf("\n");
    //**********************************

    //Tests for completeBoard
    printf("\033[1;34m");
    printf("###Tests for completeBoard###\n");
    printf("\n");

    char board23[SIZE * SIZE][SIZE * SIZE];
    char str23[] = "12a4/4321/2a13/3142";
    char tBoard23[SIZE * SIZE][SIZE * SIZE] = {'1', '2', ' ', '4', '4', '3', '2', '1', '2', ' ', '1', '3', '3', '1', '4', '2'};

    createBoard(board23, str23);
    completeBoard(board23);
    printf("\033[0;31m");
    printf("Expected for board23:\n");
    printf("\033[0;31m");
    printBoard(board21);
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    printBoard(board23);
    printf("\n");

    assert(isSameBoard(board23, board21));
    printf("\033[0;31m");
    printf("passed test for completing board23\n");
    printf("\n");

    printf("\033[0;31m");
    printf("Expected for completeBoard(board22):\n");
    printf("\033[0;31m");
    printf("Error\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    completeBoard(board22);
    printf("\n");

//   test was changed based on piazza
    //an unsolvable board- that passes the testBoard function
//    printf("\033[0;31m");
//    printf("Expected for completeBoard(boardS1):\n");
//    printf("\033[0;31m");
//    printf("Error\n");
//    printf("\n");
//    printf("\033[1;32m");
//    printf("Got:\n");
//    printf("\033[0m");
//    completeBoard(boardS1);
//    printf("\n");

    completeBoard(boardS1);
    assert(!testBoard(boardS1));
    printf("\033[0;31m");
    printf("Expected for boardS1 and tBoardS1:\n");
    printf("Found inequality on row 0 col 3.\n");
    printf("\n");
    printf("\033[1;32m");
    printf("Got:\n");
    printf("\033[0m");
    assert(!isSameBoard(boardS1, tBoardS1));
    printf("\033[0;31m");
    printf("\n");
    printf("passed test for boardS1\n");
    printf("\n");

    printf("\033[0;31m");
    printf("passed all tests for completeBoard\n");
    printf("\n");
    //*******************************
    printf("\n");
    printf("\033[0;31m");
    printf("passed all tests for SIZE = 2\nyou can now change SIZE and run next set of tests\n");
    printf("\n");

    //****************************************************************************************************************
//****************************************************************************************************************
    printf("\033[1;34m");
    printf("\n");
    printf("####End of tests####\n");
}