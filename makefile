CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY : all
all : program class_tests

program : LibrarySystem.cpp Book.o Person.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

class_tests : ClassTests.cpp Book.o Person.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

Book.o : Book.cpp Book.h
	$(CXX) $(CXXFLAGS) -c $<

Person.o : Person.cpp Person.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean :
	rm *.o
	rm *~
	rm program
	rm class_tests