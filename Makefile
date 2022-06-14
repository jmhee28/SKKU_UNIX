#Makefile
cc=gcc
TARGET=mysh
OBJECTS=pa2.o
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^  
	rm -f *o
clean:
	rm $(OBJECTS) $(TARGET)
