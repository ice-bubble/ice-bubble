#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IP_Switch_From_Dotted_DEC_To_BIN.c"
#include "IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min.c"
#include "Protocol_number_Switch_From_HEX_To_DEC.c"
#include "Match_in_the_order_of_Rules.c"

struct rule
{
	char z0[3], z1[3];
	char ip0bin[37], ip1bin[37];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12, x0, x1;
	struct rule* next;
};

int main()
{
	FILE* fp_rule, * fp_out, * fp_packet;
	struct rule* head, * p, * prev;
	char input[9854] = { 0 };//存储规则集文件的完整路径
	char packet[9854] = { 0 };//存储数据集文件的完整路径
	char output[9855] = { 0 };//存储数据匹配结果文件的完整路径
	char judge[25655] = { 0 };//判断是否结束程序
	int i, count, flag, c = 0;
	unsigned int ip0, ip1, d0, d1, x;
	printf("文件路径输入示例：\n\nF:\\Github\\FZU_OOP_2022_Homework_2\\dataset1\\rule1.txt\n\n");
	do
	{
		c++;
		if (c == 1)
		{
			printf("请输入规则集文件的完整路径（可含空格，不含引号）：\n");
			if (!gets(input))break;
			printf("请输入数据集文件的完整路径（可含空格，不含引号）：\n");
			if (!gets(packet))break;
			printf("请输入数据匹配结果文件的完整路径，若文件不存在，则会自动新建文件（可含空格，不含引号）：\n");
			if (!gets(output))break;
		}
		else
		{
			printf("请输入规则集文件的完整路径（可含空格，不含引号）【若不输入（输入Ctrl+Z后回车）则使用上一次输入的规则集文件】：\n");
			gets(input);
			printf("请输入数据集文件的完整路径（可含空格，不含引号）【若不输入（输入Ctrl+Z后回车）则使用上一次输入的数据集文件】：\n");
			gets(packet);
			printf("请输入数据匹配结果文件的完整路径，若文件不存在，则会自动新建文件【若不输入（输入Ctrl+Z后回车）则使用上一次输入的匹配结果输出文件】（可含空格，不含引号）：\n");
			gets(output);
		}
		fp_rule = fopen(input, "r");//“r”表示以只读模式打开文件
		head = (struct rule*)malloc(sizeof(struct rule));//建立链表头结点
		head->next = NULL;
		prev = head;
		p = (struct rule*)malloc(sizeof(struct rule));
		while ((fscanf(fp_rule, "@%d%*c%d%*c%d%*c%d%*c%d", &p->ip01, &p->ip02, &p->ip03, &p->ip04, &p->ip0wei)) != EOF)//从文件中按行读取相应类型数据，EOF表示读取到文件末尾后结束循环
		{
			fscanf(fp_rule, "%d%*c%d%*c%d%*c%d%*c%d", &p->ip11, &p->ip12, &p->ip13, &p->ip14, &p->ip1wei);
			fscanf(fp_rule, "%d%*c%*c%*c%d", &p->d01, &p->d02);
			fscanf(fp_rule, "%d%*c%*c%*c%d", &p->d11, &p->d12);
			fscanf(fp_rule, "%*c%*c%*c%c%c%*c%*c%*c%c%c%*c", &p->z0[0], &p->z0[1], &p->z1[0], &p->z1[1]);
			for (i = 0; i < 37; i++)//初始化链表字符数组
				p->ip0bin[i] = p->ip1bin[i] = '\0';
			ip_swap_to_bin(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//将源IP地址转换为二进制形式储存到链表相应的字符数组中
			ip_swap_to_bin(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//将目的IP地址转换为二进制形式储存到链表相应的字符数组中
			CIDR_ip_swap_to_max_and_min(p->ip0bin, p->ip0wei, &p->ip0max, &p->ip0min);//将源IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
			CIDR_ip_swap_to_max_and_min(p->ip1bin, p->ip1wei, &p->ip1max, &p->ip1min);//将目的IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
			xieyi_swap_to_dec(&p->x0, &p->x1, p->z0, p->z1);//将协议号上下范围分别转换为十进制表示方式存储到链表相应变量中
			/*以下4行代码为建立新链表的过程*/
			prev->next = p;
			p->next = NULL;
			prev = p;
			p = (struct rule*)malloc(sizeof(struct rule));
		}
		fclose(fp_rule);//关闭文件指针对应文件【rule】
		fp_packet = fopen(packet, "r");
		fp_out = fopen(output, "w+");//“w+”表示打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
		while ((fscanf(fp_packet, "%d%d%d%d%d", &ip0, &ip1, &d0, &d1, &x)) != EOF)
		{
			for (p = head->next, count = 0, flag = 0; p; p = p->next)//按建立顺序访问链表
			{
				if (rule_match(ip0, ip1, d0, d1, x, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
				{
					fprintf(fp_out, "%d\n", count);
					flag = 1;
					break;
				}
				count++;//计数器，表示当前为第几条规则【规则从0开始编号】
			}
			if (!flag)fprintf(fp_out, "-1\n");
		}
		fclose(fp_out);//关闭文件指针对应文件【res】
		for (p = head; p; head = p->next, free(p))//完成任务，释放访问和连接链表的指针所占用的内存
		{
			p = head;
			if (!p)
			{
				free(p);
				free(head);
				break;
			}
		}
		printf("\n本次数据集和规则集的匹配已完成，匹配结果已输出到指定文件，如需继续匹配其他数据集和规则集，请直接按回车键或输入任意内容后回车，结束程序请输入Ctrl+Z之后回车\n");
	} while (gets(judge));
	return 0;
}