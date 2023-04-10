/***********************
* David Shnaiderov
* 209198308
* 01
* EX05
***********************/

#include "ex5.h"

#pragma region ManageCourses
#define TEMP_NAME "~"
#define MAX_GRADE 100
#define MAX_CHARACTES 200
#define INITIAL_VALUE -1

typedef enum { courseNum = 1, grades = 0 } mode;

/************************************************************************
* Function Name: resetStudent
* Input: student current (a student to copy)
* Output student (Initialised student)
* Function Operation: Resets a student to an initial value
************************************************************************/
student resetStudent(student current) {
	student dest;
	dest.next = current.next;
	strcpy(dest.studentName, TEMP_NAME);
	for (int i = 0; i < MAX_COURSES; i++) {
		dest.courseNum[i] = INITIAL_VALUE;
		dest.grade[i] = INITIAL_VALUE;
	}
	return dest;
}

/************************************************************************
* Function Name: updateCourse
* Input: course courseList[MAX_COURSES] (array of courses)
		 int* numOfCoursesPTR (pointer to the number of courses)
		 char courseNum[MAX_COURSES + 1] (the course's ID)
		 char courseName[MAX_COURSE_NAME + 1] (the course's name)
* Output Void
* Function Operation: adds the class
************************************************************************/
void updateCourse(course courseList[MAX_COURSES], int* numOfCoursesPTR,
	char courseNum[MAX_COURSES + 1], char courseName[MAX_COURSE_NAME + 1]) {
	//checks if the course already exists
	for (int i = 0; i < *numOfCoursesPTR; i++) {
		if (strcmp(courseList[i].courseNum, courseNum) == 0) {
			strcpy(courseList[i].courseName, courseName);
			printf("Class \"%s %s\" updated.\n", courseNum, courseName);
			return;
		}
	}
	if (*numOfCoursesPTR >= MAX_COURSES) {
		printf("Unfortunately, there is no room for more classes.\n");
		return;
	}
	//creates the course
	strcpy(courseList[*numOfCoursesPTR].courseNum, courseNum);
	strcpy(courseList[*numOfCoursesPTR].courseName, courseName);
	printf("Class \"%s %s\" added.\n", courseNum, courseName);
	*numOfCoursesPTR = *numOfCoursesPTR + 1;
}


/************************************************************************
* Function Name: updateCourse
* Input: char tempNum[200] (input which should represent the course's ID)
* output: int - (1/0 depending on the validity of the input)
* Function Operation: checks that the course ID matches the format
************************************************************************/
int checkCourseNum(char tempNum[MAX_CHARACTES]) {
	//check if the length is 5 digits
	if (strlen(tempNum) != MAX_COURSES) {
		return error0;
	}
	//check if input is only digits
	for (int i = 0; i < MAX_COURSES; i++) {
		if (isdigit(tempNum[i]) == 0) {
			return error0;
		}
	}
	return works;
}

/************************************************************************
* Function Name: updateCourse
* Input: char tempNum[200] (input which should represent the course's ID)
* output: int - (1/0 depending on the validity of the input)
* Function Operation: Checks if course num is number and course name is letters
************************************************************************/
int checkCourseInput(char tempNum[MAX_CHARACTES], char courseNum[MAX_COURSES + 1],
	char details[MAX_CHARACTES], char courseName[MAX_COURSE_NAME + 1]) {
	int count = 0;
	int flag = error0;
	//validates format
	if (strlen(details) > MAX_COURSE_NAME || checkCourseNum(tempNum) == 0)
		return error0;
	strcpy(courseNum, tempNum);
	courseNum[MAX_COURSES] = '\0';

	/*
	*makes sure the name is valid
	*and has at least one letter
	*/
	for (unsigned int i = 0; i < strlen(details) - 1; i++) {

		if (isalpha(details[i]) != 0) {
			flag++;
			courseName[i] = details[i];
		}
		else if (isdigit(details[i]) != 0 || details[i] == ' ') {
			courseName[i] = details[i];
		}
		else {
			return error0;
		}
	}
	//no letters in name
	if (flag == error0) {
		return error0;
	}
	courseName[strlen(details) - 1] = '\0';
	return works;
}

