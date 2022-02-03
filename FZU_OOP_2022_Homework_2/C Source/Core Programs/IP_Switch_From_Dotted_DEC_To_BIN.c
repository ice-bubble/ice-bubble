void ip_swap_to_bin(int ip1, int ip2, int ip3, int ip4, char ip_bin[])
{
	char* p;
	for (p = ip_bin + 32; ip4; ip4 /= 2, p--)
		*p = ip4 % 2 + '0';
	if (p != ip_bin + 24)
		for (; p > ip_bin + 24; p--)
			*p = '0';
	for (; ip3; ip3 /= 2, p--)
		*p = ip3 % 2 + '0';
	if (p != ip_bin + 16)
		for (; p > ip_bin + 16; p--)
			*p = '0';
	for (; ip2; ip2 /= 2, p--)
		*p = ip2 % 2 + '0';
	if (p != ip_bin + 8)
		for (; p > ip_bin + 8; p--)
			*p = '0';
	for (; ip1; ip1 /= 2, p--)
		*p = ip1 % 2 + '0';
	if (p != ip_bin)
		for (; p > ip_bin; p--)
			*p = '0';
}