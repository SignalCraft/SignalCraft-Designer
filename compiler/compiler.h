#ifndef COMPILER_H
#define COMPILER_H

#include "flowchart/flowchart.h"
#include "flowchart/block.h"

#include <QString>
#include <QList>
#include <QSet>

QString generatePicCode(const FlowChart flow);
bool isExpandable(const Block block, const QSet<int> toBeExpanded);
QSet<QString> extractUniqueBlockNames(const FlowChart flow);
QList<int> extractInputBlocks(const FlowChart flow);
QSet<QString> extractWireNames(const FlowChart flow);

#endif // COMPILER_H