#pragma endregion

#pragma region manageStudents
/************************************************************************
* Function Name: checkCourseExists
* Input: char tempString[MAX_COURSES]  (input which should represent the course's ID)
		 course courseList[MAX_COURSES]  (array of courses)
* output: int - (1/0 depending on the validity of the input)
* Function Operation: check if the input course is registred in the system
************************************************************************/
int checkCourseExists(char tempString[MAX_COURSES], course courseList[MAX_COURSES]) {
	int courseExists = 0;
	for (int j = 0; j < MAX_COURSES; j++) {
		if (strcmp(tempString, courseList[j].courseNum) == 0) {
			courseExists = 1;
			break;
		}
	}
	return courseExists;
}

/************************************************************************
* Function Name: checkNameFormat
* Input: char tempString[MAX_COURSES]  (input which should represent the student's name)
* output: int - (1/0 depending on the validity of the input)
* Function Operation: check if the student's name is valid
************************************************************************/
int checkNameFormat(char tempString[MAX_CHARACTES]) {
	//checks if name longer than allowed length
	if (strlen(tempString) > STUDENT_NAME)
		return error0;
	//check if name valid
	for (int j = 0; tempString[j] != '\0'; j++) {
		if (isalpha(tempString[j]) == 0 && tempString[j] != ' ') {
			return error0;
		}
	}
	return works;
}
/************************************************************************
* Function Name: courseFormat
* Input: char char input[MAX_CHARACTES]  (input - course ID/Grade)
* output: void
* Function Operation: checks and fixes input formatting
************************************************************************/
void courseFormat(char input[MAX_CHARACTES], int num) {
	char tempString[MAX_CHARACTES] = { 0 };
	char* stringPTR = tempString;
	strcpy(tempString, input);
	//removes spaces from beginning 
	while (stringPTR[0] == ' ')
		stringPTR++;

	if (stringPTR[strlen(stringPTR) - 1] == '\n')
		stringPTR[strlen(stringPTR) - 1] = '\0';
	//works on course Number
	if (num == courseNum) {
		if (strlen(stringPTR) != MAX_COURSES)
			strcpy(stringPTR, "ERROR");

	}
	//works on grades
	else if (num == grades) {
		if (atoi(stringPTR) > MAX_GRADE)
			strcpy(stringPTR, "ERROR");
	}
	strcpy(input, stringPTR);
}

/************************************************************************
* Function Name: checkStudentParams
* Input: int counter (counts number of parameters)
		 char* parameters[MAX_CHARACTES] (pointer array for saving parameters)
		 course courseList[MAX_COURSES]  (array of courses)
* output: int - (1/0 depending on the validity of the input)
* Function Operation: check if the input course ID and Grade are digits and continues to assign
************************************************************************/
int checkStudentParams(int counter, char* parameters[MAX_CHARACTES], course courseList[MAX_COURSES]) {
	//checks if for every courseNum there is a grade
	if (counter % 2 != 0) {
		return error0;
	}
	char tempString[MAX_CHARACTES] = { 0 };

	/*
	*loops through 'parametrs' to check
	*each parameter's validity
	*/
	for (int i = 0; i < counter; i++) {
		strcpy(tempString, parameters[i]);
		//parameter is course number
		if (i % 2 == 0) {
			courseFormat(tempString, courseNum);
			if (checkCourseExists(tempString, courseList) == 0)
				return error0;
		}
		//parameter is grade
		else if (i % 2 == 1) {
			courseFormat(tempString, grades);
			for (int j = 0; tempString[j] != '\0'; j++) {
				if (isdigit(tempString[j]) == 0) {
					return error0;
				}
			}
		}
		strcpy(parameters[i], tempString);
	}
	parameters[counter] = "\0";

	return works;
}

