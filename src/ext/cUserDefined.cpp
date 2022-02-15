//
// Created by Paul Ross on 08/02/2022.
//
// https://docs.python.org/3/extending/newtypes_tutorial.html#adding-data-and-methods-to-the-basic-example
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *first; /* first name */
    PyObject *last;  /* last name */
    int number;
} CustomObject;

static void
Custom_dealloc(CustomObject *self) {
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
Custom_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
    CustomObject *self;
    self = (CustomObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->last = PyUnicode_FromString("");
        if (self->last == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->number = 0;
    }
    return (PyObject *) self;
}

static int
Custom_init(CustomObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {
            const_cast<char *>("first"),
            const_cast<char *>("last"),
            const_cast<char *>("number"),
            NULL};
    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|UUi", kwlist,
                                     &first, &last,
                                     &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }
    return 0;
}

static PyMemberDef Custom_members[] = {
        {"number", T_INT, offsetof(CustomObject, number), 0,
                "custom number"},
        {NULL, 0, 0, 0, NULL}  /* Sentinel */
};

static PyObject *
Custom_getfirst(CustomObject *self, void *Py_UNUSED(closure)) {
    Py_INCREF(self->first);
    return self->first;
}

static int
Custom_setfirst(CustomObject *self, PyObject *value, void *Py_UNUSED(closure)) {
    PyObject *tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The first attribute value must be a string");
        return -1;
    }
    tmp = self->first;
    Py_INCREF(value);
    self->first = value;
    Py_DECREF(tmp);
    return 0;
}

static PyObject *
Custom_getlast(CustomObject *self, void *Py_UNUSED(closure)) {
    Py_INCREF(self->last);
    return self->last;
}

static int
Custom_setlast(CustomObject *self, PyObject *value, void *Py_UNUSED(closure)) {
    PyObject *tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The last attribute value must be a string");
        return -1;
    }
    tmp = self->last;
    Py_INCREF(value);
    self->last = value;
    Py_DECREF(tmp);
    return 0;
}

static PyGetSetDef Custom_getsetters[] = {
        {"first", (getter) Custom_getfirst, (setter) Custom_setfirst,
                "first name", NULL},
        {"last", (getter) Custom_getlast, (setter) Custom_setlast,
                "last name", NULL},
        {NULL, NULL, NULL, NULL, NULL}  /* Sentinel */
};

