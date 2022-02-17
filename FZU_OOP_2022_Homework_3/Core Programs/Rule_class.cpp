#include "IP_Switch_From_Dotted_DEC_To_BIN.cpp"
#include "IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min.cpp"
#include "Protocol_number_Switch_From_HEX_To_DEC.cpp"
#include "Process_Rule_class.cpp"
#include "Match_in_the_order_of_Rules.cpp"
using namespace std;

class rule
{
public:
	int in(ifstream& fp_rule);//fstream�Ŀ�������ֵ�����캯������ɾ����������&����ʾ�ǽ��������β�����Ϊ�������ͣ���ֹ����
	class rule* create_chain_table(ifstream& fp_rule);
	void process_chain_table(rule* p);
	void visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out);
	void process_rule_class(class rule** p, unsigned int ip0min, unsigned int ip0max, unsigned int ip1min, unsigned int ip1max, int d01, int d02, int d11, int d12, int x0, int x1);

private:
	unsigned int num;//��ʾ������
	char ip0bin[37], ip1bin[37], z0[3], z1[3];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01, ip02, ip03, ip04, ip0wei;
	int ip11, ip12, ip13, ip14, ip1wei;
	int d01, d02, d11, d12, x0, x1;
	char x;
	rule* next;
	rule* next_arr[101];//���ڷ�������������
};
class rule* pr[101];//���ڴ洢�����ĸ��������һ�����
class rule* head;
int rule::in(ifstream& fp_rule)
{
	if (fp_rule >> x >> ip01 >> x >> ip02 >> x >> ip03 >> x >> ip04 >> x >> ip0wei >> ip11 >> x >> ip12 >> x >> ip13 >> x >> ip14 >> x >> ip1wei >> d01 >> x >> d02 >> d11 >> x >> d12 >> x >> x >> z0[0] >> z0[1] >> x >> x >> x >> z1[0] >> z1[1])return 1;
	else return 0;
}
class rule* rule::create_chain_table(ifstream& fp_rule)
{
	rule* p, * prev;
	unsigned int number = 0;
	head = new(rule);
	head->next = NULL;
	prev = head;
	for (int i = 0; i < 101; i++)
	{
		head->next_arr[i] = NULL;
		pr[i] = head;
	}
	do
	{
		p = new(rule);
		p->next = NULL;
		prev->next = p;
		prev = p;
		p->num = number++;//��ʾ������
	} while (p->in(fp_rule));//����������������
	return head->next;//headΪ����ͷ�ڵ㣬head->next���Ǵ������ݵĵ�һ������
}
void rule::process_chain_table(rule* p)//���ʲ����������������
{
	while (p->next)
	{
		for (int i = 0; i < 37; i++)//��ʼ�������ַ�����
			p->ip0bin[i] = p->ip1bin[i] = '\0';
		IP_Switch_From_Dotted_DEC_To_BIN(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//��ԴIP��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
		IP_Switch_From_Dotted_DEC_To_BIN(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//��Ŀ��IP��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
		IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(p->ip0bin, p->ip0wei, &p->ip0max, &p->ip0min);//��ԴIP��ַ��CIDR��ַ������IP��ַ����СIP��ַ�ֱ���ʮ���Ʊ�ʾ��ʽ�洢���������Ӧ������
		IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(p->ip1bin, p->ip1wei, &p->ip1max, &p->ip1min);//��Ŀ��IP��ַ��CIDR��ַ������IP��ַ����СIP��ַ�ֱ���ʮ���Ʊ�ʾ��ʽ�洢���������Ӧ������
		Protocol_number_Switch_From_HEX_To_DEC(&p->x0, &p->x1, p->z0, p->z1);//��Э������·�Χ�ֱ�ת��Ϊʮ���Ʊ�ʾ��ʽ�洢��������Ӧ������
		process_rule_class(&p, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1);
		p = p->next;
	}
}
void rule::process_rule_class(class rule** p, unsigned int ip0min, unsigned int ip0max, unsigned int ip1min, unsigned int ip1max, int d01, int d02, int d11, int d12, int x0, int x1)
{
	int oz;
	if (d11 >= 0 && d11 <= 50 && d12 >= 0 && d12 <= 50)oz = 2;
	else if (d11 >= 51 && d11 <= 100 && d12 >= 51 && d12 <= 100)oz = 4;
	else if (d11 >= 101 && d11 <= 150 && d12 >= 101 && d12 <= 150)oz = 6;
	else if (d11 >= 151 && d11 <= 200 && d12 >= 151 && d12 <= 200)oz = 8;
	else oz = 10;
	(*p)->next_arr[oz] = NULL;
	pr[oz]->next_arr[oz] = *p;
	pr[oz] = *p;
}
void rule::visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out)
{
	unsigned int ip0, ip1, d0, d1, y, flag, oz;
	while (fp_packet >> ip0 >> ip1 >> d0 >> d1 >> y)
	{
		if (d1 >= 0 && d1 <= 50)oz = 2;
		else if (d1 <= 100)oz = 4;
		else if (d1 <= 150)oz = 6;
		else if (d1 <= 200)oz = 8;
		else oz = 10;
		for (p = head, flag = 0; p; p = p->next_arr[oz])
		{
			if (rule_match(ip0, ip1, d0, d1, y, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
			{
				fp_out << p->num << endl;
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			for (p = head, flag = 0; p; p = p->next_arr[10])
			{
				if (rule_match(ip0, ip1, d0, d1, y, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
				{
					fp_out << p->num << endl;
					flag = 1;
					break;
				}
			}
		}
		if (!flag)fp_out << "-1\n";
	}
}