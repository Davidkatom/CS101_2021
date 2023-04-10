/***********************
* David Shnaiderov
* 209198308
* 01
* ass3
***********************/
#include "ass3.h"
#include "stdio.h"

#define BONUS
//number of possible digits {0,1,2}
#define WILD_DIC 3
#define WILD_CHAR '?'

/***************************************************
Function Name:towerOfHanoi
Function Input: 
    numdisks - the number to multiply
    fromRod - original rod
    toRod - destination rod
    auxRod - temp rod
Function Operation: prints the steps required to solve the 
tower of hanoi recursivly 
****************************************************/

void towerOfHanoi(int numDisks, char fromRod, char toRod, char auxRod){
    if( numDisks == 0)
        return;
    if(numDisks == 1){
        printf("Move disk 1 from rod %c to rod %c.\n", fromRod, toRod);
        return;
    }
    towerOfHanoi(numDisks - 1, fromRod, auxRod, toRod);
    printf("Move disk %d from rod %c to rod %c.\n",numDisks, fromRod, toRod);
    towerOfHanoi(numDisks-1, auxRod, toRod, fromRod);
}


/***************************************************
Function Name:isPalindrome
Function Input: 
    char str[] - the letter/number sequance
    int len - sequance length    
Function Operation: calls the function isPalindrome to print if the seqance entered is a palindrome
****************************************************/
int checkifPalindrome(char str[], int len, int index);
void isPalindrome(char str[], int len){
    if(checkifPalindrome(str, len, 0) == 1)
        printf("The reverse of %s is also %s.\n", str, str);
    else
        printf("The reverse of %s is not %s.\n", str, str);
}



/***************************************************
Function Name:isPalindrome
Function Input: 
    char str[] - the letter/number sequance
    int len - sequance length 
function Output
    int 1/0 - if output 1 then it's a palindrome, 0 if not       
Function Operation: checks recursivly if the sequance is a palindrome
****************************************************/

int checkifPalindrome(char str[], int len, int index){
    if(index == len-1 || index > len-1)
        return 1;

    if(str[index] == str[len-1]){
        return checkifPalindrome(str, len-1, index+1);
    }
    else{
        return 0;
    }
            
}


/*****************************************************************************************************
Function Name: recPrintAllCombinations
Function Input: 
    char pattern[] - the recived pattern
    int len - the length of the pattern
    int rows - the number of combinations that should be printed.
    int numWilds - the number of '?' in the sequnace
    int curRow - the current row that is being worked on
    int curCol - the current column that is being worked on
    int index - the index of the '?'
Function Operation: prints recursivly all the possible combinations of the pattern
                    where the '?' is replaced by {0,1,2}.
******************************************************************************************************/

float calcPowRec(long int firstNum, long int secondNum);
void recPrintAllCombinations(char pattern[], int len, int rows, int numWilds, int curRow, int curCol, int index){
    //creates a local index variable for '?'
    int curIndex = index; 
	
	//checks if done
	if (curCol == len && curRow == rows - 1) {
		printf("\n");
		return;
	}

	//checks if the sepcific combination is done
	if (curCol == len) {
		printf("\n");
		curIndex = numWilds - 1;
		curCol = 0;
		curRow = curRow + 1;
	}

	//fixed digit
	if (pattern[curCol] != WILD_CHAR) {
		printf("%c", pattern[curCol]);
	}
	//wild num
	else {
		printf("%d", (curRow / (int)calcPowRec(WILD_DIC, curIndex)) % WILD_DIC);
		curIndex = curIndex - 1;
	}
	curCol++;		
	recPrintAllCombinations(pattern, len, rows, numWilds, curRow, curCol, curIndex);  
}

/*****************************************************************************************************
Function Name: recPrintAllCombinations
Function Input: 
    char pattern[] - the recived pattern
    int len - the length of the pattern
function Output:
    int, the number of '?' found in the sequance.
Function Operation: returns the number of '?' in the given sequance recursivlt
******************************************************************************************************/
int calcNumberOfOptions(char pattern[], int len, int numWilds){
    if(pattern[len-1] == WILD_CHAR && len-1 ==0)
        return numWilds + 1;
    if(len-1 == 0)
        return numWilds;
    if(pattern[len-1] == WILD_CHAR)
        return calcNumberOfOptions(pattern, len-1, numWilds + 1);

    else
        return calcNumberOfOptions(pattern, len-1, numWilds);

}

/*****************************************************************************************************
Function Name: printAllCombinations
Function Input: 
    char pattern[] - the recived pattern
    int len - the length of the pattern
Function Operation: calls the recursive function that prints all the possible combinations of the pattern
                    where the '?' is replaced by {0,1,2}. Then prints the total number of combinations.
******************************************************************************************************/
float calcPowRec(long int firstNum, long int secondNum);
void printAllCombinations(char pattern[], int len){
    int numOfWilds = calcNumberOfOptions(pattern, len, 0);
    int combinations = (int)calcPowRec(WILD_DIC, numOfWilds);
    recPrintAllCombinations(pattern, len, combinations, numOfWilds, 0, 0, numOfWilds-1);
    printf("Number of combinations is: %d\n", combinations);
}

/***************************************************
Function Name:calcPowRec
function Output: calculated float 
Function Input: 
    firstNum - the number to multiply
    secondNum - the power
Function Operation: calculates and returns the the first number in the power of the 
power of the second recursivly 
****************************************************/

float calcPowRec(long int firstNum, long int secondNum){
    if(secondNum == 0)
        return 1;

    if(firstNum == 0)
        return 0;

    if (secondNum < 0)
        secondNum = secondNum * -1;    
    return firstNum * calcPowRec(firstNum, secondNum-1);
}


