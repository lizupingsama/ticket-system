#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6054)
#pragma warning(disable:28182)
#pragma warning(disable:6011)
#pragma warning(disable:6308)
#pragma warning(disable:28183)
#pragma warning(disable:6387)
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<标头.h>
extern FILE* fp1;
extern FILE* fp2;
extern FILE* fp3;
extern FILE* fp4;
extern FILE* fp5;//Ticket.txt
extern FILE* fp6;//NumOfSite.txt
extern int NumOfManager;
extern int NumOfPassenger;
extern int NumOfSite;
void ManagerLog()//员工登录注册界面
{
	system("cls");
	printf("     欢迎使用后台管理\n");
	printf("**************************\n");
	printf("***    1.登录已有账户  ***\n");
	printf("***    2.注册新账户    ***\n");
	printf("***    3.返回上一级    ***\n");
	printf("**************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:login(); break;
	case 50:logon(); break;
	case 51:main();
	}
}
void BackStage()//后台管理界面
{
	system("cls");
	printf(" 请选择您需要的服务\n");
	printf("************************\n");
	printf("***   1.站点操作     ***\n");
	printf("***   2.票务操作     ***\n");
	printf("***   3.返回上一级   ***\n");
	printf("***   按esc退出程序  ***\n");
	printf("************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:site(); break;
	case 50:ModifyNum(); break;
	case 51:ManagerLog();  break;
	case 27:exit(0);
	}
}
void logon()//管理员账户注册
{
	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp3);//检查文件长度
	fseek(fp3, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)//第一个员工创建账号
	{
		char key[20];//用于存储再次输入的密码
		system("cls");
		struct manager* manager = (struct manager*)malloc(sizeof(struct manager));
		printf("请创建一个账号\n");
		scanf("%s", &manager[0].id);
		printf("请输入您的密码\n");
		scanf("%s", &manager[0].password);
		printf("请确认您的密码\n");
		scanf("%s", &key);
		if (strcmp(manager[0].password, key) != 0)//检验两次输入密码是否相同
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("您输入的两次密码不同，请重新输入密码\n");
				scanf("%s", &manager[0].password);
				printf("请确认您的密码");
				scanf("%s", key);
				if (strcmp(manager[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");//创建NumOfManager.txt
		fprintf(fp3, "%d", NumOfManager);//将管理人员人数写入文件中
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//将管理人员结构体写入文件
		fclose(fp1);
		free(manager);
		system("cls");
		printf("创建账户成功\n按任意键返回登录界面");
		_getch();
		ManagerLog();
	}
	else//后续员工创建账号
	{
		system("cls");
		fp3 = fopen("NumOfManager.txt", "r");
		fscanf(fp3, "%d", &NumOfManager);//从文件读取管理人员人数
		fclose(fp3);

		struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
		fp1 = fopen("Manager.txt", "rb");
		fread(manager, sizeof(struct manager), NumOfManager, fp1);//从文件中读取管理人员结构体
		fclose(fp1);

		manager = (struct manager*)realloc(manager, sizeof(struct manager) * (NumOfManager + 1));
		//管理人员结构体扩容一个单位

		char key[20];//用于存储再次输入的密码
		printf("请创建一个账号\n");
		scanf("%s", &manager[NumOfManager].id);
		for (int i = 0; i < NumOfManager; i++)
		{
			if (strcmp(manager[NumOfManager].id, manager[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("已有账号，请重新输入");
					scanf("%s", &manager[NumOfManager].id);
					for (int n = 0; n < NumOfManager; n++)
					{
						if (strcmp(manager[NumOfManager].id, manager[n].id) == 0)
							break;
						if (n == NumOfManager - 1)
							flag = 0;
					}
				}
				break;
			}
		}
		printf("请输入您的密码\n");
		scanf("%s", &manager[NumOfManager].password);
		printf("请确认您的密码\n");
		scanf("%s", &key);
		if (strcmp(manager[NumOfManager].password, key) != 0)//检验两次输入密码是否相同
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("您输入的两次密码不同，请重新输入密码\n");
				scanf("%s", &manager[NumOfManager].password);
				printf("请确认您的密码");
				scanf("%s", key);
				if (strcmp(manager[NumOfManager].password, key) == 0)
					flag = 0;
			}
		}
		printf("创建账户成功\n按任意键返回登录界面");
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");
		fprintf(fp3, "%d", NumOfManager);//将管理人员人数写入文件中
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//将管理人员人数写入文件中
		fclose(fp1);
		free(manager);
		_getch();
		system("cls");
		ManagerLog();
	}
}
void login()//账户登录
{
	char id[20];
	char password[20];
	system("cls");
	printf("请输入账号\n");
	scanf("%s", &id);
	printf("请输入密码\n");
	scanf("%s", &password);

	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp3);//检查文件长度
	fseek(fp3, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)
	{
		system("cls");
		printf("您输入的账号或密码有误按任意键重新输入,ESC返回");
		int esc = _getch();
		if (esc == 27)
		{
			ManagerLog();
		}
		else
		{
			login();
		}
	}

	fp3 = fopen("NumOfManager.txt", "r");
	fscanf(fp3, "%d", &NumOfManager);//从文件读取管理人员人数
	fclose(fp3);

	struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
	fp1 = fopen("Manager.txt", "rb");
	fread(manager, sizeof(struct manager), NumOfManager, fp1);//从文件中读取管理人员结构体
	fclose(fp1);
	int flag = 1;
	while (flag)
	{
		for (int i = 0; i < NumOfManager; i++)
		{
			if (strcmp(id, manager[i].id) == 0)
			{
				for (int m = 0; m < NumOfManager; m++)
				{
					if (strcmp(password, manager[m].password) == 0)
					{
						flag = 0;
						break;
					}
				}
				break;
			}
		}
		if (flag == 1)
		{
			system("cls");
			printf("您输入的账号或密码有误\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				ManagerLog();
			system("cls");
			printf("请输入账号\n");
			scanf("%s", &id);
			printf("请输入密码\n");
			scanf("%s", &password);
		}
	}
	BackStage();
}
void site()
{
	system("cls");
	printf(" 请选择您需要的操作\n");
	printf("************************\n");
	printf("***   1.查看站点     ***\n");
	printf("***   2.添加站点     ***\n");
	printf("***   3.修改站点     ***\n");
	printf("***   4.删除站点     ***\n");
	printf("***   5.返回上一级   ***\n");
	printf("***   按esc退出程序  ***\n");
	printf("************************\n");
	int key = _getch();
	switch (key)
	{
	case 49:view(); break;
	case 50:AddSite(); break;
	case 51:modify(); break;
	case 52:delet(); break;
	case 53:BackStage(); break;
	}
}
void AddSite()
{
	if ((fp6 = fopen("NumOfSite.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfSite.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfSite.txt", "rb");
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)//第一次添加站点
	{
		NumOfSite = 1;
		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		ticket[0].no = NumOfSite;
		system("cls");
		printf("请输入起始站\n");
		scanf("%s", &ticket[0].start);
		printf("请输入终点站\n");
		scanf("%s", &ticket[0].destination);
		printf("请输入出发时间\n");
		scanf("%s", &ticket[0].StartTime);
		printf("请输入到达时间\n");
		scanf("%s", &ticket[0].ArriveTime);
		printf("请输入车票张数\n");
		scanf("%d", &ticket[0].RestOfTicket);
		fp6 = fopen("NumOfSite.txt", "w");
		fprintf(fp6, "%d", NumOfSite);//将站点数写入文件中
		fclose(fp6);
		fp5 = fopen("Ticket.txt", "wb");
		fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//将车票结构体写入文件
		fclose(fp5);
		free(ticket);
		printf("添加完成，按任意键返回\n");
		_getch();
		site();
	}
	else//后续添加站点
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//从文件读取车票数
		NumOfSite++;
		fclose(fp6);
		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//从文件中读取车票结构体
		fclose(fp5);
		system("cls");
		ticket[NumOfSite - 1].no = NumOfSite;
		printf("请输入起始站\n");
		scanf("%s", &ticket[NumOfSite - 1].start);
		printf("请输入终点站\n");
		scanf("%s", &ticket[NumOfSite - 1].destination);
		printf("请输入出发时间\n");
		scanf("%s", &ticket[NumOfSite - 1].StartTime);
		printf("请输入到达时间\n");
		scanf("%s", &ticket[NumOfSite - 1].ArriveTime);
		printf("请输入车票张数\n");
		scanf("%d", &ticket[NumOfSite - 1].RestOfTicket);

		fp6 = fopen("NumOfSite.txt", "w");
		fprintf(fp6, "%d", NumOfSite);//将站点数写入文件中
		fclose(fp6);
		fp5 = fopen("Ticket.txt", "wb");
		fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//将车票结构体写入文件
		fclose(fp5);
		free(ticket);
		printf("添加完成，按任意键返回\n");
		_getch();
		site();
	}
}
void view()
{
	if ((fp6 = fopen("NumOfSite.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfSite.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfSite.txt", "rb");
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加站点信息
	{
		system("cls");
		printf("当前没有车次信息\n按任意键返回");
		_getch();
		site();
	}

	else//已添加站点信息
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//从文件读取车票数
		fclose(fp6);
		if (NumOfSite == 0)//站点数为0
		{
			system("cls");
			printf("当前没有车次信息\n按任意键返回");
			_getch();
			site();
		}
		else//站点数不为0
		{
			struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
			fp5 = fopen("Ticket.txt", "rb");
			fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//从文件中读取车票结构体
			fclose(fp5);
			system("cls");
			for (int i = 0; i < NumOfSite; i++)
			{
				printf("NO.%d\n", ticket[i].no);
				printf("起点站：%s\n", ticket[i].start);
				printf("终点站：%s\n", ticket[i].destination);
				printf("发车时间：%s\n", ticket[i].StartTime);
				printf("预计到达时间：%s\n", ticket[i].ArriveTime);
				printf("余票数：%d\n", ticket[i].RestOfTicket);
				printf("                                                 \n");
				printf("-------------------------------------------------\n");
				printf("                                                 \n");
			}
			free(ticket);
			printf("按任意键返回");
			_getch();
			site();
		}
	}
}
void modify()
{
	if ((fp6 = fopen("NumOfSite.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfSite.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfSite.txt", "rb");
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加站点信息
	{
		system("cls");
		printf("当前没有车次信息\n按任意键返回");
		_getch();
		site();
	}

	else
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//从文件读取车票数
		fclose(fp6);
		if (NumOfSite == 0)//站点数为0
		{
			system("cls");
			printf("当前没有车次信息\n按任意键返回");
			_getch();
			site();
		}
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//从文件读取车票数
		fclose(fp6);

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//从文件中读取车票结构体
		fclose(fp5);

		system("cls");
		printf("请选择要修改的车次编号");
		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfSite; i++)
		{
			if (no == ticket[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("没有找到该车次信息\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				site();
			else
				modify();
		}
		else//找到对应车次信息
		{
			system("cls");
			printf("NO.%d\n", ticket[no - 1].no);
			printf("起点站：%s\n", ticket[no - 1].start);
			printf("终点站：%s\n", ticket[no - 1].destination);
			printf("发车时间：%s\n", ticket[no - 1].StartTime);
			printf("预计到达时间：%s\n", ticket[no - 1].ArriveTime);
			printf("余票数：%d\n", ticket[no - 1].RestOfTicket);
			printf("\n");
			printf("请选择要修改的内容\n");
			printf("************************\n");
			printf("***   1.起点站       ***\n");
			printf("***   2.终点站       ***\n");
			printf("***   3.发车时间     ***\n");
			printf("***   4.预计到达时间 ***\n");
			printf("***   5.余票数       ***\n");
			printf("***   6.返回上一级   ***\n");
			printf("************************\n");
			int choose = _getch();
			switch (choose)
			{
			case 49:printf("请输入起点站"); scanf("%s", &ticket[no - 1].start); break;
			case 50:printf("请输入终点站"); scanf("%s", &ticket[no - 1].destination); break;
			case 51:printf("请输入发车时间"); scanf("%s", &ticket[no - 1].StartTime); break;
			case 52:printf("请输入预计到达时间"); scanf("%s", &ticket[no - 1].ArriveTime); break;
			case 53:printf("请输入余票数"); scanf("%d", &ticket[no - 1].RestOfTicket); break;
			case 54:modify(); break;
			}
			fp5 = fopen("Ticket.txt", "wb");
			fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//将车票结构体写入文件
			fclose(fp5);
			free(ticket);
			system("cls");
			printf("更改完成，按任意键返回");
			_getch();
			site();
		}
	}
}
void delet()
{
	if ((fp6 = fopen("NumOfSite.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfSite.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfSite.txt", "rb");
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加站点信息
	{
		system("cls");
		printf("当前没有车次信息\n按任意键返回");
		_getch();
		site();
	}

	else//添加过站点信息
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//从文件读取车票数
		fclose(fp6);

		if (NumOfSite == 0)//站点数为0
		{
			system("cls");
			printf("当前没有车次信息\n按任意键返回");
			_getch();
			site();
		}

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//从文件中读取车票结构体
		fclose(fp5);

		system("cls");
		printf("请选择要删除的车次编号\n");
		for (int i = 0; i < NumOfSite; i++)
		{
			printf("NO.%d\n", ticket[i].no);
			printf("起点站：%s\n", ticket[i].start);
			printf("终点站：%s\n", ticket[i].destination);
			printf("发车时间：%s\n", ticket[i].StartTime);
			printf("预计到达时间：%s\n", ticket[i].ArriveTime);
			printf("余票数：%d\n", ticket[i].RestOfTicket);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}

		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfSite; i++)//寻找对应车次信息
		{
			if (no == ticket[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("没有找到该车次信息\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				site();
			else
			{
				delet();
			}
		}
		else
		{
			system("cls");
			printf("NO.%d\n", ticket[no - 1].no);
			printf("起点站：%s\n", ticket[no - 1].start);
			printf("终点站：%s\n", ticket[no - 1].destination);
			printf("发车时间：%s\n", ticket[no - 1].StartTime);
			printf("预计到达时间：%s\n", ticket[no - 1].ArriveTime);
			printf("余票数：%d\n", ticket[no - 1].RestOfTicket);
			printf("\n");
			printf("您确定要删除该车次信息吗？\n");
			printf("按任意键确认，ESC取消\n");
			int esc = _getch();
			if (esc == 27)
			{
				site();
			}
			else
			{
				for (int i = no - 1; i < NumOfSite - 1; i++)
				{
					ticket[i] = ticket[i + 1];
				}
				ticket = (struct ticket*)realloc(ticket, sizeof(struct ticket) * (NumOfSite - 1));
				NumOfSite--;
				for (int i = 0; i < NumOfSite; i++)//删除后重新编号
				{
					ticket[i].no = i + 1;
				}
				fp6 = fopen("NumOfSite.txt", "w");
				fprintf(fp6, "%d", NumOfSite);//将站点数写入文件中
				fclose(fp6);
				fp5 = fopen("Ticket.txt", "wb");
				fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//将车票结构体写入文件
				fclose(fp5);
				free(ticket);
				printf("删除完成，按任意键返回\n");
				_getch();
				site();
			}
		}
	}
}
void ModifyNum()
{
	if ((fp6 = fopen("NumOfSite.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfSite.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfSite.txt", "rb");
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加站点信息
	{
		system("cls");
		printf("当前没有车次信息\n按任意键返回");
		_getch();
		BackStage();
	}

	else//添加过站点信息
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//从文件读取车票数
		fclose(fp6);

		if (NumOfSite == 0)//站点数为0
		{
			system("cls");
			printf("当前没有车次信息\n按任意键返回");
			_getch();
			BackStage();
		}

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//从文件中读取车票结构体
		fclose(fp5);

		system("cls");
		for (int i = 0; i < NumOfSite; i++)
		{
			printf("NO.%d\n", ticket[i].no);
			printf("起点站：%s\n", ticket[i].start);
			printf("终点站：%s\n", ticket[i].destination);
			printf("发车时间：%s\n", ticket[i].StartTime);
			printf("预计到达时间：%s\n", ticket[i].ArriveTime);
			printf("余票数：%d\n", ticket[i].RestOfTicket);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("请选择要操作的车次编号\n");

		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfSite; i++)//寻找对应车次信息
		{
			if (no == ticket[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("没有找到该车次信息\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				site();
			else
			{
				ModifyNum();
			}
		}
		else
		{
			printf("请输入修改的车票数目\n");
			scanf("%d", &ticket[no - 1].RestOfTicket);
			fp5 = fopen("Ticket.txt", "wb");
			fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//将车票结构体写入文件
			fclose(fp5);
			free(ticket);
			system("cls");
			printf("更改完成，按任意键返回");
			_getch();
			BackStage();
		}
	}
}