CC=gcc
TARGET=e5.out
OBJS=e5.o
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
e5.o : e5.c
	$(CC) -c -o e5.o e5.c
clean:
	rm -f *.o
	rm -f $(TARGET)
