#ifndef BLOCKOPTIONCONTROLINTEGER_H
#define BLOCKOPTIONCONTROLINTEGER_H

#include "gui/blockoptioncontrol.h"
#include <QString>
#include <QWidget>
#include <QSpinBox>

class BlockOptionControlInteger : public BlockOptionControl {
public:
    explicit BlockOptionControlInteger(const QString & title, int minimum, int maximum, QWidget *parent = 0);
    virtual void setCurrentValue(QString value) override;
    virtual QString textValue() const override;
private:
    QSpinBox *m_control;
};

#endif // BLOCKOPTIONCONTROLINTEGER_H
