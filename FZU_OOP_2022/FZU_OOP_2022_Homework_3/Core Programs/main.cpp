#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Rule_class.h"
#include "Process_Rule_class.cpp"
using namespace std;

int main()
{
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
		long start_time = clock();//��¼��������֮���ʱ��Ϊ��ʼʱ��
		ifstream fp_rule(rule_packet_save, ios::in | ios::_Nocreate);
		head = (rule*)malloc(sizeof(rule));
		p = head->create_chain_table(fp_rule);//pָ���һ���������ݵ�����
		fp_rule.close();//�ر�ָ���ļ�
		p->process_chain_table(p);//���ʲ����������������
		ifstream fp_packet(packet_save, ios::in | ios::_Nocreate);
		ofstream fp_out(output_save, ios::out);
		p->visit_processed_chain_table(p, fp_packet, fp_out);//���ʴ����Ĺ�����������
		fp_packet.close();
		fp_out.close();
		long end_time = clock();//��¼�ر��ļ�֮���ʱ��Ϊ����ʱ��
		double time = 1.0 * (end_time - start_time) / 1000;
		cout << "����ƥ����ʱ��" << time << "s" << endl;
		cout << "\n�������ݼ��͹��򼯵�ƥ������ɣ�ƥ�����������ָ���ļ����������ƥ���������ݼ��͹��򼯣���ֱ�Ӱ��س����������������ݺ�س�����������������Ctrl+Z֮��س�" << endl;
	} while (gets_s(judge));
	system("pause");
	return 0;
}