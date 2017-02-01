CC = gcc

CFLAGS = -g -Wall
DEPS = read_txt_file.h
OBJ = main.o read_txt_file.o 

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o