/***************************************************
Function Name:powRec
Function Input: 
    firstNum - the number to multiply
    secondNum - the power
Function Operation: calls the function calcPowRec and 
prints the first number in the power of the second number
****************************************************/

void powRec(long int firstNum, long int secondNum){
    float sum = calcPowRec(firstNum, secondNum);
    if(secondNum < 0)
        sum = 1/sum;

    printf("The result is %f.\n", sum);
}

/***************************************************
Function Name:recIsDivisibleBy3
Function Input: 
    long long n - the number to check if is divisible by 3
    int toAdd - the next digit to check
Function Operation: checks recursivly if the input n is
                    divisible by 3 by checking the next
                    digit and determening using a two digit
                    number what should be the next one.
                    in the end for the number to be divisible 
                    the function must return 0
****************************************************/
long long removeThree(long long n);
long long recIsDivisibleBy3(long long n, int toAdd){
    //temp number to calculate the modulu for
    int num1;
    n = removeThree(n);
    if(toAdd == 0){
        toAdd = n%10;
        n = removeThree(n/10);
    }
	//recieve next digit
    num1 = n%10;
    
    if((num1 == 1 || num1 == -1) && (toAdd == 1 || toAdd == -1))
        toAdd = 2;
    else if((num1 == 1 || num1 == -1) && (toAdd == 2 || toAdd == -2))
        toAdd = 0;
    else if((num1 == 2 || num1 == -2) && (toAdd == 1 || toAdd == -1))
        toAdd = 0;
    else if((num1 == 2 || num1 == -2) && (toAdd == 2 || toAdd == -2)) 
        toAdd = 1;

        
    if(n/10 == 0)
        return toAdd;

    return recIsDivisibleBy3(n/10 , toAdd);

}

/***************************************************
Function Name:removeThree
Function Input: 
    long long n - a number to remove 3 from.
Function Operation: recives a number and returns the next non 3 digit
****************************************************/

long long removeThree(long long n){
    if(n%10 == 3 || n%10 == -3){
        return removeThree(n/10);
    }
        return n;
}

/***************************************************
Function Name:isDivisibleBy3
Function Input: 
    long long n - the number to check if is divisible by 3
Function Operation: calls the function recIsDivisibleBy3
                     and prints if n is divisible by 3
****************************************************/
void isDivisibleBy3(long long n){
    if (recIsDivisibleBy3(n, 0) == 0 )
        printf("The number %lld is divisible by 3.\n", n);
    else
        printf("The number %lld is not divisible by 3.\n", n);
}

/***************************************************
Function Name:isPalindromeIter
Function Input: 
    char str[] - the letter/number sequance
    int len - sequance length  
Function Operation: checks if the sequance is a palindrome
****************************************************/

void isPalindromeIter(char str[], int len){
    int isPolindrome = 0;
    for (int i = 0; i <= len/2; i++)
    {
        if(str[i] != str[len -1 -i]){
            isPolindrome = 1;
            break;
        }
    }
    if(isPolindrome == 0){
        printf("The reverse of %s is also %s.\n", str, str);
    }
    else
        printf("The reverse of %s is not %s.\n", str, str);
           
}

/***************************************************
Function Name:IsDividedBy3Iter
Function Input: 
    long long n - the number to check if is divisible by 3
Function Operation: prints if n is divisible by 3
****************************************************/
void IsDividedBy3Iter(long long n){
    long long finalN = n;
    int tempN = 0;
    do{
        while(finalN != 0){
            tempN = tempN + finalN%10;
            finalN = finalN/10;
        }
        finalN = tempN;
        tempN = 0;
    }while(finalN > 9 || finalN < -9);

    if(finalN == 0 || finalN == 3 || finalN == 3*2 || finalN == 3*3 ||
		finalN == -3 || finalN == -3*2 || finalN == -3*3)
        printf("The number %lld is divisible by 3.\n", n);
    else
        printf("The number %lld is not divisible by 3.\n", n);    
}


/***************************************************
Function Name:calcGcd
Function Input: 
    long int n1 - the first number
    long int n2 - the second number
Function Operation: calculates the greatest common denominator and 
                    prints the steps required to reach the solution
****************************************************/
long int calcGcd(long int n1, long int n2){
    if(n2 == 0){
        if(n1 < 0)
            n1 = n1*-1;        
        return n1;
    }

    else{
		//print steps
        if(n1/n2 != 0)
            printf("%ld*%ld+%ld=%ld(a=%ld,b=%ld)\n", n2,(n1/n2),(n1%n2),n1,n1,n2);
        return calcGcd(n2, n1%n2);
    }
}

/***************************************************
Function Name:gcd
Function Input: 
    long int n1 - the first number
    long int n2 - the second number
Function Operation: calls the function calcGcd
****************************************************/
void gcd(long int n1, long int n2){
    printf("GCD=%ld\n", calcGcd(n1,n2));
}

/***************************************************
Function Name:recCountDigit
Function Input: 
    long long n - the number to work on
    int d - the digit to check
    int counter - how many times the digit was spotted
Function output - returns counter
Function Operation: checks recursivly how many times
                    the digit d is contained in n
****************************************************/
int recCountDigit(long long n, int d, int counter){
    if(n == 0)
        return counter;    

    if(n%10 == d)
        return recCountDigit(n/10, d, counter+1);

    recCountDigit(n/10, d, counter);    
}

/***************************************************
Function Name:countDigit
Function Input: 
    long long n - the number to work on
    int d - the digit to check
Function Operation: calls the funcion recCountDigit
                    and prints the number of times
                    d is contained in n
****************************************************/
void countDigit(long long n, int d){
    if(n == 0 && d == 0)
        printf("%lld has 1 times 0.", n);
    printf("%lld has %d times %d.\n", n, recCountDigit(n, d, 0), d);
}