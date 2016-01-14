/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2016 Mateusz Kolodziejski
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
 * @file tests/FindTest/TestFindTest.hpp
 *
 * @desc Tests used to check correctness of FindTest functor.
 */

#ifndef MOCTEST_TESTS_FINDTEST_TEST_FINDTEST_HPP
#define MOCTEST_TESTS_FINDTEST_TEST_FINDTEST_HPP

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

class TestFindTest final : public CPPUNIT_NS::TestCase {
CPPUNIT_TEST_SUITE(TestFindTest);
        CPPUNIT_TEST(test_find_test);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;

    void tearDown() override;

protected:
    void test_find_test();
};

class TestOne final : public CPPUNIT_NS::TestCase {
CPPUNIT_TEST_SUITE(TestOne);
        CPPUNIT_TEST(underlying_test_one);
        CPPUNIT_TEST(underlying_test_two);
        CPPUNIT_TEST(underlying_test_three);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override { }

    void tearDown() override { }

protected:
    void underlying_test_one() { }

    void underlying_test_two() { }

    void underlying_test_three() { }
};

class TestTwo final : public CPPUNIT_NS::TestCase {
CPPUNIT_TEST_SUITE(TestTwo);
        CPPUNIT_TEST(underlying_test_one);
        CPPUNIT_TEST(underlying_test_two);
        CPPUNIT_TEST(underlying_test_three);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override { }

    void tearDown() override { }

protected:
    void underlying_test_one() { }

    void underlying_test_two() { }

    void underlying_test_three() { }
};

#endif // MOCTEST_TESTS_FINDTEST_TEST_FINDTEST_HPP
