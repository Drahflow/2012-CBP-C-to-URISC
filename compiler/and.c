

int dddata[16] = { 0x8000, 0x4000, 0x2000, 0x1000,0x800, 0x400, 0x200, 0x100,0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
int And(int a, int b)
{
	int ret;
	int count;
	int tmp1;
	int tmp2;
	ret = 0;
	for( count = 0; 16 > count; count = count + 1 )
	{
		tmp1 = 1;
		tmp2 = 2;
		if( a >= dddata[count] )
		{
			tmp1 = 0;
			a = a - dddata[count];
		}
		if( b >= dddata[count] )
		{
			tmp2 = 0;
			b = b - dddata[count];
		}
		if( tmp1 == tmp2 )
		{
			ret = ret + dddata[count];
		}
	}
	return ret;
}

int main(void)
{
	int a;
	a = 1;
}
