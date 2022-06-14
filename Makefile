#Makefile
TARGET = e8.out
CXX = gcc
CXXFLAGS = -w
OBJECTS = e8.o
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
main.o: e8.c
	$(CXX) $(CXXFLAGS) -c $^
clean:
	rm *.o
