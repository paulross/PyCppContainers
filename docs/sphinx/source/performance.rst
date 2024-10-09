.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. PythonCppContainers Performance

.. _PythonCppContainers.Performance:

===================
Performance
===================

Here are some benchmarks for converting Python containers to and from their C++ equivalents.

The C++ code was compiled with ``-O3`` and run on Apple M1 (2020) CPU running Mac OS X 13.5.1 (Ventura) with 16 GB RAM.
These test results are built with Python 3.12.

There is a lot of formal engineering data in this chapter, so here is a summary:

.. toctree::
   :maxdepth: 4
   :caption: Contents:

   performance/performance_summary
   performance/performance_cpp
   performance/performance_roundtrip
   performance/performance_memory
