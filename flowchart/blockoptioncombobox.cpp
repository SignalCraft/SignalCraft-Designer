#include "flowchart/blockoptioncombobox.h"

#include "gui/blockoptioncontrol.h"
#include "gui/blockoptioncontrolcombobox.h"
#include <QString>
#include <QMap>
#include "flowchart/jsonforqt.h"
#include <QJsonValue>
#include <QJsonObject>

BlockOptionComboBox::BlockOptionComboBox(QString displayName, QString defaultValue, QMap<QString, QString> choices) : BlockOption(displayName, defaultValue, BLOCK_OPTION_TYPE_COMBOBOX) {
    m_choices = choices;
}

BlockOptionControl *BlockOptionComboBox::makeControl() const {
    BlockOptionControlComboBox *control = new BlockOptionControlComboBox(displayName(), m_choices);
    return control;
}

QJsonValue BlockOptionComboBox::toJson() const {
    QJsonObject nodeObj = BlockOption::toJson().toObject();
    nodeObj["choices"] = QMap_QString_QString_toJson(m_choices);
    return nodeObj;
}


