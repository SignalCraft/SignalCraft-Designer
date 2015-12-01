#include "blockoptioncontrol.h"

#include <QString>
#include <QWidget>

BlockOptionControl::BlockOptionControl(const QString & title, QWidget *parent) : QGroupBox(title, parent) { }

void BlockOptionControl::setCurrentValue(QString value) { }

QString BlockOptionControl::textValue() const {
    // TODO: throw
    return "bad";
}
