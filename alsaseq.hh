#pragma once

#include <string>
#include <alsa/asoundlib.h>

namespace alsaseq
{
	class Port
	{
	public:
		int port;
	};

	class Event
	{
	public:
		Event();
		~Event();

		snd_seq_event_t* get();

		void clear();
		void set_source(Port);
		void set_subs();
		void set_direct();

		void set_noteon(int channel, int key, int velocity);
		void set_noteoff(int channel, int key, int velocity);
		void set_controller(int channel, int controller, int value);
		void set_pgmchange(int channel, int value);
		void set_sysex(std::string const& data);

	private:
		snd_seq_event_t* ev;
	};

	class Sequencer
	{
	public:
		Sequencer();
		~Sequencer();

		snd_seq_t* get();

		void set_client_name(std::string const&);
		Port create_simple_port(std::string const&);
		void event_output(Event const&);
		void drain_output();

	private:
		snd_seq_t* seq;
	};
}
