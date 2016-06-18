#include "tst_flowchart.h"

#include <QTest>
#include <QString>

TestFlowchart::TestFlowchart() { }

void TestFlowchart::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestFlowchart)
