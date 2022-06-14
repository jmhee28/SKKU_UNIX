#Makefile
all: server client
CC = gcc
CFLAGS = -Wall
TARGET1 = server
TARGET2 = client
OBJECTS1 = server.o
OBJECTS2 = client.o

$(TARGET1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^
$(TARGET2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm *.o
