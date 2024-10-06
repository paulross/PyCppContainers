//
// Created by Paul Ross on 06/10/2024.
//

#include "test_internal.h"


void test_internal_test_framework_test_result(TestResultS &test_results) {
    // Mock up a test result
    std::ostringstream title;
    title << __FUNCTION__;
    TestResult mock_test_result(title.str());
    ExecClock exec_clock;
    // Unused
    size_t mock_repeat = 4;
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
    failed |= mock_test_result.execTime(mock_scale) != 0.0;

    // Now add the test result of this function.
    double exec_time = exec_clock.seconds();
    TestResult test_result(title.str());
    mock_test_result.execTimeAdd(failed, exec_clock.seconds(), 1, 1);
    test_results.push_back(test_result);
}

void test_internal_all(TestResultS &test_results) {
    std::cout << __FUNCTION__ << " START" << std::endl;
    RSSSnapshot rss_overall("==== test_functional.cpp");

    test_internal_test_framework_test_result(test_results);

    std::cout << "==== " << rss_overall << std::endl;
    std::cout << __FUNCTION__ << " FINISH" << std::endl;
}