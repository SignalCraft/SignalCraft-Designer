#include <QTest>
#include <QString>
#include "lisp_exp.h"
#include <QList>

class TestLispExp : public QObject {
    Q_OBJECT

public:
    TestLispExp() { }

private Q_SLOTS:

    void testParseEmptyList() {
        lisp_exp result = lisp_exp::parseString("()");
        QList<lisp_exp> elements;
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseEmptyListPrependedSpaces() {
        lisp_exp result = lisp_exp::parseString("  ()");
        QList<lisp_exp> elements;
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseEmptyListInnerSpaces() {
        lisp_exp result = lisp_exp::parseString("(  )");
        QList<lisp_exp> elements;
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseEmptyListAppendedSpaces() {
        lisp_exp result = lisp_exp::parseString("()  ");
        QList<lisp_exp> elements;
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseEmptyListAllSpaces() {
        lisp_exp result = lisp_exp::parseString("  (  )  ");
        QList<lisp_exp> elements;
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseEmptyListWhitespace() {
        lisp_exp result = lisp_exp::parseString(" \t\n ( \t\n ) \t\n ");
        QList<lisp_exp> elements;
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseSingleLeaf() {
        lisp_exp result = lisp_exp::parseString("(abc)");
        QList<lisp_exp> elements;
        elements.push_back(lisp_exp("abc"));
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseSingleLeafWhitespace() {
        lisp_exp result = lisp_exp::parseString(" \t\n ( \t\n abc \t\n ) \t\n ");
        QList<lisp_exp> elements;
        elements.push_back(lisp_exp("abc"));
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseMultiLeaf() {
        lisp_exp result = lisp_exp::parseString("(abc def ghi)");
        QList<lisp_exp> elements;
        elements.push_back(lisp_exp("abc"));
        elements.push_back(lisp_exp("def"));
        elements.push_back(lisp_exp("ghi"));
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseMultiLeafWhitespace() {
        lisp_exp result = lisp_exp::parseString(" \t\n ( \t\n abc \t\n def \t\n ghi \t\n ) \t\n ");
        QList<lisp_exp> elements;
        elements.push_back(lisp_exp("abc"));
        elements.push_back(lisp_exp("def"));
        elements.push_back(lisp_exp("ghi"));
        lisp_exp expected(elements);
        QCOMPARE(result, expected);
    }

    void testParseBigTree() {
        lisp_exp result = lisp_exp::parseString("(()(abc)((def ghi)()(jkl mno))(pqr)())");
        QList<lisp_exp> emptyList;
        QList<lisp_exp> list1;
        QList<lisp_exp> list2;
        QList<lisp_exp> list3;
        QList<lisp_exp> list4;
        QList<lisp_exp> innerList;
        QList<lisp_exp> baseList;
        list1.push_back(lisp_exp("abc"));
        list2.push_back(lisp_exp("def"));
        list2.push_back(lisp_exp("ghi"));
        list3.push_back(lisp_exp("jkl"));
        list3.push_back(lisp_exp("mno"));
        list4.push_back(lisp_exp("pqr"));
        innerList.push_back(lisp_exp(list2));
        innerList.push_back(lisp_exp(emptyList));
        innerList.push_back(lisp_exp(list3));
        baseList.push_back(lisp_exp(emptyList));
        baseList.push_back(lisp_exp(list1));
        baseList.push_back(lisp_exp(innerList));
        baseList.push_back(lisp_exp(list4));
        baseList.push_back(lisp_exp(emptyList));
        lisp_exp expected(baseList);
        QCOMPARE(result, expected);
    }

    void testParseInvalidEmptyString() {
        lisp_exp result = lisp_exp::parseString("");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidSpaces() {
        lisp_exp result = lisp_exp::parseString(" ");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidWhiteSpace() {
        lisp_exp result = lisp_exp::parseString(" \t\n ");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidSingleOpen() {
        lisp_exp result = lisp_exp::parseString("(");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidSingleClose() {
        lisp_exp result = lisp_exp::parseString(")");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidOpenToken() {
        lisp_exp result = lisp_exp::parseString("(abc");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidTokenClose() {
        lisp_exp result = lisp_exp::parseString("abc)");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidMultipleList() {
        lisp_exp result = lisp_exp::parseString("(abc)(def)");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidNegativeDepth() {
        lisp_exp result = lisp_exp::parseString("((abc)def))((ghi(jkl))");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidPrependedToken() {
        lisp_exp result = lisp_exp::parseString("abc()");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidAppendedToken() {
        lisp_exp result = lisp_exp::parseString("()abc");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidBigTreeUnbalancedPositive() {
        lisp_exp result = lisp_exp::parseString("(()(abc)((def ghi)()(jkl mno))(pqr)()");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }

    void testParseInvalidBigTreeUnbalancedNegative() {
        lisp_exp result = lisp_exp::parseString("()(abc)((def ghi)()(jkl mno))(pqr)())");
        lisp_exp expected; // invalid
        QCOMPARE(result, expected);
    }


};

QTEST_APPLESS_MAIN(TestLispExp)

#include "tst_lisp_exp.moc"



