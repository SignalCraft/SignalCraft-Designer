#include "tst_block.h"

#include <QTest>
#include <QString>

#include "block.h"

TestBlock::TestBlock()
{
}

void TestBlock::testCase1()
{
    Block b("mytype", QPointF(4,5));
    QVERIFY2(b.blockTypeName() == "mytype", "Failure");
}

QTEST_APPLESS_MAIN(TestBlock)
