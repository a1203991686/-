#include "stdafx.h"
#include "string.h"
#include "stdlib.h"
#include "windows.h"

#define superadmin d:/1/superadmin.txt
#define superadmin_a d:/1/superadmin_a.txt

/*
 * 部员数目不定，所以使用链表
 * 部长固定6人，使用数组
 * 主席固定1人
 * 超级管理员固定一个账户
*/

char department1[6][7] = { "办公室", "外联", "宣传", "组织", "文艺", "财政" };

struct birthday //出生日期
{
	int year;
	int month;
	int day;
};

typedef struct champion //主席信息
{
	char num[9];         //学号
	char name[9];        //姓名
	char college[21];	 //院系
	char class1[9];      //班级
	struct birthday day; //出生日期
} CHM;

CHM chm; //定义一个变量

typedef struct minister //部长信息
{
	char num[9];         //学号
	char name[9];        //姓名
	char college[21];	 //院系
	char class1[9];      //班级
	struct birthday day; //出生日期
	char department[7];  //部门
} MIN;

//0办公室，1外联，2宣传，3组织，4文艺，5财政
MIN min[6]; //一个部一个部长，一共6个部

typedef struct staff //部员信息
{
	char num[9];         //学号
	char name[9];        //姓名
	char college[21];	 //院系
	char class1[9];      //班级
	struct birthday day; //出生日期
	char department[7]; //部门
	struct staff *next;
} STA;

/*
* USR —— 用户名
* PW —— 密码
*/
typedef struct superadmin_account //超级管理员账户
{
	char USR[9];	 //账号
	char PW[20]; //密码
} SU_a;

SU_a su_a;

typedef struct champion_account //主席账号
{
	char USR[9];	 //账号
	char PW[20]; //密码
} CHM_a;

CHM_a chm_a;

typedef struct minister_account //部长账户
{
	char USR[9];
	char PW[20];
} MIN_a;

MIN_a min_a[6]; //与部长对应

typedef struct staff_account //部员账户
{
	char USR[9];	 //账号
	char PW[20]; //密码
	struct staff_account *next;
} STA_a;

void show_1(); //主页面
void choose_1(STA *head_s, STA_a *head_s_a); //选择选项
void show_su_1(); //超级管理员选单
void choose_su_1(); //超级管理员选单选项
void show_c_1(); //主席主选单
void choose_c_1(STA *head_s, STA_a *head_s_a); //主席主选单选项
void show_c_2(); //主席登录信息操作选单
void choose_c_2(STA *head_s, STA_a *head_s_a); //主席登录信息操作选单选项
void show_m_1(); //部长主选单
void choose_m_1(STA *head_s, STA_a *head_s_a, char USR[]); //部长主选单选项
void show_s_1(); //部员选单
void choose_s_1(STA *head_s, STA_a *head_s_a, char USR[]); //部员选单选项

void login_su(); //超级管理员-登录界面
void inf_su_a(); // 超级管理员账户-文件读取

STA *create_s(STA *head_s, STA_a *head_s_a); //部员-创建
STA *find_s(STA *head_s, char num[]); //部员-查找
STA *insert_s(STA *head_s); //部员-头插法
void delete_s(STA *head_s, STA_a *head_s_a, char num[]); //部员-删除
void change_s(STA *head_s, char num[]); //部员-修改
void output_s(STA *head_s); //部员-输出
void login_s(STA_a *head_s_a, char USR[]); //部员-登录界面
void save_s(STA *head_s); //部员-文件保存
STA *inf_s();  //部员-文件读取
STA_a *create_s_a(STA_a *head_s_a, STA *head_s); //部员账户-创建
STA_a *find_s_a(STA_a *head_s_a, char num[]); //部员账户-查找
void deleter_s_a(STA_a *head_s_a, char num[]); //部员账户-删除
void change_s_a(STA_a *head_s_a, char num[]); //部员账户-修改
void save_s_a(STA_a *head_s_a); //部员账户-文件保存
STA_a *inf_s_a();  //部员账户-文件读取

void create_m(STA *head_s, STA_a *head_s_a); //部长-新建
void deleter_m(char num[]); //部长-删除
int find_m(char num[]); //部长-查找
void change_m(char num[]); //部长-修改
void output_m(); //部长-输出
void save_m(); //部长-文件保存
void inf_m(); //部长-文件读取
void create_m_a(char num[], int i); //部长账户-创建
int find_m_a(char num[]); //部长账户-查找
void change_m_a(char USR[]); //部长账号-修改
void deleter_m_a(char num[]); //部长账号-删除
void save_m_a(); //部长账户-文件保存
void inf_m_a();  //部长账户-文件读取
void login_m(char USR[]); //部长-登录界面

void create_c(); //主席-创建
void deleter_c(); //主席-删除
void change_c(); //主席-修改
void save_c(); //主席-文件保存
void inf_c(); //主席-文件读取
void login_c(); //主席-登录界面
void create(char num[]); // 主席账户-创建
void deleter_c_a(); //主席账户-删除
void change_c_a(); //主席账户-修改
void save_c_a(); //主席-文件保存
void inf_c_a(); //主席-文件读取

