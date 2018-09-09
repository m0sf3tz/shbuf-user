all: user.c lfsr.c
	$(CC) -Os -Wall parseLibrary.c lfsr.c user.c -o shbuf_user

