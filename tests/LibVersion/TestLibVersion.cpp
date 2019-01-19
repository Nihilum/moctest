/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2019 Mateusz Kolodziejski
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
 * @file tests/LibVersion/TestLibVersion.cpp
 *
 * @desc Three tests which compare LibVersion functions results with the library version macros.
 */

#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

#include <moctest/LibVersion.hpp>

#include "TestLibVersion.hpp"

void TestLibVersion::setUp() {
}

void TestLibVersion::tearDown() {
}

void TestLibVersion::test_get_library_version_major() {
    uint16_t expected_major_version = 0;
    CPPUNIT_ASSERT_EQUAL(expected_major_version, moctest::get_library_version_major());
}

void TestLibVersion::test_get_library_version_minor() {
    uint16_t expected_minor_version = 6;
    CPPUNIT_ASSERT_EQUAL(expected_minor_version, moctest::get_library_version_minor());
}

void TestLibVersion::test_get_library_version_patch() {
    uint16_t expected_patch_version = 0;
    CPPUNIT_ASSERT_EQUAL(expected_patch_version, moctest::get_library_version_patch());
}

void TestLibVersion::test_get_library_version_string() {
    const char *expected_version = "0.6.0";
    CPPUNIT_ASSERT_EQUAL(std::string(expected_version), std::string(moctest::get_library_version_string()));
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestLibVersion);

int main(int argc, char *argv[]) {
    CPPUNIT_NS::TestResult controller;

    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener(&progress);

    CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    runner.run(controller);

    CPPUNIT_NS::CompilerOutputter outputter(&result, std::cerr);
    outputter.write();

    return result.wasSuccessful() ? 0 : 1;
}
