#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <QMap>
#include <QString>
#include "flowchart/datatype.h"

class BlockType
{
public:
    BlockType();
    QString name;
    QMap<QString, DataType> inputs;
    QMap<QString, DataType> outputs;

};

#endif // BLOCKTYPE_H
