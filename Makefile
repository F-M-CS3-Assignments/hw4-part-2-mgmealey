all:
	g++ -g -std=c++11 -Wall main.cpp -o bdc

run:
	./bdc

try: all run