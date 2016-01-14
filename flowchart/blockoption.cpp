#include "blockoption.h"

#include <QJsonValue>
#include <QSharedPointer>
#include "flowchart/blockoptioninteger.h"
#include "flowchart/blockoptioncombobox.h"
#include "flowchart/blockoptioninteger.h"
#include <QJsonObject>
#include "jsonforqt.h"

BlockOption::BlockOption(QString displayName, QString defaultValue, BlockOptionType type) {
    m_displayName = displayName;
    m_defaultValue = defaultValue;
    m_type = type;
}

QString BlockOption::displayName() const {
    return m_displayName;
}

QString BlockOption::defaultValue() const {
    return m_defaultValue;
}

BlockOptionType BlockOption::type() const {
    return m_type;
}

BlockOptionControl *BlockOption::makeControl(QString currentValue) const {
    BlockOptionControl *control = makeControl();
    control->setCurrentValue(currentValue);
    return control;
}

QJsonValue BlockOption::toJson() const {
    QJsonObject nodeObj;
    nodeObj["displayName"] = displayName();
    nodeObj["defaultValue"] = defaultValue();
    nodeObj["type"] = BlockOptionType_toJson(type());
    return nodeObj;
}

QJsonValue BlockOptionType_toJson(BlockOptionType obj) {
    return QJsonValue((int)obj);
}

BlockOptionType BlockOptionType_fromJson(QJsonValue node) {
    return (BlockOptionType)(node.toInt());
}

QJsonValue BlockOption_toJson(QSharedPointer<const BlockOption> obj) {
    return obj->toJson();
}

QSharedPointer<const BlockOption> BlockOption_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    QString displayName = nodeObj["displayName"].toString();
    QString defaultValue = nodeObj["defaultValue"].toString();
    BlockOptionType type = BlockOptionType_fromJson(nodeObj["type"]);
    switch (type) {
    case BLOCK_OPTION_TYPE_COMBOBOX: {
        QMap<QString, QString> choices = QMap_QString_QString_fromJson(nodeObj["choices"]);
        return QSharedPointer<const BlockOption>(new BlockOptionComboBox(displayName, defaultValue, choices));
    }
    case INTEGER: {
        int minimum = nodeObj["minimum"].toInt();
        int maximum = nodeObj["maximum"].toInt();
        return QSharedPointer<const BlockOption>(new BlockOptionInteger(displayName, defaultValue, minimum, maximum));
    }
    default:
        return QSharedPointer<const BlockOption>();
    }
}

