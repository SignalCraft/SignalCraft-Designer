#include <QTest>
#include <QString>
#include "block.h"

class TestBlock : public QObject
{
    Q_OBJECT

public:
    TestBlock() { }

private Q_SLOTS:
    void testCase1(){
		Block b("myType", QPointF());
		QVERIFY2(b.blockTypeName() == "myType", "Failure");
	}
};

QTEST_APPLESS_MAIN(TestBlock)

#include "tst_block.moc"



