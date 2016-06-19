#ifndef BLOCKOPTIONCOMBOBOX
#define BLOCKOPTIONCOMBOBOX

#include "blockoption.h"
#include <QString>
#include "blockoptioncontrol.h"
#include <QMap>
#include <QJsonValue>

/**
 * A BlockOptionComboBox is a BlockOption that specifies a set of values, from
 * which one is chosen.
 */
class BlockOptionComboBox : public BlockOption {
public:
    /**
     * Construct a BlockOptionComboBox.
     * @param displayName the display name
     * @param defaultValue the default value
     * @param choices an ordered mapping from each choice's display name to
     * its value
     */
    explicit BlockOptionComboBox(QString displayName, QString defaultValue, QMap<QString, QString> choices);

    /**
     * Create the BlockOptionControl for controlling this option.
     * The returned object will be a BlockOptionControlComboBox.
     * @return A pointer to the heap-allocated control object.
     */
    virtual BlockOptionControl *makeControl() const override;

    virtual QJsonValue toJson() const override;

private:
    QMap<QString, QString> m_choices;
};

#endif // BLOCKOPTIONCOMBOBOX

