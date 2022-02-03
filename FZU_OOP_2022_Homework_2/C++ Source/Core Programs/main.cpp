#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "IP_Switch_From_Dotted_DEC_To_BIN.cpp"
#include "IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min.cpp"
#include "Protocol_number_Switch_From_HEX_To_DEC.cpp"
#include "Match_in_the_order_of_Rules.cpp"
using namespace std;

class rule
{
public:
	int in(ifstream& fp_rule);//fstream�Ŀ�������ֵ�����캯������ɾ����������&����ʾ�ǽ��������β�����Ϊ�������ͣ���ֹ����
	class rule* create_chain_table(ifstream& fp_rule);
	void visit_chain_table(rule* p);
	void visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out);
	
private:
	char ip0bin[37], ip1bin[37], z0[3], z1[3];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12, x0, x1;
	char x;
	rule* next;
};
int rule::in(ifstream& fp_rule)
{
	if (fp_rule >> x >> ip01 >> x >> ip02 >> x >> ip03 >> x >> ip04 >> x >> ip0wei >> ip11 >> x >> ip12 >> x >> ip13 >> x >> ip14 >> x >> ip1wei >> d01 >> x >> d02 >> d11 >> x >> d12 >> x >> x >> z0[0] >> z0[1] >> x >> x >> x >> z1[0] >> z1[1])return 1;
	else return 0;
}
class rule* rule::create_chain_table(ifstream& fp_rule)
{
	
	rule* head, * p, * prev;
	head = new(rule);
	head->next = NULL;
	prev = head;
	do
	{
		p = new(rule);
		p->next = NULL;
		prev->next = p;
		prev = p;
	} while (p->in(fp_rule));//����������������
	return head->next;//headΪ����ͷ�ڵ㣬head->next���Ǵ������ݵĵ�һ������
}
void rule::visit_chain_table(rule* p)//���ʲ����������������
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
		p = p->next;
	}
}
void rule::visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out)
{
	unsigned int ip0, ip1, d0, d1, y, count, flag;
	rule* pt = p;//��ŵ�һ������ָ��
	while (fp_packet >> ip0 >> ip1 >> d0 >> d1 >> y)
	{
		for (p = pt, count = 0, flag = 0; p->next; p = p->next)
		{
			if (rule_match(ip0, ip1, d0, d1, y, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
			{
				fp_out << count << endl;
				flag = 1;
				break;
			}
			count++;//����������ʾ��ǰΪ�ڼ������򡾹����0��ʼ��š�
		}
		if (!flag)fp_out << "-1\n";
	}
}

int main()
{
	//FILE* fp_rule, * fp_out, * fp_packet;
	rule* head, * p;
	char rule_packet[9854] = {};//�洢�����ļ�������·��
	char rule_packet_save[9854] = {};//�洢�����ļ�������·��
	char packet[9854] = {};//�洢���ݼ��ļ�������·��
	char packet_save[9854] = {};//�洢���ݼ��ļ�������·��
	char output[9855] = {};//�洢����ƥ�����ļ�������·��
	char output_save[9855] = {};//�洢����ƥ�����ļ�������·��
	char judge[25655] = {};//�ж��Ƿ��������
	int c = 0;//ִ�г���Ĵ���
	do
	{
		c++;
		if (c == 1)
		{
			cout << "����������ļ�������·�����ɺ��ո񣬲������ţ���" << endl;
			if (!gets_s(rule_packet))break;
			else strcpy(rule_packet_save, rule_packet);
			cout << "���������ݼ��ļ�������·�����ɺ��ո񣬲������ţ���" << endl;
			if (!gets_s(packet))break;
			else strcpy(packet_save, packet);
			cout << "����������ƥ�����ļ�������·�������ļ������ڣ�����Զ��½��ļ����ɺ��ո񣬲������ţ���" << endl;
			if (!gets_s(output))break;
			else strcpy(output_save, output);
		}
		else
		{
			cout << "����������ļ�������·�����ɺ��ո񣬲������ţ����������루����Ctrl+Z��س�����ʹ����һ������Ĺ����ļ�����" << endl;
			if (gets_s(rule_packet))strcpy(rule_packet_save, rule_packet);
			cout << "���������ݼ��ļ�������·�����ɺ��ո񣬲������ţ����������루����Ctrl+Z��س�����ʹ����һ����������ݼ��ļ�����" << endl;
			if (gets_s(packet))strcpy(packet_save, packet);
			cout << "����������ƥ�����ļ�������·�������ļ������ڣ�����Զ��½��ļ����������루����Ctrl+Z��س�����ʹ����һ�������ƥ��������ļ������ɺ��ո񣬲������ţ���" << endl;
			if (gets_s(output))strcpy(output_save, output);
		}
		ifstream fp_rule(rule_packet_save, ios::in | ios::_Nocreate);
		head = (rule*)malloc(sizeof(rule));
		p = head->create_chain_table(fp_rule);//pָ���һ���������ݵ�����
		fp_rule.close();//�ر�ָ���ļ�
		p->visit_chain_table(p);//���ʲ����������������
		ifstream fp_packet(packet_save, ios::in | ios::_Nocreate);
		ofstream fp_out(output_save, ios::out);
		p->visit_processed_chain_table(p, fp_packet, fp_out);
		fp_packet.close();
		fp_out.close();
		cout << "\n�������ݼ��͹��򼯵�ƥ������ɣ�ƥ�����������ָ���ļ����������ƥ���������ݼ��͹��򼯣���ֱ�Ӱ��س����������������ݺ�س�����������������Ctrl+Z֮��س�" << endl;
	} while (gets_s(judge));
	system("pause");
	return 0;
}