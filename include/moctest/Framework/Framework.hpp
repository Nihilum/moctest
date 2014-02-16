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
 * @file moctest/Framework/Framework.hpp
 *
 * @desc Framework encapsulating CPPUNIT.
 */

#ifndef MOCTEST_FRAMEWORK_FRAMEWORK_HPP
#define MOCTEST_FRAMEWORK_FRAMEWORK_HPP

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <moctest/Config.hpp>
#include <moctest/Framework/ProgramOptions.hpp>

namespace moctest
{

class MOCTEST_DLL_PUBLIC Framework
{
public:
    Framework(int argc, char** argv);

    template <typename T>
    void register_suite(T& test_suite)
    {
        static CPPUNIT_NS::TestSuiteFactory<T> factory;
        get_registry()->registerFactory(&factory);
    }

    int run();

protected:
    CPPUNIT_NS::TestFactoryRegistry* get_registry();

protected:
    ProgramOptions m_po;
};

}

#endif // MOCTEST_FRAMEWORK_FRAMEWORK_HPP
