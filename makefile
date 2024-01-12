CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY : all
all : program class_tests

program : LibrarySystem.cpp HelperFunctions.o Book.o Person.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

class_tests : ClassTests.cpp HelperFunctions.o Book.o Person.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

HelperFunctions.o : HelperFunctions.cpp HelperFunctions.h
	$(CXX) $(CXXFLAGS) -c $<

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