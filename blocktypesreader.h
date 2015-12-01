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

class BlockTypesReader {
public:
    BlockTypesReader();
    QMap<QString, BlockType> blockTypes();
    void read(QIODevice *device);
protected:
    QMap<QString, BlockType> m_blockTypes;
    QMap<QString, BlockType> readBlockTypes(QJsonValue node);
    BlockType readBlockType(QJsonValue node);
    QSharedPointer<const BlockOption> readBlockOption(QJsonValue node);
    QMap<QString, DataType> readPinList(QJsonValue node);
};

#endif // BLOCKTYPESREADER_H
