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
 * @file src/ListTests.cpp
 *
 * @desc Tests listing implementation.
 */

#include <cppunit/Test.h>

#include <moctest/ListTests.hpp>

namespace moctest
{

ListTests::ListTests()
 : m_top_level(true)
{
}

void ListTests::operator()(std::stringstream& sStr, CPPUNIT_NS::Test* test, uint16_t tabs)
{
    if (test == nullptr) {
        return;
    }

    bool local_level = m_top_level;

    if (m_top_level) {
        sStr << "Available tests:\n";
        sStr << "- " << test->getName() << "\n";
        m_top_level = false;
    } else {
        for (uint16_t i = 0; i < tabs; ++i) {
            sStr << "\t";
        }

        sStr << "- " << test->getName() << "\n";
    }

    for (uint16_t i = 0; i < test->getChildTestCount(); ++i) {
        operator()(sStr, test->getChildTestAt(i), tabs + (uint16_t)1);
    }

    m_top_level = local_level;
}

}
