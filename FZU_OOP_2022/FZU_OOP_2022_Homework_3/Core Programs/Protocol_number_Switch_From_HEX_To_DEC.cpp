void Protocol_number_Switch_From_HEX_To_DEC(int* x0, int* x1, char z0[], char z1[])
{
	*x0 = *x1 = 0;
	switch (z0[0])
	{
	case '0':*x0 += 0 * 16; break;
	case '1':*x0 += 1 * 16; break;
	case '2':*x0 += 2 * 16; break;
	case '3':*x0 += 3 * 16; break;
	case '4':*x0 += 4 * 16; break;
	case '5':*x0 += 5 * 16; break;
	case '6':*x0 += 6 * 16; break;
	case '7':*x0 += 7 * 16; break;
	case '8':*x0 += 8 * 16; break;
	case '9':*x0 += 9 * 16; break;
	case 'A':*x0 += 10 * 16; break;
	case 'B':*x0 += 11 * 16; break;
	case 'C':*x0 += 12 * 16; break;
	case 'D':*x0 += 13 * 16; break;
	case 'E':*x0 += 14 * 16; break;
	case 'F':*x0 += 15 * 16; break;
	}
	switch (z0[1])
	{
	case '0':*x0 += 0; break;
	case '1':*x0 += 1; break;
	case '2':*x0 += 2; break;
	case '3':*x0 += 3; break;
	case '4':*x0 += 4; break;
	case '5':*x0 += 5; break;
	case '6':*x0 += 6; break;
	case '7':*x0 += 7; break;
	case '8':*x0 += 8; break;
	case '9':*x0 += 9; break;
	case 'A':*x0 += 10; break;
	case 'B':*x0 += 11; break;
	case 'C':*x0 += 12; break;
	case 'D':*x0 += 13; break;
	case 'E':*x0 += 14; break;
	case 'F':*x0 += 15; break;
	}
	switch (z1[0])
	{
	case '0':*x1 += 0 * 16; break;
	case '1':*x1 += 1 * 16; break;
	case '2':*x1 += 2 * 16; break;
	case '3':*x1 += 3 * 16; break;
	case '4':*x1 += 4 * 16; break;
	case '5':*x1 += 5 * 16; break;
	case '6':*x1 += 6 * 16; break;
	case '7':*x1 += 7 * 16; break;
	case '8':*x1 += 8 * 16; break;
	case '9':*x1 += 9 * 16; break;
	case 'A':*x1 += 10 * 16; break;
	case 'B':*x1 += 11 * 16; break;
	case 'C':*x1 += 12 * 16; break;
	case 'D':*x1 += 13 * 16; break;
	case 'E':*x1 += 14 * 16; break;
	case 'F':*x1 += 15 * 16; break;
	}
	switch (z1[1])
	{
	case '0':*x1 += 0; break;
	case '1':*x1 += 1; break;
	case '2':*x1 += 2; break;
	case '3':*x1 += 3; break;
	case '4':*x1 += 4; break;
	case '5':*x1 += 5; break;
	case '6':*x1 += 6; break;
	case '7':*x1 += 7; break;
	case '8':*x1 += 8; break;
	case '9':*x1 += 9; break;
	case 'A':*x1 += 10; break;
	case 'B':*x1 += 11; break;
	case 'C':*x1 += 12; break;
	case 'D':*x1 += 13; break;
	case 'E':*x1 += 14; break;
	case 'F':*x1 += 15; break;
	}
}