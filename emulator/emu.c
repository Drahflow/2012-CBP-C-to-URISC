#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* ==== Machine Spec ====
 *
 * This implements a URISC machine with the following features:
 *   * 1 instruction
 *   * 1 register
 *   * 16 bit data width
 *   * 16 bit logical address width
 *   * 31 bit physical address width
 *   * memory mapped IO for display and keyboard
 * 
 * ==== Instruction ====
 *
 * The instruction takes an address argument.
 * 1. it loads the data at that address.
 * 2. it substracts the accumulator from that data.
 * 3. if this substraction resulted in underflow
 * 3a. it increments the program counter by 2, otherwise
 * 3b. it increments the program counter by 1.
 * 4. it writes the result of the computation into
 *    the register and the memory at the address.
 *
 * ==== Memory Layout ====
 *
 *          0x0000: This memory address holds the program counter
 *          0x0001: Memory mapped IO high address lines
 *          0x0002: Code start after reset
 * 0x0002 - 0x7FFF: General purpose RAM
 * 0x8000 - 0xFFFF: Area for memory mapped IO
 *
 * ==== IO Interfaces ====
 *
 * The addresses given include the set bit due to the
 * logical memory mapping.
 *
 *              0x00008000: keyboard data, with the following bit fields
 *                          0x8000: set if new data is ready
 *                          0x0800: set if keyboard data has been lost
 *                                  if this occurs, poll faster
 *                          0x00FF: the character entered, in ASCII
 *
 *              0x00008002: screen width in pixels
 *              0x00008003: screen height in pixels
 *
 * 0x00018000 - 0x0001FFFF: screen pixel data
 */

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_ZOOM 4
#define START 0x0002

Display *display;
unsigned long white;
unsigned long black;
unsigned long long tick = 0;

char disp[DISPLAY_WIDTH][DISPLAY_HEIGHT];
unsigned short basemem[0x8000];
unsigned short acc;
unsigned short keybleds;

unsigned char kbd_ready;
unsigned char kbd_loss;
unsigned char kbd_chr;

int fast, benchmark;

unsigned short keybdata(void)
{
	unsigned short ret;
	ret = (kbd_ready << 15) + (kbd_loss << 11) + kbd_chr;
	kbd_loss = 0;
	kbd_ready = 0;
	return ret;
}

unsigned short readmem(unsigned short addr)
{
	if(addr < 0x8000)
		return basemem[addr];
	else
		switch(basemem[1])
		{
			case 0x0000:
				switch(addr)
				{
					case 0x8000: return keybdata();
					case 0x8001: return 0;
					case 0x8002: return DISPLAY_WIDTH;
					case 0x8003: return DISPLAY_HEIGHT;
					case 0x8004: return 0;
					default: return 0;
				}
			case 0x0001: return 0;
			default:
				return 0;
		}
}

unsigned short writemem(unsigned short addr, unsigned short data,
		Window win, GC gc)
{
	if(addr < 0x8000)
		return basemem[addr] = data;
	else
		switch(basemem[1])
		{
			case 0x0000:
				switch(addr)
				{
					case 0x8000: return keybdata();
					case 0x8001: return keybleds = data;
					case 0x8002: return DISPLAY_WIDTH;
					case 0x8003: return DISPLAY_HEIGHT;
					case 0x8004: return 0;
					default: return 0;
				}
			case 0x0001:
				{
					int x = (addr - 0x8000) % DISPLAY_WIDTH;
					int y = (addr - 0x8000) / DISPLAY_WIDTH;
					if(y >= DISPLAY_HEIGHT)
						return 0;
					if((disp[x][y] = data))
						XSetForeground(display,gc,white);
					else
						XSetForeground(display,gc,black);
					XFillRectangle(display, win, gc,
							x * DISPLAY_ZOOM, y * DISPLAY_ZOOM,
							DISPLAY_ZOOM, DISPLAY_ZOOM);
					return data;
				}
			default:
				return 0;
		}
}

void redraw(Window win,GC gc)
{
	int x, y;
	for(x = 0; x < DISPLAY_WIDTH; x++)
		for(y = 0; y < DISPLAY_HEIGHT; y++)
		{
			if(disp[x][y])
				XSetForeground(display,gc,white);
			else
				XSetForeground(display,gc,black);
			XFillRectangle(display, win, gc,
					x * DISPLAY_ZOOM, y * DISPLAY_ZOOM,
					DISPLAY_ZOOM, DISPLAY_ZOOM);
		}
	XFlush(display);
}

