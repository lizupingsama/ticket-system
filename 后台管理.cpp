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
#include<��ͷ.h>
extern FILE* fp1;
extern FILE* fp2;
extern FILE* fp3;
extern FILE* fp4;
extern FILE* fp5;//Ticket.txt
extern FILE* fp6;//NumOfSite.txt
extern int NumOfManager;
extern int NumOfPassenger;
extern int NumOfSite;
void ManagerLog()//Ա����¼ע�����
{
	system("cls");
	printf("     ��ӭʹ�ú�̨����\n");
	printf("**************************\n");
	printf("***    1.��¼�����˻�  ***\n");
	printf("***    2.ע�����˻�    ***\n");
	printf("***    3.������һ��    ***\n");
	printf("**************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:login(); break;
	case 50:logon(); break;
	case 51:main();
	}
}
void BackStage()//��̨�������
{
	system("cls");
	printf(" ��ѡ������Ҫ�ķ���\n");
	printf("************************\n");
	printf("***   1.վ�����     ***\n");
	printf("***   2.Ʊ�����     ***\n");
	printf("***   3.������һ��   ***\n");
	printf("***   ��esc�˳�����  ***\n");
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
void logon()//����Ա�˻�ע��
{
	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp3);//����ļ�����
	fseek(fp3, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)//��һ��Ա�������˺�
	{
		char key[20];//���ڴ洢�ٴ����������
		system("cls");
		struct manager* manager = (struct manager*)malloc(sizeof(struct manager));
		printf("�봴��һ���˺�\n");
		scanf("%s", &manager[0].id);
		printf("��������������\n");
		scanf("%s", &manager[0].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(manager[0].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &manager[0].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(manager[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");//����NumOfManager.txt
		fprintf(fp3, "%d", NumOfManager);//��������Ա����д���ļ���
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//��������Ա�ṹ��д���ļ�
		fclose(fp1);
		free(manager);
		system("cls");
		printf("�����˻��ɹ�\n����������ص�¼����");
		_getch();
		ManagerLog();
	}
	else//����Ա�������˺�
	{
		system("cls");
		fp3 = fopen("NumOfManager.txt", "r");
		fscanf(fp3, "%d", &NumOfManager);//���ļ���ȡ������Ա����
		fclose(fp3);

		struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
		fp1 = fopen("Manager.txt", "rb");
		fread(manager, sizeof(struct manager), NumOfManager, fp1);//���ļ��ж�ȡ������Ա�ṹ��
		fclose(fp1);

		manager = (struct manager*)realloc(manager, sizeof(struct manager) * (NumOfManager + 1));
		//������Ա�ṹ������һ����λ

		char key[20];//���ڴ洢�ٴ����������
		printf("�봴��һ���˺�\n");
		scanf("%s", &manager[NumOfManager].id);
		for (int i = 0; i < NumOfManager; i++)
		{
			if (strcmp(manager[NumOfManager].id, manager[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("�����˺ţ�����������");
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
		printf("��������������\n");
		scanf("%s", &manager[NumOfManager].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(manager[NumOfManager].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &manager[NumOfManager].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(manager[NumOfManager].password, key) == 0)
					flag = 0;
			}
		}
		printf("�����˻��ɹ�\n����������ص�¼����");
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");
		fprintf(fp3, "%d", NumOfManager);//��������Ա����д���ļ���
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//��������Ա����д���ļ���
		fclose(fp1);
		free(manager);
		_getch();
		system("cls");
		ManagerLog();
	}
}
void login()//�˻���¼
{
	char id[20];
	char password[20];
	system("cls");
	printf("�������˺�\n");
	scanf("%s", &id);
	printf("����������\n");
	scanf("%s", &password);

	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp3);//����ļ�����
	fseek(fp3, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)
	{
		system("cls");
		printf("��������˺Ż����������������������,ESC����");
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
	fscanf(fp3, "%d", &NumOfManager);//���ļ���ȡ������Ա����
	fclose(fp3);

	struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
	fp1 = fopen("Manager.txt", "rb");
	fread(manager, sizeof(struct manager), NumOfManager, fp1);//���ļ��ж�ȡ������Ա�ṹ��
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
			printf("��������˺Ż���������\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				ManagerLog();
			system("cls");
			printf("�������˺�\n");
			scanf("%s", &id);
			printf("����������\n");
			scanf("%s", &password);
		}
	}
	BackStage();
}
void site()
{
	system("cls");
	printf(" ��ѡ������Ҫ�Ĳ���\n");
	printf("************************\n");
	printf("***   1.�鿴վ��     ***\n");
	printf("***   2.���վ��     ***\n");
	printf("***   3.�޸�վ��     ***\n");
	printf("***   4.ɾ��վ��     ***\n");
	printf("***   5.������һ��   ***\n");
	printf("***   ��esc�˳�����  ***\n");
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
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)//��һ�����վ��
	{
		NumOfSite = 1;
		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		ticket[0].no = NumOfSite;
		system("cls");
		printf("��������ʼվ\n");
		scanf("%s", &ticket[0].start);
		printf("�������յ�վ\n");
		scanf("%s", &ticket[0].destination);
		printf("���������ʱ��\n");
		scanf("%s", &ticket[0].StartTime);
		printf("�����뵽��ʱ��\n");
		scanf("%s", &ticket[0].ArriveTime);
		printf("�����복Ʊ����\n");
		scanf("%d", &ticket[0].RestOfTicket);
		fp6 = fopen("NumOfSite.txt", "w");
		fprintf(fp6, "%d", NumOfSite);//��վ����д���ļ���
		fclose(fp6);
		fp5 = fopen("Ticket.txt", "wb");
		fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
		fclose(fp5);
		free(ticket);
		printf("�����ɣ������������\n");
		_getch();
		site();
	}
	else//�������վ��
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		NumOfSite++;
		fclose(fp6);
		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
		fclose(fp5);
		system("cls");
		ticket[NumOfSite - 1].no = NumOfSite;
		printf("��������ʼվ\n");
		scanf("%s", &ticket[NumOfSite - 1].start);
		printf("�������յ�վ\n");
		scanf("%s", &ticket[NumOfSite - 1].destination);
		printf("���������ʱ��\n");
		scanf("%s", &ticket[NumOfSite - 1].StartTime);
		printf("�����뵽��ʱ��\n");
		scanf("%s", &ticket[NumOfSite - 1].ArriveTime);
		printf("�����복Ʊ����\n");
		scanf("%d", &ticket[NumOfSite - 1].RestOfTicket);

		fp6 = fopen("NumOfSite.txt", "w");
		fprintf(fp6, "%d", NumOfSite);//��վ����д���ļ���
		fclose(fp6);
		fp5 = fopen("Ticket.txt", "wb");
		fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
		fclose(fp5);
		free(ticket);
		printf("�����ɣ������������\n");
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
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���վ����Ϣ
	{
		system("cls");
		printf("��ǰû�г�����Ϣ\n�����������");
		_getch();
		site();
	}

	else//�����վ����Ϣ
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);
		if (NumOfSite == 0)//վ����Ϊ0
		{
			system("cls");
			printf("��ǰû�г�����Ϣ\n�����������");
			_getch();
			site();
		}
		else//վ������Ϊ0
		{
			struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
			fp5 = fopen("Ticket.txt", "rb");
			fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
			fclose(fp5);
			system("cls");
			for (int i = 0; i < NumOfSite; i++)
			{
				printf("NO.%d\n", ticket[i].no);
				printf("���վ��%s\n", ticket[i].start);
				printf("�յ�վ��%s\n", ticket[i].destination);
				printf("����ʱ�䣺%s\n", ticket[i].StartTime);
				printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[i].ArriveTime);
				printf("��Ʊ����%d\n", ticket[i].RestOfTicket);
				printf("                                                 \n");
				printf("-------------------------------------------------\n");
				printf("                                                 \n");
			}
			free(ticket);
			printf("�����������");
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
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���վ����Ϣ
	{
		system("cls");
		printf("��ǰû�г�����Ϣ\n�����������");
		_getch();
		site();
	}

	else
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);
		if (NumOfSite == 0)//վ����Ϊ0
		{
			system("cls");
			printf("��ǰû�г�����Ϣ\n�����������");
			_getch();
			site();
		}
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
		fclose(fp5);

		system("cls");
		printf("��ѡ��Ҫ�޸ĵĳ��α��");
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
			printf("û���ҵ��ó�����Ϣ\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				site();
			else
				modify();
		}
		else//�ҵ���Ӧ������Ϣ
		{
			system("cls");
			printf("NO.%d\n", ticket[no - 1].no);
			printf("���վ��%s\n", ticket[no - 1].start);
			printf("�յ�վ��%s\n", ticket[no - 1].destination);
			printf("����ʱ�䣺%s\n", ticket[no - 1].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[no - 1].ArriveTime);
			printf("��Ʊ����%d\n", ticket[no - 1].RestOfTicket);
			printf("\n");
			printf("��ѡ��Ҫ�޸ĵ�����\n");
			printf("************************\n");
			printf("***   1.���վ       ***\n");
			printf("***   2.�յ�վ       ***\n");
			printf("***   3.����ʱ��     ***\n");
			printf("***   4.Ԥ�Ƶ���ʱ�� ***\n");
			printf("***   5.��Ʊ��       ***\n");
			printf("***   6.������һ��   ***\n");
			printf("************************\n");
			int choose = _getch();
			switch (choose)
			{
			case 49:printf("���������վ"); scanf("%s", &ticket[no - 1].start); break;
			case 50:printf("�������յ�վ"); scanf("%s", &ticket[no - 1].destination); break;
			case 51:printf("�����뷢��ʱ��"); scanf("%s", &ticket[no - 1].StartTime); break;
			case 52:printf("������Ԥ�Ƶ���ʱ��"); scanf("%s", &ticket[no - 1].ArriveTime); break;
			case 53:printf("��������Ʊ��"); scanf("%d", &ticket[no - 1].RestOfTicket); break;
			case 54:modify(); break;
			}
			fp5 = fopen("Ticket.txt", "wb");
			fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
			fclose(fp5);
			free(ticket);
			system("cls");
			printf("������ɣ������������");
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
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���վ����Ϣ
	{
		system("cls");
		printf("��ǰû�г�����Ϣ\n�����������");
		_getch();
		site();
	}

	else//��ӹ�վ����Ϣ
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);

		if (NumOfSite == 0)//վ����Ϊ0
		{
			system("cls");
			printf("��ǰû�г�����Ϣ\n�����������");
			_getch();
			site();
		}

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
		fclose(fp5);

		system("cls");
		printf("��ѡ��Ҫɾ���ĳ��α��\n");
		for (int i = 0; i < NumOfSite; i++)
		{
			printf("NO.%d\n", ticket[i].no);
			printf("���վ��%s\n", ticket[i].start);
			printf("�յ�վ��%s\n", ticket[i].destination);
			printf("����ʱ�䣺%s\n", ticket[i].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[i].ArriveTime);
			printf("��Ʊ����%d\n", ticket[i].RestOfTicket);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}

		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfSite; i++)//Ѱ�Ҷ�Ӧ������Ϣ
		{
			if (no == ticket[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("û���ҵ��ó�����Ϣ\n");
			printf("��������������룬��ESC����");
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
			printf("���վ��%s\n", ticket[no - 1].start);
			printf("�յ�վ��%s\n", ticket[no - 1].destination);
			printf("����ʱ�䣺%s\n", ticket[no - 1].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[no - 1].ArriveTime);
			printf("��Ʊ����%d\n", ticket[no - 1].RestOfTicket);
			printf("\n");
			printf("��ȷ��Ҫɾ���ó�����Ϣ��\n");
			printf("�������ȷ�ϣ�ESCȡ��\n");
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
				for (int i = 0; i < NumOfSite; i++)//ɾ�������±��
				{
					ticket[i].no = i + 1;
				}
				fp6 = fopen("NumOfSite.txt", "w");
				fprintf(fp6, "%d", NumOfSite);//��վ����д���ļ���
				fclose(fp6);
				fp5 = fopen("Ticket.txt", "wb");
				fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
				fclose(fp5);
				free(ticket);
				printf("ɾ����ɣ������������\n");
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
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���վ����Ϣ
	{
		system("cls");
		printf("��ǰû�г�����Ϣ\n�����������");
		_getch();
		BackStage();
	}

	else//��ӹ�վ����Ϣ
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);

		if (NumOfSite == 0)//վ����Ϊ0
		{
			system("cls");
			printf("��ǰû�г�����Ϣ\n�����������");
			_getch();
			BackStage();
		}

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
		fclose(fp5);

		system("cls");
		for (int i = 0; i < NumOfSite; i++)
		{
			printf("NO.%d\n", ticket[i].no);
			printf("���վ��%s\n", ticket[i].start);
			printf("�յ�վ��%s\n", ticket[i].destination);
			printf("����ʱ�䣺%s\n", ticket[i].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[i].ArriveTime);
			printf("��Ʊ����%d\n", ticket[i].RestOfTicket);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("��ѡ��Ҫ�����ĳ��α��\n");

		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfSite; i++)//Ѱ�Ҷ�Ӧ������Ϣ
		{
			if (no == ticket[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("û���ҵ��ó�����Ϣ\n");
			printf("��������������룬��ESC����");
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
			printf("�������޸ĵĳ�Ʊ��Ŀ\n");
			scanf("%d", &ticket[no - 1].RestOfTicket);
			fp5 = fopen("Ticket.txt", "wb");
			fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
			fclose(fp5);
			free(ticket);
			system("cls");
			printf("������ɣ������������");
			_getch();
			BackStage();
		}
	}
}