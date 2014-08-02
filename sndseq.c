#include <Python.h>
#include <alsa/asoundlib.h>

/* -- ALSA sequencer port --------------------------------------------------- */
typedef struct {
	PyObject_HEAD
	int port;
} Port;

static PyTypeObject PortType = {
	PyObject_HEAD_INIT(NULL)
	0,                           /*ob_size*/
	"sndseq.Port",               /*tp_name*/
	sizeof(Port),                /*tp_basicsize*/
	0,                           /*tp_itemsize*/
	0,                           /*tp_dealloc*/
	0,                           /*tp_print*/
	0,                           /*tp_getattr*/
	0,                           /*tp_setattr*/
	0,                           /*tp_compare*/
	0,                           /*tp_repr*/
	0,                           /*tp_as_number*/
	0,                           /*tp_as_sequence*/
	0,                           /*tp_as_mapping*/
	0,                           /*tp_hash */
	0,                           /*tp_call*/
	0,                           /*tp_str*/
	0,                           /*tp_getattro*/
	0,                           /*tp_setattro*/
	0,                           /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,          /*tp_flags*/
	"wrapper for snd_seq port",  /* tp_doc */
};

/* -- ALSA sequencer event -------------------------------------------------- */
typedef struct {
	PyObject_HEAD
	snd_seq_event_t ev;
} Event;

static PyTypeObject EventType = {
	PyObject_HEAD_INIT(NULL)
	0,                             /*ob_size*/
	"sndseq.Event",                /*tp_name*/
	sizeof(Event),                 /*tp_basicsize*/
	0,                             /*tp_itemsize*/
	0,                             /*tp_dealloc*/
	0,                             /*tp_print*/
	0,                             /*tp_getattr*/
	0,                             /*tp_setattr*/
	0,                             /*tp_compare*/
	0,                             /*tp_repr*/
	0,                             /*tp_as_number*/
	0,                             /*tp_as_sequence*/
	0,                             /*tp_as_mapping*/
	0,                             /*tp_hash */
	0,                             /*tp_call*/
	0,                             /*tp_str*/
	0,                             /*tp_getattro*/
	0,                             /*tp_setattro*/
	0,                             /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,            /*tp_flags*/
	"wrapper for snd_seq_event_t", /* tp_doc */
};

/* -- Python module --------------------------------------------------------- */
static PyMethodDef module_methods[] = {
	{NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initsndseq(void) 
{
	PyObject* m;
	m = Py_InitModule3("sndseq", module_methods,
		"wrapper for the alsa sequencer");

	// Port
	PortType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&PortType) < 0)
		return;
	Py_INCREF(&PortType);
	PyModule_AddObject(m, "Port", (PyObject *)&PortType);

	// Event
	EventType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&EventType) < 0)
		return;
	Py_INCREF(&EventType);
	PyModule_AddObject(m, "Event", (PyObject *)&EventType);
}
