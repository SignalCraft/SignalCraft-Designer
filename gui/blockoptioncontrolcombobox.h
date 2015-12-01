#ifndef BLOCKOPTIONCONTROLCOMBOBOX
#define BLOCKOPTIONCONTROLCOMBOBOX

#include "gui/blockoptioncontrol.h"
#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QMap>

class BlockOptionControlComboBox : public BlockOptionControl {
public:
    explicit BlockOptionControlComboBox(const QString & title, QMap<QString, QString> choices, QWidget *parent = 0);
    virtual void setCurrentValue(QString value) override;
    virtual QString textValue() const override;
private:
    QComboBox *m_control;
};

#endif // BLOCKOPTIONCONTROLCOMBOBOX

