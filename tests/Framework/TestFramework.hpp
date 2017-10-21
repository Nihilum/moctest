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
 * @file tests/Framework/TestFramework.hpp
 *
 * @desc Tests which check and demonstrate capabilities of moctest framework.
 */

#ifndef MOCTEST_TESTS_FRAMEWORK_TEST_FRAMEWORK_HPP
#define MOCTEST_TESTS_FRAMEWORK_TEST_FRAMEWORK_HPP

#include <moctest/moctest.hpp>

class TestFramework final : public CPPUNIT_NS::TestCase {
CPPUNIT_TEST_SUITE(TestFramework);
        CPPUNIT_TEST(test_framework);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;

    void tearDown() override;

protected:
    void test_framework();
};

#endif // MOCTEST_TESTS_FRAMEWORK_TEST_FRAMEWORK_HPP
