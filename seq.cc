#include <string>
#include <unistd.h>
#include <alsa/asoundlib.h>

class Sequencer
{
	public:
	Sequencer(std::string const&);
	~Sequencer();

	void create_port(std::string const&);
	int port();

	void event_output(snd_seq_event_t*);

	private:
	snd_seq_t* _seq;
	int _port;
};

Sequencer::Sequencer(std::string const& name)
{
	snd_seq_open(&_seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
	snd_seq_set_client_name(_seq, name.c_str());
}

Sequencer::~Sequencer()
{
	snd_seq_close(_seq);
}

void Sequencer::create_port(std::string const& name)
{
	_port = snd_seq_create_simple_port(
		_seq,
		name.c_str(),
		SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
		SND_SEQ_PORT_TYPE_MIDI_GENERIC);
}

int Sequencer::port()
{
	return _port;
}

void Sequencer::event_output(snd_seq_event_t* ev)
{
	snd_seq_event_output(_seq, ev);
	snd_seq_drain_output(_seq);
}

class Event
{
	public:
	Event(int sourceport);
	void noteon(int channel, int key, int velocity);
	snd_seq_event_t* raw_event();

	private:
	snd_seq_event_t _ev;
};

Event::Event(int sourceport)
{
	snd_seq_ev_clear(&_ev);
	snd_seq_ev_set_source(&_ev, sourceport);
	snd_seq_ev_set_subs(&_ev);
	snd_seq_ev_set_direct(&_ev);
}

void Event::noteon(int channel, int key, int velocity)
{
	snd_seq_ev_set_noteon(&_ev, channel, key, velocity);
}

snd_seq_event_t* Event::raw_event()
{
	return &_ev;
}

int main()
{
	Sequencer seq("testclient");
	seq.create_port("testport");

	for (int i = 0; i != 100; ++i) {
		Event ev(seq.port());
		ev.noteon(0, 60 + i, 0x40);
		seq.event_output(ev.raw_event());
		sleep(1);
	}
}
