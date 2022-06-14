#Makefile
TARGET = proj1.out
CXX = gcc
CXXFLAGS = -w
OBJECTS = pa1.o
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	rm pa1.o
pa1.o: pa1.c
	$(CXX) $(CXXFLAGS) -c $^
clean:
	rm *.out