/************************************************************************
* Function Name: getStudentName
* Input: char tempInput[MAX_CHARACTES] (recived input)
		 char studentName[MAX_CHARACTES] (students name)
		 char tempParameters[MAX_CHARACTES] (string to save the course ID and Grade)
* output: Void
* Function Operation: seperates student name form input
************************************************************************/
void getStudentName(char tempInput[MAX_CHARACTES], char studentName[MAX_CHARACTES],
	char tempParameters[MAX_CHARACTES]) {
	int counter = 0;
	char* nameToken = NULL;
	nameToken = strtok(tempInput, ":");
	int length;
	while (nameToken != NULL) {
		//more than one ':'
		if (counter == 2)
			return;
		//save student's name
		if (counter == 0) {
			length = strlen(nameToken);
			if (length > STUDENT_NAME)
				return;
			strcpy(studentName, nameToken);
		}
		//save the rest of the input
		else
			strcpy(tempParameters, nameToken);
		counter++;
		nameToken = strtok(NULL, ":");
	}
}

/************************************************************************
* Function Name: checkStudentInput
* Input: char tempInput[MAX_CHARACTES] (Input from user)
		 char* parameters[MAX_CHARACTES] (array to save parrameters to)
		 course courseList[MAX_COURSES] (array of courses)
		 char tempParameters[MAX_CHARACTES] (input string recived form function getStudentName
* output: int - (0 for error. else for counter)
* Function Operation: check if the input course ID and Grade are digits and continues to assign
************************************************************************/
int checkStudentInput(char tempInput[MAX_CHARACTES], char* parameters[MAX_CHARACTES],
	course courseList[MAX_COURSES], char tempParameters[MAX_CHARACTES]) {
	int counter = 0;
	char* token = NULL;
	token = strtok(tempParameters, ",;");
	//breaks input into formated parameters
	while (token != NULL) {
		parameters[counter] = token;
		counter++;
		token = strtok(NULL, ",;");
	}
	if (counter == 1)
		return error0;
	return checkStudentParams(counter - 1, parameters, courseList);

}

/************************************************************************
* Function Name: addStudent
* Input: student * head (first student in likned list)
		 char* parameters[MAX_CHARACTES] (array of grades and IDs)
		 course courseList[MAX_COURSES] (array of courses)
		 char studentName[STUDENT_NAME] (the student's name)
* output: Void
* Function Operation: adds a student to the linked list
************************************************************************/
void assignCourses(char* parameters[MAX_CHARACTES], course courseList[MAX_COURSES],
	student * current, char studentName[STUDENT_NAME]);
void addStudent(char* parameters[MAX_CHARACTES], student * head, course courseList[MAX_COURSES],
	char studentName[STUDENT_NAME]) {
	student* current = head;
	//finds the student if allready exists
	while (current->next != NULL) {
		if (strcmp(current->studentName, studentName) == 0) {
			break;
		}
		current = current->next;
	}
	//create new student node
	if (current->next == NULL) {
		current->next = (student*)malloc(sizeof(student));
		if (current->next == NULL)
			quit(head);
		else
			current->next->next = NULL;
		//reset a student to his initial valuse
		*(current->next) = resetStudent(*(current->next));
	}
	strcpy(current->studentName, studentName);
	assignCourses(parameters, courseList, current, studentName);
}

