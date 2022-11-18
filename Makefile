CCFLAGS = -Wall -fPIC -shared -nostartfiles -s
CC = gcc

x86_64 : preload.c
	$(CC) preload.c ${CCFLAGS} -m64 -o preload_x86_64.so
               
x86 : preload.c
	$(CC) preload.c $(CCFLAGS) -m32 -o preload_x86.so

       
.PHONY : clean 
clean : 
	rm *.so
