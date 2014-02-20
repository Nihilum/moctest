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
 * @file src/Framework/ProgramOptions.cpp
 *
 * @desc ProgramOptions support for moctest::Framework.
 */

#include <iostream>

#include <boost/program_options.hpp>

#include <moctest/Framework/ProgramOptions.hpp>

namespace moctest
{

ProgramOptions::ProgramOptions(int argc, char** argv)
: m_argc(argc), m_argv(argv), m_vm(new po::variables_map)
{
}

ProgramOptions::~ProgramOptions()
{
}

bool ProgramOptions::parse_options()
{
    // Options allowed only with the command line
    po::options_description po_cmdline("Command Line options");

    po_cmdline.add_options()
        ("help,h", "show help message")
        ("list,l", "show test list")
        ("test,t", po::value< std::vector<std::string> >(&m_tests)->multitoken(), "runs given tests only")
        ("regtest,r", po::value<std::string>(&m_regtest), "runs only tests which names match given regexp")
        ;

    try {
        store(po::command_line_parser(m_argc, m_argv).options(po_cmdline).run(), *m_vm);
        notify(*m_vm);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

bool ProgramOptions::asked_for_help() const { return m_vm->count("help") >= 1; }
bool ProgramOptions::asked_for_list() const { return m_vm->count("list") >= 1; }
bool ProgramOptions::asked_to_run_only_some_tests() const { return m_vm->count("test") >= 1; }
bool ProgramOptions::asked_for_regtest() const { return m_vm->count("regtest") >= 1; }

}
