#ifndef BLOCKOPTION_H
#define BLOCKOPTION_H

#include <QString>
#include "gui/blockoptioncontrol.h"
#include <QJsonValue>
#include <QSharedPointer>

/**
 * The immutable BlockOption abstract class represents one of a
 * blocktype's options.
 *
 * A BlockOption stores all the data about the option's type, possible
 * values, default value, and display characteristics. It also handles the
 * creation of the appropriate BlockOptionControl object.
 *
 * Note that option values are always represented as QStrings, since their
 * only function is to end up as text anyway.
 *
 * Since BlockOption is abstract, only its subclasses should be
 * instantiated. Subclasses must override makeControl() but should not
 * override makeControl(QString), which calls makeControl internally.
 */
class BlockOption {
public:
    /**
     * Construct a BlockOption.
     * @param displayName the BlockOption's display name.
     * @param defaultValue the BlockOption's default value.
     */
    explicit BlockOption(QString displayName, QString defaultValue);

    /**
     * @return the display name
     */
    QString displayName() const;

    /**
     * @return the default value
     */
    QString defaultValue() const;

    /**
     * Create the BlockOptionControl for controlling this option.
     * This is a pure virtual function: subclasses must implement it.
     * @return A pointer to the heap-allocated control object.
     */
    virtual BlockOptionControl *makeControl() const = 0;

    /**
     * Create the BlockOptionControl for controlling this option, with the given current value.
     * This function calls makeControl internally.
     * @return A pointer to the heap-allocated control object.
     */
    BlockOptionControl *makeControl(QString currentValue) const;

private:
    QString m_displayName;
    QString m_defaultValue;
};

QJsonValue BlockOption_toJson(QSharedPointer<const BlockOption> obj);
QSharedPointer<const BlockOption> BlockOption_fromJson(QJsonValue node);

#endif // BLOCKOPTION_H
