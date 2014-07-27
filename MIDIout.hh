#include <string>
#include <vector>

#include <alsa/asoundlib.h>

class MIDIout
{
public:
	MIDIout(std::string const&, std::string const&);
	~MIDIout();

	void noteon(int channel, int key, int velocity);
	void noteoff(int channel, int key, int velocity);
	void controller(int channel, int controller, int value);
	void pgmchange(int channel, int value);
	void sysex(std::vector<unsigned char> & data);

private:
	snd_seq_t* _seq;
	int _port;
};

