CXX = g++
CPPFLAGS = -Wall -g
all: rsa

rsa: rsa.cpp rsa.h
	$(CXX) $(CPPFLAGS) $< -o $@
