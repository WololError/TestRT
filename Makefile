CXX = g++
CXXFLAGS = -std=c++17 -I./include -I./src

all: prepoc

prepoc: preprocessing.cpp src/rainbow.cpp src/gen_table.cpp utils/sha256.cpp
	$(CXX) $(CXXFLAGS) preprocessing.cpp src/rainbow.cpp src/gen_table.cpp utils/sha256.cpp -o prepoc
	./prepoc

readRT: readRT.cpp src/rainbow.cpp src/gen_table.cpp utils/sha256.cpp src/SimpleCrack.cpp
	$(CXX) $(CXXFLAGS) readRT.cpp src/rainbow.cpp src/gen_table.cpp utils/sha256.cpp src/SimpleCrack.cpp -o readRT
	./readRT