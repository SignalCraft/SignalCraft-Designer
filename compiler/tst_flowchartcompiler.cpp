#include <QTest>
#include <QString>
#include "flowchart.h"

class TestFlowChartCompiler : public QObject {
    Q_OBJECT

public:
    TestFlowChartCompiler() { }

private Q_SLOTS:

    void testIsExpandable() {
        QWARN("No test implemented");
    }

    void testExtractUniqueBlockNames() {
        QWARN("No test implemented");
    }

    void testExtractInputBlocks() {
        QWARN("No test implemented");
    }

    void testGeneratePicCode() {
        QWARN("No test implemented");
    }

};

QTEST_APPLESS_MAIN(TestFlowChartCompiler)

#include "tst_flowchartcompiler.moc"



