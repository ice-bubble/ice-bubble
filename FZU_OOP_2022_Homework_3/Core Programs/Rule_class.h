#ifndef RULE_CLASS_H
#define RULE_CLASS_H

#include <iostream>
#include <fstream>
using namespace std;

class rule
{
public:
	int in(ifstream& fp_rule);//fstream的拷贝（赋值）构造函数是已删除函数，“&”表示是将函数的形参设置为引用类型，防止报错
	class rule* create_chain_table(ifstream& fp_rule);
	void process_chain_table(rule* p);
	void visit_processed_chain_table(rule* p, ifstream& fp_packet, ofstream& fp_out);
	void process_rule_class(class rule** p, unsigned int ip0min, unsigned int ip0max, unsigned int ip1min, unsigned int ip1max, int d01, int d02, int d11, int d12, int x0, int x1);

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
#endif