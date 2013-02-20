/*
 * shortened sample program for parser testing, with data omitted
 */
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

int foo = {3};

int data[3] = { 42, 1337, 23 /* , ... */ };

int drawbyte(int pos, int b)
{
  *0x800a = b;
  if(b & 0x80) *(pos + 0x8000) = 1;
  if(b & 0x40) *(pos + 0x8001) = 1;
  if(b & 0x20) *(pos + 0x8002) = 1;
  if(b & 0x10) *(pos + 0x8003) = 1;
  if(b & 0x08) *(pos + 0x8004) = 1;
  if(b & 0x04) *(pos + 0x8005) = 1;
  if(b & 0x02) *(pos + 0x8006) = 1;
  if(b & 0x01) *(pos + 0x8007) = 1;
  // ...
}

int main(void)
{
  int i;
  int j;
  int dpos;
  int nextrow;
 
  *1 = 1; // enable display output
  drawbyte( 0, 0x80);
  nextrow = 0x0080;
  
  i = 0;
  dpos = 0;
  while((j = data[i]) < 0x200)
  {
    if(j > 0xFF)
    {
      while(dpos < nextrow)
      {
        dpos = dpos + 1;
      }
      nextrow = nextrow + 0x0080;
      j = j - 0x100;
    }
    drawbyte(dpos, j);
    dpos = dpos + 8;
    i = i + 1;
  }
}
