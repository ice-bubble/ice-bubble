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
	int in(ifstream& fp_rule);//fstream�Ŀ�������ֵ�����캯������ɾ����������&����ʾ�ǽ��������β�����Ϊ�������ͣ���ֹ����
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
	IP_Switch_From_Dotted_DEC_To_BIN(ip01, ip02, ip03, ip04, ip0bin);//��ԴIP��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
	IP_Switch_From_Dotted_DEC_To_BIN(ip11, ip12, ip13, ip14, ip1bin);//��Ŀ��IP��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
	IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(ip0bin, ip0wei, &ip0max, &ip0min);//��ԴIP��ַ��CIDR��ַ������IP��ַ����СIP��ַ�ֱ���ʮ���Ʊ�ʾ��ʽ�洢���������Ӧ������
	IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(ip1bin, ip1wei, &ip1max, &ip1min);//��Ŀ��IP��ַ��CIDR��ַ������IP��ַ����СIP��ַ�ֱ���ʮ���Ʊ�ʾ��ʽ�洢���������Ӧ������
	Protocol_number_Switch_From_HEX_To_DEC(&x0, &x1, z0, z1);//��Э������·�Χ�ֱ�ת��Ϊʮ���Ʊ�ʾ��ʽ�洢��������Ӧ������
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
	char rule_packet[9854] = {};//�洢�����ļ�������·��
	char rule_packet_save[9854] = {};//�洢�����ļ�������·��
	char packet[9854] = {};//�洢���ݼ��ļ�������·��
	char packet_save[9854] = {};//�洢���ݼ��ļ�������·��
	char output[9855] = {};//�洢����ƥ�����ļ�������·��
	char output_save[9855] = {};//�洢����ƥ�����ļ�������·��
	char judge[25655] = {};//�ж��Ƿ��������
	unsigned int ip0, ip1, d0, d1, y;//��̬�洢���ݼ�ÿ������
	int count, flag;
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
		long start_time = clock();//��¼��������֮���ʱ��Ϊ��ʼʱ��
		ifstream fp_rule(rule_packet_save, ios::in | ios::_Nocreate);
		head = (rule*)malloc(sizeof(rule));//��������ͷ���
		head->next = NULL;
		prev = head;
		p = (rule*)malloc(sizeof(rule));
		while (p->in(fp_rule))
		{
			p->process_chain_table();//���ʲ����������������
			/*����4�д���Ϊ����������Ĺ���*/
			prev->next = p;
			p->next = NULL;
			prev = p;
			p = (rule*)malloc(sizeof(rule));
		}
		fp_rule.close();//�ر�ָ���ļ�	
		ifstream fp_packet(packet_save, ios::in | ios::_Nocreate);
		ofstream fp_out(output_save, ios::out);
		while (fp_packet >> ip0 >> ip1 >> d0 >> d1 >> y)
		{
			for (p = head->next, count = 0, flag = 0; p; p = p->next)
			{
				if (!p->visit_processed_chain_table(&flag, &count, fp_out, ip0, ip1, d0, d1, y))break;
				count++;//����������ʾ��ǰΪ�ڼ������򡾹����0��ʼ��š�
			}
			if (!flag)fp_out << "-1\n";
		}
		fp_packet.close();
		fp_out.close();
		long end_time = clock();//��¼�ر��ļ�֮���ʱ��Ϊ����ʱ��
		for (p = head; p; head = p->next, free(p))//��������ͷŷ��ʺ����������ָ����ռ�õ��ڴ�
		{
			p = head;
			if (!p)
			{
				free(p);
				free(head);
				break;
			}
		}
		double time = 1.0 * (end_time - start_time) / 1000;//����ƥ����̵���ʱ
		cout << "����ƥ����ʱ��" << time << "s" << endl;
		cout << "\n�������ݼ��͹��򼯵�ƥ������ɣ�ƥ�����������ָ���ļ����������ƥ���������ݼ��͹��򼯣���ֱ�Ӱ��س����������������ݺ�س�����������������Ctrl+Z֮��س�" << endl;
	} while (gets_s(judge));
	system("pause");
	return 0;
}