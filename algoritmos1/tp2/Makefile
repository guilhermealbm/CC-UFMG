ALL = tp2
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CC = g++

# The flags below will be included in the implicit compilation rules
# 'make' infers that the code in the directory is in c++
# and looks for the CPPFLAGS variable
CPPFLAGS = -g -Wall -std=c++11 -O3

all: $(ALL)

$(ALL): $(OBJ)
	$(CC) $(CPPFLAGS) -c $(SRC)
	$(CC) $(CPPFLAGS) $(OBJ) -o $@ 

clean:
	rm $(ALL) *.o