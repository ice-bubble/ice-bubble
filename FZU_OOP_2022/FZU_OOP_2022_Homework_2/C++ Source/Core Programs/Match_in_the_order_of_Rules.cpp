int rule_match(unsigned int ip0, unsigned int ip1, int d0, int d1, int x, unsigned int ip0min, unsigned int ip0max, unsigned int ip1min, unsigned int ip1max, int d01, int d02, int d11, int d12, int x0, int x1)
{
	int c = 0;
	if (ip0 >= ip0min && ip0 <= ip0max)c++;
	if (ip1 >= ip1min && ip1 <= ip1max)c++;
	if (d0 >= d01 && d0 <= d02)c++;
	if (d1 >= d11 && d1 <= d12)c++;
	if (x == x0 || x1 == 0)c++;
	if (c == 5)return 1;
	else return 0;
}