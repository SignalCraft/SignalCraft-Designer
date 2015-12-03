#include "blockoption.h"

BlockOption::BlockOption(QString displayName, QString defaultValue) {
    m_displayName = displayName;
    m_defaultValue = defaultValue;
}

QString BlockOption::displayName() const {
    return m_displayName;
}

QString BlockOption::defaultValue() const {
    return m_defaultValue;
}

BlockOptionControl *BlockOption::makeControl(QString currentValue) const {
    BlockOptionControl *control = makeControl();
    control->setCurrentValue(currentValue);
    return control;
}

