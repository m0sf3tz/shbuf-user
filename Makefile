all: user.c lfsr.c
	$(CC) -Os -Wall lfsr.c user.c -o shbuf_user