int count_m, count_c;

void show_1() //主页面
{
	printf("\t\t\t************************************************\n");
	printf("\t\t\t\t欢迎进入大学生社团学生信息管理系统!!!\n");
	printf("\t\t\t\t\t1. 主席\n");
	printf("\t\t\t\t\t2. 部长\n");
	printf("\t\t\t\t\t3. 部员\n");
	printf("\t\t\t\t\t0. 退出系统\n");
	printf("\t\t\t\t请输入您的身份(0~3):");
}

void choose_1(STA *head_s, STA_a *head_s_a) //选择选项
{
	while (1)
	{
		system("cls");
		show_1();
		char a;
		scanf("%c", &a);
		while (a > '4' || a < '0')
		{
			system("cls");
			show_1();
			printf("\t\t\t\t对不起，您输入有误，请重新输入(0~3):");
			scanf("%c", &a);
		}
		switch (a)
		{
			char USR[9], PW[20];
		case '1':
			login_c();
			choose_c_1(head_s, head_s_a);
			break;
		case '2':
			setbuf(stdin, NULL);
			printf("请输入账号\n");
			scanf("%s", USR);
			login_m(USR);
			choose_m_1(head_s, head_s_a, USR);
			break;
		case '3':
			setbuf(stdin, NULL);
			printf("请输入账号\n");
			scanf("%s", USR);
			login_s(head_s_a, USR);
			choose_s_1(head_s, head_s_a, USR);
			break;
		case '4':
			login_su();
			choose_su_1();
			break;
		case '0':
			printf("正在退出请稍后!!!\n");
			Sleep(1000);
			exit(0);
			break;
		}
	}
}

void show_su_1() //超级管理员选单
{
	printf("\t\t\t************************************************\n");
	printf("\t\t\t\t\t\t超级管理员选单\n");
	printf("\t\t\t\t\t1. 新建主席信息\t2. 修改主席信息\n");
	printf("\t\t\t\t\t3. 修改主席密码\t4. 删除主席信息\n");
	printf("\t\t\t\t\t0. 退出系统\n ");
	printf("\t\t\t\t请输入您需要的功能(0~4):");
}

void choose_su_1() //超级管理员选单选项
{
	while (1)
	{
		system("cls");
		show_su_1();
		char a;
		scanf("%c", &a);
		while (a > '4' || a < '0')
		{
			system("cls");
			// system("cls");
			show_su_1();
			printf("\t\t\t\t对不起，您输入有误，请重新输入(0~4):");
			scanf("%c", &a);
		}
		switch (a)
		{
		case '1':
			create_c();
			break;
		case '2':
			change_c();
			break;
		case '3':
			change_c_a();
			break;
		case '4':
			deleter_c();
			break;
		case '0':
			printf("正在退出请稍后!!!\n");
			// sleep(1000);
			Sleep(1000);
			exit(0);
			break;
		}
	}
}

void show_c_1() //主席主选单
{
	printf("\t\t\t************************************************\n");
	printf("\t\t\t\t\t\t主席选单\n");
	printf("\t\t\t\t\t1. 新建部员信息\t2. 增加部员信息\n");
	printf("\t\t\t\t\t3. 修改部员信息\t4. 删除部员信息\n");
	printf("\t\t\t\t\t5. 设置为部长\t6. 修改部长信息\n");
	printf("\t\t\t\t\t7. 删除部长信息\t8.输出部长信息\n");
	printf("\t\t\t\t\t9. 输出部员信息\t0. 退出系统\n");
	printf("\t\t\t\t\tx. 登陆信息操作\n ");
	printf("\t\t\t\t请输入您需要的功能(0~9):");
}

void choose_c_1(STA *head_s, STA_a *head_s_a) //主席主选单选项
{
	while (1)
	{
		head_s = inf_s();
		head_s_a = inf_s_a();
		setbuf(stdin, NULL);
		system("cls");
		show_c_1();
		char a;
		scanf("%c", &a);
		while ((a > '9' || a < '0') && a != 'x')
		{
			system("cls");
			show_c_1();
			printf("\t\t\t\t对不起，您输入有误，请重新输入(0~9):");
			scanf("%c", &a);
		}
		switch (a)
		{
			char num[9];
		case '1':
			head_s = create_s(head_s, head_s_a);
			save_s(head_s);
			break;
		case '2':
			head_s = insert_s(head_s);
			save_s(head_s);
			break;
		case '3':
			setbuf(stdin, NULL);
			printf("请输入学号\n");
			scanf("%s", num);
			change_s(head_s,num);
			save_s(head_s);
			break;
		case '4':
			setbuf(stdin, NULL);
			printf("请输入需要删除的学号\n");
			scanf("%s", num);
			delete_s(head_s, head_s_a, num);
			break;
		case '5':
			create_m(head_s, head_s_a);
			break;
		case '6':
			setbuf(stdin, NULL);
			printf("请输入需要修改的部长的学号\n");
			scanf("%s", num);
			change_m(num);
			break;
		case '7':
			setbuf(stdin, NULL);
			printf("请输入需要删除的学号");
			scanf("%s", num);
			deleter_m(num);
			save_m();
			break;
		case '8':
			output_m();
			break;
		case '9':
			head_s = inf_s();
			output_s(head_s);
			getchar();
			break;
		case '0':
			printf("正在退出请稍后!!!\n");
			// sleep(1000);
			Sleep(1000);
			exit(0);
			break;
		case 'x':
			choose_c_2(head_s, head_s_a);
			break;
		}
	}
}

