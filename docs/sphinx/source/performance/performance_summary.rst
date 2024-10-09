.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers Summary

.. _PythonCppContainers.Summary:

Summary
==============================

* Fundamental types ( ``bool``, ``int``, ``float``, ``complex``) can be converted at around 100m objects/sec.
  Converting these from Python to C++ is often around 4x faster than the reverse.
* Sequences of bytes or 8 bit character strings are converted at a memory rate of around 30 GB/sec.
* Sequences 8 bit character strings are 3x slower than bytes achieving a memory rate of around 10 GB/sec.
* 16 and 32 bit character strings are much slower than 8 bit strings (100x), around 100 MB/s.
* Dicts and sets are about 3-10x slower than lists and tuples.
  This can be explained by, whilst both list and dict operations are O(1),
  the list insert is much faster as an insert into a dict/set involves hashing.
* There are no memory leaks in this library.
