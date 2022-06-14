cc=gcc
TARGET=e6.out
OBJECTS=w6.o
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^
	rm -f *o
w6.o: w6.c
	$(CC) -c w6.c
clean:
	rm $(OBJECTS) $(TARGET)
