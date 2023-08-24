OBJ:=$(patsubst %.c,%.o,$(wildcard *.c))
li.exe : $(OBJ) 
	gcc -o $@ $^
clean:
	rm *.exe *.o