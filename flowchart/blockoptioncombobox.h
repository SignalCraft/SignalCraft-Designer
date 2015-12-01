#ifndef BLOCKOPTIONCOMBOBOX
#define BLOCKOPTIONCOMBOBOX

#include "flowchart/blockoption.h"
#include <QString>
#include "gui/blockoptioncontrol.h"
#include <QMap>

class BlockOptionComboBox : public BlockOption {
public:
    explicit BlockOptionComboBox(QString displayName, QString defaultValue, QMap<QString, QString> choices);
    virtual BlockOptionControl *makeControl() const override;
private:
    QMap<QString, QString> m_choices;
};

#endif // BLOCKOPTIONCOMBOBOX

