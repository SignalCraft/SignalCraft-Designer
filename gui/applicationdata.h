#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QVector>
#include "flowchart/blocktype.h"

class ApplicationData {
public:
    ApplicationData();
    QVector<BlockType> blockTypes;
};

#endif // APPLICATIONDATA_H
