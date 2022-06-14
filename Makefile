#Makefile
TARGET=e13.out
CXX=gcc
CXXFLAGS=-w
OBJECTS=e13.o
$(TARGET):$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread
main.o:e13.c
	$(CXX) $(CXXFLAGS) -c $^ -lpthread
clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)
