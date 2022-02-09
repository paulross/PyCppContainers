.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. User defined types

********************************
Adding User Defined Types
********************************

Based on `the example in the Python documentation <https://docs.python.org/3/extending/newtypes_tutorial.html#adding-data-and-methods-to-the-basic-example>`_

Stuff
============================================================


The File ``cUserDefined.h``
---------------------------------------


.. code-block:: cpp

    class CppCustomObject {
    public:
        CppCustomObject(
                const std::string &first,
                const std::string &last,
                long number) : m_first(first), m_last(last), m_number(number) {}
        // Accessors
        const std::string &first() const { return m_first; }
        const std::string &last() const { return m_last; }
        long number() const { return m_number; }
        // Other methods here...
    private:
        std::string m_first;
        std::string m_last;
        long m_number;
    };



.. code-block::

    >>> import cUserDefined
    >>> list_of_names = [cUserDefined.Custom('First', 'Last', 21), cUserDefined.Custom('One', 'Two', 2487)]
    >>> list_of_names
    [<cUserDefined.Custom object at 0x10169c720>, <cUserDefined.Custom object at 0x10169c6f0>]
    >>> [v.name() for v in list_of_names]
    ['First Last', 'One Two']

Now reverse the names using C++:

.. code-block::

    >>> result = cUserDefined.reverse_names(list_of_names)

The objects returned are new objects (compare with above):

.. code-block::

    >>> result
    [<cUserDefined.Custom object at 0x1018ab4e0>, <cUserDefined.Custom object at 0x1018ab810>]

And their names are reversed:

.. code-block::

    >>> [v.name() for v in result]
    ['Last First', 'Two One']

