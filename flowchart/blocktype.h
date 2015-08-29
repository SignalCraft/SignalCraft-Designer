#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <QVector>
#include <QString>

class BlockType
{
public:
    BlockType();
    QString name;
    QVector<QString> inputs;
    QVector<QString> outputs;
};

#endif // BLOCKTYPE_H