int main(int argc, char **argv)
{
	int screennum;
	int slow, debug, i;
        int binary;
	Window root_window;
	Window win;
	int winx,winy;
	unsigned short command;
	unsigned short input, output;
	FILE *fp;
	GC gc;
	XGCValues gcvals;
	XEvent event;

	basemem[0] = START;

	slow = debug = binary = fast = 0;
	for(i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "--slow")) {
			slow = debug = 1;
                } else if(!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")) {
			debug = 1;
                } else if(!strcmp(argv[i], "-f") || !strcmp(argv[i], "--fast")) {
			fast = 1;
                } else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
                	printf("usage: ./emu [-s | --slow] [-f | --fast] [-d | --debug] [-h | --help]\n             [-b | --benchmark] [--binary] <file>\n");
                        return 1;
                } else if(!strcmp(argv[i], "--binary")) {
			binary = 1;
                } else if(!strcmp(argv[i], "-b") || !strcmp(argv[i], "--benchmark")) {
			benchmark = 1;
                } else {
			if((fp = fopen(argv[i], "r")))
			{
				int pos = START;
				char line[1024];
				int buf;
				printf("File loading in progress...");
				fflush(stdout);
                                if(binary) {
                                  printf("Binary mode loading...");
                                  fflush(stdout);
                                  while(pos < 0x8000 && fread(basemem + pos++, 2, 1, fp) == 1);
                                } else {
                                  while(fgets(line, 1024, fp))
                                  {
                                          if(pos >= 0x8000)
                                                  break;
                                          if(line[0] == ';' || line[0] == '\n')
                                                  continue;
                                          if(line[0] == '.')
                                          {
                                                  buf = -1;
                                                  sscanf(line+1, "%X", &buf);
                                                  if(buf == -1)
                                                  {
                                                          printf("File loading error - could not convert number\n");
                                                          continue;
                                                  }
                                                  pos = buf;
                                                  continue;
                                          }
                                          buf = -1;
                                          sscanf(line, "%X", &buf);
                                          if(buf == -1)
                                          {
                                                  printf("File loading error - could not convert number\n");
                                                  continue;
                                          }
                                          basemem[pos++] = buf;
                                  }
                                }
				fclose(fp);
				printf("done\n");
				fflush(stdout);
			}
			else
				printf("Cannot open file: %s\n", argv[1]);
		}
	}
	
	if(benchmark)
	{
		win = 0;
		gc = NULL;
		basemem[0] = 0;

		for(i = 0; i < 1000000; i++)
		{
			command = readmem(basemem[0]);
			input = readmem(command);
			if(input < acc)
				basemem[0] += 2;
			else
				basemem[0] ++;
			output = input - acc;
			acc = writemem(command, output, win, gc);
		}
		return 0;
	}
	
	if(!(display=XOpenDisplay(getenv("DISPLAY"))))
	{
		fprintf(stderr,"Cannot open display\n");
		return 0;
	}

	screennum=DefaultScreen(display);
	root_window=RootWindow(display,screennum);
	white=WhitePixel(display,screennum);
	black=BlackPixel(display,screennum);
	winx=winy=0;
	win=XCreateSimpleWindow(display,root_window,winx,winy,
			DISPLAY_WIDTH * DISPLAY_ZOOM, DISPLAY_HEIGHT * DISPLAY_ZOOM,
			0,black,black);
	if(!(gc=XCreateGC(display,win,0,&gcvals)))
	{
		fprintf(stderr,"Graphic contest won't show up\n");
		return 0;
	}
	XSetForeground(display,gc,white);
	XSetBackground(display,gc,white);
	XSetFillStyle(display,gc,FillSolid);
	XSelectInput(display,win,ExposureMask|KeyPressMask);
	XMapWindow(display,win);
	XFlush(display);

	while(1)
	{
		if(XCheckMaskEvent(display,ExposureMask|KeyPressMask,&event))
			switch(event.type)
			{
				case KeyPress:
					{
						//KeySym key=XKeycodeToKeysym(display,event.xkey.keycode,0);
                                                KeySym key = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);
						if(debug)
							printf("%c\n",(char) key-XK_A+'A');
						if(kbd_ready)
							kbd_loss = 1;
						kbd_ready = 1;
						kbd_chr = (unsigned char) (key - XK_A + 'A');
					}
				case Expose:
					if(event.xexpose.count==0)
						redraw(win,gc);
					break;
				default:
					fprintf(stderr,"Unknown event received\n");
					break;
			}
		else
		{
			if(fast)
			{
				for(i = 0; i < 1000; i++)
				{
					command = readmem(basemem[0]);
					input = readmem(command);
					if(debug)
						printf("%lld: %04X [%04X] => %04X - %04X = %04X %s ",
								tick++, (int) basemem[0], (int) command, (int) input, (int) acc,
								(unsigned int) (input - acc) & 0xFFFF,
								(input < acc) ? "skip" : "--->");
					if(input < acc)
						basemem[0] += 2;
					else
						basemem[0] ++;
					output = input - acc;
					acc = writemem(command, output, win, gc);
				}
			}
			else
			{
				command = readmem(basemem[0]);
				input = readmem(command);
				if(debug)
					printf("%lld: %04X [%04X] => %04X - %04X = %04X %s ",
							tick++, (int) basemem[0], (int) command, (int) input, (int) acc,
							(unsigned int) (input - acc) & 0xFFFF,
							(input < acc) ? "skip" : "--->");
				if(input < acc)
					basemem[0] += 2;
				else
					basemem[0] ++;
				output = input - acc;
				acc = writemem(command, output, win, gc);
				if(debug)
				{
					printf("%04X next %04X\n", acc, basemem[0]);
					fflush(stdout);
				}
				if(slow)
					sleep(1);
			}
		}
	}
	XCloseDisplay(display);
}
