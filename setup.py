import os
from setuptools import setup, Extension
import sysconfig

DEBUG = True
DEBUG = False

# Generally I write code so that if DEBUG is defined as 0 then all optimisations
# are off and asserts are enabled. Typically run times of these builds are x2 to x10
# release builds.
# If DEBUG > 0 then extra code paths are introduced such as checking the integrity of
# internal data structures. In this case the performance is by no means comparable
# with release builds.
DEBUG_LEVEL = 0

# Our level of C++
LANGUAGE_STANDARD = "c++11"

# Common flags for both release and debug builds.
extra_compile_args = sysconfig.get_config_var('CFLAGS').split()
extra_compile_args += ["-std=%s" % LANGUAGE_STANDARD, "-Wall", "-Wextra"]
if DEBUG:
    extra_compile_args += ["-g3", "-O0", "-DDEBUG=%s" % DEBUG_LEVEL, "-UNDEBUG"]
else:
    extra_compile_args += ["-DNDEBUG", "-O3"]

setup(
    name='PythonCppContainers',
    version='0.3.1',
    author='Paul Ross',
    author_email='apaulross@gmail.com',
    maintainer='Paul Ross',
    maintainer_email='apaulross@gmail.com',
    description='Python and C++ Container interoperability.',
    long_description="""TODO.""",
    platforms=['Mac OSX', 'POSIX', ],
    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: C++',
        'Programming Language :: Python :: 3',
        'Topic :: Programming',
    ],
    license='GNU General Public License v2 (GPLv2)',
    ext_modules=[
        Extension(
            'cPyCppContainers',
            sources=[
                'src/ext/cPyCppContainers.cpp',
                'src/cpy/auto_py_convert_internal.cpp',
                'src/cpy/python_container_convert.cpp',
                'src/cpy/python_object_convert.cpp',
            ],
            include_dirs=[
                'src',
            ],
            extra_compile_args=extra_compile_args,
        ),
        Extension(
            'cUserDefined',
            sources=[
                'src/ext/cUserDefined.cpp',
                'src/cpy/auto_py_convert_internal.cpp',
                'src/cpy/python_container_convert.cpp',
                'src/cpy/python_object_convert.cpp',
            ],
            include_dirs=[
                'src',
            ],
            extra_compile_args=extra_compile_args,
        ),
    ]
)
