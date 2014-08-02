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

/* -- ALSA sequencer -------------------------------------------------------- */
typedef struct {
	PyObject_HEAD
	snd_seq_t* seq;
} Sequencer;

static void
Sequencer_dealloc(Sequencer* self)
{
	snd_seq_close(self->seq);
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
Sequencer_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Sequencer *self;

    self = (Sequencer*)type->tp_alloc(type, 0);
    if (self != NULL) {
	    snd_seq_open(&self->seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
    }

    return (PyObject *)self;
}

static PyObject *
Sequencer_set_client_name(Sequencer* self, PyObject* args)
{
	const char *name;

	if (!PyArg_ParseTuple(args, "s", &name))
		return NULL;

	snd_seq_set_client_name(self->seq, name);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Sequencer_create_simple_port(Sequencer* self)
{
 	Port* p;
	p = (Port*)PortType.tp_alloc(&PortType, 0);

	if (p != NULL) {
		p->port = snd_seq_create_simple_port(
			self->seq,
			"testport",
			SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
			SND_SEQ_PORT_TYPE_MIDI_GENERIC
		);
	}

	return (PyObject*)p;
}

static PyMethodDef Sequencer_methods[] = {
	{"set_client_name",
		(PyCFunction)Sequencer_set_client_name,
		METH_VARARGS,
		"snd_seq_set_client_name"
	},
	{"create_simple_port",
		(PyCFunction)Sequencer_create_simple_port,
		METH_NOARGS,
		"snd_seq_create_simple_port"
	},
	{NULL}
};

static PyTypeObject SequencerType = {
	PyObject_HEAD_INIT(NULL)
	0,                             /* ob_size */
	"sndseq.Sequencer",            /* tp_name */
	sizeof(Sequencer),             /* tp_basicsize */
	0,                             /* tp_itemsize */
	(destructor)Sequencer_dealloc, /* tp_dealloc */
	0,                             /* tp_print */
	0,                             /* tp_getattr */
	0,                             /* tp_setattr */
	0,                             /* tp_compare */
	0,                             /* tp_repr */
	0,                             /* tp_as_number */
	0,                             /* tp_as_sequence */
	0,                             /* tp_as_mapping */
	0,                             /* tp_hash */
	0,                             /* tp_call */
	0,                             /* tp_str */
	0,                             /* tp_getattro */
	0,                             /* tp_setattro */
	0,                             /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,            /* tp_flags */
	"wrapper for snd_seq_t",       /* tp_doc */
	0,                             /* tp_traverse */
	0,                             /* tp_clear */
	0,                             /* tp_richcompare */
	0,                             /* tp_weaklistoffset */
	0,                             /* tp_iter */
	0,                             /* tp_iternext */
	Sequencer_methods,             /* tp_methods */
	0,                             /* tp_members */
	0,                             /* tp_getset */
	0,                             /* tp_base */
	0,                             /* tp_dict */
	0,                             /* tp_descr_get */
	0,                             /* tp_descr_set */
	0,                             /* tp_dictoffset */
	0,                             /* tp_init */
	0,                             /* tp_alloc */
	Sequencer_new,                 /* tp_new */
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

	// Sequencer
	if (PyType_Ready(&SequencerType) < 0)
		return;
	Py_INCREF(&SequencerType);
	PyModule_AddObject(m, "Sequencer", (PyObject *)&SequencerType);
}