/************************************************************************
* Function Name: assignCourses
* Input: student * curretn (the student to assign)
		 char* parameters[MAX_CHARACTES] (array of grades and IDs)
		 course courseList[MAX_COURSES] (array of courses)
		 char studentName[STUDENT_NAME] (the student's name)
* output: Void
* Function Operation: assigns the students to courses
************************************************************************/
void assignCourses(char* parameters[MAX_CHARACTES], course courseList[MAX_COURSES],
	student * current, char studentName[STUDENT_NAME]) {
	int tempGrade, tempCourseNum, tempCourseIndex, counter = 0, updateCourse = 0;
	char tempInput[MAX_COURSES + 1] = { 0 };

	/*
	*loops thorugh paramets and asigns student a grade
	*and a course depnding on if the counter is even or odd.
	*/
	while (strcmp(parameters[counter], "\0") != 0) {
		strcpy(tempInput, parameters[counter]);
		//assigns course number
		if (counter % 2 == 0) {
			tempCourseNum = atoi(parameters[counter]);
			for (int i = 0; i < MAX_COURSES; i++) {
				//finds a free space in student's array of courses.
				if (current->courseNum[i] < 0 || current->courseNum[i] == atoi(parameters[counter])) {
					if (current->courseNum[i] == atoi(parameters[counter]))
						updateCourse = 1;
					tempCourseIndex = i;
					current->courseNum[i] = atoi(parameters[counter]);
					break;
				}
			}
		}
		else {
			//assigns grade
			tempGrade = atoi(parameters[counter]);
			current->grade[tempCourseIndex] = atoi(parameters[counter]);
			char courseName[MAX_COURSE_NAME] = { 0 };
			int courseIndex;

			/*
			*check if the student is registred and if he is
			*return his index.
			*assign course
			*/
			for (int i = 0; i <= MAX_COURSES; i++) {
				if (current->courseNum[tempCourseIndex] == atoi(courseList[i].courseNum)) {
					strcpy(courseName, courseList[i].courseName);
					courseIndex = i;
				}
			}
			if (updateCourse == 0) {
				printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n",
					studentName, courseList[courseIndex].courseNum, courseName, current->grade[tempCourseIndex]);
			}
			else {
				printf("Student \"%s\" updated on class \"%s %s\" with grade %d.\n",
					studentName, courseList[courseIndex].courseNum, courseName, current->grade[tempCourseIndex]);
			}
		}
		counter++;
	}
}


#pragma endregion

#pragma region RemoveStudents

/************************************************************************
* Function Name: findCourseName
* Input: course courseList[MAX_COURSES] (array of courses)
		 int input (course ID)
* output: int - (-1 for error. else for index)
* Function Operation: find the index of course in array 'courseList'
************************************************************************/
int findCourseName(course courseList[MAX_COURSES], int input) {
	for (int i = 0; i < MAX_COURSES; i++)
	{
		if (input == atoi(courseList[i].courseNum))
			return i;
	}
	return error1;
}

/************************************************************************
* Function Name: removeStudent
* Input: int courseIndex - course's index in courseList
		 student * current - the student to remove
		 char courseNum[] - course ID
		 course courseList[MAX_COURSES] (array of courses)
* output: Void
* Function Operation: find the index of course in array 'courseList'
************************************************************************/
void removeStudent(int courseIndex, student * current, char courseNum[], course courseList[MAX_COURSES]) {
	int index = findCourseName(courseList, atoi(courseNum));
	printf("Student \"%s\" removed from class \"%s %s\".\n",
		current->studentName, courseNum, courseList[index].courseName);
	current->courseNum[courseIndex] = -1;
	current->grade[courseIndex] = -1;
}

/************************************************************************
* Function Name: reciveRemoveInput
* Input: char* parameters[MAX_CHARACTES] (array to save parameters)
		 char tempParameters[MAX_CHARACTES] (user input without name)
* output: int (counter)
* Function Operation: tokenizes input to format course IDs
************************************************************************/
int reciveRemoveInput(char* parameters[MAX_CHARACTES], char tempParameters[MAX_CHARACTES]) {
	int counter = 0;
	char* token = NULL;
	token = strtok(tempParameters, ",");
	//creates tokens
	while (token != NULL) {
		parameters[counter] = token;
		counter++;
		token = strtok(NULL, ",");
	}
	return counter - 1;
}

