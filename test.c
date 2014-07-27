#include <unistd.h>
#include <alsa/asoundlib.h>

int main()
{
	snd_seq_t *seq;
	int port;

	snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
	snd_seq_set_client_name(seq, "my testclient");
	port = snd_seq_create_simple_port(seq, "my testport",
			SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
			SND_SEQ_PORT_TYPE_MIDI_GENERIC);

	int i;
	snd_seq_event_t ev;
	snd_seq_ev_clear(&ev);
	snd_seq_ev_set_source(&ev, port);
	snd_seq_ev_set_subs(&ev);
	snd_seq_ev_set_direct(&ev);

	for (i = 0; i != 100; ++i) {
		snd_seq_ev_set_noteon(&ev, 0, 60 + i, 0x40);
		snd_seq_event_output(seq, &ev);
		snd_seq_drain_output(seq);
		sleep(1);
	}
}
