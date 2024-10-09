//
// Created by Paul Ross on 06/10/2024.
//

#include "test_internal.h"

/**
 * Compare two doubles to see if they are 'similar'.
 * If possible this normalises the two values to unity before comparing them with
 * \c std::numeric_limits<double>::epsilon()
 *
 * @param a
 * @param b
 * @return Zero if the two arguments are equal, non-zero if they are out of range.
 *  This allows: <tt>result |= doubles_cmp(value, expected);</tt>
 */
int doubles_cmp(double a, double b) {
    int ret = 0;
    double mean = (a + b) / 2.0;
    if (mean != 0.0) {
        // Normalise
        ret = std::abs(a / mean - b / mean) > std::numeric_limits<double>::epsilon();
    } else {
        // Mean is zero
        ret = std::abs(a - b) > std::numeric_limits<double>::epsilon();
    }
    return ret;
}

/**
 * This demonstrates that the number or tests is the summ of all the test_counts for each added result.
 *
 * @param test_results
 */
void test_internal_test_result_test_count(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    failed |= mock_test_result.failed() != 0;
    auto temp = mock_test_result.testCount(mock_scale);
    failed |= temp != 4 * mock_test_count;

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

/**
 * This demonstrates that the total execution time is the sum of all the sub-test execution time.
 *
 * @param test_results
 */
void test_internal_test_result_total_time(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    failed |= mock_test_result.failed() != 0;
    auto temp = mock_test_result.totalTime(mock_scale);
    failed |= doubles_cmp(mock_test_result.totalTime(mock_scale), 1.0 + 2.0 + 3.0 + 4.0);

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_test_result_exec_time_min_max(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    failed |= mock_test_result.failed() != 0;
    auto temp = mock_test_result.execTime(mock_scale);
    failed |= doubles_cmp(mock_test_result.execTimeMin(mock_scale), 1.0);
    failed |= doubles_cmp(mock_test_result.execTimeMax(mock_scale), 4.0);

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_test_result_exec_time(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    failed |= mock_test_result.failed() != 0;
    auto temp = mock_test_result.execTime(mock_scale);
    failed |= doubles_cmp(temp, (1.0 + 2.0 + 3.0 + 4.0) / 4.0);

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_test_result_string(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    std::ostringstream result_stream;
    failed |= mock_test_result.failed() != 0;
    result_stream << mock_test_result;
    auto result_string = result_stream.str();
    // std::cout << "TRACE:" << result_string << std::endl;
    //       HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    std::string exp_string(
            "TEST:    0      99       4     2.500000000     1.118033989     1.000000000     4.000000000       400         160.0 test_internal_test_result_string"
            );
    failed |= result_string != exp_string;

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_test_result_string_multiple_a(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, 2);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, 4);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, 8);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, 16);
    int failed = 0;

    auto scale = mock_test_result.scaleValues();
    // Now check the test result object
    std::ostringstream result_stream;
    failed |= mock_test_result.failed() != 0;
    result_stream << mock_test_result;
    auto result_string = result_stream.str();
    //std::cout << "TRACE:" << result_string << std::endl;
    //       HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    std::string exp_string(
            "TEST:    0       2       1     1.000000000             N/A             N/A             N/A       100         100.0 test_internal_test_result_string_multiple_a\n"
            "TEST:    0       4       1     2.000000000             N/A             N/A             N/A       100          50.0 test_internal_test_result_string_multiple_a\n"
            "TEST:    0       8       1     3.000000000             N/A             N/A             N/A       100          33.3 test_internal_test_result_string_multiple_a\n"
            "TEST:    0      16       1     4.000000000             N/A             N/A             N/A       100          25.0 test_internal_test_result_string_multiple_a"
            );
    failed |= result_string != exp_string;

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_test_result_string_multiple_b(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, 2);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, 2);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, 4);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, 4);
    int failed = 0;

    auto scale = mock_test_result.scaleValues();
    // Now check the test result object
    std::ostringstream result_stream;
    failed |= mock_test_result.failed() != 0;
    result_stream << mock_test_result;
    auto result_string = result_stream.str();
    //std::cout << "TRACE:" << result_string << std::endl;
    //       HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    std::string exp_string(
            "TEST:    0       2       2     1.500000000     0.500000000     1.000000000     2.000000000       200         133.3 test_internal_test_result_string_multiple_b\n"
            "TEST:    0       4       2     3.500000000     0.500000000     3.000000000     4.000000000       200          57.1 test_internal_test_result_string_multiple_b"
            );
    failed |= result_string != exp_string;

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

/**
 * Example of a very fast test where using the "Rate" column can recover the mean time with accuracy.
 *
 * @param test_results
 */
void test_internal_test_result_string_using_rate(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 1;
    size_t mock_scale = 99;
    mock_test_result.execTimeAdd(0, 1.23456789e-9, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    std::ostringstream result_stream;
    failed |= mock_test_result.failed() != 0;
    result_stream << mock_test_result;
    auto result_string = result_stream.str();
    //std::cout << "TRACE:" << result_string << std::endl;
    //       HEAD: Fail   Scale  Repeat         Mean(s)     Std.Dev.(s)         Min.(s)         Max.(s)     Count      Rate(/s) Name
    std::string exp_string(
            "TEST:    0      99       1     0.000000001             N/A             N/A             N/A         1   810000007.4 test_internal_test_result_string_using_rate"
            );
    failed |= result_string != exp_string;

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_test_result_atomic_test_mean_exec_time(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    ExecClock exec_clock; // For the real test.
    TestResult mock_test_result(title.str());
    // Unused
    size_t mock_test_count = 100;
    size_t mock_scale = 99;
    // Now add 4 (mock_repeat) tests results, each has 100 atomic tests.
    mock_test_result.execTimeAdd(0, 1.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 2.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 3.0, mock_test_count, mock_scale);
    mock_test_result.execTimeAdd(0, 4.0, mock_test_count, mock_scale);
    int failed = 0;
    // Now check the test result object
    std::ostringstream result_stream;
    failed |= mock_test_result.failed() != 0;
    auto temp = mock_test_result.atomicTestMeanExecTime(mock_scale);
    failed |= doubles_cmp(temp, (1.0 + 2.0 + 3.0 + 4.0) / (4 * mock_test_count));

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_all(TestResultS &test_results) {
    std::cout << __FUNCTION__ << " START" << std::endl;
    RSSSnapshot rss_overall("==== test_functional.cpp");

    test_internal_test_result_test_count(test_results);
    test_internal_test_result_total_time(test_results);
    test_internal_test_result_exec_time_min_max(test_results);
    test_internal_test_result_exec_time(test_results);
    test_internal_test_result_string(test_results);
    test_internal_test_result_string_multiple_a(test_results);
    test_internal_test_result_string_multiple_b(test_results);
    test_internal_test_result_string_using_rate(test_results);
    test_internal_test_result_atomic_test_mean_exec_time(test_results);

    std::cout << "==== " << rss_overall << std::endl;
    std::cout << __FUNCTION__ << " FINISH" << std::endl;
}