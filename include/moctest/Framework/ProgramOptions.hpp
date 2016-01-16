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
 * @file moctest/Framework/ProgramOptions.hpp
 *
 * @desc ProgramOptions support for moctest::Framework.
 */

#ifndef MOCTEST_FRAMEWORK_PROGRAMOPTIONS_HPP
#define MOCTEST_FRAMEWORK_PROGRAMOPTIONS_HPP

#include <string>
#include <memory>
#include <vector>

#include <moctest/Config.hpp>

namespace boost {

    namespace program_options {
        class variables_map;
    }

}

namespace po = boost::program_options;

namespace moctest {

    class MOCTEST_DLL_PUBLIC ProgramOptions final {
    public:
        using TestsList = std::vector<std::string>;
        using RegularExpression = std::string;
        using ProgramVariables = std::unique_ptr<po::variables_map>;

    public:
        ProgramOptions(int argc, const char *const *argv);

        ~ProgramOptions();

        bool parse_options();

        bool asked_for_help() const;

        bool asked_for_list() const;

        bool asked_to_run_only_some_tests() const;

        bool asked_for_regtest() const;

        const TestsList &get_tests_to_run() const { return m_tests; }

        const RegularExpression &get_regtest() const { return m_regtest; }

    private:
        int m_argc;
        const char *const *m_argv;
        ProgramVariables m_program_variables;
        TestsList m_tests;
        RegularExpression m_regtest;
    };

}

#endif // MOCTEST_FRAMEWORK_PROGRAMOPTIONS_HPP
