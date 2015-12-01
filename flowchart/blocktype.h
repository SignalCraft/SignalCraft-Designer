#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <QMap>
#include <QHash>
#include <QString>
#include "flowchart/datatype.h"
#include <QPointF>
#include <QtGlobal>
#include "flowchart/blockoption.h"
#include <QSharedPointer>

class BlockType {
public:
    BlockType();
    BlockType(QString name, QString displayName, QMap<QString, DataType> inputs, QMap<QString, DataType> outputs, QMap<QString, QSharedPointer<const BlockOption> > options);
    QPointF inputPinPos(QString pinName) const;
    QPointF outputPinPos(QString pinName) const;
    QPointF inputPinCenterPos(QString pinName) const;
    QPointF outputPinCenterPos(QString pinName) const;
    qreal displayWidth() const;
    qreal displayHeight() const;
    bool isPinOutput(QString pinName) const;
    QString name() const;
    QString displayName() const;
    QMap<QString, DataType> inputs() const;
    QMap<QString, DataType> outputs() const;
    QMap<QString, QSharedPointer<const BlockOption> > options() const;
    QHash<QString, QString> defaultOptionValues() const;
public:
    static QPointF inputPinIndexToPos(int pinIndex);
    static QPointF outputPinIndexToPos(int pinIndex);
    static QPointF inputPinIndexToCenterPos(int pinIndex);
    static QPointF outputPinIndexToCenterPos(int pinIndex);
private:
    QString m_name;
    QString m_displayName;
    QMap<QString, DataType> m_inputs;
    QMap<QString, DataType> m_outputs;
    QMap<QString, QSharedPointer<const BlockOption> > m_options;
};

#endif // BLOCKTYPE_H
