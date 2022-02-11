#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "IP_Switch_From_Dotted_DEC_To_BIN.cpp"
#include "IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min.cpp"
#include "Protocol_number_Switch_From_HEX_To_DEC.cpp"
#include "Match_in_the_order_of_Rules.cpp"
using namespace std;

class rule
{
public:
	int in(ifstream& fp_rule);//fstream的拷贝（赋值）构造函数是已删除函数，“&”表示是将函数的形参设置为引用类型，防止报错
	void process_chain_table();
	int visit_processed_chain_table(int* flag, int* count, ofstream& fp_out, unsigned int ip0, unsigned int ip1, unsigned int d0, unsigned int d1, unsigned int y);
	rule* next;
	
private:
	char ip0bin[37], ip1bin[37], z0[3], z1[3];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12, x0, x1;
	char x;	
};
int rule::in(ifstream& fp_rule)
{
	if (fp_rule >> x >> ip01 >> x >> ip02 >> x >> ip03 >> x >> ip04 >> x >> ip0wei >> ip11 >> x >> ip12 >> x >> ip13 >> x >> ip14 >> x >> ip1wei >> d01 >> x >> d02 >> d11 >> x >> d12 >> x >> x >> z0[0] >> z0[1] >> x >> x >> x >> z1[0] >> z1[1])return 1;
	else return 0;
}
void rule::process_chain_table()
{
	for (int i = 0; i < 37; i++)
		ip0bin[i] = ip1bin[i] = '\0';
	IP_Switch_From_Dotted_DEC_To_BIN(ip01, ip02, ip03, ip04, ip0bin);//将源IP地址转换为二进制形式储存到链表相应的字符数组中
	IP_Switch_From_Dotted_DEC_To_BIN(ip11, ip12, ip13, ip14, ip1bin);//将目的IP地址转换为二进制形式储存到链表相应的字符数组中
	IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(ip0bin, ip0wei, &ip0max, &ip0min);//将源IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
	IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(ip1bin, ip1wei, &ip1max, &ip1min);//将目的IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
	Protocol_number_Switch_From_HEX_To_DEC(&x0, &x1, z0, z1);//将协议号上下范围分别转换为十进制表示方式存储到链表相应变量中
}
int rule::visit_processed_chain_table(int* flag, int* count, ofstream& fp_out, unsigned int ip0, unsigned int ip1, unsigned int d0, unsigned int d1, unsigned int y)
{
	int* f = flag, * c = count;
	if (rule_match(ip0, ip1, d0, d1, y, ip0min, ip0max, ip1min, ip1max, d01, d02, d11, d12, x0, x1))
	{
		fp_out << *c << endl;
		*f = 1;
		return 0;
	}
	else return 1;
}

int main()
{
	rule* head, * p, * prev;
	ifstream fp_packet; 
	ofstream fp_out;
	char rule_packet[9854] = {};//存储规则集文件的完整路径
	char rule_packet_save[9854] = {};//存储规则集文件的完整路径
	char packet[9854] = {};//存储数据集文件的完整路径
	char packet_save[9854] = {};//存储数据集文件的完整路径
	char output[9855] = {};//存储数据匹配结果文件的完整路径
	char output_save[9855] = {};//存储数据匹配结果文件的完整路径
	char judge[25655] = {};//判断是否结束程序
	unsigned int ip0, ip1, d0, d1, y;//动态存储数据集每条数据
	int count, flag;
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
		head = (rule*)malloc(sizeof(rule));//建立链表头结点
		head->next = NULL;
		prev = head;
		p = (rule*)malloc(sizeof(rule));
		while (p->in(fp_rule))
		{
			p->process_chain_table();//访问并处理规则集链表数据
			/*以下4行代码为建立新链表的过程*/
			prev->next = p;
			p->next = NULL;
			prev = p;
			p = (rule*)malloc(sizeof(rule));
		}
		fp_rule.close();//关闭指定文件	
		ifstream fp_packet(packet_save, ios::in | ios::_Nocreate);
		ofstream fp_out(output_save, ios::out);
		while (fp_packet >> ip0 >> ip1 >> d0 >> d1 >> y)
		{
			for (p = head->next, count = 0, flag = 0; p; p = p->next)
			{
				if (!p->visit_processed_chain_table(&flag, &count, fp_out, ip0, ip1, d0, d1, y))break;
				count++;//计数器，表示当前为第几条规则【规则从0开始编号】
			}
			if (!flag)fp_out << "-1\n";
		}
		fp_packet.close();
		fp_out.close();
		long end_time = clock();//记录关闭文件之后的时间为结束时间
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
		double time = 1.0 * (end_time - start_time) / 1000;//计算匹配过程的用时
		cout << "本次匹配用时：" << time << "s" << endl;
		cout << "\n本次数据集和规则集的匹配已完成，匹配结果已输出到指定文件，如需继续匹配其他数据集和规则集，请直接按回车键或输入任意内容后回车，结束程序请输入Ctrl+Z之后回车" << endl;
	} while (gets_s(judge));
	system("pause");
	return 0;
}