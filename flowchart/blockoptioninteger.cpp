#include "flowchart/blockoptioninteger.h"
#include "gui/blockoptioncontrol.h"
#include "gui/blockoptioncontrolinteger.h"
#include <QString>

BlockOptionInteger::BlockOptionInteger(QString displayName, QString defaultValue, int minimum, int maximum) : BlockOption(displayName, defaultValue) {
    m_minimum = minimum;
    m_maximum = maximum;
}

BlockOptionControl *BlockOptionInteger::makeControl() const {
    BlockOptionControlInteger *control = new BlockOptionControlInteger(displayName(), m_minimum, m_maximum);
    return control;
}

