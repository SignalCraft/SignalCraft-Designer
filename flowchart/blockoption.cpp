#include "blockoption.h"

#include <QJsonValue>
#include <QSharedPointer>
#include "flowchart/blockoptioninteger.h"

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

QJsonValue BlockOption_toJson(QSharedPointer<const BlockOption> obj) {
    return QJsonValue();
}

QSharedPointer<const BlockOption> BlockOption_fromJson(QJsonValue node) {
    return QSharedPointer<const BlockOption>(new BlockOptionInteger("", "", 0, 0));
}

