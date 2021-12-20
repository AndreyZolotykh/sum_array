all:
	g++ -pthread -Wall -Wextra -Wpedantic -O3 -o test main.cpp sum_array.cpp
