"""
This is a fairly crude way of parsing the output of the Python performance code into different .dat files that
gnuplot can use.

Example:

PASSED
tests/unit/test_perf_cPyCppContainers.py::test_new_dict_unordered_map_str_str
RSS was 335,093,760 now 425,144,320 diff: 90,050,560
test_new_dict_unordered_map_str_str() String length 16
Size            Count              Min             Mean           Median         Std.Dev.              Max      Max/Min  Min/Size e9
2                   5      0.000000776      0.000002235      0.000000862      0.000003078      0.000007738        9.972        388.0
4                   5      0.000001538      0.000001967      0.000001710      0.000000577      0.000002912        1.893        384.5
...
1048576             5      1.204595211      1.249261654      1.227217851      0.057037247      1.347109490        1.118       1148.8

RSS was 425,152,512 now 655,880,192 diff: 230,727,680
test_new_dict_unordered_map_str_str() String length 128
Size            Count              Min             Mean           Median         Std.Dev.              Max      Max/Min  Min/Size e9
2                   5      0.000001539      0.000003191      0.000001660      0.000003380      0.000009228        5.996        769.5
4                   5      0.000003146      0.000003577      0.000003272      0.000000639      0.000004663        1.482        786.5
...
"""
import os.path


SOURCE_FILE_NAME = 'python_test_results.txt'
TARGET_DIRECTORY = os.path.join(os.path.dirname(__file__), 'dat')


def main():
    # dat_file_lines = {}
    # filename_to_cpp_strings = {}
    all_test_results = {}
    with open(SOURCE_FILE_NAME) as file:
        lines = file.readlines()
        current_block = []
        test_name = ''
        line_index = 0
        while line_index < len(lines):
            if lines[line_index].startswith('Size            Count              Min'):
                # Walk back to find test name
                start_line = line_index
                while start_line:
                    # Look for test name, examples:
                    # tests/unit/test_perf_cPyCppContainers.py::test_new_list_vector_complex
                    # test_new_list_vector_complex()
                    # test_new_list_vector_bytes() Byte length 2
                    if not test_name and lines[start_line].startswith('tests/unit'):
                        test_name = lines[start_line].split('::')[1].strip()
                    else:
                        split_lines =lines[start_line].split('()')
                        if len(split_lines) == 2:
                            if split_lines[1] == '':
                                test_name = split_lines[0].strip()
                            else:
                                # Example:
                                # ''.join('test_new_list_vector_bytes() Byte length 2'.split('()')).replace(' ', '_')
                                # 'test_new_list_vector_bytes_Byte_length_2'
                                test_name = ''.join(split_lines).replace(' ', '_').strip()
                    if lines[start_line].strip() in ('', 'PASSED') or lines[start_line].startswith('tests/unit'):
                        break
                    start_line -= 1
                current_block = [f'# {lines[i]}' for i in range(start_line + 1, line_index + 1)]
                current_block.insert(
                    3,
                    '#$1             $2                  $3              $4              $5              $6                  $7          $8          $9\n'
                )
                start_line = line_index
                # Walk forward to find a blank line or 'PASSED'
                while line_index < len(lines):
                    if len(lines[line_index].strip()) == 0 or lines[line_index].startswith('PASSED'):
                        current_block.extend(lines[start_line:line_index])
                        if test_name in all_test_results:
                            raise ValueError(f'Test name "{test_name}" already seen.')
                        all_test_results[test_name] = current_block[:]
                        test_name = ''
                        current_block = []
                        break
                    line_index += 1
            else:
                line_index += 1
    for k in all_test_results:
        file_name = f'roundtrip_{k}.dat'.replace('_test_new_', '_')
        with open(os.path.join(TARGET_DIRECTORY, file_name), 'w') as file:
            file.writelines(all_test_results[k])
    print(f'Wrote {len(all_test_results)} files.')
    return 0


if __name__ == '__main__':
    exit(main())
