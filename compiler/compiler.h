#ifndef COMPILER_H
#define COMPILER_H

#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include <QString>
#include <QList>
#include <QSet>

/** @file */

/**
 * Compile the given flowchart into c code for the device.
 * @param flow the flowchart to compile
 * @return the c code for the device
 */
QString generatePicCode(const FlowChart flow);

/**
 * Determine whether or not the given block is expandable.
 * A block is expandable if all of its inputs have already been expanded.
 * @param block the block in question
 * @param expanded the set of block indexes that have already been expanded
 * @return true if the block is expandable, or false if not
 */
bool isExpandable(const Block block, const QSet<int> expanded);

/**
 * Determine the set of unique block type names from the given flowchart.
 * @param flow the flowchart in question
 * @return the set of block type names
 */
QSet<QString> extractUniqueBlockNames(const FlowChart flow);

/**
 * Determine the list of input block indexes from the given flowchart.
 * @param flow the flowchart in question
 * @return the list of input block indexes
 */
QList<int> extractInputBlocks(const FlowChart flow);

/**
 * Determine the set of wire names from the given flowchart.
 * @param flow the flowchart in question
 * @return the set of wire names
 */
QSet<QString> extractWireNames(const FlowChart flow);

#endif // COMPILER_H

