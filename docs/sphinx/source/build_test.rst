.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. Python/C++ Homogeneous Containers documentation master file, created by
    sphinx-quickstart on Mon May 24 12:09:05 2021.
    You can adapt this file completely to your liking, but it should at least
    contain the root `toctree` directive.


.. _PyCppContainers_BuildTest:

***************************************
Building and Testing
***************************************

This chapter describes how to build and test this library.
It assumes that you are in your chosen directory and have done:

.. code-block:: shell

    $ git pull https://github.com/paulross/PyCppContainers.git

================================
Building and Testing C++ Code
================================

--------------------------------
Code Generation
--------------------------------

If necessary run the code generator:

.. code-block:: shell

    cd src/py
    python3 code_gen.py

Which should give you something like:

.. code-block:: shell

    Version: 0.4.0
    Target directory "src/cpy"
    Writing declarations to "src/cpy/auto_py_convert_internal.h"
    Wrote 4125 lines of code with 356 declarations.
    Writing definitions to  "src/cpy/auto_py_convert_internal.cpp"
    Wrote 3971 lines of code with 352 definitions.

    Process finished with exit code 0

--------------------------------
Building C++ Code
--------------------------------

Here are some examples of cleaning and building this project, both debug and release builds:

.. code-block:: shell

    echo "---> C++ clean debug"
    cmake --build cmake-build-debug --target clean -- -j 6
    echo "---> C++ build debug"
    cmake --build cmake-build-debug --target PyCppContainers -- -j 6
    echo "---> C++ clean release"
    cmake --build cmake-build-release --target clean -- -j 6
    echo "---> C++ build release"
    cmake --build cmake-build-release --target PyCppContainers -- -j 6

--------------------------------
Testing C++ Code
--------------------------------

.. code-block:: shell

    echo "---> C++ debug tests"
    cmake-build-debug/PyCppContainers
    echo "---> C++ release tests"
    cmake-build-release/PyCppContainers

The debug tests only test the basic functionality but they do so with some expensive integrity tests.
Release tests are much more extensive testing the performance of the library.

For example running the debug tests:

.. code-block:: shell

    time cmake-build-debug/PyCppContainers
    Hello, World!
    Python version: 3.12.1
    test_functional_all START
    RSS(Mb): was:     17.555 now:     17.613 diff:     +0.059 Peak was:     17.555 now:     17.613 diff:     +0.059 test_vector_to_py_tuple<bool>
    RSS(Mb): was:     17.617 now:     17.660 diff:     +0.043 Peak was:     17.617 now:     17.660 diff:     +0.043 test_vector_to_py_tuple<long>
    RSS(Mb): was:     17.660 now:     17.664 diff:     +0.004 Peak was:     17.660 now:     17.664 diff:     +0.004 test_vector_to_py_tuple<double>
    8<---- Snip ---->8
    RSS(Mb): was:     16.762 now:     16.805 diff:     +0.043 Peak was:     16.762 now:     16.805 diff:     +0.043 test_cpp_std_map_to_py_dict_string
    RSS(Mb): was:     16.805 now:     16.828 diff:     +0.023 Peak was:     16.805 now:     16.828 diff:     +0.023 test_py_dict_to_cpp_std_map_like_string
    RSS(Mb): was:     16.805 now:     16.828 diff:     +0.023 Peak was:     16.805 now:     16.828 diff:     +0.023 test_py_dict_to_cpp_std_map_string
    ==== RSS(Mb): was:      7.203 now:     16.828 diff:     +9.625 Peak was:      7.203 now:     16.828 diff:     +9.625 ==== test_functional.cpp
    test_functional_all FINISH

This is followed by the test results:

