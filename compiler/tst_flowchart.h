#ifndef TESTFLOWCHART_H
#define TESTFLOWCHART_H

#include <QObject>

class TestFlowchart : public QObject
{
    Q_OBJECT
public:
    TestFlowchart();

private Q_SLOTS:
    void testCase1();
};

#endif // TESTFLOWCHART_H
