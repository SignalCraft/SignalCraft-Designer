#include <QTest>
#include <QString>
#include "block.h"
#include "blockpin.h"
#include <QHash>
#include <QPointF>
#include <QSet>

class TestBlock : public QObject {
    Q_OBJECT

public:
    TestBlock() { }

private Q_SLOTS:

    void testIsValid() {
        Block invalid0;
        Block invalid1("", QPointF(5,5));
        Block valid0("aaa", QPointF(0,0));
        QVERIFY2(!invalid0.isValid(), "Default constructor fails to create invalid block");
        QVERIFY2(!invalid1.isValid(), "Empty blockTypeName fails to create invalid block");
        QVERIFY2(valid0.isValid(), "Non-empty blockTypeName fails to create valid block");
    }

    void testPos() {
        Block empty;
        Block zero("aaa", QPointF(0,0));
        Block oneMinusFive("bbb", QPointF(1, -5));
        QCOMPARE(empty.pos(), QPointF(0,0));
        QCOMPARE(zero.pos(), QPointF(0,0));
        QCOMPARE(oneMinusFive.pos(), QPointF(1,-5));
    }

    void testBlockTypeName() {
        Block empty;
        Block setEmpty("", QPointF());
        Block aaa("aaa", QPointF());
        QCOMPARE(empty.blockTypeName(), QString(""));
        QCOMPARE(setEmpty.blockTypeName(), QString(""));
        QCOMPARE(aaa.blockTypeName(), QString("aaa"));
    }

    void testHasInputConnections() {
        Block constructor0;
        Block constructor1("a", QPointF());
        QHash<QString, BlockPin> inputConnections;
        QHash<QString, QSet<BlockPin>> outputConnections;
        Block setEmpty("a", QPointF(), inputConnections, outputConnections);
        inputConnections.insert("", BlockPin(1, "in1"));
        Block setOneEmptyString("a", QPointF(), inputConnections, outputConnections);
        inputConnections.remove("");
        inputConnections.insert("w", BlockPin());
        Block setOneInvalid("a", QPointF(), inputConnections, outputConnections);
        Block setOneInvalidDelete("a", QPointF(), inputConnections, outputConnections);
        setOneInvalidDelete.disconnectInput("w");
        inputConnections.insert("w", BlockPin(1, "in1"));
        Block setOneValid("a", QPointF(), inputConnections, outputConnections);
        Block setOneValidDelete("a", QPointF(), inputConnections, outputConnections);
        setOneValidDelete.disconnectInput("w");
        inputConnections.insert("x", BlockPin(2, "in2"));
        Block setTwoValidDeleteOne("a", QPointF(), inputConnections, outputConnections);
        setTwoValidDeleteOne.disconnectInput("x");
        inputConnections.insert("x", BlockPin());
        Block setOneValidOneInvalidDeleteInvalid("a", QPointF(), inputConnections, outputConnections);
        setOneValidOneInvalidDeleteInvalid.disconnectInput("x");
        Block setOneValidOneInvalidDeleteValid("a", QPointF(), inputConnections, outputConnections);
        setOneValidOneInvalidDeleteValid.disconnectInput("w");

        QVERIFY2(!constructor0.hasInputConnections(), "Default constructor fails to have no input connections");
        QVERIFY2(!constructor1.hasInputConnections(), "2-parameter constructor fails to have no input connections");
        QVERIFY2(!setEmpty.hasInputConnections(), "Empty initializer fails to have no input connections");
        QVERIFY2(setOneEmptyString.hasInputConnections(), "Fails to accept empty string wire name as input connection");
        QVERIFY2(setOneInvalid.hasInputConnections(), "Fails to accept invalid BlockPin as input connection");
        QVERIFY2(!setOneInvalidDelete.hasInputConnections(), "Fails to properly delete input connection to invalid BlockPin");
        QVERIFY2(setOneValid.hasInputConnections(), "Fails to accept input connection");
        QVERIFY2(!setOneValidDelete.hasInputConnections(), "Fails to properly delete input connection");
        QVERIFY2(setTwoValidDeleteOne.hasInputConnections(), "Fails to keep all input connections when some are deleted");
        QVERIFY2(setOneValidOneInvalidDeleteInvalid.hasInputConnections(), "Fails to keep all input connections when some are deleted");
        QVERIFY2(setOneValidOneInvalidDeleteValid.hasInputConnections(), "Fails to keep all input connections when some are deleted");
    }