void show_c_2() //主席登录信息操作选单
{
	printf("\t\t\t*************************************************\n");
	printf("\t\t\t\t\t\t主席登陆信息操作选单\n");
	printf("\t\t\t\t\t1.修改部长密码\n");
	printf("\t\t\t\t\t2.创建部员账号\t3. 修改部员密码\n");
	printf("\t\t\t\t\t4. 修改自己密码\t5. 返回上一级\n");
	printf("\t\t\t\t请输入您需要的功能(1~5):");
}

void choose_c_2(STA *head_s, STA_a *head_s_a) //主席登录信息操作选单选项
{
	while (1)
	{
		setbuf(stdin, NULL);
		system("cls");
		show_c_2();
		char a;
		scanf("%c", &a);
		while (a > '5' || a < '1')
		{
			system("cls");
			// system("cls");
			show_c_2();
			printf("\t\t\t\t对不起，您输入有误，请重新输入(1~5):");
			scanf("%c", &a);
		}
		switch (a)
		{
		case '1':
			setbuf(stdin, NULL);
			char USR[9];
			printf("请输入需要修改的学号\n");
			scanf("%s", USR);
			change_m_a(USR);
			break;
		case '2':

			head_s_a = create_s_a(head_s_a, head_s);
			save_s_a(head_s_a);
			break;
		case '3':
			setbuf(stdin, NULL);
			char num[9];
			printf("请输入学号");
			scanf("%s", num);
			change_s_a(head_s_a, num);
			break;
		case '4':
			change_c_a();
			break;
		case '5':
			choose_c_1(head_s, head_s_a);
			break;
		}
	}
}

void show_m_1() //部长主选单
{
	printf("\t\t\t*************************************************\n");
	printf("\t\t\t\t\t\t部长主选单\n");
	printf("\t\t\t\t\t1. 新建本部学生信息\t2. 加入本部学生信息\t3. 修改本部学生信息\n");
	printf("\t\t\t\t\t4. 删除本部学生信息\t5. 修改自己信息\t6. 修改自己密码\n");
	printf("\t\t\t\t\t7. 修改部员密码\t0. 退出\n");
	printf("\t\t\t\t请输入您需要的功能(0~7):");
}

void choose_m_1(STA *head_s, STA_a *head_s_a, char USR[]) //部长主选单选项
{
	while (1)
	{
		setbuf(stdin, NULL);
		system("cls");
		show_m_1();
		char a;
		scanf("%c", &a);
		getchar();
		while (a > '7' || a < '0')
		{
			system("cls");
			// system("cls");
			show_m_1();
			printf("\t\t\t\t对不起，您输入有误，请重新输入(0~7):");
			scanf("%c", &a);
			getchar();
		}
		switch (a)
		{
			char num[9];
		case '1':
			head_s = create_s(head_s, head_s_a);
			save_s(head_s);
			break;
		case '2':
			head_s = insert_s(head_s);
			save_s(head_s);
			break;
		case '3':
			setbuf(stdin, NULL);
			printf("请输入学号\n");
			scanf("%s", num);
			change_s(head_s, num);
			break;
		case '4':
			setbuf(stdin, NULL);
			printf("请输入需要删除的学号\n");
			scanf("%s", num);
			delete_s(head_s, head_s_a, num);
			break;
		case '5':
			change_m(USR);
			break;
		case '6':
			change_m_a(USR);
			break;
		case '7':
			setbuf(stdin, NULL);
			printf("请输入学号");
			scanf("%s", num);
			change_s_a(head_s_a,num);
			break;
		case '0':
			printf("正在退出请稍后!!!\n");
			// sleep(1000);
			Sleep(1000);
			exit(0);
			break;
		}
	}
}

void show_s_1() //部员选单
{
	printf("\t\t\t*************************************************\n");
	printf("\t\t\t\t\t\t部员主选单\n");
	printf("\t\t\t\t\t1. 修改自己信息\t2. 修改自己密码\n");
	printf("\t\t\t\t\t0. 退出\n");
	printf("\t\t\t\t请输入您需要的功能(0~2):");
}

