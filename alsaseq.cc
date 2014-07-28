#include "alsaseq.hh"

alsaseq::Event::Event()
{
}

alsaseq::Event::~Event()
{
}

snd_seq_event_t* alsaseq::Event::get()
{
}

void alsaseq::Event::clear()
{
}

void alsaseq::Event::set_source(Port)
{
}

void alsaseq::Event::set_subs()
{
}

void alsaseq::Event::set_direct()
{
}

void alsaseq::Event::set_noteon(int channel, int key, int velocity)
{
}

void alsaseq::Event::set_noteoff(int channel, int key, int velocity)
{
}

void alsaseq::Event::set_controller(int channel, int controller, int value)
{
}

void alsaseq::Event::set_pgmchange(int channel, int value)
{
}

void alsaseq::Event::set_sysex(std::string const& data)
{
}


alsaseq::Sequencer::Sequencer()
{
}

alsaseq::Sequencer::~Sequencer()
{
}


snd_seq_t* alsaseq::Sequencer::get()
{
}


void alsaseq::Sequencer::set_client_name(std::string const&)
{
}

alsaseq::Port alsaseq::Sequencer::create_simple_port(std::string const&)
{
}

void alsaseq::Sequencer::event_output(alsaseq::Event const&)
{
}

void alsaseq::Sequencer::drain_output()
{
}

