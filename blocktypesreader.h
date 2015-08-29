#ifndef BLOCKTYPESREADER_H
#define BLOCKTYPESREADER_H

#include <QVector>
#include <flowchart/blocktype.h>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QString>

class BlockTypesReader {
public:
    BlockTypesReader();
    QVector<BlockType> blockTypes();
    void read(QIODevice *device);
protected:
    QVector<BlockType> m_blockTypes;
    QXmlStreamReader xml;
    void readBlockTypes();
    BlockType readBlockType();
    QVector<QString> readVectorString();
    QString readString();
};

#endif // BLOCKTYPESREADER_H