void choose_s_1(STA *head_s, STA_a *head_s_a, char USR[]) //部员选单选项
{
	while (1)
	{
		setbuf(stdin, NULL);
		system("cls");
		show_s_1();
		char a;
		scanf("%c", &a);
		while (a > '2' || a < '0')
		{
			system("cls");
			// system("cls");
			show_s_1();
			printf("\t\t\t\t对不起，您输入有误，请重新输入(0~2):");
			scanf("%c", &a);
		}
		switch (a)
		{
		case '1':
			change_s(head_s, USR);
			break;
		case '2':
			change_s_a(head_s_a, USR);
			break;
		case '0':
			printf("正在退出请稍后!!!\n");
			// sleep(1000);
			Sleep(1000);
			exit(0);
			break;
		}
	}
}

void login_su() //超级管理员-登录界面
{
	setbuf(stdin, NULL);
	char USR[9], PW[20];
	printf("请输入账号\n");
	scanf("%s", USR);
	getchar();
	if (!strcmp(USR, su_a.USR))
	{
		printf("请输入密码\n");
		scanf("%s", PW);
		int count = 0;
		count++;
		while (strcmp(PW, su_a.PW))
		{
			printf("密码输入错误，还有%d次机会，请重新输入\n", 3 - count);
			scanf("%s", PW);
			count++;
			getchar();
			if (3 - count == 0)
			{
				printf("密码输入错误超过三次，正在退出系统!!!\n");
				Sleep(1000);
				exit(0);
			}
		}
	}
	else
	{
		printf("没有找到此账号\n返回上一步\n");
		Sleep(1000);
	}
}

void inf_su_a() // 超级管理员账户-文件读取
{
	FILE *fp;
	fp = fopen("d:/superadmin_a.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/superadmin_a.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	fscanf(fp, "%s %s", su_a.USR, su_a.PW);
	fclose(fp);
}

STA *create_s(STA *head_s, STA_a *head_s_a) //部员-创建
{
	STA *p, *q;
	head_s = NULL;
	STA_a *p1, *p2;
	head_s_a = NULL;
	printf("请输入需要新建的学生信息的人数：");
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		p = (STA *)malloc(sizeof(STA));
		printf("请输入第%d名同学学号\n", i + 1);
		char num[9];	  //学号
		scanf("%s", num);
		printf("请输入第%d名同学姓名\n", i + 1);
		char name[9];	  //姓名
		scanf("%s", name);
		printf("请输入第%d名同学院系\n", i + 1);
		char college[21]; //院系
		scanf("%s", &college);
		printf("请输入第%d名同学班级\n", i + 1);
		char class1[9];   //班级
		scanf("%s", class1);
		printf("请输入第%d名同学出生年月日(yy mm dd)\n", i + 1);
		int year, month, day;
		scanf("%d %d %d", &year, &month, &day);
		printf("请输入第%d名同学部门\n", i + 1);
		char department[7];
		scanf("%s", department);
		printf("\n");
		strcpy(p->num, num);
		strcpy(p->name, name);
		strcpy(p->college, college);
		strcpy(p->class1, class1);
		p->day.year = year;
		p->day.month = month;
		p->day.day = day;
		strcpy(p->department, department);
		p->next = NULL;
		if (head_s == NULL)
			head_s = p;
		else
			q->next = p;
		q = p;
	}
	return head_s;
	
}

STA *find_s(STA *head_s, char num[]) //部员-查找
{
	setbuf(stdin, NULL);
	STA *p;
	p = head_s;
	int k = 0;
	while (p)
	{
		if (!strcmp(p->num, num))
		{
			k++;
			break;
		}
		p = p->next;
	}
	if (k)
		return p;
	else
		return NULL;
}

STA *insert_s(STA *head_s) //部员-头插法
{
	STA *p, *q;
	q = head_s;
	p = (STA *)malloc(sizeof(STA));
	printf("请输入学号\n");
	char num[9]; //学号
	scanf("%s", num);
	printf("请输入姓名\n");
	char name[9]; //姓名
	scanf("%s", name);
	printf("请输入院系\n");
	char college[21]; //院系
	scanf("%s", &college);
	printf("请输入班级\n");
	char class1[9]; //班级
	scanf("%s", class1);
	printf("请输入出生年月日(yy mm dd)\n");
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	printf("请输入部门\n");
	char department[7];
	scanf("%s", department);
	strcpy(p->num, num);
	strcpy(p->name, name);
	strcpy(p->college, college);
	strcpy(p->class1, class1);
	p->day.year = year;
	p->day.month = month;
	p->day.day = day;
	strcpy(p->department, department);
	head_s = p;
	p->next = q;
	return head_s;
	STA *m;
	printf("学号\t姓名\t院系\t班级\t出生日期\t部门\n");
	m = head_s;
	while (m)
	{
		printf("%s\t%s\t%s\t%s\t%d-%d-%d\t%s\n", m->num, m->name, m->college, m->class1, m->day.year, m->day.month, m->day.day, m->department);
		m = m->next;
	}
	getchar();
}

void delete_s(STA *head_s, STA_a *head_s_a, char num[]) //部员-删除
{
	STA *p, *q;
	p = q = head_s;
	if (!strcmp(head_s->num, num))
	{
		p = head_s;
		q = head_s->next;
		head_s = q;
	}
	else
	{
		while (p->next)
		{
			if (!strcmp(p->num, num))
			{
				break;
			}
			q = p;
			p = p->next;
		}
		q->next = p->next;
	}
	free(p);
	deleter_s_a(head_s_a, num);
	save_s(head_s);
}

