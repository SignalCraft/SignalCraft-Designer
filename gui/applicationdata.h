#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QMap>
#include <QString>
#include "flowchart/blocktype.h"

class ApplicationData {
public:
    ApplicationData();
    QMap<QString, BlockType> blockTypes;
};

#endif // APPLICATIONDATA_H
