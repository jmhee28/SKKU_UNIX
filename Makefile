#Makefile
cc=gcc
TARGET=mysh
OBJECTS=pa2.o
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^  
	rm -f *o
2020315044.o: pa2.c
	$(CC) -c 2020315044.c
clean:
	rm $(OBJECTS) $(TARGET)
