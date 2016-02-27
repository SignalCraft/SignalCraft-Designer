#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <QMap>
#include <QHash>
#include <QString>
#include "flowchart/pintype.h"
#include <QPointF>
#include <QtGlobal>
#include "flowchart/blockoption.h"
#include <QSharedPointer>
#include <QJsonValue>
#include "flowchart/overloadtype.h"

/**
 * The immutable BlockType class represents a type of Block that can exist.
 */
class BlockType {
public:
    /**
     * Construct an invalid BlockType.
     */
    BlockType();

    /**
     * Construct a BlockType.
     * @param name the programmatic name that determines this BlockType's identity
     * @param displayName the display name
     * @param overload the type of overloading this block uses
     * @param inputs the mapping of input pin names to data types
     * @param outputs the mapping of output pin names to data types
     * @param options the mapping of option names to shared BlockOption objects
     */
    BlockType(QString name, QString displayName, OverloadType overload, QMap<QString, PinType> inputs, QMap<QString, PinType> outputs, QMap<QString, QSharedPointer<const BlockOption> > options);

    /**
     * Determine whether or not this BlockType is valid.
     * A BlockType is valid if its name is nonempty.
     * @return true if this is a valid BlockType, false otherwise
     */
    bool isValid() const;

    /**
     * Calculate the relative position of the top-left corner of the named input pin.
     * @param pinName the name of the input pin
     * @return the relative position
     */
    QPointF inputPinPos(QString pinName) const;

    /**
     * Calculate the relative position of the top-left corner of the named output pin.
     * @param pinName the name of the output pin
     * @return the relative position
     */
    QPointF outputPinPos(QString pinName) const;

    /**
     * Calculate the relative position of the center of the named input pin.
     * @param pinName the name of the input pin
     * @return the relative position
     */
    QPointF inputPinCenterPos(QString pinName) const;

    /**
     * Calculate the relative position of the center of the named output pin.
     * @param pinName the name of the output pin
     * @return the relative position
     */
    QPointF outputPinCenterPos(QString pinName) const;

    /**
     * Calculate the block's display width
     * @return the display width
     */
    qreal displayWidth() const;

    /**
     * Calculate the block's display height
     * @return the display height
     */
    qreal displayHeight() const;

    /**
     * Determine whether or not the named pin is an output
     * @param pinName the pin's name
     * @return true if the pin is an output, false otherwise
     */
    bool isPinOutput(QString pinName) const;

    /**
     * @return the name
     */
    QString name() const;

    /**
     * @return the display name
     */
    QString displayName() const;

    /**
     * @return the overload type
     */
    OverloadType overloadType() const;

    /**
     * @return the mapping of input pin names to data types
     */
    QMap<QString, PinType> inputs() const;

    /**
     * @return the mapping of output pin names to data types
     */
    QMap<QString, PinType> outputs() const;

    /**
     * @return the mapping of option names to shared BlockOption objects
     */
    QMap<QString, QSharedPointer<const BlockOption> > options() const;

    /**
     * @return the mapping of option names to default option values
     */
    QHash<QString, QString> defaultOptionValues() const;

    /**
     * Use the given possibly-incomplete option values to determine the complete option values.
     * @param optionValues the mapping of option names to values that overrides the defaults
     * @return the resulting complete mapping of option names to option values
     */
    QHash<QString, QString> resultingOptionValues(QHash<QString, QString> optionValues) const;

public:
    /**
     * Convert the index of an input pin to the relative position of its top-left corner.
     * @param pinIndex the input pin's index
     * @return the relative position
     */
    static QPointF inputPinIndexToPos(int pinIndex);

    /**
     * Convert the index of an output pin to the relative position of its top-left corner.
     * @param pinIndex the output pin's index
     * @return the relative position
     */
    static QPointF outputPinIndexToPos(int pinIndex);

    /**
     * Convert the index of an input pin to the relative position of its center.
     * @param pinIndex the input pin's index
     * @return the relative position
     */
    static QPointF inputPinIndexToCenterPos(int pinIndex);

    /**
     * Convert the index of an output pin to the relative position of its center.
     * @param pinIndex the output pin's index
     * @return the relative position
     */
    static QPointF outputPinIndexToCenterPos(int pinIndex);

private:
    QString m_name;
    QString m_displayName;
    OverloadType m_overloadType;
    QMap<QString, PinType> m_inputs;
    QMap<QString, PinType> m_outputs;
    QMap<QString, QSharedPointer<const BlockOption> > m_options;
};

QJsonValue BlockType_toJson(BlockType obj);
BlockType BlockType_fromJson(QJsonValue node);

QJsonValue BlockTypes_toJson(QHash<QString, BlockType> obj);
QHash<QString, BlockType> BlockTypes_fromJson(QJsonValue node);

#endif // BLOCKTYPE_H