/************************************************************************
* Function Name: checkIsRegistred
* Input: int courseNum (Course ID)
		 student * current (Student to check)
* output: (-2 for error, else for index)
* Function Operation: checks if the student is signed up to a course and returns his index
************************************************************************/
int checkIsRegistred(int courseNum, student * current) {
	int registered = error2;
	for (int i = 0; i < MAX_COURSES; i++) {
		if (current->courseNum[i] == courseNum) {
			registered = i;
		}
	}
	return registered;
}

/************************************************************************
* Function Name: RemoveInputFormat
* Input: char tempString[MAX_CHARACTES] (input from chracter)
		 char* parameters[MAX_CHARACTES] (array of course id's to remove)
		 student * current (the student to remove)
		 course courseList[MAX_COURSES] (array of courses)
		 int courseIndex[MAX_COURSES + 1] (array of indexes in student's courses)
		 int counter (number of courses to remove to pass on)
* output: (-2 if the student is not a member,-1 if the course doesn't exists. 1 to cointinue)
* Function Operation: checks if the student is signed up to a course and returns his index
************************************************************************/
int RemoveInputFormat(char tempString[MAX_CHARACTES], char* parameters[MAX_CHARACTES],
	student * current, course courseList[MAX_COURSES], int courseIndex[MAX_COURSES + 1], int counter) {

	/*
	*loops 'parameters' fixes it and checks
	*if the student is signed up to the course
	*/
	for (int i = 0; i < counter; i++)
	{
		strcpy(tempString, parameters[i]);
		//fix format
		courseFormat(tempString, courseNum);
		//checks if student signed up
		if (checkCourseExists(tempString, courseList) == 0)
			return error1;
		int registred = checkIsRegistred(atoi(tempString), current);
		if (registred == error2) {
			printf("Error: student is not a member of class \"%s %s\".\n",
				tempString, courseList[findCourseName(courseList, atoi(tempString))].courseName);
			return error2;
		}
		courseIndex[i] = registred;
		//copy formated string to the original array
		strcpy(parameters[i], tempString);
	}
	return works;
}

/************************************************************************
* Function Name: checkRemoveInput
* Input: char studentName[STUDENT_NAME] (student's name)
		 char* parameters[MAX_CHARACTES] (array of course id's to remove)
		 course courseList[MAX_COURSES] (array of courses)
		 student * head (the first student in the Linked List)
		 int counter (number of courses to remove to pass on)
* output: int (-1/-2/-3 for error, 1 to continue)
* Function Operation: checks formating, finds the student and removes him from the list
************************************************************************/
int checkRemoveInput(char studentName[STUDENT_NAME],
	char* parameters[MAX_CHARACTES], course courseList[MAX_COURSES], student * head, int counter) {
	student* current = head;
	int courseIndex[MAX_COURSES + 1];
	char tempString[MAX_CHARACTES] = { 0 };
	int existingStudent = error1;
	//finds the student to remove
	while (current->next != NULL) {
		if (strcmp(current->studentName, studentName) == 0) {
			existingStudent = works;
			break;
		}
		current = current->next;
	}
	if (existingStudent == error1) {
		return existingStudent;
	}
	//check course format
	int checkError = RemoveInputFormat(tempString, parameters, current, courseList, courseIndex, counter);
	if (checkError != 1)
		return checkError;
	
	//make sure the student is not removed from all courses
	int numOfCourses = 0;
	for (int i = 0; i < MAX_COURSES; i++) {
		if (current->courseNum[i] > 0) {
			numOfCourses++;
		}
	}
	if (counter == numOfCourses)
		return error3;

	//remove student
	for (int i = 0; i < counter; i++) {
		strcpy(tempString, parameters[i]);
		removeStudent(courseIndex[i], current, tempString, courseList);
	}
	return works;
}

#pragma endregion

