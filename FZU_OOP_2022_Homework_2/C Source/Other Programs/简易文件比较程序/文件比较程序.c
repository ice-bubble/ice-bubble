/*�ļ��Ƚϳ���*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE* fp1, * fp2;
	char x1[2050000] = { 0 }, x2[2050000] = { 0 };
	int line, count, c = 1;
	char file1[98550] = { 0 }, file2[98540] = { 0 };
	char judge;
	printf("�ļ�·������ʾ����\n\nF:\\Github\\FZU_OOP_2022_Homework_2\\dataset1\\ans1.txt\n\n");
	do
	{
		line = count = 0;
		if (c == 1)//�ж��Ƿ��ǵ�һ�αȽ�
		{
			puts("��������Ҫ�Ƚϵ��ļ�1������·�����������ţ���");
			if (!gets(file1))break;
			puts("��������Ҫ�Ƚϵ��ļ�2������·�����������ţ���");
			if (!gets(file2))break;
		}
		else
		{
			puts("��������Ҫ�Ƚϵ��ļ�1������·�����������ţ���������Ctrl+Z��س�����ʹ����һ��������ļ�1����");
			gets(file1);
			puts("��������Ҫ�Ƚϵ��ļ�2������·�����������ţ���������Ctrl+Z��س�����ʹ����һ��������ļ�2����");
			gets(file2);
		}
		fp1 = fopen(file1, "r");
		fp2 = fopen(file2, "r");
		while (fgets(x1, 2050000, fp1))
		{
			fgets(x2, 2050000, fp2);
			if (strcmp(x1, x2))
			{
				printf("Differences on Line %d\n", line);
				count++;
			}
			line++;
		}
		if (count == 1)printf("Total: %d different line.\n", count);
		else if (count > 1)printf("Total: %d different lines.\n", count);
		else if (!count)printf("Total: %d different line.\nThe two files are the same!\n", count);
		fclose(fp1);
		fclose(fp2);
		c++;//�Ƚϴ���+1
		printf("\n�Ƿ�����Ƚ������ļ���(Y/N)");
		scanf("%c%*c", &judge);
	} while (judge == 'Y' || judge == 'y');
	printf("�������岿���ѽ���,");
	system("pause");
	return 0;
}