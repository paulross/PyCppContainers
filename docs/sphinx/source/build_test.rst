.. moduleauthor:: Paul Ross <apaulross@gmail.com>
.. sectionauthor:: Paul Ross <apaulross@gmail.com>

.. Python/C++ Homogeneous Containers documentation master file, created by
    sphinx-quickstart on Mon May 24 12:09:05 2021.
    You can adapt this file completely to your liking, but it should at least
    contain the root `toctree` directive.


.. _PythonCppContainers_BuildTest:

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

    ./cmake-build-debug/PyCppContainers
    Hello, World!
    Python version: 3.12.1
    test_functional_all START
    RSS(Mb): was:     14.551 now:     14.594 diff:     +0.043 Peak was:     14.551 now:     14.594 diff:     +0.043 test_vector_to_py_tuple<bool>
    RSS(Mb): was:     14.594 now:     14.602 diff:     +0.008 Peak was:     14.594 now:     14.602 diff:     +0.008 test_vector_to_py_tuple<long>
    RSS(Mb): was:     14.602 now:     14.617 diff:     +0.016 Peak was:     14.602 now:     14.617 diff:     +0.016 test_vector_to_py_tuple<double>
    8<---- Snip ---->8
    RSS(Mb): was:     16.762 now:     16.805 diff:     +0.043 Peak was:     16.762 now:     16.805 diff:     +0.043 test_cpp_std_map_to_py_dict_string
    RSS(Mb): was:     16.805 now:     16.828 diff:     +0.023 Peak was:     16.805 now:     16.828 diff:     +0.023 test_py_dict_to_cpp_std_map_like_string
    RSS(Mb): was:     16.805 now:     16.828 diff:     +0.023 Peak was:     16.805 now:     16.828 diff:     +0.023 test_py_dict_to_cpp_std_map_string
    ==== RSS(Mb): was:      7.203 now:     16.828 diff:     +9.625 Peak was:      7.203 now:     16.828 diff:     +9.625 ==== test_functional.cpp
    test_functional_all FINISH

This is followed by the test results:

.. code-block:: shell

    Number of tests: 82
    REGEX_HEAD: "HEAD:\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)"
    REGEX_TEST: "TEST:\s+(\d+)\s+(\d+)\s+(\d+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+([0-9+-.]+)\s+(\d+)\s+([0-9+-.]+)\s+(\S+)"
    REGEX_TAIL: "TAIL:\s+(.+)"
    HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    TEST:    0 1048576       1     0.003036695             N/A             N/A             N/A         1         329.3 test_functional_tuple_setitem():[1048576]
    TEST:    0 1048576       1     0.000766948             N/A             N/A             N/A         1        1303.9 test_functional_list_setitem():[1048576]
    TEST:    0 1048576       1     0.000942830             N/A             N/A             N/A         1        1060.6 test_functional_set_add():[1048576]
    8<---- Snip ---->8
    TEST:    0    1024       1     0.030543838             N/A             N/A             N/A         1          32.7 test_py_dict_to_cpp_std_map_like_bytesstd::map<std::string[32]>>():[1024]
    TEST:    0    1024       1     0.000364432             N/A             N/A             N/A         1        2744.0 test_cpp_std_map_like_to_py_dict_stringstd::map<std::string[32]>>():[1024]
    TEST:    0    1024       1     0.003625261             N/A             N/A             N/A         1         275.8 test_py_dict_to_cpp_std_map_like_stringstd::map<std::string[32]>>():[1024]
    TAIL: Passed=82/82 Failed=0/82
    All tests pass.

    ====RSS(Mb): was:      7.184 now:     16.875 diff:     +9.691 Peak was:      7.184 now:     16.883 diff:     +9.699 main.cpp
    Total execution time:        0.980 (s)
    Count of unique strings created: 16394
    Bye, bye! Returning 0

This takes, typically, under a second.
A return code of 0 is success.
If there are any failing tests then the return code will be the number of failing tests.

================================
Building and Testing Python Code
================================


--------------------------------
Building Python Code
--------------------------------


--------------------------------
Testing Python Code
--------------------------------

The Python tests check these things:

- Functional testing for Python C extensions.
- Performance testing for Python C extensions that exercise the C++ library.
  Usually round tripping Python structures to C++ and back again.
- Memory usage testing for Python C extensions that use this C++ library.

As a basic:

.. code-block:: shell

    $ pytest tests/
    ================================== test session starts ===================================
    platform darwin -- Python 3.12.1, pytest-8.3.3, pluggy-1.5.0
    rootdir: PyCppContainers, configfile: pytest.ini
    collected 128 items

    tests/unit/test_cPyCppContainers.py ......x....................................... [ 35%]
    ...........................                                                        [ 57%]
    tests/unit/test_cUserDefined.py .........                                          [ 64%]
    tests/unit/test_perf_cPyCppContainers.py sssssssssssssssssssssssssssssssssss       [ 91%]
    tests/unit/test_with_pymemtrace.py sssssssssss                                     [100%]

    ======================= 81 passed, 46 skipped, 1 xfailed in 2.74s ========================

Many of the tests are skipped as they are slow, such as performance tests.
To run these tests you need to add the arguments ``--runslow`` and ``-pymemtrace`` respectively, see below.

Testing Performance
--------------------------------



Testing Memory Usage
--------------------------------



=================================================================
Building and Testing Everything for Multiple Python Versions
=================================================================

The script ``build_all.sh`` will execute:

- C++ clean and build debug and release versions.
- Run C++ debug build and the associated tests (this omits C++ performance tests).
- Run C++ release build and the all the tests including C++ performance tests.
- For each Python version (currently 3.8, 3.9, 3.10, 3.11, 3.12, 3.13) it:
    - Creates a new virtual environment.
    - Runs ``pip install -r requirements-dev.txt``.
    - Runs ``python setup.py develop``.
    - Runs ``pytest tests/ -x`` to catch any functional errors.
    - Runs ``pytest tests/ -vs --runslow --pymemtrace`` to run all tests.
    - Runs ``pytest tests/ -vs --runslow --pymemtrace`` to run all tests.
    - Runs ``python setup.py bdist_wheel`` to create the wheels.
    - Runs ``python setup.py sdist`` to create the source distribution.

If any of these fail the script will halt with a failure indication.

The output is verbose typically 30,000 lines.

The typical time breakdown is:

- C++ debug and release builds: 5 minutes.
- C++ debug tests (3,000+): 40 minutes.
- C++ release tests (around 25,000): about 6.5 hours
- Python; create environment and run all tests (127): around 1 hour per Python version.

For all Python versions (6 currently) this takes about 12 to 13 hours.

