#include <boost/python.hpp>
#include "MIDIout.hh"
#include "alsaseq.hh"

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
//	.def("sysex", &MIDIout::sysex)
	;

	bp::class_<alsaseq::Event>("Event")
	.def("get", &alsaseq::Event::get,
		bp::return_value_policy<bp::reference_existing_object>()
	)
	.def("clear", &alsaseq::Event::clear)
	.def("set_source", &alsaseq::Event::set_source)
	.def("set_subs", &alsaseq::Event::set_subs)
	.def("set_direct", &alsaseq::Event::set_direct)
	;
}
