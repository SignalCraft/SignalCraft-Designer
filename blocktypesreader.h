#ifndef BLOCKTYPESREADER_H
#define BLOCKTYPESREADER_H

#include <QMap>
#include <flowchart/blocktype.h>
#include <QIODevice>
#include <QJsonObject>
#include <QString>
#include "flowchart/datatype.h"
#include "gui/blockoptioncontrol.h"
#include "flowchart/blockoption.h"
#include <QSharedPointer>

/**
 * A BlockTypesReader reads a JSON file from an IO device as a list of
 * serialized BlockTypes file, and stores an ordered mapping from block type
 * names to the BlockType objects.
 */
class BlockTypesReader {
public:
    /**
     * Construct a BlockTypesReader.
     */
    BlockTypesReader();

    /**
     * @return an ordered mapping from block type names to BlockTypes.
     */
    QMap<QString, BlockType> blockTypes() const;

    /**
     * Read a JSON file as a list of block types to be stored.
     * @param device the device to read from
     */
    void read(QIODevice *device);

private:
    QMap<QString, BlockType> m_blockTypes;
    QMap<QString, BlockType> readBlockTypes(QJsonValue node);
    BlockType readBlockType(QJsonValue node);
    QSharedPointer<const BlockOption> readBlockOption(QJsonValue node);
    QMap<QString, DataType> readPinList(QJsonValue node);
};

#endif // BLOCKTYPESREADER_H
