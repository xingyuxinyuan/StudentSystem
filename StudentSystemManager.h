#pragma once
#include"common.h"
//≤‚ ‘
typedef struct _Student
{
	int stuNum;//—ß∫≈
	char name[20];//–’√˚
	int score;//≥…º®
}Student;

typedef struct _Node
{
	_Student student;
	struct _Node *next;
}Node;

void welcome(Node* head);

void inputStudent(Node* head);

void printStudent(Node* head);

void countStudent(Node* head);

void findStudent(Node* head);

void saveStudent(Node* head);

void loadStudent(Node* head);

void updateStudent(Node* head);

void deleteStudent(Node* head);

void sortStudent(Node* head);