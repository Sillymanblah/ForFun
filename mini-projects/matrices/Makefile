CC = g++
CPPFLAGS = -c
CPPVERSION = -std=c++20
WARNINGS = -Wall -Wpedantic -Wextra
OBJECTS = driver.o
BUILD_ID = 0.0.0

all : $(OBJECTS)
	$(CC) $(OBJECTS) -o Build_$(BUILD_ID).exe

%.o : %.cpp
	$(CC) $(CPPVERSION) $(CPPFLAGS) $(WARNINGS) $<

driver.o : matrix.hpp specialized_arithmetic.hpp complex.hpp

.PHONY : clean
clean : 
	rm *.exe *.o