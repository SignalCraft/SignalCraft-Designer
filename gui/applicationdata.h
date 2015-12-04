#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QMap>
#include <QString>
#include "flowchart/blocktype.h"

/**
 * The ApplicationData class stores all the information that is loaded at
 * runtime and must persist for the lifetime of the process.
 */
class ApplicationData {
public:
    /**
     * Construct an ApplicationData object.
     */
    ApplicationData();

    /**
     * Stores an order mapping from block names to BlockTypes.
     */
    QMap<QString, BlockType> blockTypes; // TODO: QHash
};

#endif // APPLICATIONDATA_H
