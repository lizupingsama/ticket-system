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
extern int NumOfManager;
extern int NumOfPassenger;
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
	case 49:; break;
	case 50:; break;
	case 51:ManagerLog();  break;
	case 27:exit(0);
	}
}
void logon()//����Ա�˻�ע��
{
	if ( (fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3=fopen("NumOfManager.txt", "w");
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

		manager = (struct manager*)realloc(manager, sizeof(struct manager) * (NumOfManager+1));
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
					for ( int n = 0; n < NumOfManager; n++)
					{
						if (strcmp(manager[NumOfManager].id, manager[n].id) == 0)
							break;
						if (n == NumOfManager-1)
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
