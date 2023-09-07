CXX = /usr/bin/g++
TARGET = main2
CXXFLAGS = -Wall -Wextra -O2 -march=native -mtune=native -std=c++2b 
LDLFLAGS = -lstdc++
SRCS = main2.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

run: all
	./$(TARGET)

clean:
	rm $(TARGET)
