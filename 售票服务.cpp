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
int IdOfPassenger;
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
	printf("***   3.Ԥ����Ʊ    ***\n");
	printf("***   4.�˶���Ʊ    ***\n");
	printf("***   5.������һ��    ***\n");
	printf("***   ��esc�˳�����   ***\n");
	printf("*************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:pview(); break;
	case 50:ViewMine(); break;
	case 51:subscribe();  break;
	case 52:cancel(); break;
	case 53:main(); break;
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
	case 49:PassengerLogin(); break;
	case 50:PassengerLogon(); break;
	case 51:main();
	}
}

void PassengerLogon()
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
		passenger[0].NumOfTicket = 0;
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
		passenger[NumOfPassenger].NumOfTicket = 0;
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
void PassengerLogin()//�˻���¼
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
			PassengerLogin();
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
						IdOfPassenger = m;
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
void subscribe()
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
		printf("��ǰû�п�Ԥ���ĳ���\n�����������");
		_getch();
		Ticketing();
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
		printf("��ѡ��ҪԤ���ĳ��α��\n");
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
				Ticketing();
			else
			{
				subscribe();
			}
		}
		else
		{
			system("cls");
			printf("��ȷ��ҪԤ���ó��γ�Ʊ��\n");
			printf("NO.%d\n", ticket[no - 1].no);
			printf("���վ��%s\n", ticket[no - 1].start);
			printf("�յ�վ��%s\n", ticket[no - 1].destination);
			printf("����ʱ�䣺%s\n", ticket[no - 1].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[no - 1].ArriveTime);
			printf("��Ʊ����%d\n", ticket[no - 1].RestOfTicket);
			printf("\n");
			if (ticket[no - 1].RestOfTicket <= 0)
			{
				system("cls");
				printf("�Բ��𣬸ó��γ�Ʊ�ѱ�Ԥ����\n");
				printf("�����������");
				_getch();
				Ticketing();
			}
			printf("�������ȷ�ϣ�ESCȡ��\n");
			int esc = _getch();
			if (esc == 27)
			{
				Ticketing();
			}
			else
			{
				fp4 = fopen("NumOfPassenger.txt", "r");
				fscanf(fp4, "%d", &NumOfPassenger);//���ļ���ȡ�˿�����
				fclose(fp4);

				struct passenger* passenger = (struct passenger*)malloc(sizeof(struct passenger) * NumOfPassenger);
				fp2 = fopen("Passenger.txt", "rb");
				fread(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���ļ��ж�ȡ�˿ͽṹ��
				fclose(fp2);
				passenger[IdOfPassenger].NoOfTicket[passenger[IdOfPassenger].NumOfTicket] = ticket[no - 1].no;
				passenger[IdOfPassenger].NumOfTicket++;
				ticket[no - 1].RestOfTicket--;
				fp5 = fopen("Ticket.txt", "wb");
				fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
				fclose(fp5);
				free(ticket);
				fp2 = fopen("Passenger.txt", "wb");
				fwrite(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���˿ͽṹ��д���ļ�
				fclose(fp2);
				free(passenger);
				printf("�����ɣ������������");
				Ticketing();
			}

		}
	}
}
void ViewMine()
{
	fp4 = fopen("NumOfPassenger.txt", "r");
	fscanf(fp4, "%d", &NumOfPassenger);//���ļ���ȡ�˿�����
	fclose(fp4);

	struct passenger* passenger = (struct passenger*)malloc(sizeof(struct passenger) * NumOfPassenger);
	fp2 = fopen("Passenger.txt", "rb");
	fread(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���ļ��ж�ȡ�˿ͽṹ��
	fclose(fp2);

	if (passenger[IdOfPassenger].NumOfTicket == 0)
	{
		system("cls");
		printf("��δ��ѯ�����ĳ�ƱԤ����Ϣ\n");
		printf("�����������");
		_getch();
		free(passenger);
		Ticketing();
	}
	else
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
		fclose(fp5);

		system("cls");
		printf("����%d��Ԥ���ĳ�Ʊ\n", passenger[IdOfPassenger].NumOfTicket);
		for (int i = 0; i < passenger[IdOfPassenger].NumOfTicket; i++)
		{
			printf("NO.%d\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].no);
			printf("���վ��%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].start);
			printf("�յ�վ��%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].destination);
			printf("����ʱ�䣺%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].ArriveTime);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("�����������");
		free(ticket);
		free(passenger);
		_getch();
		Ticketing();
	}
}

void cancel()
{
	fp4 = fopen("NumOfPassenger.txt", "r");
	fscanf(fp4, "%d", &NumOfPassenger);//���ļ���ȡ�˿�����
	fclose(fp4);

	struct passenger* passenger = (struct passenger*)malloc(sizeof(struct passenger) * NumOfPassenger);
	fp2 = fopen("Passenger.txt", "rb");
	fread(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���ļ��ж�ȡ�˿ͽṹ��
	fclose(fp2);

	if (passenger[IdOfPassenger].NumOfTicket == 0)
	{
		system("cls");
		printf("��δ��ѯ�����ĳ�ƱԤ����Ϣ\n");
		printf("�����������");
		free(passenger);
		_getch();
		Ticketing();
	}
	else
	{
		fp6 = fopen("NumOfSite.txt", "r");
		fscanf(fp6, "%d", &NumOfSite);//���ļ���ȡ��Ʊ��
		fclose(fp6);

		struct ticket* ticket = (struct ticket*)malloc(sizeof(struct ticket) * NumOfSite);
		fp5 = fopen("Ticket.txt", "rb");
		fread(ticket, sizeof(struct ticket), NumOfSite, fp5);//���ļ��ж�ȡ��Ʊ�ṹ��
		fclose(fp5);

		system("cls");
		for (int i = 0; i < passenger[IdOfPassenger].NumOfTicket; i++)
		{
			printf("NO.%d\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].no);
			printf("���վ��%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].start);
			printf("�յ�վ��%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].destination);
			printf("����ʱ�䣺%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[passenger[IdOfPassenger].NoOfTicket[i] - 1].ArriveTime);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("��ѡ��Ҫ�˶��ĳ��α��");
		int no;
		int index;//���³��α�Ŵ�����NoOfTicket�е�λ��
		scanf("%d", &no);
		int flag = 0;
		for (int i = 0; i < passenger[IdOfPassenger].NumOfTicket; i++)
		{
			if (passenger[IdOfPassenger].NoOfTicket[i] == no)
			{
				flag = 1;
				index = i;
				break;
			}
		}
		if (flag == 0)
		{
			system("cls");
			printf("�Բ�����û��Ԥ���ó���\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				Ticketing();
			else
				cancel();
		}
		else
		{
			system("cls");
			printf("NO.%d\n", ticket[no - 1].no);
			printf("���վ��%s\n", ticket[no - 1].start);
			printf("�յ�վ��%s\n", ticket[no - 1].destination);
			printf("����ʱ�䣺%s\n", ticket[no - 1].StartTime);
			printf("Ԥ�Ƶ���ʱ�䣺%s\n", ticket[no - 1].ArriveTime);
			printf("\n");
			printf("��ȷ��Ҫɾ���ó���Ԥ����Ϣ��\n");
			printf("�������ȷ������ESCȡ��\n");
			int esc = _getch();
			if (esc == 27)
				Ticketing();
			else
			{
				for (int i = index; i < passenger[IdOfPassenger].NumOfTicket - 1; i++)
				{
					passenger[IdOfPassenger].NoOfTicket[i] = passenger[IdOfPassenger].NoOfTicket[i + 1];
				}
				passenger[IdOfPassenger].NumOfTicket--;
				ticket[no - 1].RestOfTicket++;
			}
			fp5 = fopen("Ticket.txt", "wb");
			fwrite(ticket, sizeof(struct ticket), NumOfSite, fp5);//����Ʊ�ṹ��д���ļ�
			fclose(fp5);
			free(ticket);
			fp2 = fopen("Passenger.txt", "wb");
			fwrite(passenger, sizeof(struct passenger), NumOfPassenger, fp2);//���˿ͽṹ��д���ļ�
			fclose(fp2);
			free(passenger);
			printf("ɾ���ɹ��������������");
			_getch();
			Ticketing();
		}
	}
}
