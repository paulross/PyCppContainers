"""
Searches a directory for gnuplot .dat and .plt files and finds .dat files that are missing or unused.
"""
import os
import pprint
import re
import typing

DIR_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir, 'docs/sphinx/source/plots'))

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir)) + os.sep

# Matches "dat/test_py_dict_to_cpp_std_unordered_map_vector_char_multiple_std_vector_char_128.dat"
RE_DAT_IN_PLT = re.compile('^.+"(.+\.dat)".+$')


def strip_project_root(path: str) -> str:
    return path[len(PROJECT_ROOT):]


def strip_project_root_and_plot_path(path: str) -> str:
    return path[len(DIR_PATH) + 1:]


def parse_plt_file(plt_file_path: str) -> typing.Set[str]:
    ret = set()
    with open(plt_file_path) as file:
        for line in file.readlines():
            m = RE_DAT_IN_PLT.match(line)
            if m is not None:
                dat_path = os.path.abspath(os.path.join(os.path.dirname(plt_file_path), m.group(1)))
                ret.add(dat_path)
    return ret


def main() -> int:
    # List of discovered .dat absolute paths
    dat_files = set()
    # .plt files and the .data files they reference {pltpath : set(dat_file_paths), ...}
    plt_files = {}
    for root, dirs, files in os.walk(DIR_PATH):
        for name in files:
            file_path = os.path.abspath(os.path.join(root, name))
            if os.path.splitext(name)[1] == '.plt':
                plt_files[file_path] = parse_plt_file(file_path)
            elif os.path.splitext(name)[1] == '.dat':
                dat_files.add(file_path)

    print(f'Directory root: {DIR_PATH}/')
    print(f'  Project root: {PROJECT_ROOT}')
    print(f'.dat files: {len(dat_files)}')
    print(f'.plt files: {len(plt_files)}')

    # .plt file structure
    print(f' .plt structure [{len(plt_files)}] '.center(75, '-'))
    for p in sorted(plt_files.keys()):
        print(f'.plt: {strip_project_root_and_plot_path(p)}')
        for d in sorted(plt_files[p]):
            print(f'    {strip_project_root_and_plot_path(d)}')
    print(f' .plt structure {len(plt_files)} DONE '.center(75, '-'))

    # print(' .dat files '.center(75, '-'))
    # pprint.pprint(dat_files)
    # print(' .dat files DONE '.center(75, '-'))
    # print(' .plt files '.center(75, '-'))
    # pprint.pprint(plt_files)
    # print(' .plt files DONE '.center(75, '-'))

    # Now reconcile

    # First .dat files that are referenced but missing.
    missing_dat = {}
    for p in plt_files:
        for d in plt_files[p]:
            if d not in dat_files:
                if p not in missing_dat:
                    missing_dat[d] = set()
                missing_dat[d].add(p)
    print(f' Missing .dat files [{len(missing_dat)}] '.center(75, '-'))
    # pprint.pprint(missing_dat)
    for d in sorted(missing_dat.keys()):
        print(f'.dat: {strip_project_root_and_plot_path(d)}')
        for p in sorted(missing_dat[d]):
            print(f'    .plt: {strip_project_root_and_plot_path(p)}')
    print(f' Missing .dat files [{len(missing_dat)}] DONE '.center(75, '-'))

    # Now .dat files that are not referenced by any .plt file
    dat_superset = set()
    for p in plt_files:
        dat_superset |= plt_files[p]
    unused_dat = dat_files - dat_superset
    print(f' Unused .dat files [{len(unused_dat)}] '.center(75, '-'))
    # pprint.pprint(sorted(strip_project_root_and_plot_path(p) for p in unused_dat))
    for unused_dat in sorted([strip_project_root_and_plot_path(p) for p in unused_dat]):
        print(unused_dat)
    print(f' Unused .dat files [{len(unused_dat)}] DONE '.center(75, '-'))


if __name__ == '__main__':
    exit(main())
