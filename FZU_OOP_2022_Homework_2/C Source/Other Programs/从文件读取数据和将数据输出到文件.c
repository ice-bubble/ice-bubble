/*从文件读取数据和将数据输出到文件*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp, * out;
	char z[9854] = {};
	char input[2022] = {};//存储数据来源文件的完整路径
	char output[2022] = {};//存储数据输出文件的完整路径
	int i;
	printf("请输入数据来源文件的完整路径：\n");
	gets(input);
	printf("请输入数据输出文件的完整路径：\n");
	gets(output);
	fp = fopen(input, "r");//“r”表示以只读模式打开文件
	out = fopen(output, "w+");//“w+”表示打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
	while ((fscanf(fp, "%s", z)) != EOF)//从文件中按行读取相应类型数据，EOF表示读取到文件末尾后结束循环
	{
		fprintf(out, "%s\n", z);//将相应类型数据输出到文件
	}
	fclose(fp);//关闭文件指针对应文件
	fclose(out);
	system("pause");
	return 0;
}