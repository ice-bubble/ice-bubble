void ip_swap_to_dec(unsigned int *p,char x[])
{
	int i, m;
	*p = 0;
	for (i = 1, m = 31; i <= 32; i++, m--)
		*p += (x[i] - '0') * (1 << m);//利用位运算将二进制IP地址转换为十进制
}