#include <boost/python.hpp>
#include "alsaseq.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(alsaseq)
{
	class_<alsaseq::Port>("Port");

	class_<alsaseq::Event>("Event")
	.def("clear", &alsaseq::Event::clear)
	.def("set_source", &alsaseq::Event::set_source)
	.def("set_subs", &alsaseq::Event::set_subs)
	.def("set_direct", &alsaseq::Event::set_direct)

	.def("set_noteon", &alsaseq::Event::set_noteon)
	.def("set_noteoff", &alsaseq::Event::set_noteoff)
	.def("set_controller", &alsaseq::Event::set_controller)
	.def("set_pgmchange", &alsaseq::Event::set_pgmchange)
	.def("set_sysex", &alsaseq::Event::set_sysex)
	;

	class_<alsaseq::Sequencer>("Sequencer")
	.def("set_client_name", &alsaseq::Sequencer::set_client_name)
	.def("create_simple_port", &alsaseq::Sequencer::create_simple_port)
	.def("event_output", &alsaseq::Sequencer::event_output)
	.def("drain_output", &alsaseq::Sequencer::drain_output)
	;
}
