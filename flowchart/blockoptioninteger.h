#ifndef BLOCKOPTIONINTEGER_H
#define BLOCKOPTIONINTEGER_H

#include "flowchart/blockoption.h"
#include <QString>
#include "gui/blockoptioncontrol.h"

class BlockOptionInteger : public BlockOption {
public:
    explicit BlockOptionInteger(QString displayName, QString defaultValue, int minimum, int maximum);
    virtual BlockOptionControl *makeControl() const override;
private:
    int m_minimum;
    int m_maximum;
};

#endif // BLOCKOPTIONINTEGER_H
