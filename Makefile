NAME=siv
FULLNAME=simple-image-viewer

CFLAGS	+= `pkg-config --cflags gtk+-3.0`
LIBS	+= `pkg-config --libs gtk+-3.0`
FLAGS	=
TARGETDIR = `$PWD`

.PHONY: all
all:
	$(CC) $(CFLAGS) -g $(LIBS) $(FULLNAME).c -o $(NAME)

.PHONY: clean
clean:
	rm $(NAME)
