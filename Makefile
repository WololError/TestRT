all:
	g++ preprocessing.cpp utils/sha256.cpp -I./include -o prepoc
	./prepoc