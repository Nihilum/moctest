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
 * @file src/Framework/Framework.cpp
 *
 * @desc Framework encapsulating CPPUNIT.
 */

#include <sstream>

#include <gsl.h>

#include <cppunit/CompilerOutputter.h>

#include <moctest/FindTest.hpp>
#include <moctest/ListTests.hpp>
#include <moctest/FindRegTest.hpp>
#include <moctest/Framework/Framework.hpp>

namespace moctest {
    Framework::Framework(int argc, char **argv)
            : m_program_options(argc, argv) {
    }

    Framework::ReturnCode Framework::run() {
        Ensures(m_program_options.parse_options());

        if (m_program_options.asked_for_help()) {
            return help();
        }

        if (m_program_options.asked_for_list()) {
            return list();
        }

        CPPUNIT_NS::TextUi::TestRunner runner;

        if (m_program_options.asked_to_run_only_some_tests()) {
            Ensures(combine_tests_subset(runner));
        } else if (m_program_options.asked_for_regtest()) {
            Ensures(combine_regtest_subset(runner));
        } else {
            runner.addTest(get_registry()->makeTest());
        }

        CPPUNIT_NS::TestResult controller;

        CPPUNIT_NS::TestResultCollector result;
        controller.addListener(&result);

        CPPUNIT_NS::BriefTestProgressListener progress;
        controller.addListener(&progress);
        runner.run(controller);

        CPPUNIT_NS::CompilerOutputter outputter(&result, std::cerr);
        outputter.write();

        return result.wasSuccessful() ? SUCCESS : FAILURE;
    }

    CPPUNIT_NS::TestFactoryRegistry *Framework::get_registry() const {
        return &CPPUNIT_NS::TestFactoryRegistry::getRegistry();
    }

    Framework::ReturnCode Framework::help() const {
        std::cout << "Possible options:\n";
        std::cout << "--help (-h)\tshows this help message\n";
        std::cout << "--list (-l)\tshows the list of all possible tests\n";
        std::cout << "--test (-t) <test_name1> [<test_name2>...]\truns given tests only\n";
        std::cout << "--regtest (-r) <name_regex> runs only tests which names match given regexp\n";
        return SUCCESS;
    }

    Framework::ReturnCode Framework::list() const {
        std::stringstream sStr;
        ListTests list_tests;
        list_tests(sStr, get_registry()->makeTest());
        std::cout << sStr.str() << std::endl;
        return SUCCESS;
    }

    bool Framework::combine_tests_subset(CPPUNIT_NS::TextUi::TestRunner &runner) const {
        FindTest find_test;

        for (auto &name : m_program_options.get_tests_to_run()) {
            CPPUNIT_NS::Test *test = find_test(name, get_registry()->makeTest());

            if (test == nullptr) {
                std::cerr << "Cannot find test '" << name << "'!" << std::endl;
                return false;
            }

            runner.addTest(test);
        }

        return true;
    }

    bool Framework::combine_regtest_subset(CPPUNIT_NS::TextUi::TestRunner &runner) const {
        FindRegTest find_regtest;

        try {
            auto tests_to_run = find_regtest(m_program_options.get_regtest(), get_registry()->makeTest());

            for (auto &test : tests_to_run) {
                runner.addTest(test);
            }
        } catch (const std::exception &e) {
            std::cerr << "Cannot match your regexp: " << e.what() << std::endl;
            return false;
        }

        return true;
    }
}
