#include "blockoptioncontrolcombobox.h"
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMap>
#include <QVariant>

BlockOptionControlComboBox::BlockOptionControlComboBox(const QString & title, QMap<QString, QString> choices, QWidget *parent) : BlockOptionControl(title, parent) {
    m_control = new QComboBox(this);
    for (QString key : choices.keys()) {
        QString value = choices[key];
        m_control->addItem(key, QVariant(value));
    }
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(m_control);
    this->setLayout(vbox);
}

QString BlockOptionControlComboBox::textValue() const {
    return m_control->itemData(m_control->currentIndex()).toString();
}

void BlockOptionControlComboBox::setCurrentValue(QString value) {
    m_control->setCurrentIndex(m_control->findData(QVariant(value)));
}
