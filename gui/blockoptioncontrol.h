#ifndef BLOCKOPTIONCONTROL_H
#define BLOCKOPTIONCONTROL_H

#include <QGroupBox>
#include <QString>
#include <QWidget>

/**
 * A BlockOptionControl is an input widget used in an BlockOptionsDialog to
 * set one of a block's options.
 *
 * Since BlockOptionControl is an abstract class, it must be subclassed to
 * be used, and all subclasses must implement setCurrentValue(QString) and
 * textValue().
 */
class BlockOptionControl : public QGroupBox {
    Q_OBJECT
public:
    /**
     * Construct a BlockOptionControl.
     * @param title the control's title
     * @param parent the optional parent widget
     */
    explicit BlockOptionControl(const QString & title, QWidget *parent = 0);

    /**
     * Set the current value of the control.
     * @param value the new value
     */
    virtual void setCurrentValue(QString value) = 0;

    /**
     * Determine the current value of the control.
     * @return the current value
     */
    virtual QString textValue() const = 0;
};

#endif // BLOCKOPTIONCONTROL_H
