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

//登录界面
void login();
//学生登录
void studentLogin();
//老师登录
void teacherLogin();
//学生菜单界面
void studentMenu();
//教师菜单界面
void teacherMenu();
//学生选课界面
void  classChoose();
//选课数据处理
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
//查询课程
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

//将字符串转换为整数输出，转换失败输出-1
int strToInt(char* str);
void delay();

struct Class
{
	int id; //课程编号
	char name[50]; //课程名字
	char chara[10]; //课程性质
	int score; //课程学分
	char teacherName[20]; //老师
	int num; //选课人数
	struct Class* next;//下一节点
} *classHead,*classRear;

struct Student
{
	char name[15]; //学生名字
	int id; //学生学号
	int classes[3]; //所选课程
	char password[20]; //学生密码
	struct Student* next;//下一节点
} *studentHead,*studentRear;

struct Student* studentNow=NULL;//记录登录的学生

struct Teacher
{
	char name[15]; //教师名字
	int id; //教师编号
	char password[20]; //教师密码
	struct Teacher* next;
} *teacherHead;

static int  classCount = 0;
static int  studentCount = 0;

//登录界面
void login()
{
	int choice=0; char buffer;
	SetConsoleTitleA("登录");
	printf("|------------------------------------------------------------|\n");
	printf("|----------欢迎使用南昌航空大学科技学院选课系统(C语言)-------|\n");
	printf("|                                                            |\n");
	printf("|--------------------请选择你的身份--------------------------|\n");
	printf("|                                                            |\n");
	printf("|------------------------1.学生------------------------------|\n");
	printf("|                                                            |\n");
	printf("|------------------------2.老师------------------------------|\n");                                            
	printf("|                                                            |\n");
	printf("|------------------------3.退出------------------------------|\n");
	printf("|                                                            |\n");
	printf("|-------------------请输入正确编号继续-----------------------|\n");

	buffer = _getch();
	if ('1' <= buffer && buffer <= '3')
		choice = buffer - '0';

	while (choice == 0) {
		printf("请输入正确编号!!\n");
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
			printf("成功退出\n");
			exit(0);
	default:
			printf("程序出错，\n");
			login(); break;
	}
	system("cls");
	login();
}

