
CXX = g++
CXXFLAGS = -O3 -g

MeanShift: cpp_test.o MeanShift.o
	g++ -o $@ $+
