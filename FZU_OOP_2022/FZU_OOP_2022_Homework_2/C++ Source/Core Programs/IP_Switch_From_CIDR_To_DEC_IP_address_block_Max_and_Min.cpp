#include "IP_Switch_From_BIN_To_DEC.cpp"

void IP_Switch_From_CIDR_To_DEC_IP_address_block_Max_and_Min(char x[], int w, unsigned int* max, unsigned int* min)
{
	char max_x[37] = {};
	char min_x[37] = {};
	int i;
	for (i = 1; i <= w; i++)
		max_x[i] = min_x[i] = x[i];
	for (i = w + 1; i <= 32; i++)
	{
		max_x[i] = '1';
		min_x[i] = '0';
	}
	IP_Switch_From_BIN_To_DEC(max, max_x);
	IP_Switch_From_BIN_To_DEC(min, min_x);
}