#ifndef BLOCKOPTION_H
#define BLOCKOPTION_H

#include <QString>
#include "gui/blockoptioncontrol.h"

class BlockOption {
public:
    explicit BlockOption();
    explicit BlockOption(QString displayName, QString defaultValue);
    QString displayName() const;
    QString defaultValue() const;
    virtual BlockOptionControl *makeControl() const;
    BlockOptionControl *makeControl(QString currentValue) const;
private:
    QString m_displayName;
    QString m_defaultValue;
};

#endif // BLOCKOPTION_H
