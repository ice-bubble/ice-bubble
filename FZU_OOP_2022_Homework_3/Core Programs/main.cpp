#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Rule_class.cpp"
using namespace std;

int main()
{
	rule* head, * p;
	char rule_packet[9854] = {};//存储规则集文件的完整路径
	char rule_packet_save[9854] = {};//存储规则集文件的完整路径
	char packet[9854] = {};//存储数据集文件的完整路径
	char packet_save[9854] = {};//存储数据集文件的完整路径
	char output[9855] = {};//存储数据匹配结果文件的完整路径
	char output_save[9855] = {};//存储数据匹配结果文件的完整路径
	char judge[25655] = {};//判断是否结束程序
	int c = 0;//执行程序的次数
	do
	{
		c++;
		if (c == 1)
		{
			cout << "请输入规则集文件的完整路径（可含空格，不含引号）：" << endl;
			if (!gets_s(rule_packet))break;
			else strcpy(rule_packet_save, rule_packet);
			cout << "请输入数据集文件的完整路径（可含空格，不含引号）：" << endl;
			if (!gets_s(packet))break;
			else strcpy(packet_save, packet);
			cout << "请输入数据匹配结果文件的完整路径，若文件不存在，则会自动新建文件（可含空格，不含引号）：" << endl;
			if (!gets_s(output))break;
			else strcpy(output_save, output);
		}
		else
		{
			cout << "请输入规则集文件的完整路径（可含空格，不含引号）【若不输入（输入Ctrl+Z后回车）则使用上一次输入的规则集文件】：" << endl;
			if (gets_s(rule_packet))strcpy(rule_packet_save, rule_packet);
			cout << "请输入数据集文件的完整路径（可含空格，不含引号）【若不输入（输入Ctrl+Z后回车）则使用上一次输入的数据集文件】：" << endl;
			if (gets_s(packet))strcpy(packet_save, packet);
			cout << "请输入数据匹配结果文件的完整路径，若文件不存在，则会自动新建文件【若不输入（输入Ctrl+Z后回车）则使用上一次输入的匹配结果输出文件】（可含空格，不含引号）：" << endl;
			if (gets_s(output))strcpy(output_save, output);
		}
		long start_time = clock();//记录输入数据之后的时间为开始时间
		ifstream fp_rule(rule_packet_save, ios::in | ios::_Nocreate);
		head = (rule*)malloc(sizeof(rule));
		p = head->create_chain_table(fp_rule);//p指向第一个存有数据的链表
		fp_rule.close();//关闭指定文件
		p->process_chain_table(p);//访问并处理规则集链表数据
		ifstream fp_packet(packet_save, ios::in | ios::_Nocreate);
		ofstream fp_out(output_save, ios::out);
		p->visit_processed_chain_table(p, fp_packet, fp_out);//访问处理后的规则集链表数据
		fp_packet.close();
		fp_out.close();
		long end_time = clock();//记录关闭文件之后的时间为结束时间
		double time = 1.0 * (end_time - start_time) / 1000;
		cout << "本次匹配用时：" << time << "s" << endl;
		cout << "\n本次数据集和规则集的匹配已完成，匹配结果已输出到指定文件，如需继续匹配其他数据集和规则集，请直接按回车键或输入任意内容后回车，结束程序请输入Ctrl+Z之后回车" << endl;
	} while (gets_s(judge));
	system("pause");
	return 0;
}