    void testInputConnection() {
        Block constructor0;
        Block constructor1("a", QPointF());
        QHash<QString, BlockPin> inputConnections;
        QHash<QString, QSet<BlockPin>> outputConnections;
        Block setEmpty("a", QPointF(), inputConnections, outputConnections);
        inputConnections.insert("", BlockPin(1, "in1"));
        Block setOneEmptyString("a", QPointF(), inputConnections, outputConnections);
        inputConnections.remove("");
        inputConnections.insert("w", BlockPin());
        Block setOneInvalid("a", QPointF(), inputConnections, outputConnections);
        Block setOneInvalidDelete("a", QPointF(), inputConnections, outputConnections);
        setOneInvalidDelete.disconnectInput("w");
        inputConnections.insert("w", BlockPin(1, "in1"));
        Block setOneValid("a", QPointF(), inputConnections, outputConnections);
        Block setOneValidDelete("a", QPointF(), inputConnections, outputConnections);
        setOneValidDelete.disconnectInput("w");
        inputConnections.insert("x", BlockPin(2, "in2"));
        Block setTwoValidDeleteOne("a", QPointF(), inputConnections, outputConnections);
        setTwoValidDeleteOne.disconnectInput("x");
        inputConnections.insert("x", BlockPin());
        Block setOneValidOneInvalidDeleteInvalid("a", QPointF(), inputConnections, outputConnections);
        setOneValidOneInvalidDeleteInvalid.disconnectInput("x");
        Block setOneValidOneInvalidDeleteValid("a", QPointF(), inputConnections, outputConnections);
        setOneValidOneInvalidDeleteValid.disconnectInput("w");
        inputConnections.insert("x", BlockPin(2, "in2"));
        Block setTwoValid("a", QPointF(), inputConnections, outputConnections);

        QCOMPARE(constructor0.inputConnection(""), BlockPin());
        QCOMPARE(constructor0.inputConnection("w"), BlockPin());
        QCOMPARE(constructor1.inputConnection(""), BlockPin());
        QCOMPARE(setEmpty.inputConnection(""), BlockPin());
        QCOMPARE(setOneEmptyString.inputConnection(""), BlockPin(1, "in1"));
        QCOMPARE(setOneInvalid.inputConnection("w"), BlockPin());
        QCOMPARE(setOneInvalidDelete.inputConnection("w"), BlockPin());
        QCOMPARE(setOneValid.inputConnection("w"), BlockPin(1, "in1"));
        QCOMPARE(setOneValidDelete.inputConnection("w"), BlockPin());
        QCOMPARE(setTwoValidDeleteOne.inputConnection("w"), BlockPin(1, "in1"));
        QCOMPARE(setTwoValidDeleteOne.inputConnection("x"), BlockPin());
        QCOMPARE(setOneValidOneInvalidDeleteInvalid.inputConnection("w"), BlockPin(1, "in1"));
        QCOMPARE(setOneValidOneInvalidDeleteInvalid.inputConnection("x"), BlockPin());
        QCOMPARE(setOneValidOneInvalidDeleteValid.inputConnection("w"), BlockPin());
        QCOMPARE(setOneValidOneInvalidDeleteValid.inputConnection("x"), BlockPin());
        QCOMPARE(setTwoValid.inputConnection("w"), BlockPin(1, "in1"));
        QCOMPARE(setTwoValid.inputConnection("x"), BlockPin(2, "in2"));
    }

    void testOutputConnection() {
        QWARN("No test implemented");
    }

    void testOptionValue() {
        QWARN("No test implemented");
    }

    void testConnectOutput() {
        QWARN("No test implemented");
    }

    void testDisconnectOutput() {
        QWARN("No test implemented");
    }

    void testConnectInput() {
        QWARN("No test implemented");
    }

    void testDisconnectInput() {
        QWARN("No test implemented");
    }

    void testSetPos() {
        QWARN("No test implemented");
    }

    void testSetOptionValue() {
        QWARN("No test implemented");
    }

    void testResetOptionValues() {
        QWARN("No test implemented");
    }

    void testBlockToJson() {
        QWARN("No test implemented");
    }

    void testBlockFromJson() {
        QWARN("No test implemented");
    }

    void testQHashIntBlockToJson() {
        QWARN("No test implemented");
    }

    void testQHashIntBlockFromJson() {
        QWARN("No test implemented");
    }

    void testQMapIntBlockToJson() {
        QWARN("No test implemented");
    }

    void testQMapIntBlockFromJson() {
        QWARN("No test implemented");
    }
};

QTEST_APPLESS_MAIN(TestBlock)

#include "tst_block.moc"



