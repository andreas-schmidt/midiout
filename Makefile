CC := gcc
CXX := g++
CXXFLAGS := -fPIC -std=c++0x -I/usr/include/python2.7
LDLIBS := -lasound

alsaseq.so: pyalsaseq.o alsaseq.o
	$(CXX) -o $@ -shared $^ $(LDLIBS) -lpython2.7 -lboost_python

main: MIDIout.o main.o
	$(CXX) $^ $(LDLIBS) -o $@

MIDIout.so: MIDIout.o bpwrap.o alsaseq.o
	$(CXX) -o $@ -shared $^ $(LDLIBS) -lpython2.7 -lboost_python

sndseq.so: sndseq.c
	$(CC) -o $@ -fPIC -shared $(shell python-config --cflags --ldflags) $^ -lasound

clean:
	rm -f *.so *.o