/************************************************************************
* Function Name: printCourse
* Input: char input[200] (user Input)
		 course courseList[MAX_COURSES] (array of courses)
		 student * head (the first student in the Linked List)
* output: Void
* Function Operation: prints all students in specifed course in alphabetical order
************************************************************************/
void printCourse(student * head, course courseList[MAX_COURSES], char input[200]) {
	int hasPrinted = error0;
	student* current = head;
	int index = findCourseName(courseList, atoi(input));

	/*
	*loops all students and check if they are registered to this course
	*if they are, print their name and grade
	*/
	while (current->next != NULL) {
		int courseNum = checkIsRegistred(atoi(input), current);
		if (courseNum != error2) {
			if (hasPrinted == error0) {
				printf("Class \"%s %s\" students:\n", input, courseList[index].courseName);
				hasPrinted = works;
			}
			printf("%s, %d\n", current->studentName, current->grade[courseNum]);
		}
		current = current->next;
	}
	if (hasPrinted == error0)
		printf("Class \"%s %s\" has no students.\n", input, courseList[index].courseName);
}

/************************************************************************
* Function Name: copyStudent
* Input: student copy(the student to copy from)
* output: student information
* Function Operation: copies the student information to another student
************************************************************************/
student copyStudent(student copy, student * ptr) {
	student dest;
	dest.next = ptr->next;
	strcpy(dest.studentName, copy.studentName);
	for (int i = 0; i < MAX_COURSES; i++) {
		dest.courseNum[i] = copy.courseNum[i];
		dest.grade[i] = copy.grade[i];
	}
	return dest;
}


/************************************************************************
* Function Name: calcChoice
* Input: int sum (sum of all courses)
		 int minGrade (lowest grade in course)
		 int maxGrade (highest grade in course)
		 int count (number of students in course)
		 char choice (user's choice)
* output: int (result)
* Function Operation: returns a result depending on the user's input
************************************************************************/
int calcChoice(int sum, int minGrade, int maxGrade, int count, char choice) {
	switch (choice) {
		//average 
	case 'a':
		return sum / count;
		break;
	case 'b':
		return maxGrade;
		break;
	case 'c':
		return minGrade;
		break;
	case 'd':
		return sum;
		break;
	case 'e':
		return count;
		break;
	default:
		break;
	}
	return count;
}

/************************************************************************
* Function Name: checkRemoveInput
* Input: student * head (the first student in the Linked List)
		 int courseNum (course Id)
		 course courseList[MAX_COURSES] (array of courses)
		 int courseIndex (index of course in course list)
		 char choice (user's choice)
* output: int (-1 for error, else for result)
* Function Operation: calculates all the possible parameters to print
************************************************************************/
int calcDetalis(student * head, int courseNum, course courseList[MAX_COURSES], int courseIndex, char choice) {
	student* current = head;
	int sum = 0;
	int index;
	int minGrade = MAX_GRADE;
	int maxGrade = 0;
	int count = 0;

	/*
	*loops students and calculates:
	*sum, number of studnets in course, max grade and min grade
	*(average is calculated later)
	*/
	while (current->next != NULL) {
		index = checkIsRegistred(courseNum, current);
		if (index != error2) {
			sum = sum + current->grade[index];
			if (current->grade[index] > maxGrade)
				maxGrade = current->grade[index];
			if (current->grade[index] < minGrade)
				minGrade = current->grade[index];
			count++;
		}
		current = current->next;
	}
	//in case there are no students in course 
	if (count == 0) {
		printf("Class \"%s %s\" has no students.\n",
			courseList[courseIndex].courseNum, courseList[courseIndex].courseName);
		return error1;
	}
	return calcChoice(sum, minGrade, maxGrade, count, choice);
}
/************************************************************************
* Function Name: printDetails
* Input: student * head (the first student in the Linked List)
		 course courseList[MAX_COURSES] (array of courses)
		 int courseNum (course Id)
		 int* numOfCoursesPTR (pointer to the number of total courses)
		 char choice (user's choice)
* output: Void
* Function Operation: prints the details depending on the user's choice
************************************************************************/
void printDetails(student * head, course courseList[MAX_COURSES], int* numOfCoursesPTR, char choice) {
	int result;
	for (int i = 0; i < *numOfCoursesPTR; i++) {
		result = calcDetalis(head, atoi(courseList[i].courseNum), courseList, i, choice);
		if (result != -1)
			printf("%s %s, %d\n", courseList[i].courseNum, courseList[i].courseName, result);
	}
}

