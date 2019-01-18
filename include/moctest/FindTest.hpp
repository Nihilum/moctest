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
 * @file moctest/FindTest.hpp
 *
 * @desc FindTest functor.
 */

#ifndef MOCTEST_FINDTEST_HPP
#define MOCTEST_FINDTEST_HPP

#include <gsl/gsl>

#include <string>

#include <moctest/Config.hpp>

namespace CPPUNIT_NS {
    class Test;
}

namespace moctest {

    class MOCTEST_DLL_PUBLIC FindTest final {
    public:
        CPPUNIT_NS::Test *operator()(const std::string &test_name, gsl::not_null<CPPUNIT_NS::Test *> test) const;
    };

}

#endif // MOCTEST_FINDTEST_HPP
