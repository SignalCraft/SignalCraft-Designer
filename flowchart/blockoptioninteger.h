#ifndef BLOCKOPTIONINTEGER_H
#define BLOCKOPTIONINTEGER_H

#include "flowchart/blockoption.h"
#include <QString>
#include "gui/blockoptioncontrol.h"
#include <QJsonValue>

/**
 * A BlockOptionInteger is a BlockOption that selects from a range of integers.
 */
class BlockOptionInteger : public BlockOption {
public:
    /**
     * Construct a BlockOptionInteger.
     * @param displayName the display name
     * @param defaultValue the default value
     * @param minimum the minimum value
     * @param maximum the maximum value
     */
    explicit BlockOptionInteger(QString displayName, QString defaultValue, int minimum, int maximum);

    /**
     * Create the BlockOptionControl for controlling this option.
     * The returned object will be a BlockOptionControlInteger.
     * @return A pointer to the heap-allocated control object.
     */
    virtual BlockOptionControl *makeControl() const override;

    virtual QJsonValue toJson() const override;

private:
    int m_minimum;
    int m_maximum;
};

#endif // BLOCKOPTIONINTEGER_H