.. code-block:: shell

    Number of tests: 3333
    REGEX_HEAD: "HEAD:\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)"
    REGEX_TEST: "TEST:\s+(\d+)\s+(\d+)\s+(\d+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+(\d+)\s+([0-9+-.]+)\s+(\S+)"
    REGEX_TAIL: "TAIL:\s+(.+)"
    HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    TEST:    0 1048576       1     0.001676959             N/A             N/A             N/A         1         596.3 test_functional_tuple_setitem():[1048576]
    TEST:    0 1048576       1     0.000595792             N/A             N/A             N/A         1        1678.4 test_functional_list_setitem():[1048576]
    TEST:    0 1048576       1     0.000947000             N/A             N/A             N/A         1        1056.0 test_functional_set_add():[1048576]    8<---- Snip ---->8
    TEST:    0   32768       1     0.117341292             N/A             N/A             N/A         1           8.5 test_py_tuple_str32_to_vector std::string[2048]>():[32768]
    TEST:    0   65536       1     0.249899958             N/A             N/A             N/A         1           4.0 test_py_tuple_str32_to_vector std::string[2048]>():[65536]
    TEST:    0    4096       1     4.806965084             N/A             N/A             N/A         1           0.2 test_unordered_set_bytes_to_py_set std::string[1048576]>():[4096]
    TAIL: Passed=3333/3333 Failed=0/3333
    All tests pass.

    ====RSS(Mb): was:     10.012 now:    180.496 diff:   +170.484 Peak was:     10.012 now:   3250.059 diff:  +3240.047 main.cpp
    Total execution time:     2370.715 (s)
    Count of unique strings created: 5895690
    Bye, bye! Returning 0
         2371.63 real      2324.66 user        32.06 sys

This takes, typically, 40 minutes.
A return code of 0 is success.
If there are any failing tests then the return code will be the number of failing tests.

The release tests are similar but they include all the performance tests which take a long while.
Run time is around six hours.

================================
Building and Testing Python Code
================================

--------------------------------
Building Python Code
--------------------------------

To build all the Python code create a virtual environment then:

.. code-block:: shell

    $ pip install -r requirements-dev.txt
    $ python setup.py develop

This takes a minute or so.

--------------------------------
Testing Python Code
--------------------------------

The Python tests check these things:

- Functional testing for Python C extensions.
- Performance testing for Python C extensions that exercise the C++ library.
  Usually round tripping Python structures to C++ and back again.
- Memory usage testing for Python C extensions that use this C++ library.

As a basic, from your virtual environment:

.. code-block:: shell

    $ pytest tests/
    ================================ test session starts ==============================
    platform darwin -- Python 3.12.1, pytest-8.3.3, pluggy-1.5.0
    rootdir: PyCppContainers, configfile: pytest.ini
    collected 128 items

    tests/unit/test_cPyCppContainers.py ......x................................. [ 35%]
    .................................                                            [ 57%]
    tests/unit/test_cUserDefined.py .........                                    [ 64%]
    tests/unit/test_perf_cPyCppContainers.py sssssssssssssssssssssssssssssssssss [ 91%]
    tests/unit/test_with_pymemtrace.py sssssssssss                               [100%]

    ====================== 81 passed, 46 skipped, 1 xfailed in 2.74s ==================

By default this only does the functional tests and skips the others such as performance and memory tests.
To run these tests you need to add the arguments ``--runslow`` and ``-pymemtrace`` respectively, see below.

Testing Performance
--------------------------------

To include all the performance tests, this takes about 25 minutes:

.. code-block:: shell

    $ pytest tests/ --runslow

Example:

.. code-block:: shell


    $ time pytest tests --runslow
    ============================ test session starts ==================================
    platform darwin -- Python 3.12.1, pytest-8.3.3, pluggy-1.5.0
    rootdir: PythonCppHomogeneousContainers
    configfile: pytest.ini
    collected 128 items

    tests/unit/test_cPyCppContainers.py ......x................................. [ 35%]
    .................................                                            [ 57%]
    tests/unit/test_cUserDefined.py .........                                    [ 64%]
    tests/unit/test_perf_cPyCppContainers.py ................................... [ 91%]
    tests/unit/test_with_pymemtrace.py sssssssssss                               [100%]

    =========== 116 passed, 11 skipped, 1 xfailed in 1595.44s (0:26:35) ===============
    pytest tests --runslow  1122.24s user 376.19s system 93% cpu 26:35.99 total


Testing Memory Usage
--------------------------------

To include all the memory tests, this takes about 20 minutes:

.. code-block:: shell

    $ time pytest tests --pymemtrace
    ============================ test session starts ==================================
    platform darwin -- Python 3.12.1, pytest-8.3.3, pluggy-1.5.0
    rootdir: PythonCppHomogeneousContainers
    configfile: pytest.ini
    collected 128 items

    tests/unit/test_cPyCppContainers.py ......x................................. [ 35%]
    .................................                                            [ 57%]
    tests/unit/test_cUserDefined.py .........                                    [ 64%]
    tests/unit/test_perf_cPyCppContainers.py sssssssssssssssssssssssssssssssssss [ 91%]
    tests/unit/test_with_pymemtrace.py ...........                               [100%]

    ============= 92 passed, 35 skipped, 1 xfailed in 1237.96s (0:20:37) ==============
    Opening log file 20241010_102101_11927.log
    Opening log file 20241010_102106_11927.log
    Opening log file 20241010_102115_11927.log
    Opening log file 20241010_102136_11927.log
    Opening log file 20241010_102202_11927.log
    Opening log file 20241010_102214_11927.log
    Opening log file 20241010_103049_11927.log
    Opening log file 20241010_103453_11927.log
    Opening log file 20241010_103925_11927.log
    Opening log file 20241010_104003_11927.log
    Opening log file 20241010_104051_11927.log
    pytest tests --pymemtrace  982.16s user 248.42s system 99% cpu 20:38.30 total

