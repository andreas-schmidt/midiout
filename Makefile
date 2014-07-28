CC := gcc
CXX := g++
CXXFLAGS := -fPIC -std=c++0x
LDLIBS := -lasound

main: MIDIout.o main.o
	$(CXX) $^ $(LDLIBS) -o $@

bpwrap.o: bpwrap.cc
	$(CXX) $(CXXFLAGS) -I/usr/include/python2.7 -c $<

MIDIout.so: MIDIout.o bpwrap.o
	$(CXX) -o$@ -shared $^ $(LDLIBS) -lpython2.7 -lboost_python