static PyObject *
Custom_name(CustomObject *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Custom_methods[] = {
        {"name", (PyCFunction) Custom_name, METH_NOARGS,
                "Return the name, combining the first and last name"
        },
        {NULL, NULL, 0, NULL}  /* Sentinel */
};

static PyTypeObject CustomType = {
        PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "cUserDefined.Custom",
        .tp_doc = "Custom objects",
        .tp_basicsize = sizeof(CustomObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
        .tp_new = Custom_new,
        .tp_init = (initproc) Custom_init,
        .tp_dealloc = (destructor) Custom_dealloc,
        .tp_members = Custom_members,
        .tp_methods = Custom_methods,
        .tp_getset = Custom_getsetters,
};

// NOTE: added
// NOTE: Now add to this module
#include "cUserDefined.h"
#include "cpy/python_object_convert.h"

int py_custom_object_check(PyObject *op) {
    if (Py_TYPE(op) != &CustomType) {
        return 0;
    }
    CustomObject *p = (CustomObject *) op;
    if (!Python_Cpp_Containers::py_unicode_check(p->first)) {
        return 0;
    }
    if (!Python_Cpp_Containers::py_unicode_check(p->last)) {
        return 0;
    }
    return 1;
}

CppCustomObject py_custom_object_to_cpp_custom_object(PyObject *op) {
    if (!py_custom_object_check(op)) {
        // TODO: throw
    }
    CustomObject *p = (CustomObject *) op;
    return CppCustomObject(
            Python_Cpp_Containers::py_unicode_to_cpp_string(p->first),
            Python_Cpp_Containers::py_unicode_to_cpp_string(p->last),
            p->number
    );
}

PyObject *
cpp_custom_object_to_py_custom_object(const CppCustomObject &obj) {
    CustomObject *op = (CustomObject *) Custom_new(&CustomType, NULL, NULL);
    if (op) {
        op->first = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.first());
        op->last = Python_Cpp_Containers::cpp_string_to_py_unicode(obj.last());
        op->number = obj.number();
    }
    return (PyObject *) op;
}

namespace Python_Cpp_Containers {

    // Specialised implementations
    template<>
    PyObject *
    cpp_std_list_like_to_py_list<CppCustomObject>(const std::vector<CppCustomObject> &container) {
        return generic_cpp_std_list_like_to_py_list<
                CppCustomObject, &cpp_custom_object_to_py_custom_object
        >(container);
    }

    template<>
    int
    py_list_to_cpp_std_list_like<CppCustomObject>(PyObject *op, std::vector<CppCustomObject> &container) {
        return generic_py_list_to_cpp_std_list_like<
                CppCustomObject, &py_custom_object_check, &py_custom_object_to_cpp_custom_object
        >(op, container);
    }

    // Add dict support
    // Specialised declarations
    template<>
    PyObject *
    cpp_std_map_like_to_py_dict<std::map, long, CppCustomObject>(const std::map<long, CppCustomObject> &map) {
        return generic_cpp_std_map_like_to_py_dict<
                std::map, long, CppCustomObject,
                &cpp_long_to_py_long, &cpp_custom_object_to_py_custom_object
            >(map);
    }

    template <>
    int
    py_dict_to_cpp_std_map_like<std::map, long, CppCustomObject>(PyObject* op, std::map<long, CppCustomObject> &map) {
        return generic_py_dict_to_cpp_std_map_like<
                std::map,
                long, CppCustomObject,
                &py_long_check, &py_custom_object_check,
                &py_long_to_cpp_long, &py_custom_object_to_cpp_custom_object
        >(op, map);
    }

} // namespace Python_Cpp_Containers

static PyObject *
reverse_list_names(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::vector<CppCustomObject> input;
    if (! Python_Cpp_Containers::py_list_to_cpp_std_list_like(arg, input)) {
        std::vector<CppCustomObject> output;
        for (const auto &object: input) {
            output.emplace_back(CppCustomObject(object.last(), object.first(), object.number()));
        }
        return Python_Cpp_Containers::cpp_std_list_like_to_py_list(output);
    }
    return NULL;
}


static PyObject *
reverse_dict_names(PyObject *Py_UNUSED(module), PyObject *arg) {
    std::map<long, CppCustomObject> input;
    if (! Python_Cpp_Containers::py_dict_to_cpp_std_map_like(arg, input)) {
        std::map<long, CppCustomObject> output;
        for (const auto &iter: input) {
            output.emplace(
                std::make_pair(
                    iter.first,
                    CppCustomObject(
                            iter.second.last(),
                            iter.second.first(),
                            iter.second.number()
                    )
                )
            );
        }
        return Python_Cpp_Containers::cpp_std_map_like_to_py_dict(output);
    }
    return NULL;
}


// Module functions
static PyMethodDef cUserDefinedMethods[] = {
        {"reverse_list_names", reverse_list_names, METH_O,
            "Take a list of cUserDefined.Custom objects"
            " and return a new list with the name reversed."},
        {"reverse_dict_names", reverse_dict_names, METH_O,
            "Take a dict of [int, cUserDefined.Custom] objects"
            " and return a new dict with the name reversed."},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};

// NOTE: modified by adding module methods.
static struct PyModuleDef cUserDefinedmodule = {
        PyModuleDef_HEAD_INIT,
        "cUserDefined",
        "Example extension module that defines a custom object and converts to and from their C++ equivalents.",
        -1,
        cUserDefinedMethods,
        NULL,
        NULL,
        NULL,
        NULL
};

// NOTE: modified by name.
PyMODINIT_FUNC
PyInit_cUserDefined(void) {
    PyObject *m;
    if (PyType_Ready(&CustomType) < 0)
        return NULL;

    m = PyModule_Create(&cUserDefinedmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&CustomType);
    if (PyModule_AddObject(m, "Custom", (PyObject *) &CustomType) < 0) {
        Py_DECREF(&CustomType);
        Py_DECREF(m);
        return NULL;
    }
    if (
        PyModule_AddStringConstant(
            m,
            "PYTHON_CPP_CONTAINERS_VERSION",
            PYTHON_CPP_CONTAINERS_VERSION
        )
    ) {
        return NULL;
    }

    return m;
}
