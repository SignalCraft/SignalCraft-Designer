#ifndef BLOCKOPTIONCONTROLCOMBOBOX
#define BLOCKOPTIONCONTROLCOMBOBOX

#include "blockoptioncontrol.h"
#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QMap>

/**
 * A BlockOptionControlComboBox is a BlockOptionControl that allows the user to
 * choose one of several possible values.
 */
class BlockOptionControlComboBox : public BlockOptionControl {
public:
    /**
     * Construct a BlockOptionControlComboBox.
     * @param title the control's title
     * @param choices an ordered mapping from choice names to choice values
     * @param parent the optional parent widget
     */
    explicit BlockOptionControlComboBox(const QString & title, QMap<QString, QString> choices, QWidget *parent = 0);

    virtual void setCurrentValue(QString value) override;

    virtual QString textValue() const override;

private:
    QComboBox *m_control;
};

#endif // BLOCKOPTIONCONTROLCOMBOBOX

