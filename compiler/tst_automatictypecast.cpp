#include <QTest>
#include <QString>
#include "automatictypecast.h"

class TestAutomaticTypeCast : public QObject {
    Q_OBJECT

public:
    TestAutomaticTypeCast() { }

private Q_SLOTS:

    void testCode() {
        QWARN("No test implemented");
    }

};

QTEST_APPLESS_MAIN(TestAutomaticTypeCast)

#include "tst_automatictypecast.moc"



