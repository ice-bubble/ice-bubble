#include "IP_Switch_From_Dotted_DEC_To_BIN.cpp"
#include "IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min.cpp"
#include "Protocol_number_Switch_From_HEX_To_DEC.cpp"
#include "Process_Rule_class.cpp"
#include "Match_in_the_order_of_Rules.cpp"
using namespace std;

class rule
{
public:
	int in(ifstream& fp_rule);//fstream的拷贝（赋值）构造函数是已删除函数，“&”表示是将函数的形参设置为引用类型，防止报错
	class rule* create_chain_table(ifstream& fp_rule);
	void process_chain_table(rule* p);
	void visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out);
	class rule* Process_Rule_class(rule* p, unsigned int ip0min, unsigned int ip0max, unsigned int ip1min, unsigned int ip1max, int d01, int d02, int d11, int d12, int x0, int x1);

private:
	unsigned int num;//表示规则编号
	char ip0bin[37], ip1bin[37], z0[3], z1[3];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01, ip02, ip03, ip04, ip0wei;
	int ip11, ip12, ip13, ip14, ip1wei;
	int d01, d02, d11, d12, x0, x1;
	char x;
	rule* next;
	rule* next_arr[101];//用于分类后的链表连接
};
rule* h[101];//全局变量，用于存储分类后的各类规则集头结点
rule* point[101];
rule* pr[101];
int rule::in(ifstream& fp_rule)
{
	if (fp_rule >> x >> ip01 >> x >> ip02 >> x >> ip03 >> x >> ip04 >> x >> ip0wei >> ip11 >> x >> ip12 >> x >> ip13 >> x >> ip14 >> x >> ip1wei >> d01 >> x >> d02 >> d11 >> x >> d12 >> x >> x >> z0[0] >> z0[1] >> x >> x >> x >> z1[0] >> z1[1])return 1;
	else return 0;
}
class rule* rule::create_chain_table(ifstream& fp_rule)
{

	rule* head, * p, * prev;
	unsigned int number = 0;
	head = new(rule);
	head->next = NULL;
	prev = head;
	do
	{
		p = new(rule);
		p->next = NULL;
		prev->next = p;
		prev = p;
		p->num = number++;//表示规则编号
	} while (p->in(fp_rule));//向链表中输入数据
	return head->next;//head为链表头节点，head->next才是存有数据的第一个链表
}
void rule::process_chain_table(rule* p)//访问并处理规则集链表数据
{
	while (p->next)
	{
		for (int i = 0; i < 37; i++)//初始化链表字符数组
			p->ip0bin[i] = p->ip1bin[i] = '\0';
		IP_Switch_From_Dotted_DEC_To_BIN(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//将源IP地址转换为二进制形式储存到链表相应的字符数组中
		IP_Switch_From_Dotted_DEC_To_BIN(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//将目的IP地址转换为二进制形式储存到链表相应的字符数组中
		IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(p->ip0bin, p->ip0wei, &p->ip0max, &p->ip0min);//将源IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
		IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(p->ip1bin, p->ip1wei, &p->ip1max, &p->ip1min);//将目的IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
		Protocol_number_Switch_From_HEX_To_DEC(&p->x0, &p->x1, p->z0, p->z1);//将协议号上下范围分别转换为十进制表示方式存储到链表相应变量中
		Process_Rule_class(p, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1);
		p = p->next;
	}
}
void rule::visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out)
{
	unsigned int ip0, ip1, d0, d1, y, flag;
	rule* head = p;//存放第一个结点的指针
	while (fp_packet >> ip0 >> ip1 >> d0 >> d1 >> y)
	{
		for (p = head, flag = 0; p->next; p = p->next)
		{
			if (rule_match(ip0, ip1, d0, d1, y, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
			{
				fp_out << p->num << endl;
				flag = 1;
				break;
			}
		}
		if (!flag)fp_out << "-1\n";
	}
}