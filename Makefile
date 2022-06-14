#Makefile
TARGET=e9.out
CXX=gcc
CXXFLAGS=-W
OBJECTS= main.o
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
main.o: main.c
	$(CXX) $(CXXFLAGS) -c $^
clean:
	rm -f $(OBJECTS)
