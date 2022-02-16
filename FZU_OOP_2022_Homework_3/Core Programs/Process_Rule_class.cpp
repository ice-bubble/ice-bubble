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
		pr[0]->next = p;
		pr[0] = p;
		if (d11 >= 0 && d11 <= 50)
		{
			p->next_arr[2] = NULL;
			pr[2]->next = p;
			pr[2] = p;
		}
	}
	else
	{
		p->next_arr[1] = NULL;
		pr[1]->next = p;
		pr[1] = p;
	}

}