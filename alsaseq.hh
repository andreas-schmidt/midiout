#pragma once

namespace alsaseq
{
	class Port{int port};

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

	private:
		snd_seq_event_t* ev;
	};

	class Sequencer
	{
	public:
		Client();
		~Client();

		snd_seq_t* get();

		void set_client_name(std::string const&);
		Port create_simple_port(std::string const&);
		void event_output(Event const&);
		void drain_output();

	private:
		snd_seq_t* seq;
	};
}
