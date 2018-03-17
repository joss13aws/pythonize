all:
	g++ test.cpp -o test -std=c++14 -pedantic -Wfatal-errors -O3 2> error.log