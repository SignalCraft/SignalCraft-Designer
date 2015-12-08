#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QHash>
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
     * Stores a mapping from block names to BlockTypes.
     */
    QHash<QString, BlockType> blockTypes;
};

#endif // APPLICATIONDATA_H
