#ifndef MAIN_C_EX5_H
#define MAIN_C_EX5_H

#define MAX_COURSES 5
#define MAX_COURSE_NAME 31
#define STUDENT_NAME 21

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "ex5.h"

typedef struct {
	char courseName[MAX_COURSE_NAME + 1];
	char courseNum[MAX_COURSES + 1];
}course;

typedef struct students {
	char studentName[STUDENT_NAME];
	int courseNum[MAX_COURSES];
	int grade[MAX_COURSES];
	struct students* next;
}student;
typedef enum { fullMenu = 1, shortMenu = 0 } printMenu;
typedef enum { error0 = 0, error1 = -1, error2 = -2, error3 = -3, works = 1 } errorNum;

void menu(course courseList[MAX_COURSES], int* numOfCoursesPTR, student* head, int menuType);
void quit(student* head);
student resetStudent(student current);
#endif