//学生登录
void studentLogin()
{
	int id, loopNum = 0;
	char buffer[20];
	char password[20];
	SetConsoleTitleA("学生登录");

	while (1) {
		printf("|-----------------请输入您的学号(-1退出)-----------------------|\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);

		while (id == -1) {
			printf("|-----------------请输入正确的学号(-1退出)---------------------|\n");
			scanf("%s", buffer);
			if (buffer[0] == '-' && buffer[1] == '1')
				return;
			id = strToInt(buffer);
		}
	
		printf("|-------------------请输入密码(-1退出)---------------------------|\n");
		scanf("%s", password);
		if (password[0] == '-' && password[1] == '1')
			return;
		system("cls");

		if (studentCheck(id, password)) {
			printf("登录成功\n");
			studentMenu();
		}

		loopNum++;
		if (loopNum > 2) {
			delay();
			studentLogin();
		}
		printf("对不起。您的账号或密码错误。请重新输入\n");		
	};
}

//老师登录
void teacherLogin()
{
	int id, loopNum = 0;
	char buffer[20];
	char password[20];
	SetConsoleTitleA("教师登录");

	while (1) {
		printf("|---------------- 请输入您的教师账号(-1退出)-------------------|\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);

		while (id == -1) {
			
			printf("|-------------- 请输入正确的教师账号(-1退出)-----------------|\n");
			scanf("%s", buffer);
			if (buffer[0] == '-' && buffer[1] == '1')
				return;
			id = strToInt(buffer);
		}

		printf("|------------------请输入您的密码(-1退出)----------------------|\n");
		scanf("%s", password);
		if (password[0] == '-' && password[1] == '1')
			return;
		system("cls");

		if (teacherCheck(id, password)) {
			printf("登录成功\n");
			teacherMenu();
		}

		loopNum++;
		if (loopNum > 2) {
			delay();
			teacherLogin();
		}
		printf("对不起。您的账号或密码错误。请重新输入\n");
	};
}

//学生菜单界面
void studentMenu()
{ 
	
	int choice=0; char buffer;
	SetConsoleTitleA("学生选课界面");
	printf("|--------------------------------------------------------------|\n");
	printf("|------------------欢迎来到学生选课界面------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------1.选课操作界面----------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------2.查看已选课程----------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------3.查询课程--------------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------4.修改密码--------------------------------|\n");
	printf("|                                                              |\n");
	printf("|--------------------5.退出选课界面----------------------------|\n");
	printf("|                                                              |\n");
	printf("|-----------------请输入编号以继续操作-------------------------|\n");

	buffer = _getch();
	if ('1' <= buffer && buffer <= '5')
		choice = buffer - '0';

	while (choice == 0) {
		printf("请输入正确编号!!\n");
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

//教师菜单界面
void teacherMenu()
{
	int choice=-1; char buffer;
	SetConsoleTitleA("教师选课管理界面");
	printf("\t\t|------------------------------------------------------------------|\n");
	printf("\t\t|--------------------欢迎来到教师选课管理界面----------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------1.添加课程信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");	
	printf("\t\t|------------------------2.删除课程信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------3.修改课程信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------4.查看课程信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------5.课程信息排序----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------6.添加学生信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------7.删除学生信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------8.重置学生密码----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------9.查看学生信息----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------0.退出选课系统----------------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|---------------------请输入对应编号进行操作！---------------------|\n");
	printf("\t\t|                                                                  |\n");
	printf("\t\t|------------------------------------------------------------------|\n");

	buffer = _getch();
	if ('0' <= buffer && buffer <= '9')
		choice = buffer - '0';

	while (choice == -1) {
		printf("请输入正确编号!!\n");
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

//学生选课
void classChoose()
{
	char ids[40];
	struct Class* p = classHead;
	SetConsoleTitleA("选课中心");
	printf("|-------------------------2023-2024学年---------------------------------|\n");
	printf("|                                                                       |\n");
	printf("|------------------------欢迎来到学生选课中心---------------------------|\n");
	printf("|                                                                       |\n");
	printf("|-----------------------------------------------------------------------|\n");
	showClassByChara(0);
	printf("|-----------------------------------------------------------------------|\n");
	printf("|--已选课程-------------------------------------------------------------|\n");
	showStudentClass();
	printf("请输入你的选课编号（用空格隔开，回车结束,输入-1停止选课)\n");
	getchar();//清空缓存区
	while (1) {
		fgets(ids, 35, stdin);
		if (ids[0] == '-' && ids[1] == '1')
			return;
		switch (clooseService(ids))
		{
		case 0: printf("选课成功\n"); DataStorage();
		case 1: return;
		case 2: printf("请输入正确的字符\n"); break;
		case 3: printf("输入的课程编号重复\n"); break;
		case 4: printf("课程编号不正确\n"); break;
		case 5: printf("最多选择3门课程\n"); break;
		}
	}
	
}

//选课数据处理
int clooseService(char classIDs[40]) {
	int classes[4] = { 0 }; int i = 0, num = 0, classNum = 0;

	//退出
	if (classIDs[0] == '-' && classIDs[1] == '1')
		return 1;

	//字符串数据转换为整形 ，并初校验数据
	while (classIDs[i]&& classIDs[i]!='\n')
	{
		if ('0' <= classIDs[i] && classIDs[i] <= '9') {
			if (num > 2)return 5;//选课课程数量大于3
			classes[num] *= 10;
			classes[num] += classIDs[i] - '0';
		}
		else if (classIDs[i] == ' ')
		{
			if (classes[num])
				num++;
		}
		else return 2;//输入错误字符
		i++;
	}

	//课程编号是否重复
	if (classes[0] == classes[1] || (classes[1] == classes[2] && classes[1]) || classes[0] == classes[2])
		return 3;//重复
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


	//校验课程编号
	struct Class* class[4];
	for (i = 0; classes[i]; i++) {
		class[i] = findClassByID(classes[i]);
		if (  !class[i] || strcmp("选修", class[i]->chara))return 4;
		//课程编号错误
	}

	//课程人数加1
	for (i = 0; classes[i]; i++) {
		class[i]->num++;
	}

	//选课信息录入
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

//将学生信息和课程信息从文件中提取保持到相应的链表结构
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
			printf("classData.txt文件内容失效\n");
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
		printf("studentData.txt文件内容失效\n");
		studentHead = NULL;
		studentCount = 0;
	}
	free(studentP);
	fclose(studentFp);
}

//将学生信息和课程信息从链表结构保存至文件
void DataStorage()
{
	FILE* classFp, * studentFp;
	struct Class* classP = classHead; 
	struct Student* studentP = studentHead;

	//printf("正在保存课程信息。。\n");
	classFp = fopen("classData.txt", "w");	
	while (classP != NULL)
	{
		fwrite(classP, sizeof(struct Class), 1, classFp); //创建文件
		classP = classP->next;
	}
	fclose(classFp);

	//printf("正在保存学生信息。。\n");
	studentFp = fopen("studentData.txt", "w");
	while (studentP != NULL)
	{
		fwrite(studentP, sizeof(struct Student), 1, studentFp); 
		studentP = studentP->next;
	}
	fclose(studentFp);
}

//验证学生密码
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
//验证老师密码
int teacherCheck(int id, char password[])
{
	struct Teacher teacher = { "夏容",111,"666",teacherHead };
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

//添加课程
void addClass() {
	struct Class* p= NEW_CLASS;
	char buffer[20];
	//课程信息录入

	printf("请输入课程名字(输入-1退出):\n");
	scanf("%s", p->name);
	if (p->name[0] == '-' && p->name[1] == '1')
		return;

	printf("请输入课程性质(选修or必修,输入-1退出):\n");
	scanf("%s", p->chara);
	if (p->chara[0] == '-' && p->chara[1] == '1')
		return;
	while (strcmp(p->chara, "选修") && strcmp(p->chara, "必修")) {
		printf("请输入正确的课程性质(选修or必修,输入-1退出):\n");
		scanf("%s", p->chara);
		if (p->chara[0] == '-' && p->chara[1] == '1')
			return;
	}

	printf("请输入课程学分(输入-1退出):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	p->score = strToInt(buffer);
	while (p->score == -1) {
		printf("请输入正确的课程学分(输入-1退出):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		p->score = strToInt(buffer);
	}
	
	printf("请输入教学老师名字(输入-1退出)\n");
	scanf("%s", p->teacherName);
	if (p->teacherName[0] == '-' && p->teacherName[1] == '1')
		return;

	if(strcmp(p->chara,"必修"))
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
	printf("录入成功！！");

	//保存数据
	DataStorage();
};

//根据id 删除课程
void deleteClass() {
	struct Class* current =  NULL;
	struct Class* previous = classHead;
	int id; char buffer[20];
	showClass();

	printf("请输入需要删除的课程编号(输入-1退出):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ((current = findClassByID(id)) == NULL) {
		printf("请输入正确的课程编号(输入-1退出):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}

	//学生选课信息更改
	if(!strcmp(current->chara,"选修"))
	   deleteStudentClassById(id);

	if (current == classHead)
		classHead = classHead->next;
	else while (previous->next != current)
		previous = previous->next;
	previous->next = current->next;

	printf("删除成功");
	//保存数据
	DataStorage();
	classCount--;
}

// 修改课程信息
void modifyClass()
{
	int id; char newName[20]; char newChara[20]; int newScore; char newTeacherName[20];
	char buffer[20];
	struct Class* p = classHead;
	showClass();
	printf("请输入需要修改的课程编号(输入-1退出):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ((p = findClassByID(id))==NULL ) {
		printf("请输入正确的课程编号(输入-1退出):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}
	
	printf("请输入新的课程名称(输入-1退出)：\n");
	scanf("%s", newName);
	if (newName[0] == '-' && newName[1] == '1')
		return;
	
	printf("请输入新的课程性质(选修or必修,输入-1退出)：\n");
	scanf("%s", newChara);
	if (newChara[0] == '-' && newChara[1] == '1')
		return;
	while (strcmp(newChara, "选修") && strcmp(newChara, "必修")) {
		printf("请输入正确的课程性质(选修or必修,输入-1退出):\n");
		scanf("%s", newChara);
		if (newChara[0] == '-' && newChara[1] == '1')
			return;
	}

	printf("请输入新的课程学分(输入-1退出):\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	newScore = strToInt(buffer);
	while (newScore == -1) {
		printf("请输入正确的课程学分(输入-1退出):\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		newScore = strToInt(buffer);
	}
	
	printf("请输入新的老师姓名(输入-1退出)：\n");
	scanf("%s", newTeacherName);
	if (newTeacherName[0] == '-' && newTeacherName[1] == '1')
		return;

	strcpy(p->name, newName);
	strcpy(p->chara, newChara);
	p->score = newScore;
	strcpy(p->teacherName, newTeacherName);
	printf("修改成功");
	//保存数据
	DataStorage();
	return;
}

//查询课程
void queryClass() {
	int id; char buffer[20];
	struct Class* current=classHead;
	printf("请输入课程编号或课程名字(输入-1退出)：\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	if ((id = strToInt(buffer)) != -1) {
		current = findClassByID(id);
		if (current != NULL) {
			printf("|课程编号 | 课程名称        | 课程性质 | 课程学分 | 教师姓名 | 选课人数 |\n");
			printf("------------------------------------------------------------------------\n");
			printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
		}
		else printf("未查询到该编号的课程\n");
	}
	else
	{
		while (current!=NULL)
		{
			if (!strcmp(buffer, current->name)) {
				printf("|课程编号 | 课程名称        | 课程性质 | 课程学分 | 教师姓名 | 选课人数 |\n");
				printf("------------------------------------------------------------------------\n");
				printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
			}
			current = current->next;
		}
		printf("未查询到该名称的课程\n");
	}
}

//根据课程编号或选课人数排序
void sortClass() {
	char name[15]; int id; char chara[10]; char teacherName[20]; int num; int score;
	struct Class* p1 = classHead;
	struct Class* p2 = classHead;
	int choice = -1; char buffer;
	printf("   0 按照课程编号排序\n");
	printf("   1 按照课程人数排序\n");
	printf("   2 按照课程学分排序\n");
	printf("   3 退出\n");

	buffer = _getch();
	if ('3' == buffer)return;
	choice = buffer - '0';
	while (choice < 0 || choice > 2) {
		printf("请输入正确编号!!\n");
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
	//保存数据
	DataStorage();
}

// 展示所有class信息
void showClass()
{
	struct Class* current = classHead;
	printf("课程编号 | 课程名称        | 课程性质 | 课程学分 | 教师姓名 | 选课人数 \n");
	printf("---------------------------------------------------------\n");
	while (current != NULL)
	{
		printf("%-8d | %-15s | %-8s | %-8d | %-8s | %-8d \n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
		current = current->next;
	}
}

//展示已选 选修课程信息
void showStudentClass() {
	
	//展示选修课程；
	for(int i=0;i<3;i++)
	{
		struct Class* current = findClassByID(studentNow->classes[i]);
		if(current!=NULL)
		printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", current->id, current->name, current->chara, current->score, current->teacherName, current->num);
	}
}

//根据课程编号返回课程指针
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

//根据学生学号返回学生指针
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

//根据课程性质打印课程信息
void showClassByChara(int fig)
{
	char charas[2][7] = { {"选修"}, { "必修"} };
	struct Class* p = classHead;
	printf("|课程编号 | 课程名称        | 课程性质 | 课程学分 | 教师姓名 | 选课人数 |\n");
	printf("------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (!strcmp(charas[fig], p->chara))
			printf("|%-8d | %-15s | %-8s | %-8d | %-8s | %-8d |\n", p->id, p->name, p->chara, p->score, p->teacherName, p->num);
		p = p->next;
	}
	printf("------------------------------------------------------------------------\n");
}

// 添加学生
void addStudent()
{
	char name[15],buffer[20]; int id, classes[3] = { 0 },loopNum=0;
	struct Student* newStudent = NEW_STUDENT;

	// 输入学生信息
	printf("请输入学生姓名(输入-1退出)：\n");
	scanf("%s",name);
	if (name[0] == '-' && name[1] == '1')
		return;

	printf("请输入学生学号(输入-1退出)：\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ( id == -1 || findStudentByID(id)!= NULL) {
		printf("学号错误或学号被占用(输入-1退出)\n");
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

	//所有必修科目课程人数加一
	struct Class* ClassP = classHead;
	while (ClassP != NULL)
	{
		if (!strcmp("必修", ClassP->chara))
			ClassP->num++;  // =studentCount;
		ClassP = ClassP->next;
	}

	//保存数据
	DataStorage();
}

// 删除学生
void deleteStudent()
{
	struct Student* current = NULL;
	struct Student* previous =studentHead;
	int id; char buffer[20];

	printf("请输入学生学号(输入-1退出)：\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while ((current = findStudentByID(id)) == NULL) {
		printf("请输入正确的学号(输入-1退出)\n");
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

	//所选修的科目课程人数减一
	for (int i = 0; i < 3; i++) {
		struct Class* class = findClassByID(current->classes[i]);
		if (class != NULL) { class-> num--; }
	}

	//所有必修科目课程人数减一
	struct Class* ClassP = classHead;
	while (ClassP != NULL)
	{
		if (!strcmp("必修", ClassP->chara))
			ClassP->num--;
		ClassP = ClassP->next;
	}
	//保存数据
	DataStorage();
}

// 重置学生密码
void resetStudentPassword()
{
	int id, loopNum = 0; char buffer[20];
	struct Student* current;

	printf("请输入需要重置密码的学生学号(输入-1退出)\n");
	scanf("%s", buffer);
	if (buffer[0] == '-' && buffer[1] == '1')
		return;
	id = strToInt(buffer);
	while (id == -1) {
		printf("请输入正确的学号 (输入-1退出)\n");
		scanf("%s", buffer);
		if (buffer[0] == '-' && buffer[1] == '1')
			return;
		id = strToInt(buffer);
	}
	system("cls");

	while ((current =findStudentByID(id)) == NULL) {
		if (++loopNum > 3) {
			printf("操作错误次数过多，自动打印学生信息,请正确输入学生学号\n");
			showStudent();
		}else printf("未找到该学生\n");

		id = -1;
		while (id == -1) {
			printf("请输入正确的学号(输入-1退出)\n");
			scanf("%s", buffer);
			if (buffer[0] == '-' && buffer[1] == '1')
				return;
			id = strToInt(buffer);
		}
		system("cls");
	}
	strcpy(current->password, "666");
	printf("已重置 学号为  %d  %s同学的密码\n", current->id,current->name);
	//保存数据
	DataStorage();
}

//学生修改密码
void modifyStudentPassword()
{
	int loopNum=0; char newPassword1[20],newPassword2[20],oldPassword[20];

	printf("请输入旧密码( 输入-1退出 )：\n");
	scanf("%s", oldPassword);
	system("cls");
	if (oldPassword[0] == '-' && oldPassword[0] == '1')
		return;
	while(strcmp(oldPassword, studentNow->password)) {
		loopNum++;
		if (loopNum > 2) {
			printf("操作错误次数过多，自动退出登录，如忘记密码请联系老师重置\n");
			system("pause");
			system("cls");
			login();
		}

		printf("旧密码输入错误,请重新输入 ( 输入-1退出 )\n");
		scanf("%s", oldPassword);
		if (oldPassword[0] == '-' && oldPassword[0] == '1')
			return;
		system("cls");
	}
	loopNum = 0;

	printf("请输入新密码( 输入-1退出 )：\n");
	scanf("%s", newPassword1);
	system("cls");
	if (newPassword1[0] == '-' && newPassword1[0] == '1')
		return;
	
	printf("请再次输入新密码( 输入-1退出 )：\n");
	scanf("%s", newPassword2);
	system("cls");
	if (newPassword2[0] == '-' && newPassword2[0] == '1')
		return;

	while(strcmp(newPassword1, newPassword2)) {
		printf("两次输入密码不相同请重新输入\n");
		printf("请输入新密码：( 输入-1退出 )\n");
		scanf("%s", newPassword1);	
		system("cls");
		if (newPassword1[0] == '-' && newPassword1[0] == '1')
			return;
		printf("请再次输入新密码：( 输入-1退出 )\n");
		scanf("%s", newPassword2);
		system("cls");
		if (newPassword2[0] == '-' && newPassword2[0] == '1')
			return;
	}
	
	strcpy(studentNow->password, newPassword1);
	printf("密码修改成功\n");

	//保存数据
	DataStorage();
}

//根据课程编号删除学生的课程信息
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

//展示学生信息
void showStudent()
{
	struct Student* current = studentHead;
	struct Class* class[3];
	printf("姓名     | 学号            | 选课2           | 选课2           | 选课2           |\n");
	printf("---------------------------------------------------------------------------------|\n");

	while (current != NULL)
	{
		char* className[3] = { {"无"},{"无"},{"无"} };
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

//程序冻结
void delay() {
	system("cls");
	for (int i = 30; i; i--) {
		printf("操作错误次数过多,请%d秒后重新操作。\n", i);
		Sleep(1000);
		system("cls");
	}
}

//将字符串转换为整数输出，转换失败输出-1
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
//文件没有数据可以先运行一下这段代码

	//DataCollect();
	///*struct Class k4 = { 4,"美学与人生","选修",3,"鹏程",0,NULL };
	//struct Class k3 = { 3,"航空航天","选修",3,"熊小明",0,&k4 };
	//struct Class k2 = { 2,"英语","必修",3,"杨慧",6,&k3 };
	//struct Class k1 = { 1,"高等数学","必修",2,"吴蕾",6,&k2 };
	//classHead = &k1;
	//DataStorage();*/
	//
	//struct Student s6 = { "冷伟", 230207117,{0},"666",NULL };
	//struct Student s5 = { "姜嘉豪", 230207116,{0},"666",&s6 };
	//struct Student s4 = { "黄宇", 230207115,{0},"666",&s5 };
	//struct Student s3 = { "黄鹏", 230207114,{0},"666",&s4 };
	//struct Student s2 = { "何莲成", 230207113,{0},"666",&s3 };
	//struct Student s1 = { "郭阳", 230207112,{0},"666",&s2 };
	//studentHead = &s1;
	//DataStorage();

	//数据初始化
	DataCollect();
	login();
}
