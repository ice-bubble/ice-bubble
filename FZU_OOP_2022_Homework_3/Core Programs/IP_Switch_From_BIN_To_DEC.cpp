void IP_Switch_From_BIN_To_DEC(unsigned int *p,char x[])
{
	int i, m;
	*p = 0;
	for (i = 1, m = 31; i <= 32; i++, m--)
		*p += (x[i] - '0') * (1 << m);//����λ���㽫������IP��ַת��Ϊʮ����
}