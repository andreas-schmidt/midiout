LDLIBS := -lasound
CC := gcc
CXX := g++

main: MIDIout.o main.o
	$(CXX) $^ $(LDLIBS) -o $@
