#include "alsaseq.hh"

alsaseq::Event::Event()
{
	ev = new snd_seq_event_t;
}

alsaseq::Event::~Event()
{
	delete ev;
}

snd_seq_event_t* alsaseq::Event::get() const
{
	return ev;
}

void alsaseq::Event::clear()
{
	snd_seq_ev_clear(ev);
}

void alsaseq::Event::set_source(Port p)
{
	snd_seq_ev_set_source(ev, p.port);
}

void alsaseq::Event::set_subs()
{
	snd_seq_ev_set_subs(ev);
}

void alsaseq::Event::set_direct()
{
	snd_seq_ev_set_direct(ev);
}

void alsaseq::Event::set_noteon(int channel, int key, int velocity)
{
	snd_seq_ev_set_noteon(ev, channel, key, velocity);
}

void alsaseq::Event::set_noteoff(int channel, int key, int velocity)
{
	snd_seq_ev_set_noteoff(ev, channel, key, velocity);
}

void alsaseq::Event::set_controller(int channel, int controller, int value)
{
	snd_seq_ev_set_controller(ev, channel, controller, value);
}

void alsaseq::Event::set_pgmchange(int channel, int value)
{
	snd_seq_ev_set_pgmchange(ev, channel, value);
}

void alsaseq::Event::set_sysex(std::string const& data)
{
	snd_seq_ev_set_sysex(
		ev,
	       	data.length(),
	       	const_cast<char*>(data.c_str())
	);
}


alsaseq::Sequencer::Sequencer()
{
	snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
}

alsaseq::Sequencer::~Sequencer()
{
	snd_seq_close(seq);
}

snd_seq_t* alsaseq::Sequencer::get() const
{
	return seq;
}


void alsaseq::Sequencer::set_client_name(std::string const& name)
{
	snd_seq_set_client_name(seq, const_cast<char*>(name.c_str()));
}

alsaseq::Port alsaseq::Sequencer::create_simple_port(std::string const& name)
{
	return alsaseq::Port{
		snd_seq_create_simple_port(
			seq,
			name.c_str(),
			SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
			SND_SEQ_PORT_TYPE_MIDI_GENERIC
		)
	};
}

void alsaseq::Sequencer::event_output(alsaseq::Event const& event)
{
	snd_seq_event_output(seq, event.get());
}

void alsaseq::Sequencer::drain_output()
{
	snd_seq_drain_output(seq);
}

