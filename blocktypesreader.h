#ifndef BLOCKTYPESREADER_H
#define BLOCKTYPESREADER_H

#include <QVector>
#include <flowchart/blocktype.h>
#include <QIODevice>
#include <QJsonObject>
#include <QString>
#include "flowchart/datatype.h"

class BlockTypesReader {
public:
    BlockTypesReader();
    QVector<BlockType> blockTypes();
    void read(QIODevice *device);
protected:
    QVector<BlockType> m_blockTypes;
    QVector<BlockType> readBlockTypes(QJsonValue node);
    BlockType readBlockType(QJsonValue node);
    QMap<QString, DataType> readPinList(QJsonValue node);
};

#endif // BLOCKTYPESREADER_H
