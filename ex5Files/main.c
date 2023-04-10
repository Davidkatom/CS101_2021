/***********************
* David Shnaiderov
* 209198308
* 01
* EX05
***********************/

#include "ex5.h"

int main() {

	int numOfCourses = 0;	
	int* numOfCoursesPTR = &numOfCourses;
	//creates an array of courses
	course courseList[MAX_COURSES];
	//creates the first node in a linked list of students
	student* head = NULL;
	head = (student*)malloc(sizeof(student));
	if (head == NULL)
		quit(head);
	else
		head->next = NULL;
	//initialises the values foe the head student
	*head = resetStudent(*head);
	//starts the menu
	menu(courseList, numOfCoursesPTR, head, fullMenu);
	//loops until the user exits the program
	while (1)
		menu(courseList, numOfCoursesPTR, head, shortMenu);
	return 0;
}