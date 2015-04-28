NAME=siv
FULLNAME=simple-image-viewer

CFLAGS	+= `pkg-config --cflags gtk+-3.0` --std=c11 -g
LIBS	+= `pkg-config --libs gtk+-3.0`
FLAGS	=
TARGETDIR = `$PWD`

SRC=simple-image-viewer.c filenamenode.c

.PHONY: all
all:
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $(NAME)
