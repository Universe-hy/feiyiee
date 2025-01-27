#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#pragma warning(disable:4013)
#pragma warning(disable:4717)
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define NEW_CLASS (struct Class*)malloc(sizeof(struct Class))
#define NEW_STUDENT (struct Student*)malloc(sizeof(struct Student))

//��¼����
void login();
//ѧ����¼
void studentLogin();
//��ʦ��¼
void teacherLogin();
//ѧ���˵�����
void studentMenu();
//��ʦ�˵�����
void teacherMenu();
//ѧ��ѡ�ν���
void  classChoose();
//ѡ�����ݴ���
int clooseService(char classIDs[40]);

void DataCollect();
void DataStorage();
int studentCheck(int id,char password[]);
int teacherCheck(int id,char password[]);

void addClass();
void deleteClass();
void modifyClass();
void sortClass();
void showClass();
//��ѯ�γ�
void queryClass();
void showStudentClass();
void showClassByChara(int fig);

void addStudent();
void deleteStudent();
void resetStudentPassword();
void modifyStudentPassword();
void deleteStudentClassById(int id);
void showStudent(); 

struct Class* findClassByID(int id);
struct Student* findStudentByID(int id);

//���ַ���ת��Ϊ���������ת��ʧ�����-1
int strToInt(char* str);
void delay();

struct Class
{
	int id; //�γ̱��
	char name[50]; //�γ�����
	char chara[10]; //�γ�����
	int score; //�γ�ѧ��
	char teacherName[20]; //��ʦ
	int num; //ѡ������
	struct Class* next;//��һ�ڵ�
} *classHead,*classRear;

struct Student
{
	char name[15]; //ѧ������
	int id; //ѧ��ѧ��
	int classes[3]; //��ѡ�γ�
	char password[20]; //ѧ������
	struct Student* next;//��һ�ڵ�
} *studentHead,*studentRear;

struct Student* studentNow=NULL;//��¼��¼��ѧ��

struct Teacher
{
	char name[15]; //��ʦ����
	int id; //��ʦ���
	char password[20]; //��ʦ����
	struct Teacher* next;
} *teacherHead;

static int  classCount = 0;
static int  studentCount = 0;

//��¼����
void login()
{
	int choice=0; char buffer;
	SetConsoleTitleA("��¼");
	printf("|------------------------------------------------------------|\n");
	printf("|----------��ӭʹ���ϲ����մ�ѧ�Ƽ�ѧԺѡ��ϵͳ(C����)-------|\n");
	printf("|                                                            |\n");
	printf("|--------------------��ѡ��������--------------------------|\n");
	printf("|                                                            |\n");
	printf("|------------------------1.ѧ��------------------------------|\n");
	printf("|                                                            |\n");
	printf("|------------------------2.��ʦ------------------------------|\n");                                            
	printf("|                                                            |\n");
	printf("|------------------------3.�˳�------------------------------|\n");
	printf("|                                                            |\n");
	printf("|-------------------��������ȷ��ż���-----------------------|\n");

	buffer = _getch();
	if ('1' <= buffer && buffer <= '3')
		choice = buffer - '0';

	while (choice == 0) {
		printf("��������ȷ���!!\n");
		buffer = _getch();
		if ('1' <= buffer && buffer <= '3') 
			choice = buffer - '0';
	}
	system("cls");

	switch (choice)
	{
	case 1:	studentLogin(); break;
	case 2:	teacherLogin(); break;
	case 3:	DataStorage();
			printf("�ɹ��˳�\n");
			exit(0);
	default:
			printf("�������\n");
			login(); break;
	}
	system("cls");
	login();
}

