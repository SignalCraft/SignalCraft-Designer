#ifndef BLOCKTYPESREADER_H
#define BLOCKTYPESREADER_H

#include <QMap>
#include <flowchart/blocktype.h>
#include <QIODevice>
#include <QJsonObject>
#include <QString>
#include "flowchart/datatype.h"

class BlockTypesReader {
public:
    BlockTypesReader();
    QMap<QString, BlockType> blockTypes();
    void read(QIODevice *device);
protected:
    QMap<QString, BlockType> m_blockTypes;
    QMap<QString, BlockType> readBlockTypes(QJsonValue node);
    BlockType readBlockType(QJsonValue node);
    QMap<QString, DataType> readPinList(QJsonValue node);
};

#endif // BLOCKTYPESREADER_H
