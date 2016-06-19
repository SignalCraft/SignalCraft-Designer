#include "tst_block.h"

#include <QTest>
#include <QString>

TestBlock::TestBlock()
{
}

void TestBlock::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestBlock)
