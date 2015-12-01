#include "gui/blockoptioncontrolinteger.h"
#include <QWidget>
#include <QString>
#include <QSpinBox>
#include <QVBoxLayout>

BlockOptionControlInteger::BlockOptionControlInteger(const QString & title, int minimum, int maximum, QWidget *parent) : BlockOptionControl(title, parent) {
    m_control = new QSpinBox(this);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(m_control);
    this->setLayout(vbox);
    m_control->setMinimum(minimum);
    m_control->setMaximum(maximum);
}

QString BlockOptionControlInteger::textValue() const {
    return m_control->cleanText();
}

void BlockOptionControlInteger::setCurrentValue(QString value) {
    m_control->setValue(value.toInt());
}
