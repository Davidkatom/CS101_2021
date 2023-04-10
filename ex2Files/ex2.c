#include <stdio.h>

/***************************************************
Function Name:rhombus
Function Operation: recives a number from which the
function builds a rhombus with this many sides.
the long diagonal is built from "*" while the cross section is "+". 
The sides are built from "/" and "\" respectivly
****************************************************/
void rhombus(){
    int length;
    printf("Enter the sides length:\n");
    scanf("%d", &length);
    for(int i = 0; i < length*2 + 1; i++){
        for(int j = 0; j < length*2; j++){
            if(j == length){
                if(i == length)
                    printf("+");
                else        
                printf("*");
            }
            //the upper side    
            if(i < length){
                if(j == length - i -1)
                    printf("/");
            

                else if(j == length + i){
                    printf("\\");
                    break;
                }
            
                else
                    printf(" ");    
                           
            }
            //the middle
            else if(i == length){
                if(j == 0 || j == length*2-1)
                    printf("|");               

                else
                    printf(" ");
            }
            //the lower side
            else if(i >length){                   
                if(j == i - length - 1)
                    printf("\\");
            

                else if(j == length*3 - i){
                    printf("/");
                    break;
                }
            
                else
                    printf(" ");            
            }
        }
        printf("\n");
    }
}
/***************************************************
Function Name:toDecimal
Function Input: the base of the number
Function Operation: Recives a number in a reversed order and prints 
the number in base 10 in the correct order
****************************************************/

void toDecimal(int baseInput){
    //recived char from buffer
    char temp; 
    //in base 10
    int tempInt = 0;
    //final output
    int finalNum = 0; 
    //index multiplied by base
    int multiply = 1;
	//to print final answer
    int toCalculate = 1;
    printf("Enter a reversed number in base %d:\n", baseInput);    
    scanf(" %c", &temp);
    //convert numbers to base 10
    while(temp != '\n'){
		//converts the chars to base 20 numbers
        if(temp <= '9' && temp >= '0')
            tempInt = temp - '0';
        else if(temp <= 'J' && temp >= 'A')
            tempInt = temp - 'A' + 10;
        else if(temp <= 'j' && temp >= 'a')
            tempInt = temp - 'a' + 10;
        else{   
            toCalculate = 0;
            printf("Error! %c is not a valid digit in base %d\n", temp, baseInput);            
        }

        if(tempInt >= baseInput && baseInput != 20){
            toCalculate = 0;
            printf("Error! %c is not a valid digit in base %d\n", temp, baseInput);   
        }
        else{            
            finalNum = finalNum + tempInt*multiply;
            multiply *= baseInput;
        }
        scanf("%c", &temp);
    }
    if(toCalculate == 1)
        printf("%d\n", finalNum);
    
}

/***************************************************
Function Name:powerOfTwo
Function Operation: The user enters a number and 
the function prints yes if the number is a power of 2
****************************************************/
void powerOfTwo(){
    int num;
    printf("Enter a number:\n");
    scanf(" %d", &num);
    int compNum = num - 1;

    //printf("\n %d \n", num-notNum);
    if((num&compNum) == 0)
        printf("%d is a power of 2\n", num);
    else
        printf("%d is not a power of 2\n", num);
    
}

/***************************************************
Function Name:differentBits
Function Operation: prompts the user to enter two numbers and then
prints the number of different bits between them 
in binary representation
****************************************************/
void differentBits(){
    unsigned int num1;
    unsigned int num2;
    int counter = 0;
    printf("Enter two numbers:\n");
    scanf("%d",&num1);
    scanf("%d",&num2);

    while(num1 != 0 || num2 != 0){
        if(num1%2 != num2%2)
            counter++;
        num1 = num1>>1;
        num2 = num2>>1;    
    }
    printf("There are %d different bits\n", counter);

}

/***************************************************
Function Name:addNums
Function Operation: prompts the user
to enter two numbers and prints their sum
****************************************************/
void addNums(){
    int num1;
    int num2;

    printf("Enter two numbers:\n");
    scanf("%d",&num1);
    scanf("%d",&num2);

    while(num2 != 0){
        if(num2 > 0){
            num1++;
            num2--;
        }
        else
        {
            num1--;
            num2++;
        }
    }
    printf("%d\n", num1);
}
/***************************************************
Function Name:multiply
Function Operation: prompts the user to enter
two numbers and prints their product
****************************************************/
void multiply(){
    int num1;
    int num2;
    int total = 0;
    printf("Enter two numbers:\n");
    scanf("%d",&num1);
    scanf("%d",&num2);
    
    while(num2 != 0){
        if(num2 > 0){
            total = total + num1;
            num2--;
        }
        else
        {
            total = total - num1;
            num2++;
        }
    }
    printf("%d\n",total);    
}

/***********************************************************
Function Name:printMenu
Creates the menu and prompts the user to choose an option.
Calls the respective function for each option
************************************************************/
void printMenu(){
    //base recived for case 3
    int toBase = 0; 
    printf("Choose an option:\n1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n4. Pow2\n5. Different bits\n6. Add\n7. Multiply\n0. Exit\n");
    char choice; //the option the user will choose 
    scanf(" %c",&choice);
    switch (choice){
        case '0': //exit
            return;
        case '1': //rhombus
            rhombus();
            break;
        case '2': //to base 20
            toDecimal(20);
            break;    
        case '3':            
            printf("Enter a base (2-10):\n");
            scanf("%d", &toBase);
            toDecimal(toBase);
            break;
        case '4':
            powerOfTwo();        
            break;
        case '5':
            differentBits();
            break;
        case '6':
            addNums();
            break;
        case '7':
            multiply();
            break;
        default:
            printf("Wrong Option!\n");            
            break;
    }
    printMenu();
}

int main(){
    printMenu();
}

