#include <unistd.h>
#include <vector>
#include "MIDIout.hh"

int main()
{
	MIDIout mo("some client", "my port");

	int tmp[] = {0xF0, 0x18, 0x41, 0x00, 0x08, 0x00, 0x00, 0xF7};
	std::vector<unsigned char> sysex_data;
	for (int i = 0; i != 8; ++i) sysex_data.push_back(tmp[i]);


	for (int i = 0; i != 100; ++i) {
		mo.noteon(0, 60 + i, 0x40);
		mo.controller(0, 0x40, 0x7f);
		mo.noteoff(0, 60 + i, 0x50);
		mo.pgmchange(0, i);
		mo.sysex(sysex_data);
		sleep(1);
	}
}

