CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pthread -I./cyclic_list
LDFLAGS = -lgtest -lgtest_main -pthread

TARGET = test_cyclic_list

SRC = tests/test_cyclic_list.cpp
HEADERS = cyclic_list/cyclic_list.hpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
