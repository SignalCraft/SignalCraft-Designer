#ifndef BLOCKOPTIONCONTROLINTEGER_H
#define BLOCKOPTIONCONTROLINTEGER_H

#include "gui/blockoptioncontrol.h"
#include <QString>
#include <QWidget>
#include <QDoubleSpinBox>

/**
 * A BlockOptionControlInteger is a BlockOptionControl that allows the user to
 * specify an integer within a certain range.
 */
class BlockOptionControlInteger : public BlockOptionControl {
public:
    /**
     * Construct a BlockOptionControlInteger.
     * @param title the control's title
     * @param minimum the minimum value
     * @param maximum the maximum value
     * @param parent the optional parent widget
     */
    explicit BlockOptionControlInteger(const QString & title, int minimum, int maximum, QWidget *parent = 0);

    virtual void setCurrentValue(QString value) override;

    virtual QString textValue() const override;

private:
    QDoubleSpinBox *m_control;
};

#endif // BLOCKOPTIONCONTROLINTEGER_H