void change_s(STA *head_s, char num[]) //部员-修改
{
	setbuf(stdin, NULL);
	STA *p;
	p = find_s(head_s, num);
	if (p == NULL)
	{
		printf("查无此人!!!\n");
		getchar();
	}
	else
	{
		{
			printf("成员信息为");
			printf("%s\t%s\t%s\t%s\t%d-%d-%d\t%s\n", p->num, p->name, p->college, p->class1, p->day.year, p->day.month, p->day.day, p->department);
		}
		printf("请输入姓名\n");
		char name[9]; //姓名
		scanf("%s", name);
		printf("请输入院系\n");
		char college[21]; //院系
		scanf("%s", &college);
		printf("请输入班级\n");
		char class1[9]; //班级
		scanf("%s", class1);
		printf("请输入出生年月日(yy mm dd)\n");
		int year, month, day;
		scanf("%d %d %d", &year, &month, &day);
		printf("请输入部门\n");
		char department[7];
		scanf("%s", department);
		printf("\n");
		strcpy(p->num, num);
		strcpy(p->name, name);
		strcpy(p->college, college);
		strcpy(p->class1, class1);
		p->day.year = year;
		p->day.month = month;
		p->day.day = day;
		strcpy(p->department, department);
		printf("修改成功！！！");
		Sleep(500);
	}
}

void output_s(STA *head_s) //部员-输出
{
	STA *p;
	printf("学号\t姓名\t院系\t班级\t出生日期\t部门\n");
	p = head_s;
	while (p)
	{
		printf("%s\t%s\t%s\t%s\t%d-%d-%d\t%s\n", p->num, p->name, p->college, p->class1, p->day.year, p->day.month, p->day.day, p->department);
		p = p->next;
	}
	getchar();
}

void login_s(STA_a *head_s_a, char USR[]) //部员-登录界面
{
	setbuf(stdin, NULL);
	char PW[20];
	STA_a *p;
	p = find_s_a(head_s_a, USR);
	if (p == NULL)
	{
		printf("没有找到此账号\n返回上一步\n");
		Sleep(1000);
	}
	else
	{
		printf("请输入密码\n");
		scanf("%s", PW);
		int count = 0;
		count++;
		while (strcmp(PW, p->PW))
		{
			printf("密码输入错误，还有%d次机会，请重新输入\n", 3 - count);
			scanf("%s", PW);
			count++;
			getchar();
			if (3 - count == 0)
			{
				printf("密码输入错误超过三次，正在退出系统!!!\n");
				Sleep(1000);
				exit(0);
			}
		}
	}
}

