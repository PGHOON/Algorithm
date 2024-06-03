CXX = g++
CXXFLAGS = -std=c++11

TARGET = tsp

SRCS = main.cpp algorithm.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
