#include "StudentSystemManager.h"

void welcome() {
	printf("**********************************\n");
	printf("*\tѧ���ɼ�����ϵͳ\t*\n");
	printf("**********************************\n");
	printf("*\t��ѡ�����б�\t\t*\n");
	printf("**********************************\n");
	printf("*\t1.¼��ѧ����Ϣ\t\t*\n");
	printf("*\t2.��ӡѧ����Ϣ\t\t*\n");
	printf("*\t3.ͳ��ѧ������\t\t*\n");
	printf("*\t4.����ѧ����Ϣ\t\t*\n");
	printf("*\t5.�޸�ѧ����Ϣ\t\t*\n");
	printf("*\t6.ɾ��ѧ����Ϣ\t\t*\n");
	printf("*\t7.���ɼ����� \t\t*\n");
	printf("*\t8.�� �� ϵ ͳ \t\t*\n");
	printf("**********************************\n");
}

void inputStudent(Node* head) {
	Node* fresh = (Node*)malloc(sizeof(Node));
	assert(fresh); // ȷ���ڴ����ɹ�  
	fresh->next = NULL;

	bool validInput = false;
	while (!validInput) {
		printf("������ѧ�ţ�ֻ���������֣�: ");
		if (scanf("%d", &fresh->student.stuNum) == 1) {
			// ������뻺�����п��ܲ����ķ������ַ�  
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			validInput = true; // �����û����������Ч��ѧ��  
		}
		else {// ������Ч���������״̬������ѭ��  
			while (getchar() != '\n'); // ������뻺����ֱ�����з�  
			clearerr(stdin);           // �����׼����Ĵ����־  
			printf("������Ч������������ѧ�ţ�ֻ���������֣�: \n");
		}
	}
	printf("���������� �ɼ�: \n");
	scanf("%s%d", fresh->student.name, &fresh->student.score);
	Node* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	move->next = fresh;
	saveStudent(head);
	system("cls");
}
//��ӡ�ɼ�
void printStudent(Node* head)
{
	if (head == NULL || head->next == NULL)
	{
		printf("����Ϊ�գ�û��ѧ�����ݿɴ�ӡ��\n");
		system("pause");
		system("cls");
		return;
	}
	Node* move = head->next;
	assert(move);
	while (move != NULL)
	{
		printf("ѧ�ţ�%d\t������%s\t�ɼ�:%d\n", move->student.stuNum, move->student.name, move->student.score);
		move = move->next;
	}
	
	system("cls");
}
//���������
void countStudent(Node* head)
{
	int amount = 0;
	Node* move = head->next; // ��ͷ�ڵ㿪ʼ����  
	assert(move);
	while (move != NULL) {
		amount++; // ���۽ڵ��Ƿ������Ч���ݣ�������������  
		move = move->next; // �ƶ�����һ���ڵ�  
	}

	printf("%d\n", amount);
	system("pause");
	system("cls");
}
//����
void findStudent(Node* head)
{
	printf("����ѧ�ţ�");
	int stuNum = 0;
	scanf("%d", &stuNum);
	Node* move = head->next;
	assert(move);
	while (move != NULL) {
		if (stuNum == move->student.score) {
			printf("ѧ�ţ�%d\t������%s\t�ɼ�:%d\n", move->student.stuNum, move->student.name, move->student.score);
			system("pause");
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("û�ҵ�����");
	system("pause");
	system("cls");
}
//����
void saveStudent(Node* head)
{
	FILE* file = fopen("./stu.info", "w");
	if (file == NULL) {
		printf("���ļ�ʧ��\n");
		return;
	}
	Node* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->student, sizeof(Student), 1, file) != 1)
		{
			printf("д��ʧ��\n");
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
		printf("û��ѧ���ļ�������ȡ\n");
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
	printf("��ȡ�ɹ�\n");
}

void updateStudent(Node* head)
{
	printf("������ѧ��\n");
	int stuNum;
	scanf("%d", &stuNum);
	Node* move = head->next;
	while (NULL != NULL)
	{
		if (move->student.stuNum == stuNum)
		{
			printf("������Ҫ�޸ĵ���Ϣ\n");
			scanf("%s%d", move->student.name, &move->student.score);
			saveStudent(head);
			printf("�޸ĳɹ�\n");
			system("pause");
			system("cls");
			return;
		}
		move = move->next;
	}
	printf("δ�ҵ�ѧ����Ϣ\n");
	system("pause");
	system("cls");
}

void deleteStudent(Node* head)
{
	printf("������Ҫɾ����ѧ��ѧ��\n");
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
			printf("ɾ���ɹ�");
		}
		else
		{
			printf("δ�ҵ�ѧ��\n");
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
	//����ͷ�ڵ�
	Node* head = (Node*)malloc(sizeof(Node));
	assert(head);
	head->next = NULL;
	loadStudent(head);
	while (1)
	{
		welcome();
		printf("���������\n");
		//
		char data = _getch();
		//����ʾ������_getch
		switch (data)
		{
		case'1':
			inputStudent(head);
			break;
		case'2'://��ӡ
			printStudent(head);
			break;
		case'3'://ͳ��ѧ������
			countStudent(head);
			break;
		case'4'://����
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

