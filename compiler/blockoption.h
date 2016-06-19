#ifndef BLOCKOPTION_H
#define BLOCKOPTION_H

#include <QString>
#include <QJsonValue>
#include <QMap>
#include <QHash>

/**
 * The BlockOptionType enum stores what subtype a BlcokOption is at runtime.
 */
enum BlockOptionType { BLOCK_OPTION_TYPE_COMBOBOX = 1, BLOCK_OPTION_TYPE_INTEGER = 2 };

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
     * Construct an invalid BlockOption.
     */
    BlockOption();

    /**
     * This factory function constructs a Combobox BlockOption.
     * @param displayName the BlockOption's display name
     * @param defaultValue the BlockOption's default value
     * @param choices an ordered mapping from the BlockOption's option names to option values
     * @return the constructed BlockOption
     */
    static BlockOption makeComboBox(QString displayName, QString defaultValue, QMap<QString, QString> choices);

    /**
     * This factory function constructs an Integer BlockOption
     * @param displayName the BlockOption's display name
     * @param defaultValue the BlockOption's default value
     * @param minimum the BlockOption's minimum value
     * @param maximum the BlockOption's maximum value
     * @return the constructed BlockOption
     */
    static BlockOption makeInteger(QString displayName, QString defaultValue, int minimum, int maximum);

    /**
     * @return the display name
     */
    QString displayName() const;

    /**
     * @return the default value
     */
    QString defaultValue() const;

    /**
     * @return the specific subtype
     */
    BlockOptionType type() const;

    // Combobox:

    /**
     * @return an ordered mapping from the BlockOption's option names to option values
     */
    QMap<QString, QString> choices() const;

    // Integer:

    /**
     * @return the BlockOption's minimum value
     */
    int minimum() const;

    /**
     * @return the BlockOption's maximum value
     */
    int maximum() const;

private:

    /**
     * Partially construct a BlockOption, by initializing the members that are common to every type.
     * This pivate constructor is meant to be called by factory functions for each type.
     * @param displayName the BlockOption's display name
     * @param defaultValue the BlockOption's default value
     * @param type the BlockOption's subtype
     */
    explicit BlockOption(QString displayName, QString defaultValue, BlockOptionType type);

    QString m_displayName;
    QString m_defaultValue;
    BlockOptionType m_type;

    // ComboBox:
    QMap<QString, QString> m_choices;

    // Integer:
    int m_minimum;
    int m_maximum;

};

QJsonValue BlockOptionType_toJson(BlockOptionType obj);
BlockOptionType BlockOptionType_fromJson(QJsonValue node);

QJsonValue BlockOption_toJson(BlockOption obj);
BlockOption BlockOption_fromJson(QJsonValue node);

QJsonValue QHash_QString_BlockOption_toJson(QHash<QString, BlockOption> obj);
QHash<QString, BlockOption> QHash_QString_BlockOption_fromJson(QJsonValue node);

QJsonValue QMap_QString_BlockOption_toJson(QMap<QString, BlockOption> obj);
QMap<QString, BlockOption> QMap_QString_BlockOption_fromJson(QJsonValue node);

#endif // BLOCKOPTION_H
