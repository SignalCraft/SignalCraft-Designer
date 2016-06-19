#ifndef TST_BLOCK_H
#define TST_BLOCK_H

#include <QString>
#include <QtTest>

class TestBlock : public QObject
{
    Q_OBJECT

public:
    TestBlock();

private Q_SLOTS:
    void testCase1();
};

#endif // TST_BLOCK_H
