CC := gcc
PYCONFIG := $(shell python-config --cflags --ldflags)

sndseq.so: sndseq.c
	$(CC) -o $@ -fPIC -shared $(PYCONFIG) $^ -lasound

clean:
	rm -f *.so *.o *.pyc
