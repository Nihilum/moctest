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

#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

#include <moctest/FindTest.hpp>
#include <moctest/ListTests.hpp>
#include <moctest/FindRegTest.hpp>
#include <moctest/Framework/Framework.hpp>

namespace moctest {

    Framework::Framework(int argc, char **argv)
            : m_po(argc, argv) {
    }

    int Framework::run() {
        if (!m_po.parse_options()) {
            return 1;
        }

        if (m_po.asked_for_help()) {
            std::cout << "Possible options:\n";
            std::cout << "--help (-h)\tshows this help message\n";
            std::cout << "--list (-l)\tshows the list of all possible tests\n";
            std::cout << "--test (-t) <test_name1> [<test_name2>...]\truns given tests only\n";
            std::cout << "--regtest (-r) <name_regex> runs only tests which names match given regexp\n";
            return 0;
        }

        if (m_po.asked_for_list()) {
            std::stringstream sStr;
            ListTests list_tests;
            list_tests(sStr, get_registry()->makeTest());
            std::cout << sStr.str() << std::endl;
            return 0;
        }

        CPPUNIT_NS::TextUi::TestRunner runner;

        if (m_po.asked_to_run_only_some_tests()) {
            FindTest find_test;

            for (auto &name : m_po.get_tests_to_run()) {
                CPPUNIT_NS::Test *test = find_test(name, get_registry()->makeTest());

                if (test == nullptr) {
                    std::cerr << "Cannot find test '" << name << "'!" << std::endl;
                    return 1;
                }

                runner.addTest(test);
            }
        } else if (m_po.asked_for_regtest()) {
            FindRegTest find_regtest;

            try {
                auto tests_to_run = find_regtest(m_po.get_regtest(), get_registry()->makeTest());

                for (auto &test : tests_to_run) {
                    runner.addTest(test);
                }
            } catch (const std::exception &e) {
                std::cerr << "Cannot match your regexp: " << e.what() << std::endl;
                return 1;
            }
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

        return result.wasSuccessful() ? 0 : 1;
    }

    CPPUNIT_NS::TestFactoryRegistry *Framework::get_registry() {
        return &CPPUNIT_NS::TestFactoryRegistry::getRegistry();
    }

}
