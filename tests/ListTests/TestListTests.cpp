/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2017 Mateusz Kolodziejski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file tests/ListTests/TestListTests.cpp
 *
 * @desc Tests used to check correctness of prepared test list.
 */

#include <sstream>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

#include <moctest/FindTest.hpp>
#include <moctest/ListTests.hpp>

#include "TestListTests.hpp"

void TestListTests::setUp() {
}

void TestListTests::tearDown() {
}

void TestListTests::test_list_tests() {
    std::map<std::string, bool> expected_lines = {
            {"Available tests:",                     false},
            {"- All Tests",                          false},
            {"\t- TestListTests",                    false},
            {"\t\t- TestListTests::test_list_tests", false},
            {"\t- TestOne",                          false},
            {"\t\t- TestOne::underlying_test_one",   false},
            {"\t\t- TestOne::underlying_test_two",   false},
            {"\t\t- TestOne::underlying_test_three", false},
            {"\t- TestTwo",                          false},
            {"\t\t- TestTwo::underlying_test_one",   false},
            {"\t\t- TestTwo::underlying_test_two",   false},
            {"\t\t- TestTwo::underlying_test_three", false}
    };

    std::stringstream sStr;
    moctest::ListTests tests_lister;
    tests_lister(sStr, gsl::not_null<CPPUNIT_NS::Test *>(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest()));

    std::string line;
    while (std::getline(sStr, line)) {
        auto expected_line = expected_lines.find(line);

        if (expected_line == expected_lines.end()) {
            continue;
        }

        expected_line->second = true;
    }

    for (auto expected_line_found : expected_lines) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE(
                std::string("Line '") + std::string(expected_line_found.first) + std::string("' not found."), true,
                expected_line_found.second);
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestListTests);
CPPUNIT_TEST_SUITE_REGISTRATION(TestOne);
CPPUNIT_TEST_SUITE_REGISTRATION(TestTwo);

int main(int argc, char *argv[]) {
    CPPUNIT_NS::TestResult controller;

    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener(&progress);

    moctest::FindTest test_finder;
    CPPUNIT_NS::Test *list_tests = test_finder("TestListTests::test_list_tests",
                                               gsl::not_null<CPPUNIT_NS::Test *>(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest()));
    CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(list_tests);
    runner.run(controller);

    CPPUNIT_NS::CompilerOutputter outputter(&result, std::cerr);
    outputter.write();

    return result.wasSuccessful() ? 0 : 1;
}
