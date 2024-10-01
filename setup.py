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
LANGUAGE_STANDARD = "c++14"

# Common flags for both release and debug builds.
extra_compile_args = sysconfig.get_config_var('CFLAGS').split()
# Aligned with CMakeLists.txt
extra_compile_args += [
    "-std=%s" % LANGUAGE_STANDARD,
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Werror",
    "-Wfatal-errors",
    "-Wno-unused-variable", # Temporary
    "-Wno-unused-parameter", # Temporary
    "-fexceptions",
    # To allow designated initialisers.
    "-Wno-c99-extensions",
]

if DEBUG:
    extra_compile_args += ["-g3", "-O0", "-DDEBUG=%s" % DEBUG_LEVEL, "-UNDEBUG"]
else:
    extra_compile_args += ["-DNDEBUG", "-O3"]

def read_file(rel_file_path: str) -> str:
    """Returns the text of a file at the relative path tpo this file."""
    with open(os.path.join(os.path.dirname(__file__), rel_file_path)) as f:
        return f.read()

setup(
    name='PyCppContainers',
    version='0.3.2',
    author='Paul Ross',
    author_email='apaulross@gmail.com',
    maintainer='Paul Ross',
    maintainer_email='apaulross@gmail.com',
    description='Python and C++ Container interoperability.',
    long_description=read_file('README.md'),
    long_description_content_type='text/markdown',
    platforms=['Mac OSX', 'POSIX', ],
    # https://pypi.org/classifiers/
    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: C++',
        # https://devguide.python.org/versions/
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Programming Language :: Python :: 3.11',
        'Programming Language :: Python :: 3.12',
        'Programming Language :: Python :: 3.13',
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
                'src/cpp',
                'src/cpy',
                'src/ext',
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