void save_s(STA *head_s) //部员-文件保存
{
	STA *p = head_s, *sta = head_s;
	FILE *fp;
	fp = fopen("d:/staff.txt", "wt+");
	if (fp == NULL)
	{
		printf("d:/staff.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	while (sta)
	{
		p = sta->next;
		if (!p)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%d-%d-%d\t%s", sta->num, sta->name, sta->college, \
				sta->class1, sta->day.year, sta->day.month, sta->day.day, sta->department);
			break;
		}
		fprintf(fp, "%s\t%s\t%s\t%s\t%d-%d-%d\t%s\n", sta->num, sta->name, sta->college, sta->class1, sta->day.year, sta->day.month, sta->day.day, sta->department);
		sta = sta->next;
	}
	fclose(fp);
}

STA *inf_s()  //部员-文件读取
{
	STA *head_s, *p, *q;
	head_s = q = (STA *)malloc(sizeof(STA));
	head_s == NULL;
	FILE *fp;
	fp = fopen("d:/staff.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/staff.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	while (!feof(fp))
	{
		p = (STA *)malloc(sizeof(STA));
		fscanf(fp, "%s %s %s %s %d-%d-%d %s", p->num, p->name, p->college, \
			p->class1, &p->day.year, &p->day.month, &p->day.day, p->department);
		p->next = NULL;
		if (head_s == NULL)
			head_s = p;
		else
			q->next = p;
		q = p;
	}
	fclose(fp);
	return head_s->next;
}

/*
* 部员信息的创建之后必须跟着部员账户的创建
*/
STA_a *create_s_a(STA_a *head_s_a, STA *head_s) //部员账户-创建
{
	setbuf(stdin, NULL);
	STA_a *p, *q;
	q = (STA_a *)malloc(sizeof(STA_a));
	head_s_a = NULL;
	STA *p1 = head_s;
	while (p1)
	{
		p = (STA_a *)malloc(sizeof(STA));
		strcpy(p->USR, p1->num);
		printf("请输入%s的密码\n", p->USR);
		char PW[20];
		scanf("%s", PW);
		strcpy(p->PW, PW);
		p->next = NULL;
		if (head_s_a == NULL)
			head_s_a = p;
		else
			q->next = p;
		q = p;
		p1 = p1->next;
	}
	return head_s_a;
}

STA_a *find_s_a(STA_a *head_s_a, char num[]) //部员账户-查找
{
	setbuf(stdin, NULL);
	STA_a *p;
	p = head_s_a;
	int k = 0;
	while (p->next)
	{
		if (!strcmp(p->USR, num))
		{
			k++;
			break;
		}
		p = p->next;
	}
	if (k)
		return p;
	else
		return NULL;
}

void deleter_s_a(STA_a *head_s_a, char num[]) //部员账户-删除
{
	STA_a *p, *q;
	p = q = head_s_a;
	if (!strcmp(p->USR, num))
	{
		p = head_s_a;
		q = head_s_a->next;
		head_s_a = q;
	}
	else
	{
		while (p->next)
		{
			if (!strcmp(p->USR, num))
			{
				break;
			}
			q = p;
			p = p->next;
		}
		q->next = p->next;
	}
	free(p);
	save_s_a(head_s_a);
}

void change_s_a(STA_a *head_s_a,char num[]) //部员账户-修改
{
	setbuf(stdin, NULL);
	STA_a *p = find_s_a(head_s_a, num);
	char PW[20];
	printf("请输入密码");
	scanf("%s", PW);
	strcpy(p->PW, PW);
	save_s_a(head_s_a);
}

void save_s_a(STA_a *head_s_a) //部员账户-文件保存
{
	STA_a *p = head_s_a, *sta = head_s_a;
	FILE *fp;
	fp = fopen("d:/staff_a.txt", "wt+");
	if (fp == NULL)
	{
		printf("d:/staff_atxt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	while (sta)
	{
		p = sta->next;
		if (!p)
		{
			fprintf(fp, "%s\t%s", sta->USR,sta->PW);
			break;
		}
		fprintf(fp, "%s\t%s\n", sta->USR, sta->PW);
		sta = sta->next;
	}
	fclose(fp);
}

STA_a *inf_s_a()  //部员账户-文件读取
{
	STA_a *head_s_a, *p, *q;
	head_s_a = q = (STA_a *)malloc(sizeof(STA_a));
	head_s_a == NULL;
	FILE *fp;
	fp = fopen("d:/staff_a.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/staff_a.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	while (!feof(fp))
	{
		p = (STA_a *)malloc(sizeof(STA_a));
		fscanf(fp, "%s\t%s", p->USR, p->PW);
		p->next = NULL;
		if (head_s_a == NULL)
			head_s_a = p;
		else
			q->next = p;
		q = p;
	}
	fclose(fp);
	return head_s_a->next;
}

void create_m(STA *head_s, STA_a *head_s_a) //部长-新建
{
	setbuf(stdin, NULL);
	int i;
	for (i = 0; i < 6; i++)
	{
		head_s = inf_s();
		head_s_a = inf_s_a();
		char num[9];
		printf("请输入需要担任部长的部员的学号\n");
		scanf("%s", num);
		STA *p1 = find_s(head_s, num);
		while (p1 == NULL)
		{
			printf("查无此人！！！\n");
			Sleep(1000);
			printf("请输入需要担任部长的部员的学号\n");
			scanf("%s", num);
			head_s = inf_s();
			STA *p1 = find_s(head_s, num);
		}
		strcpy(min[i].num, p1->num);
		strcpy(min[i].name, p1->name);
		strcpy(min[i].college, p1->college);
		strcpy(min[i].class1, p1->class1);
		min[i].day.year = p1->day.year;
		min[i].day.month = p1->day.month;
		min[i].day.day = p1->day.day;
		strcpy(min[i].department, p1->department);
		delete_s(head_s, head_s_a, num);
		create_m_a(num, i);
		printf("\n");
	}
	save_m();
	save_m_a();
}

void deleter_m(char num[]) //部长-删除
{
	setbuf(stdin, NULL);
	int j = find_m(num);
	if (j == 6)
	{
		printf("查无此人!!!\n");
	}
	else
	{
		strcpy(min[j].num, " ");
		strcpy(min[j].name, " " );
		strcpy(min[j].college, " ");
		strcpy(min[j].class1," ");
		min[j].day.year = 0;
		min[j].day.month = 0;
		min[j].day.day = 0;
		strcpy(min[j].department, " ");
		deleter_m_a(num);
		save_m_a();
	}
}

/*
 * 返回值为6代表查无此人
 */
int find_m(char num[]) //部长-查找
{
	int i, j = 0;
	for (i = 0; i < 6; i++)
	{
		if (!strcmp(min[i].num, num))
		{
			j++;
			break;
		}
	}
	if (j = 0)
		return 6;
	else
		return j;
}

void change_m(char num[]) //部长-修改
{
	setbuf(stdin, NULL);
	int i = find_m(num);
	printf("请输入学号\n");
	scanf("%s", num);
	printf("请输入姓名\n");
	char name[9];	  //姓名
	scanf("%s", name);
	printf("请输入院系\n");
	char college[21]; //院系
	scanf("%s", &college);
	printf("请输入班级\n");
	char class1[9];   //班级
	scanf("%s", class1);
	printf("请输入出生年月日(yy mm dd)\n");
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	printf("请输入部门\n");
	char department[7];
	strcpy(min[i].num, num);
	strcpy(min[i].name, name);
	strcpy(min[i].college, college);
	strcpy(min[i].class1, class1);
	min[i].day.year = year;
	min[i].day.month = month;
	min[i].day.day = day;
	strcpy(min[i].department, department);
	save_m();
}

void output_m() //部长-输出
{
	printf("学号\t姓名\t院系\t班级\t出生日期\t部门\n");
	for (int i = 0; i < 6; i++)
	{
		printf("%s\t%s\t%s\t%s\t%d-%d-%d\t%s\n", min[i].num, min[i].name, min[i].college, min[i].class1, min[i].day.year, min[i].day.month, min[i].day.day, min[i].department);
	}
	getchar();
}

void save_m() //部长-文件保存
{
	FILE *fp;
	fp = fopen("d:/minister.txt", "wt+");
	if (fp == NULL)
	{
		printf("d:/minister.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	int i;
	for (i = 0; i < 6; i++)
	{
		if (i == 5)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%d-%d-%d\t%s", min[i].num, min[i].name, min[i].college, \
				min[i].class1, min[i].day.year, min[i].day.month, min[i].day.day, min[i].department);
		}
		else
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%d-%d-%d\t%s\n", min[i].num, min[i].name, min[i].college, \
				min[i].class1, min[i].day.year, min[i].day.month, min[i].day.day, min[i].department);
		}
	}
	fclose(fp);
}

void inf_m() //部长-文件读取
{
	FILE *fp;
	fp = fopen("d:/minister.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/minister.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	for (int i = 0; i < 6; i++)
	{
		fscanf(fp, "%s %s %s %s %d-%d-%d %s", min[i].num, min[i].name, min[i].college, \
			min[i].class1, &min[i].day.year, &min[i].day.month, &min[i].day.day, min[i].department);
	}
	fclose(fp);
}

void create_m_a(char num[], int i) //部长账户-创建
{
	setbuf(stdin, NULL);
	strcpy(min_a[i].USR, num);
	char PW[20];
	printf("请输入密码\n");
	scanf("%s", PW);
	getchar();
	strcpy(min_a[i].PW, PW);
}

int find_m_a(char num[]) //部长账户-查找
{
	int i, j = 0;
	for (i = 0; i < 6; i++)
	{
		if (!strcmp(min_a[i].USR, num))
		{
			j++;
			break;
		}
	}
	if (j = 0)
		return 6;
	else
		return j;
}

void change_m_a(char USR[]) //部长账号-修改
{
	setbuf(stdin, NULL);
	int i = find_m_a(USR);
	printf("请输入密码\n");
	char PW[20];
	scanf("%s", PW);
	strcpy(min_a->PW, PW);
	save_m_a();
}

void deleter_m_a(char num[]) //部长账号-删除
{
	int i = find_m_a(num);
	strcpy(min_a[i].USR, " ");
	strcpy(min_a[i].PW, " ");
}

void save_m_a() //部长账户-文件保存
{
	FILE *fp;
	fp = fopen("d:/minister_a.txt", "wt+");
	if (fp == NULL)
	{
		printf("minister_a_file文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	for (int i = 0; i < 6; i++)
	{
		if (i == 5)
		{
			fprintf(fp, "%s\t%s", min_a[i].USR, min_a[i].PW);
		}
		else
		{
			fprintf(fp, "%s\t%s\n", min_a[i].USR, min_a[i].PW);
		}
	}
	fclose(fp);
}

void inf_m_a()  //部长账户-文件读取
{
	FILE *fp;
	fp = fopen("d:/minister_a.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/minister_a.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	for (int i = 0; i < 6; i++)
	{
		fscanf(fp, "%s\t%s", min_a[i].USR, min_a[i].PW);
	}
	fclose(fp);
}

void login_m(char USR[]) //部长-登录界面
{
	setbuf(stdin, NULL); 
	char PW[20];
	int i = find_m_a(USR);
	if (i == 6)
	{
		printf("没有找到此账号\n退出中\n");
		Sleep(1000);
	}
	printf("请输入密码\n");
	scanf("%s", PW);
	int count = 0;
	count++;
	while (strcmp(PW, min_a[i].PW))
	{
		printf("密码输入错误，还有%d次机会，请重新输入\n", 3 - count);
		scanf("%s", PW);
		count++;
		getchar();
		if (3 - count == 0)
		{
			printf("密码输入错误超过三次，正在退出系统!!!\n");
			Sleep(1000);
			exit(0);
		}
	}
}

void create_c() //主席-创建
{
	count_m = 1;
	setbuf(stdin, NULL);
	char num[9];
	printf(" 请输入你需要添加到主席的学号\n");
	scanf("%s", num);
	int i = find_m(num);
	if (i == 6)
	{
		printf("出无此人，返回上一步!!!\n");
		Sleep(1000);
	}
	else
	{
		strcpy(chm.num, min[i].num);
		strcpy(chm.name, min[i].name);
		strcpy(chm.college, min[i].college);
		strcpy(chm.class1, min[i].class1);
		chm.day.year = min[i].day.year;
		chm.day.month = min[i].day.month;
		chm.day.day = min[i].day.day;
		deleter_m(num);
	}
}

void deleter_c() //主席-删除
{
	if (count_m == 1)
	{
		strcpy(chm.num, " ");
		strcpy(chm.name, " ");
		strcpy(chm.college, " ");
		strcpy(chm.class1, " ");
		chm.day.year = 0;
		chm.day.month = 0;
		chm.day.day = 0;
	}
	else
		printf("查询不到主席信息，主席账号为0\n");
}

void change_c() //主席-修改
{
	printf("请输入学号\n");
	char num[9]; //学号
	scanf("%s", num);
	printf("请输入姓名\n");
	char name[9]; //姓名
	scanf("%s", name);
	printf("请输入院系\n");
	char college[21]; //院系
	scanf("%s", &college);
	printf("请输入班级\n");
	char class1[9]; //班级
	scanf("%s", class1);
	printf("请输入出生年月日(yy mm dd)\n");
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	strcpy(chm.num, num);
	strcpy(chm.name, name);
	strcpy(chm.college, college);
	strcpy(chm.class1, class1);
	chm.day.year = year;
	chm.day.month = month;
	chm.day.day = day;
}

void save_c() //主席-文件保存
{
	FILE *fp;
	fp = fopen("d:/champion.txt", "wt+");
	if (fp == NULL)
	{
		printf("d:/champion.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	fprintf(fp, "%s\t%s\t%s\t%s\t%d-%d-%d", chm.num, chm.name, chm.college, chm.class1, chm.day.year, chm.day.month, chm.day.day);
	fclose(fp);
}

void inf_c() //主席-文件读取
{
	FILE *fp;
	fp = fopen("d:/champion.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/champion.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	fscanf(fp, "%s\t%s\t%s\t%s\t%d-%d-%d", chm.num, chm.name, chm.college, chm.class1, &chm.day.year, &chm.day.month, &chm.day.day);
	fclose(fp);
}

void login_c() //主席-登录界面
{
	setbuf(stdin, NULL);
	char USR[9], PW[20];
	printf("请输入账号\n");
	scanf("%s", USR);
	getchar();
	if (strcmp(USR, chm_a.USR))
	{
		printf("没有找到此账号\n退出中\n");
		Sleep(1000);
		exit(0);
	}
	printf("请输入密码\n");
	scanf("%s", PW);
	int count = 0;
	count++;
	while (strcmp(PW, chm_a.PW))
	{
		printf("密码输入错误，还有%d次机会，请重新输入\n", 3 - count);
		scanf("%s", PW);
		count++;
		getchar();
		if (count == 3)
		{
			printf("密码输入错误超过三次，正在退出系统!!!\n");
			Sleep(1000);
			exit(0);
		}
	}
}

void create(char num[]) // 主席账户-创建
{
	strcpy(chm_a.USR, num);
	char PW[20];
	printf("请输入密码\n");
	scanf("%s", PW);
	getchar();
	strcpy(chm_a.PW, PW);
}

void deleter_c_a() //主席账户-删除
{
	strcpy(chm_a.USR, " ");
	strcpy(chm_a.PW, " ");
}

void change_c_a() //主席账户-修改
{
	int count = 0;
	setbuf(stdin, NULL);
	char PW[20];
	printf("请输入原密码");
	scanf("%s", PW);
	getchar();
	count++;
	while (strcmp(PW, chm_a.PW))
	{
		printf("密码输入错误，还有%d次机会，请重新输入\n", 3 - count);
		scanf("%s", PW);
		count++;
		getchar();
		if (3 - count == 0)
		{
			printf("密码输入错误超过三次，正在退出系统!!!\n");
			Sleep(1000);
			exit(0);
		}
	}
	printf("请输入新的密码\n");
	scanf("%s", PW);
	strcpy(chm_a.PW, PW);
}

void save_c_a() //主席账户-文件保存
{
	FILE *fp;
	fp = fopen("d:/champion_a.txt", "wt+");
	if (fp == NULL)
	{
		printf("d:/champion_a.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	fprintf(fp, "%s\t%s", chm_a.USR, chm_a.PW);
	fclose(fp);
}

void inf_c_a() //主席账户-文件读取
{
	FILE *fp;
	fp = fopen("d:/champion_a.txt", "rt+");
	if (fp == NULL)
	{
		printf("d:/champion_a.txt文件打开失败，请按回车退出系统！！");
		getchar();
		exit(0);
	}
	fscanf(fp, "%s %s", chm_a.USR, chm_a.PW);
	fclose(fp);
}

int main()
{
	STA *head_s;
	STA_a *head_s_a;
	head_s = inf_s();
	head_s_a = inf_s_a();
	inf_m();
	inf_m_a();
	inf_c();
	inf_c_a();
	inf_su_a();
	choose_1(head_s, head_s_a);
	return 0;
}