//ѧ����¼
void studentLogin()
{
	int id, loopNum = 0;
	char buffer[20];
	char password[20];
	SetConsoleTitleA("ѧ����¼");

	while (1) {
		printf("|-----------------����������ѧ��(-1�˳�)-----------------------|\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);

		while (id == -1) {
			printf("|-----------------��������ȷ��ѧ��(-1�˳�)---------------------|\n");
			scanf("%s", buffer);
			if (buffer[0] == '-' && buffer[1] == '1')
				return;
			id = strToInt(buffer);
		}
	
		printf("|-------------------����������(-1�˳�)---------------------------|\n");
		scanf("%s", password);
		if (password[0] == '-' && password[1] == '1')
			return;
		system("cls");

		if (studentCheck(id, password)) {
			printf("��¼�ɹ�\n");
			studentMenu();
		}

		loopNum++;
		if (loopNum > 2) {
			delay();
			studentLogin();
		}
		printf("�Բ��������˺Ż������������������\n");		
	};
}

//��ʦ��¼
void teacherLogin()
{
	int id, loopNum = 0;
	char buffer[20];
	char password[20];
	SetConsoleTitleA("��ʦ��¼");

	while (1) {
		printf("|---------------- ���������Ľ�ʦ�˺�(-1�˳�)-------------------|\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);

		while (id == -1) {
			
			printf("|-------------- ��������ȷ�Ľ�ʦ�˺�(-1�˳�)-----------------|\n");
			scanf("%s", buffer);
			if (buffer[0] == '-' && buffer[1] == '1')
				return;
			id = strToInt(buffer);
		}

		printf("|------------------��������������(-1�˳�)----------------------|\n");
		scanf("%s", password);
		if (password[0] == '-' && password[1] == '1')
			return;
		system("cls");

		if (teacherCheck(id, password)) {
			printf("��¼�ɹ�\n");
			teacherMenu();
		}

		loopNum++;
		if (loopNum > 2) {
			delay();
			teacherLogin();
		}
		printf("�Բ��������˺Ż������������������\n");
	};
}

//ѧ���˵�����
void studentMenu()
{ 
	
	int choice=0; char buffer;
	SetConsoleTitleA("ѧ��ѡ�ν���");
	printf("|--------------------------------------------------------------|\n");
	printf("|------------------��ӭ����ѧ��ѡ�ν���------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------1.ѡ�β�������----------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------2.�鿴��ѡ�γ�----------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------3.��ѯ�γ�--------------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------4.�޸�����--------------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------5.�˳�ѡ�ν���----------------------------|\n");
	printf("|                                                              |\n");
	printf("|-----------------���������Լ�������-------------------------|\n");

	buffer = _getch();
	if ('1' <= buffer && buffer <= '5')
		choice = buffer - '0';

	while (choice == 0) {
		printf("��������ȷ���!!\n");
		buffer = _getch();
		if ('1' <= buffer && buffer <= '5')
			choice = buffer - '0';
	}
	system("cls");
	switch (choice)
	{
	case 1:classChoose();           break;
	case 2:showClassByChara(1);     
		   showStudentClass();      break;
	case 3:queryClass();            break;
	case 4:modifyStudentPassword(); break;
	case 5:login();                 break;
	}	
	system("pause");
	system("cls");
	studentMenu();
}

//��ʦ�˵�����
void teacherMenu()
{
	int choice=-1; char buffer;
	SetConsoleTitleA("��ʦѡ�ι������");
	printf("\t\t|------------------------------------------------------------------|\n");
	printf("\t\t|--------------------��ӭ������ʦѡ�ι������----------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------1.��ӿγ���Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");	
	printf("\t\t|------------------------2.ɾ���γ���Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------3.�޸Ŀγ���Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------4.�鿴�γ���Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------5.�γ���Ϣ����----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------6.���ѧ����Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------7.ɾ��ѧ����Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------8.����ѧ������----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------9.�鿴ѧ����Ϣ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------0.�˳�ѡ��ϵͳ----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|---------------------�������Ӧ��Ž��в�����---------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------------------------------------------------|\n");

	buffer = _getch();
	if ('0' <= buffer && buffer <= '9')
		choice = buffer - '0';

	while (choice == -1) {
		printf("��������ȷ���!!\n");
		buffer = _getch();
		if ('0' <= buffer && buffer <= '9')
			choice = buffer - '0';
	}
	system("cls");
	switch (choice)
	{
	case 1:addClass();             break;
	case 2:deleteClass();          break;
	case 3:modifyClass();          break;
	case 4:showClass();	           break;
	case 5:sortClass();            break;
	case 6:addStudent();           break;
	case 7:deleteStudent();        break;
	case 8:resetStudentPassword(); break;
	case 9:showStudent();          break;
	case 0:login();                break;
	}
	system("pause");
	system("cls");
	teacherMenu();
}

//ѧ��ѡ��
void classChoose()
{
	char ids[40];
	struct Class* p = classHead;
	SetConsoleTitleA("ѡ������");
	printf("|-------------------------2023-2024ѧ��---------------------------------|\n");
	printf("|                                                                       |\n");
	printf("|------------------------��ӭ����ѧ��ѡ������---------------------------|\n");
	printf("|                                                                       |\n");
	printf("|-----------------------------------------------------------------------|\n");
	showClassByChara(0);
	printf("|-----------------------------------------------------------------------|\n");
	printf("|--��ѡ�γ�-------------------------------------------------------------|\n");
	showStudentClass();
	printf("���������ѡ�α�ţ��ÿո�������س�����,����-1ֹͣѡ��)\n");
	getchar();//��ջ�����
	while (1) {
		fgets(ids, 35, stdin);
		if (ids[0] == '-' && ids[1] == '1')
			return;
		switch (clooseService(ids))
		{
		case 0: printf("ѡ�γɹ�\n"); DataStorage();
		case 1: return;
		case 2: printf("��������ȷ���ַ�\n"); break;
		case 3: printf("����Ŀγ̱���ظ�\n"); break;
		case 4: printf("�γ̱�Ų���ȷ\n"); break;
		case 5: printf("���ѡ��3�ſγ�\n"); break;
		}
	}
	
}

//ѡ�����ݴ���
int clooseService(char classIDs[40]) {
	int classes[4] = { 0 }; int i = 0, num = 0, classNum = 0;

	//�˳�
	if (classIDs[0] == '-' && classIDs[1] == '1')
		return 1;

	//�ַ�������ת��Ϊ���� ������У������
	while (classIDs[i]&& classIDs[i]!='\n')
	{
		if ('0' <= classIDs[i] && classIDs[i] <= '9') {
			if (num > 2)return 5;//ѡ�ογ���������3
			classes[num] *= 10;
			classes[num] += classIDs[i] - '0';
		}
		else if (classIDs[i] == ' ')
		{
			if (classes[num])
				num++;
		}
		else return 2;//��������ַ�
		i++;
	}

	//�γ̱���Ƿ��ظ�
	if (classes[0] == classes[1] || (classes[1] == classes[2] && classes[1]) || classes[0] == classes[2])
		return 3;//�ظ�
	for (int i = 0; i < 3; i++) {		
		for (int k = 0; k < 3; k++) {
			if (classes[i] == studentNow->classes[k]&& classes[i])
				return 3;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (classes[i])
			classNum++;
	}
	for (int i = 0; i < 3; i++) {
		if (studentNow->classes[i])
			classNum++;
	}
	if (classNum > 3)
		return 5;


	//У��γ̱��
	struct Class* class[4];
	for (i = 0; classes[i]; i++) {
		class[i] = findClassByID(classes[i]);
		if (  !class[i] || strcmp("ѡ��", class[i]->chara))return 4;
		//�γ̱�Ŵ���
	}

	//�γ�������1
	for (i = 0; classes[i]; i++) {
		class[i]->num++;
	}

	//ѡ����Ϣ¼��
	for (int i = 0; i < 3; i++) {
		if(classes[i])
		for (int k = 0; k < 3; k++) {
			if (studentNow->classes[k] == 0) {
				studentNow->classes[k] = classes[i];
				classes[i] = 0;
			}
		}
	}
	return 0;
}

//��ѧ����Ϣ�Ϳγ���Ϣ���ļ�����ȡ���ֵ���Ӧ������ṹ
void DataCollect() {
	
	FILE* classFp, * studentFp;
	struct Class* classP = NEW_CLASS; 
	classHead = classP;

	struct Student* studentP = NEW_STUDENT;
	studentHead =studentP;

	classFp = fopen("classData.txt", "r");
	if (classFp == NULL)
	{
		classHead = NULL;
		classRear = NULL;
	}else
	{
		while (fread(classP, sizeof(struct Class), 1, classFp))
		{
			classRear = classP;
			classP->next = NEW_CLASS;
			classP = classP->next;
			classCount++;
		}
		if (classRear != NULL)
			classRear->next = NULL;
		else {
			printf("classData.txt�ļ�����ʧЧ\n");
			classHead = NULL;
			classCount = 0;
		}
		free(classP);
		fclose(classFp);
	}

	studentFp = fopen("studentData.txt", "r");
	if (studentFp == NULL)
	{
		studentHead = NULL;
		studentRear = NULL;
		return;
	}
	while (fread(studentP, sizeof(struct Student), 1, studentFp))
	{
		studentRear = studentP;
		studentP->next = NEW_STUDENT;
		studentP = studentP->next;
		studentCount++;
	}
	if (studentRear != NULL)
		studentRear->next = NULL;
	else {
		printf("studentData.txt�ļ�����ʧЧ\n");
		studentHead = NULL;
		studentCount = 0;
	}
	free(studentP);
	fclose(studentFp);
}

//��ѧ����Ϣ�Ϳγ���Ϣ������ṹ�������ļ�
void DataStorage()
{
	FILE* classFp, * studentFp;
	struct Class* classP = classHead; 
	struct Student* studentP = studentHead;

	//printf("���ڱ���γ���Ϣ����\n");
	classFp = fopen("classData.txt", "w");	
	while (classP != NULL)
	{
		fwrite(classP, sizeof(struct Class), 1, classFp); //�����ļ�
		classP = classP->next;
	}
	fclose(classFp);

	//printf("���ڱ���ѧ����Ϣ����\n");
	studentFp = fopen("studentData.txt", "w");
	while (studentP != NULL)
	{
		fwrite(studentP, sizeof(struct Student), 1, studentFp); 
		studentP = studentP->next;
	}
	fclose(studentFp);
}

//��֤ѧ������
int studentCheck(int id, char password[])
{
	struct Student* p = findStudentByID(id);
	if (p != NULL && !strcmp(password, p->password))
	{
		studentNow = p;
		return 1;
	}
	return 0;
}
//��֤��ʦ����
int teacherCheck(int id, char password[])
{
	struct Teacher teacher = { "����",111,"666",teacherHead };
	teacherHead = &teacher;
	struct Teacher* p = teacherHead;
	while (p != NULL)
	{
		if (id == p->id && (!(strcmp(password, p->password))))
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//��ӿγ�
void addClass() {
	struct Class* p= NEW_CLASS;
	char buffer[20];
	//�γ���Ϣ¼��

	printf("������γ�����(����-1�˳�):\n");
	scanf("%s", p->name);
	if (p->name[0] == '-' && p->name[1] == '1')
		return;

	printf("������γ�����(ѡ��or����,����-1�˳�):\n");
	scanf("%s", p->chara);
	if (p->chara[0] == '-' && p->chara[1] == '1')
		return;
	while (strcmp(p->chara, "ѡ��") && strcmp(p->chara, "����")) {
		printf("��������ȷ�Ŀγ�����(ѡ��or����,����-1�˳�):\n");
		scanf("%s", p->chara);
		if (p->chara[0] == '-' && p->chara[1] == '1')
			return;
	}

	printf("������γ�ѧ��(����-1�˳�):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	p->score = strToInt(buffer);
	while (p->score == -1) {
		printf("��������ȷ�Ŀγ�ѧ��(����-1�˳�):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		p->score = strToInt(buffer);
	}
	
	printf("�������ѧ��ʦ����(����-1�˳�)\n");
	scanf("%s", p->teacherName);
	if (p->teacherName[0] == '-' && p->teacherName[1] == '1')
		return;

	if(strcmp(p->chara,"����"))
		p->num = 0;
	else {
		p->num = studentCount;
	}
	p->next = NULL;

	if (classHead == NULL) {
		p->id = 1;
		classHead = p;
	}
	else {
		int id = 1;
		while (findClassByID(id) != NULL)id++;
		p->id = id;
		classRear->next = p;
	}
	classRear = p;
	classCount++;
	printf("¼��ɹ�����");

	//��������
	DataStorage();
};

//����id ɾ���γ�
void deleteClass() {
	struct Class* current =  NULL;
	struct Class* previous = classHead;
	int id; char buffer[20];
	showClass();

	printf("��������Ҫɾ���Ŀγ̱��(����-1�˳�):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ((current = findClassByID(id)) == NULL) {
		printf("��������ȷ�Ŀγ̱��(����-1�˳�):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}

	//ѧ��ѡ����Ϣ����
	if(!strcmp(current->chara,"ѡ��"))
	   deleteStudentClassById(id);

	if (current == classHead)
		classHead = classHead->next;
	else while (previous->next != current)
		previous = previous->next;
	previous->next = current->next;

	printf("ɾ���ɹ�");
	//��������
	DataStorage();
	classCount--;
}

// �޸Ŀγ���Ϣ
void modifyClass()
{
	int id; char newName[20]; char newChara[20]; int newScore; char newTeacherName[20];
	char buffer[20];
	struct Class* p = classHead;
	showClass();
	printf("��������Ҫ�޸ĵĿγ̱��(����-1�˳�):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ((p = findClassByID(id))==NULL ) {
		printf("��������ȷ�Ŀγ̱��(����-1�˳�):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}
	
	printf("�������µĿγ�����(����-1�˳�)��\n");
	scanf("%s", newName);
	if (newName[0] == '-' && newName[1] == '1')
		return;
	
	printf("�������µĿγ�����(ѡ��or����,����-1�˳�)��\n");
	scanf("%s", newChara);
	if (newChara[0] == '-' && newChara[1] == '1')
		return;
	while (strcmp(newChara, "ѡ��") && strcmp(newChara, "����")) {
		printf("��������ȷ�Ŀγ�����(ѡ��or����,����-1�˳�):\n");
		scanf("%s", newChara);
		if (newChara[0] == '-' && newChara[1] == '1')
			return;
	}

	printf("�������µĿγ�ѧ��(����-1�˳�):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	newScore = strToInt(buffer);
	while (newScore == -1) {
		printf("��������ȷ�Ŀγ�ѧ��(����-1�˳�):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		newScore = strToInt(buffer);
	}
	
	printf("�������µ���ʦ����(����-1�˳�)��\n");
	scanf("%s", newTeacherName);
	if (newTeacherName[0] == '-' && newTeacherName[1] == '1')
		return;

	strcpy(p->name, newName);
	strcpy(p->chara, newChara);
	p->score = newScore;
	strcpy(p->teacherName, newTeacherName);
	printf("�޸ĳɹ�");
	//��������
	DataStorage();
	return;
}

//��ѯ�γ�
void queryClass() {
	int id; char buffer[20];
	struct Class* current=classHead;
	printf("������γ̱�Ż�γ�����(����-1�˳�)��\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	if ((id = strToInt(buffer)) != -1) {
		current = findClassByID(id);
		if (current != NULL) {
			printf("|�γ̱�� | �γ�����        | �γ����� | �γ�ѧ�� | ��ʦ���� | ѡ������ |\n");
			printf("------------------------------------------------------------------------\n");
			printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
		}
		else printf("δ��ѯ���ñ�ŵĿγ�\n");
	}
	else
	{
		while (current!=NULL)
		{
			if (!strcmp(buffer, current->name)) {
				printf("|�γ̱�� | �γ�����        | �γ����� | �γ�ѧ�� | ��ʦ���� | ѡ������ |\n");
				printf("------------------------------------------------------------------------\n");
				printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
			}
			current = current->next;
		}
		printf("δ��ѯ�������ƵĿγ�\n");
	}
}

//���ݿγ̱�Ż�ѡ����������
void sortClass() {
	char name[15]; int id; char chara[10]; char teacherName[20]; int num; int score;
	struct Class* p1 = classHead;
	struct Class* p2 = classHead;
	int choice = -1; char buffer;
	printf("   0 ���տγ̱������\n");
	printf("   1 ���տγ���������\n");
	printf("   2 ���տγ�ѧ������\n");
	printf("   3 �˳�\n");

	buffer = _getch();
	if ('3' == buffer)return;
	choice = buffer - '0';
	while (choice < 0 || choice > 2) {
		printf("��������ȷ���!!\n");
		buffer = _getch();
		choice = buffer - '0';
		if ('3' == buffer)return;
	}

	while (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			if (choice ? (choice == 1 ? (p1->num > p2->num) : (p1->score > p2->score)):(p1->id > p2->id)  ) {
				strcpy(name, p1->name);
				strcpy(p1->name, p2->name);
				strcpy(p2->name, name);

				id = p1->id;
				p1->id = p2->id;
				p2->id = id;

				strcpy(chara, p1->chara);
				strcpy(p1->chara, p2->chara);
				strcpy(p2->chara, chara);

				strcpy(teacherName, p1->teacherName);
				strcpy(p1->teacherName, p2->teacherName);
				strcpy(p2->teacherName, teacherName);

				num = p1->num;
				p1->num = p2->num;
				p2->num = num;

				score = p1->score;
				p1->score = p2->score;
				p2->score = score;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	system("cls");
	showClass();
	//��������
	DataStorage();
}

// չʾ����class��Ϣ
void showClass()
{
	struct Class* current = classHead;
	printf("�γ̱�� | �γ�����        | �γ����� | �γ�ѧ�� | ��ʦ���� | ѡ������ \n");
	printf("---------------------------------------------------------\n");
	while (current != NULL)
	{
		printf("%-8d | %-15s | %-8s | %-8d | %-8s | %-8d \n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
		current = current->next;
	}
}

//չʾ��ѡ ѡ�޿γ���Ϣ
void showStudentClass() {
	
	//չʾѡ�޿γ̣�
	for(int i=0;i<3;i++)
	{
		struct Class* current = findClassByID(studentNow->classes[i]);
		if(current!=NULL)
		printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
	}
}

//���ݿγ̱�ŷ��ؿγ�ָ��
struct Class* findClassByID(int id)
{
	if(id == -1) return NULL;
	struct Class* p = classHead;
	while (p != NULL)
	{
		if (id == p->id)
			return p;
		p = p->next;
	}
	return NULL;
}

//����ѧ��ѧ�ŷ���ѧ��ָ��
struct Student* findStudentByID(int id)
{
	struct Student* p = studentHead;
	while (p != NULL)
	{
		if (id == p->id)
			return p;
		p = p->next;
	}
	return NULL;
}

//���ݿγ����ʴ�ӡ�γ���Ϣ
void showClassByChara(int fig)
{
	char charas[2][7] = { {"ѡ��"}, { "����"} };
	struct Class* p = classHead;
	printf("|�γ̱�� | �γ�����        | �γ����� | �γ�ѧ�� | ��ʦ���� | ѡ������ |\n");
	printf("------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (!strcmp(charas[fig], p->chara))
			printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", p->id, p->name, p->chara, p->score, p->teacherName, p->num);
		p = p->next;
	}
	printf("------------------------------------------------------------------------\n");
}

// ���ѧ��
void addStudent()
{
	char name[15],buffer[20]; int id, classes[3] = { 0 },loopNum=0;
	struct Student* newStudent = NEW_STUDENT;

	// ����ѧ����Ϣ
	printf("������ѧ������(����-1�˳�)��\n");
	scanf("%s",name);
	if (name[0] == '-' && name[1] == '1')
		return;

	printf("������ѧ��ѧ��(����-1�˳�)��\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ( id == -1 || findStudentByID(id)!= NULL) {
		printf("ѧ�Ŵ����ѧ�ű�ռ��(����-1�˳�)\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}
	system("cls");

	strcpy(newStudent->name, name);
	newStudent->id = id;
	strcpy(newStudent->password, "666");
	memcpy(newStudent->classes, classes, 3 * sizeof(int));
	newStudent->next = NULL;

	if (studentHead == NULL)
	{
		studentHead = newStudent;
		studentRear = newStudent;
	}
	else
	{
		studentRear->next = newStudent;
		studentRear = newStudent;
	}

	studentCount++;

	//���б��޿�Ŀ�γ�������һ
	struct Class* ClassP = classHead;
	while (ClassP != NULL)
	{
		if (!strcmp("����", ClassP->chara))
			ClassP->num++;  // =studentCount;
		ClassP = ClassP->next;
	}

	//��������
	DataStorage();
}

// ɾ��ѧ��
void deleteStudent()
{
	struct Student* current = NULL;
	struct Student* previous =studentHead;
	int id; char buffer[20];

	printf("������ѧ��ѧ��(����-1�˳�)��\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ((current = findStudentByID(id)) == NULL) {
		printf("��������ȷ��ѧ��(����-1�˳�)\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}

	if (current == studentHead)
		studentHead = studentHead->next;
	else while (previous->next != current)
		previous = previous->next;
	previous->next = current->next;

	studentCount--;

	//��ѡ�޵Ŀ�Ŀ�γ�������һ
	for (int i = 0; i < 3; i++) {
		struct Class* class = findClassByID(current->classes[i]);
		if (class != NULL) { class-> num--; }
	}

	//���б��޿�Ŀ�γ�������һ
	struct Class* ClassP = classHead;
	while (ClassP != NULL)
	{
		if (!strcmp("����", ClassP->chara))
			ClassP->num--;
		ClassP = ClassP->next;
	}
	//��������
	DataStorage();
}

// ����ѧ������
void resetStudentPassword()
{
	int id, loopNum = 0; char buffer[20];
	struct Student* current;

	printf("��������Ҫ���������ѧ��ѧ��(����-1�˳�)\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while (id == -1) {
		printf("��������ȷ��ѧ�� (����-1�˳�)\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}
	system("cls");

	while ((current =findStudentByID(id)) == NULL) {
		if (++loopNum > 3) {
			printf("��������������࣬�Զ���ӡѧ����Ϣ,����ȷ����ѧ��ѧ��\n");
			showStudent();
		}else printf("δ�ҵ���ѧ��\n");

		id = -1;
		while (id == -1) {
			printf("��������ȷ��ѧ��(����-1�˳�)\n");
			scanf("%s", buffer);
			if (buffer[0] == '-' && buffer[1] == '1')
				return;
			id = strToInt(buffer);
		}
		system("cls");
	}
	strcpy(current->password, "666");
	printf("������ ѧ��Ϊ  %d  %sͬѧ������\n", current->id,current->name);
	//��������
	DataStorage();
}

//ѧ���޸�����
void modifyStudentPassword()
{
	int loopNum=0; char newPassword1[20],newPassword2[20],oldPassword[20];

	printf("�����������( ����-1�˳� )��\n");
	scanf("%s", oldPassword);
	system("cls");
	if (oldPassword[0] == '-' && oldPassword[0] == '1')
		return;
	while(strcmp(oldPassword, studentNow->password)) {
		loopNum++;
		if (loopNum > 2) {
			printf("��������������࣬�Զ��˳���¼����������������ϵ��ʦ����\n");
			system("pause");
			system("cls");
			login();
		}

		printf("�������������,���������� ( ����-1�˳� )\n");
		scanf("%s", oldPassword);
		if (oldPassword[0] == '-' && oldPassword[0] == '1')
			return;
		system("cls");
	}
	loopNum = 0;

	printf("������������( ����-1�˳� )��\n");
	scanf("%s", newPassword1);
	system("cls");
	if (newPassword1[0] == '-' && newPassword1[0] == '1')
		return;
	
	printf("���ٴ�����������( ����-1�˳� )��\n");
	scanf("%s", newPassword2);
	system("cls");
	if (newPassword2[0] == '-' && newPassword2[0] == '1')
		return;

	while(strcmp(newPassword1, newPassword2)) {
		printf("�����������벻��ͬ����������\n");
		printf("�����������룺( ����-1�˳� )\n");
		scanf("%s", newPassword1);	
		system("cls");
		if (newPassword1[0] == '-' && newPassword1[0] == '1')
			return;
		printf("���ٴ����������룺( ����-1�˳� )\n");
		scanf("%s", newPassword2);
		system("cls");
		if (newPassword2[0] == '-' && newPassword2[0] == '1')
			return;
	}
	
	strcpy(studentNow->password, newPassword1);
	printf("�����޸ĳɹ�\n");

	//��������
	DataStorage();
}

//���ݿγ̱��ɾ��ѧ���Ŀγ���Ϣ
void deleteStudentClassById(int id){
	struct Student* current = studentHead;
	while (current != NULL)
	{
		for (int i = 0; current->classes[i]; i++) {
			if (current->classes[i] == id)
			{
				current->classes[i] = 0;
			}
		}
		current = current->next;
	}
}

//չʾѧ����Ϣ
void showStudent()
{
	struct Student* current = studentHead;
	struct Class* class[3];
	printf("����     | ѧ��            | ѡ��2           | ѡ��2           | ѡ��2           |\n");
	printf("---------------------------------------------------------------------------------|\n");

	while (current != NULL)
	{
		char* className[3] = { {"��"},{"��"},{"��"} };
		for (int i = 0 ,k=0; i < 3; i++) {
			class[i] = findClassByID(current->classes[i]);
			if (class[i] != NULL) {
				className[i] = class[i]->name;
				k++;
			}
		}
		printf("%-8s | %-15d | %-15s | %-15s | %-15s |\n", current->name, current->id, className[0], className[1], className[2]);
		current = current->next;
	}
}

//���򶳽�
void delay() {
	system("cls");
	for (int i = 30; i; i--) {
		printf("���������������,��%d������²�����\n", i);
		Sleep(1000);
		system("cls");
	}
}

//���ַ���ת��Ϊ���������ת��ʧ�����-1
int strToInt(char* str) {
	int ans = 0;
	//int i = str[0] == '-' ? 1 : 0;
	for (int i=0; str[i]; i++) {
		ans *= 10;
		if ('0' <= str[i] && str[i] <= '9')
			ans += str[i] - '0';
		else return -1;
	}
	return ans; //str[0] == '-' ? ans*-1 : ans;
}

int System() {	
//�ļ�û�����ݿ���������һ����δ���

	//DataCollect();
	///*struct Class k4 = { 4,"��ѧ������","ѡ��",3,"����",0,NULL };
	//struct Class k3 = { 3,"���պ���","ѡ��",3,"��С��",0,&k4 };
	//struct Class k2 = { 2,"Ӣ��","����",3,"���",6,&k3 };
	//struct Class k1 = { 1,"�ߵ���ѧ","����",2,"����",6,&k2 };
	//classHead = &k1;
	//DataStorage();*/
	//
	//struct Student s6 = { "��ΰ", 230207117,{0},"666",NULL };
	//struct Student s5 = { "���κ�", 230207116,{0},"666",&s6 };
	//struct Student s4 = { "����", 230207115,{0},"666",&s5 };
	//struct Student s3 = { "����", 230207114,{0},"666",&s4 };
	//struct Student s2 = { "������", 230207113,{0},"666",&s3 };
	//struct Student s1 = { "����", 230207112,{0},"666",&s2 };
	//studentHead = &s1;
	//DataStorage();

	//���ݳ�ʼ��
	DataCollect();
	login();
}
