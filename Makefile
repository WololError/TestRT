all:
	g++ preprocessing.cpp src/rainbow.cpp src/gen_table.cpp utils/sha256.cpp -I./include -I./src -o prepoc
	./prepoc