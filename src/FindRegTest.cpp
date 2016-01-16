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
 * @file src/FindRegTest.cpp
 *
 * @desc FindRegTest functor.
 */

#include <cstdint>

#include <cppunit/Test.h>

#include <moctest/FindRegTest.hpp>

namespace moctest {

    FindRegTest::TestsList FindRegTest::operator()(const FindRegTest::RegularExpression &reg_expr,
                                                   gsl::not_null<CPPUNIT_NS::Test *> test) const {
        Expects(!reg_expr.empty());
        std::regex expr(reg_expr);
        return internal_find(expr, test);
    }

    /**
     * Travere through the test tree and find test names that are matching the given regular expression.
     */
    FindRegTest::TestsList FindRegTest::internal_find(const std::regex &expr,
                                                      gsl::not_null<CPPUNIT_NS::Test *> test) const {
        std::vector<CPPUNIT_NS::Test *> foundTests;

        if (std::regex_match(test->getName(), expr)) {
            foundTests.push_back(test.get());
            return foundTests; // since we have added parent, all children are included
        }

        for (uint16_t i = 0; i < test->getChildTestCount(); ++i) {
            std::vector<CPPUNIT_NS::Test *> childTests = internal_find(expr, test->getChildTestAt(i));

            if (!childTests.empty()) {
                foundTests.insert(foundTests.end(), childTests.begin(), childTests.end());
            }
        }

        return foundTests;
    }

}
