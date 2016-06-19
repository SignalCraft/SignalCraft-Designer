#include "blockoptioninteger.h"
#include "blockoptioncontrol.h"
#include "blockoptioncontrolinteger.h"
#include <QString>
#include <QJsonValue>
#include <QJsonObject>

BlockOptionInteger::BlockOptionInteger(QString displayName, QString defaultValue, int minimum, int maximum) : BlockOption(displayName, defaultValue, BLOCK_OPTION_TYPE_INTEGER) {
    m_minimum = minimum;
    m_maximum = maximum;
}

BlockOptionControl *BlockOptionInteger::makeControl() const {
    BlockOptionControlInteger *control = new BlockOptionControlInteger(displayName(), m_minimum, m_maximum);
    return control;
}

QJsonValue BlockOptionInteger::toJson() const {
    QJsonObject nodeObj = BlockOption::toJson().toObject();
    nodeObj["minimum"] = m_minimum;
    nodeObj["maximum"] = m_maximum;
    return nodeObj;
}
