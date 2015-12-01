#include "flowchart/blockoptioncombobox.h"
#include "gui/blockoptioncontrol.h"
#include "gui/blockoptioncontrolcombobox.h"
#include <QString>
#include <QMap>

BlockOptionComboBox::BlockOptionComboBox(QString displayName, QString defaultValue, QMap<QString, QString> choices) : BlockOption(displayName, defaultValue) {
    m_choices = choices;
}

BlockOptionControl *BlockOptionComboBox::makeControl() const {
    BlockOptionControlComboBox *control = new BlockOptionControlComboBox(displayName(), m_choices);
    return control;
}