Running with both ``--runslow`` and ``--pymentrace`` takes about an hour.

=========================================
Building the Documentation
=========================================

This describes how create the documentation with ``gnuplot``, ``Sphinx`` or ``doxygen``.

--------------------------------
``gnuplot`` Plots
--------------------------------

Recreating Plot Data
--------------------------------

If required the performance data can recreated.
Firstly the C++ performance, from the project directory:

.. code-block:: shell

    $ # Pipe the results of the C++ tests to a specific file.
    $ cmake-build-release/PyCppContainers > perf_notes/cpp_test_results.txt
    $ cd perf_notes
    $ # Run this script that will take the C++ output and split it into .dat files
    $ # in perf_notes/dat.
    $ python write_dat_files_for_cpp_test_results.py

Now for the Python tests, from the project directory, this takes about an hour:

.. code-block:: shell

    $ # Pipe the results of the Python tests to a specific file.
    $ pytest tests --runslow --pymemtrace -vs > perf_notes/python_test_results.txt
    $ cd perf_notes
    $ # Run this script that will take the Python output and split it into .dat files
    $ # in perf_notes/dat.
    $ python write_dat_files_for_python_test_results.py

.. code-block:: shell

    $ # Copy the .dat files to the documentation ready for gnuplot, from project directory.
    $ cp perf_notes/dat/*.dat docs/sphinx/source/plots/dat

.. note:: Memory plots

    The .dat files for memory plots are not (yet) automated and have to be done by hand by copying the ``pymemtrace``
    log files.

Recreating Plot Images
--------------------------------

To recreate the ``gnuplot`` plot images that are used by the documentation from the project directory:

.. code-block:: shell

    $ cd docs/sphinx/source/plots
    $ gnuplot -p *.plt

--------------------------------
Sphinx
--------------------------------

To build the HTML and PDF documentation from the project directory:

.. code-block:: shell

    $ cd docs/sphinx
    $ make clean
    $ make html latexpdf
    $ cp build/latex/PyCppContainers.pdf ..
    $ open build/html/index.html
    $ open ../PyCppContainers.pdf

--------------------------------
Doxygen
--------------------------------

To build the HTML Doxygen documentation from the project directory:

.. code-block:: shell

    $ cd docs
    $ doxygen PyCppContainers.dox
    $ open doxygen/html/index.html

The Doxygen PDF:

.. code-block:: shell

    $ cd docs/doxygen/latex
    $ make pdf
    $ cp refman.pdf ../../PyCppContainers_Doxygen.pdf

=================================================================
Building and Testing Everything for Multiple Python Versions
=================================================================

The script ``build_all.sh`` will execute:

- C++ clean and build debug and release versions.
- Run C++ debug build and the associated tests (this omits C++ performance tests).
- Run C++ release build and the all the tests including C++ performance tests.
- For each Python version ( currently 3.8, 3.9, 3.10, 3.11, 3.12, 3.13 ) it:
    - Creates a new virtual environment.
    - Runs ``pip install -r requirements-dev.txt``.
    - Runs ``python setup.py develop``.
    - Runs ``pytest tests/ -x`` to catch any functional errors.
    - Runs ``pytest tests/ -vs --runslow --pymemtrace`` to run all tests.
    - Runs ``python setup.py bdist_wheel`` to create the wheels.
    - Runs ``python setup.py sdist`` to create the source distribution.

If any of these fail the script will halt with a failure indication.

The output is verbose typically 30,000 lines.

The typical time breakdown is:

- C++ debug and release builds: 5 minutes.
- C++ debug tests (3,000+): 40 minutes.
- C++ release tests (around 25,000): about 40 minutes.
- Python: create environment and run all tests, including slow and memory tests (127): around 1 hour per Python version.

For all Python versions (6 currently) this takes about eight hours.

This does not build the documentation.
