import sndseq as alsaseq

class MIDIout(object):
    def __init__(self, client_name, port_name):
        self.seq = alsaseq.Sequencer()
        self.seq.set_client_name(client_name)
        self.port = self.seq.create_simple_port(port_name)

    def gen_event(self, eventfunc, *args, **kwargs):
        ev = alsaseq.Event()
        ev.clear()
        ev.set_source(self.port)
        ev.set_subs()
        ev.set_direct()
        getattr(ev, eventfunc)(*args, **kwargs)
        self.seq.event_output(ev)
        self.seq.drain_output()

    def noteoff(self, channel, key, velocity):
        self.gen_event('set_noteoff', channel, key, velocity)

    def noteon(self, channel, key, velocity):
        self.gen_event('set_noteon', channel, key, velocity)

    def controller(self, channel, controller, value):
        self.gen_event('set_controller', channel, controller, value)

    def pgmchange(self, channel, value):
        self.gen_event('set_pgmchange', channel, value)

    def sysex(self, data):
        self.gen_event('set_sysex', data)
