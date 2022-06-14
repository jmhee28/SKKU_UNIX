#Makefile
TARGET1 = server.out
TARGET2 = client.out
CXX = gcc
CXXFLAGS = -w

all : $(TARGET1) $(TARGET2)

$(TARGET1):server.c
	$(CXX) -o $@ $^
$(TARGET2):client.c
	$(CXX) -o $@ $^
clean:
	rm *.out
