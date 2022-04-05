#book_management.h global.h librarian.h library.h sign.h user.h
#global.c librarian.c library.c sign.c user.c


TAR=Library
OBJ=global.o librarian.o library.o sign.o user.o
CC:=gcc

$(TAR):$(OBJ)
	$(CC) $(OBJ) -o $(TAR)

%.o:%.c
	$(CC) -c %.c -o %.o


.PHONY:
clearall: 
	rm-rf $(OBJ) $(TAR)
clear:
	rm-rf $(OBJ)