#include "IP_Switch_From_BIN_To_DEC.c"

void CIDR_ip_swap_to_max_and_min(char x[], int w, unsigned int* max, unsigned int* min)
{
	char max_x[37] = { 0 };
	char min_x[37] = { 0 };
	int i;
	for (i = 1; i <= w; i++)
		max_x[i] = min_x[i] = x[i];
	for (i = w + 1; i <= 32; i++)
	{
		max_x[i] = '1';
		min_x[i] = '0';
	}
	ip_swap_to_dec(max, max_x);
	ip_swap_to_dec(min, min_x);
}