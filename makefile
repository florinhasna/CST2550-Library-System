CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY : all
all : program

program : LibrarySystem.cpp Person.o Book.o
	$(CXX) $(CXXFLAGS) -o $@ $^

Person.o : Person.cpp Person.h
	$(CXX) $(CXXFLAGS) -c $<

Book.o : Book.cpp Book.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean :
	rm *.o
	rm *~
	rm program