/*文件比较程序*/


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
	printf("文件路径输入示例：\n\nF:\\Github\\FZU_OOP_2022_Homework_2\\dataset1\\ans1.txt\n\n");
	do
	{
		line = count = 0;
		if (c == 1)//判断是否是第一次比较
		{
			puts("请输入需要比较的文件1的完整路径（不含引号）：");
			if (!gets(file1))break;
			puts("请输入需要比较的文件2的完整路径（不含引号）：");
			if (!gets(file2))break;
		}
		else
		{
			puts("请输入需要比较的文件1的完整路径（不含引号）【若输入Ctrl+Z后回车，则使用上一次输入的文件1】：");
			gets(file1);
			puts("请输入需要比较的文件2的完整路径（不含引号）【若输入Ctrl+Z后回车，则使用上一次输入的文件2】：");
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
		c++;//比较次数+1
		printf("\n是否继续比较其他文件？(Y/N)");
		scanf("%c%*c", &judge);
	} while (judge == 'Y' || judge == 'y');
	printf("程序主体部分已结束,");
	system("pause");
	return 0;
}