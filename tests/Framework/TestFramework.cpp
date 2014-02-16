/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Mateusz Kolodziejski
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
 * @file tests/Framework/TestFramework.cpp
 *
 * @desc Tests which check and demonstrate capabilities of moctest framework.
 */

#include <sstream>
#include <iostream>

#include "TestFramework.hpp"

void TestFramework::setUp()
{
}

void TestFramework::tearDown()
{
}

class TestString : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(TestString);
    CPPUNIT_TEST(test_string);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() {}
    void tearDown() {}

protected:
    void test_string() { std::cout << "Displaying something."; }
};

void TestFramework::test_framework()
{
    const int argc = 2;
    std::stringstream sCatch;

    {
        const char* h_argv[argc] = { "./framework", "-h" };
        std::string expected_h("Possible options:\n--help (-h)\tshows this help message\n--list (-l)\tshows the list of all possible tests\n"
                               "--test (-t) <test_name1> [<test_name2>...]\truns given tests only\n");

        moctest::Framework h_tests(argc, (char**)h_argv);

        std::streambuf* prevstr = std::cout.rdbuf();
        std::cout.rdbuf(sCatch.rdbuf());

        try {
            CPPUNIT_ASSERT_EQUAL_MESSAGE(sCatch.str(), 0, h_tests.run());
            CPPUNIT_ASSERT_EQUAL_MESSAGE(sCatch.str(), expected_h, sCatch.str());
        } catch (...) {
            std::cout.rdbuf(prevstr);
            throw;
        }

        std::cout.rdbuf(prevstr);
    }

    sCatch.str("");
    sCatch.clear();

    {
        const char* l_argv[argc] = { "./framework", "-l" };
        std::string expected_l("Available tests:\n- All Tests\n\t- TestFramework\n\t\t- TestFramework::test_framework\n\n");
        moctest::Framework l_tests(argc, (char**)l_argv);

        std::streambuf* prevstr = std::cout.rdbuf();
        std::cout.rdbuf(sCatch.rdbuf());

        try {
            CPPUNIT_ASSERT_EQUAL_MESSAGE(sCatch.str(), 0, l_tests.run());
            CPPUNIT_ASSERT_EQUAL_MESSAGE(sCatch.str(), expected_l, sCatch.str());
        } catch (...) {
            std::cout.rdbuf(prevstr);
            throw;
        }

        std::cout.rdbuf(prevstr);
    }

    sCatch.str("");
    sCatch.clear();

    {
        const char* t_argv[argc] = { "./framework", "-tTestString" };
        std::string expected_t("TestString::test_stringDisplaying something. : OK\n");
        moctest::Framework t_tests(argc, (char**)t_argv);
        t_tests.register_suite(TestString());

        std::streambuf* prevstr = std::cout.rdbuf();
        std::cout.rdbuf(sCatch.rdbuf());

        try {
            CPPUNIT_ASSERT_EQUAL_MESSAGE(sCatch.str(), 0, t_tests.run());
            CPPUNIT_ASSERT_EQUAL_MESSAGE(sCatch.str(), expected_t, sCatch.str());
        } catch (...) {
            std::cout.rdbuf(prevstr);
            throw;
        }

        std::cout.rdbuf(prevstr);
    }
}

int main(int argc, char* argv[])
{
    moctest::Framework tests(argc, argv);
    tests.register_suite(TestFramework());
    return tests.run();
}
