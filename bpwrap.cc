#include <boost/python.hpp>
#include "MIDIout.hh"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(MIDIout)
{
	bp::class_<MIDIout>(
		"MIDIout",
	       	bp::init<std::string, std::string>())
	.def("noteon", &MIDIout::noteon)
	.def("noteoff", &MIDIout::noteoff)
	.def("controller", &MIDIout::controller)
	.def("pgmchange", &MIDIout::pgmchange)
	.def("sysex", &MIDIout::sysex)
    ;
}

