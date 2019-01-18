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
 * @file tests/FindTest/TestFindTest.cpp
 *
 * @desc Tests used to check correctness of FindTest functor.
 */

#include <vector>
#include <algorithm>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

#include <moctest/FindTest.hpp>

#include "TestFindTest.hpp"

void TestFindTest::setUp() {
}

void TestFindTest::tearDown() {
}

void TestFindTest::test_find_test() {
    moctest::FindTest test_finder;
    std::vector<std::string> vec_tests{"All Tests",
                                       "TestFindTest", "TestFindTest::test_find_test",
                                       "TestOne", "TestOne::underlying_test_one", "TestOne::underlying_test_two",
                                       "TestOne::underlying_test_three",
                                       "TestTwo", "TestTwo::underlying_test_one", "TestTwo::underlying_test_two",
                                       "TestTwo::underlying_test_three"
    };

    std::for_each(vec_tests.begin(), vec_tests.end(), [&](const std::string &test_name) {
        CPPUNIT_NS::Test *test = test_finder(test_name, gsl::not_null<CPPUNIT_NS::Test *>(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest()));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(test_name, false, test == nullptr);
        CPPUNIT_ASSERT_EQUAL_MESSAGE(test_name, test_name, test->getName());
    });
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestFindTest);
CPPUNIT_TEST_SUITE_REGISTRATION(TestOne);
CPPUNIT_TEST_SUITE_REGISTRATION(TestTwo);

int main(int argc, char *argv[]) {
    CPPUNIT_NS::TestResult controller;

    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener(&progress);

    moctest::FindTest test_finder;
    CPPUNIT_NS::Test *find_test = test_finder("TestFindTest::test_find_test",
                                              gsl::not_null<CPPUNIT_NS::Test *>(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest()));
    CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(find_test);
    runner.run(controller);

    CPPUNIT_NS::CompilerOutputter outputter(&result, std::cerr);
    outputter.write();

    return result.wasSuccessful() ? 0 : 1;
}
