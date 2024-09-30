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
Building C++ Code
================================

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


================================
Building Python Code
================================

--------------------------------
Testing Python Code
--------------------------------


=================================================================
Building and Testing Everything for Multiple Python Versions
=================================================================

