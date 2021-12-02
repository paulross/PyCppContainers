"""
Example:
    HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
TEST:    0       1       5     0.000001235     0.000002290     0.000000065     0.000005814         5     4048910.8 test_vector_to_py_list_multiple<bool>[1]

TEST:    0    1024       5     0.000015565     0.000000977     0.000015067     0.000017520         5      321231.5 test_vector_string_to_py_list_multiple<std::string[8]>():[1024]

"""
import os.path
import pprint
import re

RE_FILENAME = re.compile(r'^(.+)\[[0-9]+\]$')


def main():
    dat_file_lines = {}
    with open('list.txt') as file:
        for line in file.readlines():
            if line.startswith('TEST:'):
                filename = line.split()[-1].replace('<', '_').replace('>', '_').replace('(', '').replace(')', '').replace(':', '_')
                m = RE_FILENAME.match(filename)
                if m is None:
                    print(f'ERROR: {filename}')
                else:
                    filename = m.group(1)
                    filename = filename.replace('[', '_').replace(']', '_')
                    filename = filename.replace('__', '_')
                    filename = filename.rstrip('_') + '.dat'
                    if filename not in dat_file_lines:
                        dat_file_lines[filename] = []
                    dat_file_lines[filename].append(line)
    # pprint.pprint(dat_file_lines, width=400)
    print(f'Files to write: {len(dat_file_lines)}')
    headers = [
        '# HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name\n',
        '# $1    $2      $3      $4              $5              $6              $7              $8        $9           $10  $11\n',
    ]
    for k in sorted(dat_file_lines.keys()):
        # print(f'{k} : {dat_file_lines[k]}')
        dat_filename = os.path.join(os.path.dirname(__file__), 'dat', k)
        with open(dat_filename, 'w') as file:
            line_count = 0
            for line in headers:
                file.write(line)
                line_count += 1
            for line in dat_file_lines[k]:
                file.write(line)
                line_count += 1
            print(f'Wrote {line_count:4d} lines ({line_count - len(headers):4d} data lines) to "{dat_filename}"')


if __name__ == '__main__':
    exit(main())