/************************************************************************
* Function Name: sortCourse
* Input: student * head (the first student in the Linked List)
		 course courseList[MAX_COURSES] (array of courses)
* output: Void
* Function Operation: sorts the students alphabeticly
************************************************************************/
void sortCourse(student * head, course courseList[MAX_COURSES]) {
	student temp;
	student* current = head;
	char input[MAX_CHARACTES] = { 0 };
	char space = 0;
	scanf("%c\n", &space);
	fgets(input, sizeof(input), stdin);
	//fix input forma
	courseFormat(input, courseNum);
	if (checkCourseExists(input, courseList) == 0) {
		printf("Error: invalid class number.\n");
		return;
	}
	//flag variable to check if there are no more changes to make
	int switched = 1;

	/*
	*loops students and switches between them in alphabetical order
	*/
	while (switched == 1) {
		switched = 0;
		while (current->next != NULL) {

			if ((strcmp(current->studentName, current->next->studentName) > 0)) {
				temp = copyStudent(*current, current);
				*current = copyStudent(*(current->next), current);
				(*current->next) = copyStudent(temp, current->next);

				switched = 1;
			}
			current = current->next;
		}
		current = head;
	}
	printCourse(head, courseList, input);
}


/************************************************************************
* Function Name: manageCourses
* Input: course courseList[MAX_COURSES] (array of courses)
		 int* numOfCoursesPTR (pointer to the number of courses)
* Output Void
* Function Operation: The Function which starts the course addition process
************************************************************************/
void manageCourses(course courseList[MAX_COURSES], int* numOfCoursesPTR) {	
	char details[MAX_CHARACTES] = { 0 };
	char* ptr = details;
	char tempNum[MAX_CHARACTES] = { 0 };
	char courseNum[MAX_COURSES + 1] = { 0 };
	char courseName[MAX_COURSE_NAME + 1] = { 0 };
	scanf(" %s", tempNum);
	fgets(details, sizeof(details), stdin);

	//remove spaces from the beginning
	while (ptr[0] == ' ')
		ptr++;

	/*
	*check if the input is valid
	*and continue the process of adding a course
	*/
	if (checkCourseInput(tempNum, courseNum, ptr, courseName) == 1)
		updateCourse(courseList, numOfCoursesPTR, courseNum, courseName);
	else
		printf("Error: invalid class number or name.\n");


}

