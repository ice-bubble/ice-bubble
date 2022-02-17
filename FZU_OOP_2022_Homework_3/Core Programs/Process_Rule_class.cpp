class rule* rule::Process_Rule_class(rule* p, unsigned int ip0min, unsigned int ip0max, unsigned int ip1min, unsigned int ip1max, int d01, int d02, int d11, int d12, int x0, int x1)
{
	int i = 0;
	for (i = 0; i < 101; i++)
	{
		h[i] = new(rule);
		h[i]->next_arr[i] = NULL;
		pr[i] = h[i];
	}
	if (x1 == 0)
	{
		p->next_arr[0] = NULL;
		pr[0]->next_arr[0] = p;
		pr[0] = p;
		if (d11 >= 0 && d11 <= 50)
		{
			p->next_arr[2] = NULL;
			pr[2]->next_arr[2] = p;
			pr[2] = p;
		}
		else if (d11 <= 100)
		{
			p->next_arr[4] = NULL;
			pr[4]->next_arr[4] = p;
			pr[4] = p;
		}
		else if (d11 <= 150)
		{
			p->next_arr[6] = NULL;
			pr[6]->next_arr[6] = p;
			pr[6] = p;
		}
		else if (d11 <= 200)
		{
			p->next_arr[8] = NULL;
			pr[8]->next_arr[8] = p;
			pr[8] = p;
		}
		else
		{
			p->next_arr[10] = NULL;
			pr[10]->next_arr[10] = p;
			pr[10] = p;
		}
	}
	else
	{
		p->next_arr[1] = NULL;
		pr[1]->next_arr[1] = p;
		pr[1] = p;
		if (d11 >= 0 && d11 <= 50)
		{
			p->next_arr[3] = NULL;
			pr[3]->next_arr[3] = p;
			pr[3] = p;
		}
		else if (d11 <= 100)
		{
			p->next_arr[5] = NULL;
			pr[5]->next_arr[5] = p;
			pr[5] = p;
		}
		else if (d11 <= 150)
		{
			p->next_arr[7] = NULL;
			pr[7]->next_arr[7] = p;
			pr[7] = p;
		}
		else if (d11 <= 200)
		{
			p->next_arr[9] = NULL;
			pr[9]->next_arr[9] = p;
			pr[9] = p;
		}
		else
		{
			p->next_arr[11] = NULL;
			pr[11]->next_arr[11] = p;
			pr[11] = p;
		}
	}

}