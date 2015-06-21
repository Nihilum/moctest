/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2015 Mateusz Kolodziejski
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
 * @file tests/LibVersion/TestLibVersion.hpp
 *
 * @desc Three tests which compare LibVersion functions results with the library version macros.
 */

#ifndef MOCTEST_TESTS_LIB_VERSION_TEST_LIB_VERSION_HPP
#define MOCTEST_TESTS_LIB_VERSION_TEST_LIB_VERSION_HPP

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

class TestLibVersion : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(TestLibVersion);
    CPPUNIT_TEST(test_get_library_version_major);
    CPPUNIT_TEST(test_get_library_version_minor);
    CPPUNIT_TEST(test_get_library_version_patch);
    CPPUNIT_TEST(test_get_library_version_string);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void test_get_library_version_major();
    void test_get_library_version_minor();
    void test_get_library_version_patch();
    void test_get_library_version_string();
};

#endif // MOCTEST_TESTS_LIB_VERSION_TEST_LIB_VERSION_HPP
