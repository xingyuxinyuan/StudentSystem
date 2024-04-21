#include "StudentSystemManager.h"

void welcome() {
	printf("**********************************\n");
	printf("*\t学生成绩管理系统\t*\n");
	printf("**********************************\n");
	printf("*\t请选择功能列表\t\t*\n");
	printf("**********************************\n");
	printf("*\t1.录入学生信息\t\t*\n");
	printf("*\t2.打印学生信息\t\t*\n");
	printf("*\t3.统计学生人数\t\t*\n");
	printf("*\t4.査找学生信息\t\t*\n");
	printf("*\t5.修改学生信息\t\t*\n");
	printf("*\t6.删除学生信息\t\t*\n");
	printf("*\t7.按成绩排序 \t\t*\n");
	printf("*\t8.退 出 系 统 \t\t*\n");
	printf("**********************************\n");
}

void inputStudent(Node* head) {
	Node* fresh = (Node*)malloc(sizeof(Node));
	assert(fresh); // 确保内存分配成功  
	fresh->next = NULL;

	bool validInput = false;
	while (!validInput) {
		printf("请输入学号（只能输入数字）: ");
		if (scanf("%d", &fresh->student.stuNum) == 1) {
			// 清除输入缓冲区中可能残留的非数字字符  
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			validInput = true; // 假设用户输入的是有效的学号  
		}
		else {// 输入无效，清除错误状态并继续循环  
			while (getchar() != '\n'); // 清除输入缓冲区直到换行符  
			clearerr(stdin);           // 清除标准输入的错误标志  
			printf("输入无效，请重新输入学号（只能输入数字）: \n");
		}
	}
	printf("请输入姓名 成绩: \n");
	scanf("%s%d", fresh->student.name, &fresh->student.score);
	Node* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	move->next = fresh;
	saveStudent(head);
	system("cls");
}
//打印成绩
void printStudent(Node* head)
{
	if (head == NULL || head->next == NULL)
	{
		printf("链表为空，没有学生数据可打印。\n");
		system("pause");
		system("cls");
		return;
	}
	Node* move = head->next;
	assert(move);
	while (move != NULL)
	{
		printf("学号：%d\t姓名：%s\t成绩:%d\n", move->student.stuNum, move->student.name, move->student.score);
		move = move->next;
	}
	
	system("cls");
}
//对链表计数
void countStudent(Node* head)
{
	int amount = 0;
	Node* move = head->next; // 从头节点开始遍历  
	assert(move);
	while (move != NULL) {
		amount++; // 无论节点是否包含有效数据，都递增计数器  
		move = move->next; // 移动到下一个节点  
	}

	printf("%d\n", amount);
	system("pause");
	system("cls");
}
//查找
void findStudent(Node* head)
{
	printf("输入学号：");
	int stuNum = 0;
	scanf("%d", &stuNum);
	Node* move = head->next;
	assert(move);
	while (move != NULL) {
		if (stuNum == move->student.score) {
			printf("学号：%d\t姓名：%s\t成绩:%d\n", move->student.stuNum, move->student.name, move->student.score);
			system("pause");
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("没找到数据");
	system("pause");
	system("cls");
}
//保存
void saveStudent(Node* head)
{
	FILE* file = fopen("./stu.info", "w");
	if (file == NULL) {
		printf("打开文件失败\n");
		return;
	}
	Node* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->student, sizeof(Student), 1, file) != 1)
		{
			printf("写入失败\n");
			return;
		}
		move = move->next;
	}
	fclose(file);
}

void loadStudent(Node* head)
{
	FILE* file = fopen("./stu.info", "r");
	if (!file) {
		printf("没有学生文件跳过读取\n");
		return;
	}
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	Node* move = head;
	while (fread(&fresh->student, sizeof(Student), 1, file) == 1)
	{
		move->next = fresh;
		move = fresh;
		fresh = (Node*)malloc(sizeof(Student));
		fresh->next = NULL;
	}
	free(fresh);
	printf("读取成功\n");
}

void updateStudent(Node* head)
{
	printf("请输入学号\n");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (NULL != NULL)
	{
		if (move->student.stuNum == stuNum)
		{
			printf("请输入要修改的信息\n");
			scanf("%s%d", move->student.name, &move->student.score);
			saveStudent(head);
			printf("修改成功\n");
			system("pause");
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("未找到学生信息\n");
	system("pause");
	system("cls");
}

void deleteStudent(Node* head)
{
	printf("请输入要删除的学生学号\n");
	int stuNum = 0;
	scanf_s("%d", &stuNum);
	Node* move = head;
	while (move->next != NULL)
	{
		if (move->next->student.stuNum == stuNum)
		{
			Node* temp = move->next;
			assert(temp);
			move->next = move->next->next;
			free(temp);
			temp = NULL;
			saveStudent(head);
			printf("删除成功");
		}
		else
		{
			printf("未找到学生\n");
		}
		move = move->next;
	}
	system("pause");
	system("cls");	
	return;
}

void sortStudent(Node* head)
{
	Node* save = NULL;
	Node* move = NULL;
	for (Node* turn = head->next; turn->next != NULL;turn=turn->next)
	{
		for (Node*move=head->next;move->next!=save;move=move->next)
		{
			if (move->student.score>move->next->next->student.score)
			{
				Student temp = move->student;
				move->student = move->next->student;
				move->next->student = temp;
			}
		}
		save = move;
	}
	printStudent(head);
}




int main() {
	//创建头节点
	Node* head = (Node*)malloc(sizeof(Node));
	assert(head);
	head->next = NULL;
	loadStudent(head);
	while (1)
	{
		welcome();
		printf("请输入序号\n");
		//
		char data = _getch();
		//不显示出来的_getch
		switch (data)
		{
		case'1':
			inputStudent(head);
			break;
		case'2'://打印
			printStudent(head);
			break;
		case'3'://统计学生函数
			countStudent(head);
			break;
		case'4'://查找
			findStudent(head);
			break;
		case'5':
			updateStudent(head);
			break;
		case'6':
			deleteStudent(head);
			break;
		case'7':
			sortStudent(head);
			break;
		case'8':
			exit(0);
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}

