#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
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
void FileManager(struct manager* manager)//������Ա�ṹ��д���ļ�����
{
	fp1 = fopen("Manager.txt", "wb");
	fwrite(manager, sizeof(struct manager), NumOfManager, fp1);
	fclose(fp1);
}