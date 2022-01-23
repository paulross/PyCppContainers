.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers Performance

.. _PythonCppContainers.Performance:

Performance
===================

Here are some benchmarks for converting Python containers to and from their C++ equivalents.

The C++ code was compiled with ``-O3`` and run on the following hardware:

.. code-block:: none

    Model Name:	                MacBook Pro
    Model Identifier:           MacBookPro15,2
    Processor Name:             Intel Core i7
    Processor Speed:            2.7 GHz
    Number of Processors:       1
    Total Number of Cores:      4
    L2 Cache (per Core):        256 KB
    L3 Cache:                   8 MB
    Hyper-Threading Technology: Enabled
    Memory:                     16 GB

    System Version:             macOS 10.14.6

.. toctree::
   :maxdepth: 4
   :caption: Contents:

   performance/performance_cpp
   performance/performance_roundtrip
   performance/performance_memory

Summary
-----------------

* Fundamental types (``bool``, ``int``, ``float``, ``complex``) can be converted at around 100m objects/sec.
* Sequences of bytes or strings are converted at a memory rate of around 4,000 Mb/sec.
* Dicts and sets are about 3-10x slower than lists and tuples.
  This can be explained by, whilst both list and dict operations are O(1),
  the list insert is much faster as an insert into a dict/set involves hashing.
* In some cases the performance of converting Python to C++ or the reverse is faster but the difference is <= 2x.
* There are no memory leaks.
