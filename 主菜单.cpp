#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<标头.h>
int NumOfManager;
int NumOfPassenger;
int NumOfSite;
 FILE* fp1;//Manager.txt
 FILE* fp2;//Passenger.txt
 FILE* fp3;//NumOfManager.txt
 FILE* fp4;//NumOfPassenger.txt
 FILE* fp5;//Ticket.txt
 FILE* fp6;//NumOfSite.txt
 FILE* fp7;
int main()
{
	system("cls");
	printf("请选择您需要的服务\n");
	printf("**********************\n");
	printf("***   1.售票服务   ***\n");
	printf("***   2.后台管理   ***\n");
	printf("***    按esc退出   ***\n");
	printf("**********************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:PassengerLog(); break;
	case 50:ManagerLog(); break;
	case 27:exit(0);
	}
}