/************************************************************************
* Function Name: manageStudents
* Input: course courseList[MAX_COURSES] (array of courses)
		 student* head (the first student node in the linked list)
* Output Void
* Function Operation: The Function which starts
						the student registration process
************************************************************************/
void manageStudents(course courseList[MAX_COURSES], student * head) {
	char* parameters[MAX_CHARACTES] = { 0 };
	char tempInput[MAX_CHARACTES] = { 0 };
	char tempParameters[MAX_CHARACTES] = { 0 };
	char studentName[MAX_CHARACTES] = { 0 };
	int temp = 0;
	scanf("%d", &temp);
	fgets(tempInput, sizeof(tempInput), stdin);
	getStudentName(tempInput, studentName, tempParameters);
	if (checkNameFormat(studentName) == 0) {
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	if (checkStudentInput(tempInput, parameters, courseList, tempParameters) == 0) {
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	addStudent(parameters, head, courseList, studentName);
}

/************************************************************************
* Function Name: manageRemoveStudents
* Input: course courseList[MAX_COURSES] (array of courses)
		 student* head (the first student node in the linked list)
* Output Void
* Function Operation: The Function which starts
						the student removal process
************************************************************************/
void manageRemoveStudents(course courseList[MAX_COURSES], student * head) {
	char input[MAX_CHARACTES] = { 0 };
	char* parameters[MAX_CHARACTES] = { 0 };
	char tempParameters[MAX_CHARACTES] = { 0 };
	char studentName[MAX_CHARACTES] = { 0 };
	int temp = 0;
	//remove \n
	scanf("%d", &temp);
	fgets(input, sizeof(input), stdin);

	//separate student name from input
	getStudentName(input, studentName, tempParameters);
	int counter = reciveRemoveInput(parameters, tempParameters);
	//check if the name had been empty
	if (counter == 0) {
		printf("Error: invalid name or class number.\n");
		return;
	}

	//check input validity and proceed to remove student 
	int checkError = checkRemoveInput(studentName, parameters, courseList, head, counter);
	switch (checkError) {
	case error1:
		printf("Error: invalid name or class number.\n");
		return;
	case error3:
		printf("Error: student cannot be removed from all classes.\n");
		return;
	default:
		break;
	}
}

/************************************************************************
* Function Name: PrintAllCourses
* Input: course courseList[MAX_COURSES] (array of courses)
		 student* head (the first student node in the linked list)
		 int* numOfCoursesPTR (pointer to the number of courses)
* Output Void
* Function Operation: Starts the process of printing all
						courses and the students signed up to them
************************************************************************/
void PrintAllCourses(student * head, course courseList[MAX_COURSES], int* numOfCoursesPTR) {
	if (*numOfCoursesPTR == 0) {
		printf("Error: there are no classes.\n");
		return;
	}
	printf("Please select the aggregation method:\n"
		"	a. Average Grade.\n"
		"	b. Maximal Grade.\n"
		"	c. Minimal Grade.\n"
		"	d. Sum.\n"
		"	e. Count.\n"
		"	0. Return to the main menu.\n");
	char choice;
	scanf(" %c", &choice);
	if (choice == '0')
		return;	
	printDetails(head, courseList, numOfCoursesPTR, choice);
}

/************************************************************************
* Function Name: quit
* Input: student * head (first student in linked list)
* Output Void
* Function Operation: frees all allocated memory and exits the program
************************************************************************/
void quit(student * head) {
	student* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	exit(0);
}

/************************************************************************
* Function Name: menu
* Input: course courseList[MAX_COURSES] (array of courses)
		 int* numOfCoursesPTR (pointer to the number of courses)
		 student* head (the first student node in the linked list)
		 int menuType ()
* Output Void
* Function Operation: prints the menu
************************************************************************/
void menu(course courseList[MAX_COURSES], int* numOfCoursesPTR, student * head, int menuType) {
	if (menuType == fullMenu) {
		printf("Please select an operation:\n"
			"	0. Exit.\n"
			"	1. Insert or update a class.\n"
			"	2. Insert or update a student.\n"
			"	3. Remove a student from classes.\n"
			"	4. Print a class.\n"
			"	5. Print all classes with their computed scores.\n"
			"	6. Print the menu.\n");
	}
	else
		printf("Select the next operation (insert 6 for the entire menu):\n");

	char choice;
	scanf(" %c", &choice);
	switch (choice) {
	case '0':
		quit(head);
		break;
	case '1':
		manageCourses(courseList, numOfCoursesPTR);
		break;
	case '2':
		manageStudents(courseList, head);
		break;
	case '3':
		manageRemoveStudents(courseList, head);
		break;
	case '4':
		sortCourse(head, courseList);
		break;
	case '5':
		PrintAllCourses(head, courseList, numOfCoursesPTR);
		break;
	case '6':
		menu(courseList, numOfCoursesPTR, head, 1);
		break;
	default:
		printf("Error: unrecognized operation.\n");
		break;
	}
}
