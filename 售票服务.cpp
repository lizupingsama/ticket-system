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
extern FILE* fp2;
extern FILE* fp2;
extern FILE* fp4;
extern FILE* fp4;
extern FILE* fp5;//Ticket.txt
extern FILE* fp6;//NumOfSite.txt
extern int NumOfManager;
extern int NumOfPassenger;
extern int NumOfSite;
void Ticketing()
{
	system("cls");
	printf(" ��ѡ������Ҫ�ķ���\n");
	printf("*************************\n");
	printf("***   1.��β�ѯ      ***\n");
	printf("***   2.�鿴�ҵĳ�Ʊ  ***\n");
	printf("***   3.������һ��    ***\n");
	printf("***   ��esc�˳�����   ***\n");
	printf("*************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:pview(); break;
	case 50:; break;
	case 51:PassengerLog();  break;
	case 27:exit(0);
	}
}
void PassengerLog()
{
	system("cls");
	printf("     ��ӭʹ����Ʊϵͳ\n");
	printf("**************************\n");
	printf("***    1.��¼�����˻�  ***\n");
	printf("***    2.ע�����˻�    ***\n");
	printf("***    3.������һ��    ***\n");
	printf("**************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:plogin(); break;
	case 50:plogon(); break;
	case 51:main();
	}
}

void plogon()//��λ�˿��˻�ע��
{
	if ((fp4 = fopen("NumOfPassenger.txt", "r")) == NULL)
	{
		fp4 = fopen("NumOfPassenger.txt", "w");
		fclose(fp4);
	}
	fp4 = fopen("NumOfPassenger.txt", "rb");
	fseek(fp4, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp4);//����ļ�����
	fseek(fp4, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)//��һ���˿ʹ����˺�
	{
		char key[20];//���ڴ洢�ٴ����������
		system("cls");
		struct passenger* passenger = (struct passenger*)malloc(sizeof(struct passenger));
		printf("�봴��һ���˺�\n");
		scanf("%s", &passenger[0].id);
		printf("��������������\n");
		scanf("%s", &passenger[0].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(passenger[0].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &passenger[0].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(passenger[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfPassenger++;
		fp4 = fopen("NumOfPassenger.txt", "w");//����NumOfPassenger.txt
		fprintf(fp4, "%d", NumOfPassenger);//���˿�����д���ļ���
		fclose(fp4);
		fp2 = fopen("Passenger.txt", "wb");
		fwrite(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���˿ͽṹ��д���ļ�
		fclose(fp2);
		free(passenger);
		system("cls");
		printf("�����˻��ɹ�\n����������ص�¼����");
		_getch();
		PassengerLog();
	}
	else//�����˿ʹ����˺�
	{
		system("cls");
		fp4 = fopen("NumOfPassenger.txt", "r");
		fscanf(fp4, "%d", &NumOfPassenger);//���ļ���ȡ�˿�����
		fclose(fp4);

		struct passenger* passenger = (struct passenger*)malloc(sizeof(struct passenger) * NumOfPassenger);
		fp2 = fopen("Passenger.txt", "rb");
		fread(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���ļ��ж�ȡ�˿ͽṹ��
		fclose(fp2);

		passenger = (struct passenger*)realloc(passenger, sizeof(struct passenger) * (NumOfPassenger + 1));
		//�˿ͽṹ������һ����λ

		char key[20];//���ڴ洢�ٴ����������
		printf("�봴��һ���˺�\n");
		scanf("%s", &passenger[NumOfPassenger].id);
		for (int i = 0; i < NumOfPassenger; i++)
		{
			if (strcmp(passenger[NumOfPassenger].id, passenger[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("�����˺ţ�����������");
					scanf("%s", &passenger[NumOfPassenger].id);
					for (int n = 0; n < NumOfPassenger; n++)
					{
						if (strcmp(passenger[NumOfPassenger].id, passenger[n].id) == 0)
							break;
						if (n == NumOfPassenger - 1)
							flag = 0;
					}
				}
				break;
			}
		}
		printf("��������������\n");
		scanf("%s", &passenger[NumOfPassenger].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(passenger[NumOfPassenger].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &passenger[NumOfPassenger].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(passenger[NumOfPassenger].password, key) == 0)
					flag = 0;
			}
		}
		printf("�����˻��ɹ�\n����������ص�¼����");
		NumOfPassenger++;
		fp4 = fopen("NumOfPassenger.txt", "w");
		fprintf(fp4, "%d", NumOfPassenger);//���˿�����д���ļ���
		fclose(fp4);
		fp2 = fopen("Passenger.txt", "wb");
		fwrite(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//������д��˿��ļ���
		fclose(fp2);
		free(passenger);
		_getch();
		system("cls");
		PassengerLog();
	}
}
void plogin()//�˻���¼
{
	char id[20];
	char password[20];
	system("cls");
	printf("�������˺�\n");
	scanf("%s", &id);
	printf("����������\n");
	scanf("%s", &password);

	if ((fp4 = fopen("NumOfPassenger.txt", "r")) == NULL)
	{
		fp4 = fopen("NumOfPassenger.txt", "w");
		fclose(fp4);
	}
	fp4 = fopen("NumOfPassenger.txt", "rb");
	fseek(fp4, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp4);//����ļ�����
	fseek(fp4, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)
	{
		system("cls");
		printf("��������˺Ż����������������������,ESC����");
		int esc = _getch();
		if (esc == 27)
		{
			PassengerLog();
		}
		else
		{
			plogin();
		}
	}

	fp4 = fopen("NumOfPassenger.txt", "r");
	fscanf(fp4, "%d", &NumOfPassenger);//���ļ���ȡ�˿�����
	fclose(fp4);

	struct passenger* passenger = (struct passenger*)malloc(sizeof(struct passenger) * NumOfPassenger);
	fp2 = fopen("Passenger.txt", "rb");
	fread(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���ļ��ж�ȡ�˿ͽṹ��
	fclose(fp2);
	int flag = 1;
	while (flag)
	{
		for (int i = 0; i < NumOfPassenger; i++)
		{
			if (strcmp(id, passenger[i].id) == 0)
			{
				for (int m = 0; m < NumOfPassenger; m++)
				{
					if (strcmp(password, passenger[m].password) == 0)
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
				PassengerLog();
			system("cls");
			printf("�������˺�\n");
			scanf("%s", &id);
			printf("����������\n");
			scanf("%s", &password);
		}
	}
	Ticketing();
}
void pview()
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
		Ticketing();
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
			Ticketing();
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
			printf("�����������");
			_getch();
			Ticketing();
		}
	}
}
