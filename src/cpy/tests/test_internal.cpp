//
// Created by Paul Ross on 06/10/2024.
//

#include "test_internal.h"

/**
 *
 * @param a
 * @param b
 * @return Zero if the two arguments are equal. This allows result |= doubles_cmp(value, expected);
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
    failed |= mock_test_result.testCount(mock_scale) != 0;

    // Now add the test result of this function.
    TestResult test_result(title.str());
    test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

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
    auto temp = mock_test_result.testCount(mock_scale);
    failed |= doubles_cmp(mock_test_result.totalTime(mock_scale), 0.0);

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
    failed |= doubles_cmp(mock_test_result.execTime(mock_scale), 2.5);

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
    std::cout << "TRACE:" << result_string << std::endl;
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

void test_internal_all(TestResultS &test_results) {
    std::cout << __FUNCTION__ << " START" << std::endl;
    RSSSnapshot rss_overall("==== test_functional.cpp");

    test_internal_test_result_test_count(test_results);
    test_internal_test_result_total_time(test_results);
    test_internal_test_result_exec_time_min_max(test_results);
    test_internal_test_result_exec_time(test_results);
    test_internal_test_result_string(test_results);

    std::cout << "==== " << rss_overall << std::endl;
    std::cout << __FUNCTION__ << " FINISH" << std::endl;
}