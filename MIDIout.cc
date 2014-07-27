#include "MIDIout.hh"

namespace {
	void prepare(snd_seq_event_t & ev, int port)
	{
		snd_seq_ev_clear(&ev);
		snd_seq_ev_set_source(&ev, port);
		snd_seq_ev_set_subs(&ev);
		snd_seq_ev_set_direct(&ev);
	}

	void output(snd_seq_event_t & ev, snd_seq_t * seq)
	{
		snd_seq_event_output(seq, &ev);
		snd_seq_drain_output(seq);
	}
}

MIDIout::MIDIout(std::string const& client_name, std::string const& port_name)
{
	snd_seq_open(&_seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
	snd_seq_set_client_name(_seq, client_name.c_str());

	_port = snd_seq_create_simple_port(
		_seq,
		port_name.c_str(),
		SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
		SND_SEQ_PORT_TYPE_MIDI_GENERIC);
}

MIDIout::~MIDIout()
{
	snd_seq_close(_seq);
}

void MIDIout::noteon(int channel, int key, int velocity)
{
	snd_seq_event_t ev;
	prepare(ev, _port);
	snd_seq_ev_set_noteon(&ev, channel, key, velocity);
	output(ev, _seq);
}

void MIDIout::noteoff(int channel, int key, int velocity)
{
	snd_seq_event_t ev;
	prepare(ev, _port);
	snd_seq_ev_set_noteoff(&ev, channel, key, velocity);
	output(ev, _seq);
}

void MIDIout::controller(int channel, int controller, int value)
{
	snd_seq_event_t ev;
	prepare(ev, _port);
	snd_seq_ev_set_controller(&ev, channel, controller, value);
	output(ev, _seq);
}

void MIDIout::pgmchange(int channel, int value)
{
	snd_seq_event_t ev;
	prepare(ev, _port);
	snd_seq_ev_set_pgmchange(&ev, channel, value);
	output(ev, _seq);
}

void MIDIout::sysex(std::vector<unsigned char> & data)
{
	snd_seq_event_t ev;
	prepare(ev, _port);
	snd_seq_ev_set_sysex(&ev, data.size(), &data[0]);
	output(ev, _seq);
}

