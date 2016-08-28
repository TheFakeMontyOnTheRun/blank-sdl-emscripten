#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include <functional>
#include <array>


using namespace CppUnit;

class TrivialPursuit : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(TrivialPursuit);
    CPPUNIT_TEST(testTrivial);
    CPPUNIT_TEST(testToFail);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp() {
    }

    virtual void tearDown() {
    }

    void testTrivial();

    void testToFail();
};

void TrivialPursuit::testTrivial() {
    CPPUNIT_ASSERT(1 == 1);
}

void TrivialPursuit::testToFail() {
    CPPUNIT_ASSERT(1 == 0);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TrivialPursuit);

int main(int argc, char *argv[]) {

    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener(&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener(&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write();

    // Output XML for Jenkins CPPunit plugin
    std::ofstream xmlFileOut("cppTestResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
