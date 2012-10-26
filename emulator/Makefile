all: emu

clean:
	rm emu

emu: emu.c
	gcc $< -lX11 -L/usr/X11R6/lib -o $@ -W -Wall -O4
