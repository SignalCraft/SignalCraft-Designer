#ifndef COMPILER_H
#define COMPILER_H

#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include <QString>
#include <QList>
#include <QSet>

/** @file */

/**
 * @brief Compile the given flowchart into c code for the device.
 *
 * @param flow The flowchart to compile
 * @return The c code for the device.
 */
QString generatePicCode(const FlowChart flow);

/**
 * @brief Determine whether or not the given block is expandable.
 *
 * A block is expandable if all of its inputs have already been expanded.
 *
 * @param block The block in question.
 * @param expanded The set of block indexes that have already been expanded.
 * @return True if the block is expandable, or false if not.
 */
bool isExpandable(const Block block, const QSet<int> expanded);

/**
 * @brief Determine the set of unique block type names from the given flowchart.
 * @param flow The flowchart in question.
 * @return The set of block type names.
 */
QSet<QString> extractUniqueBlockNames(const FlowChart flow);

/**
 * @brief Determine the list of input block indexes from the given flowchart.
 * @param flow The flowchart in question.
 * @return The list of input block indexes.
 */
QList<int> extractInputBlocks(const FlowChart flow);

/**
 * @brief Determine the set of wire names from the given flowchart.
 * @param flow The flowchart in question.
 * @return The set of wire names.
 */
QSet<QString> extractWireNames(const FlowChart flow);

#endif // COMPILER_H

