/*
 * shortened sample program for parser testing, with data omitted
 */

int foo = 3;

int data[3] = { 42, 1337, 23 /* , ... */ };

int drawbyte(int pos, int b)
{
  if(b & 0x80) *(pos + 0x8000) = 1;
  if(b & 0x40) *(pos + 0x8001) = 1;
  // ...
}

int main(void)
{
  int i;
  int j;
  int dpos;
  int nextrow;
  
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
