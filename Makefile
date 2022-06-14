#Makefile
TARGET=e11.out
CXX=gcc
CXXFLAGS=-w
OBJECTS=e11.o
$(TARGET):$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread
main.o:e11.c
	$(CXX) $(CXXFLAGS) -c $^ -lpthread
clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)
