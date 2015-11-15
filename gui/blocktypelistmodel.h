#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <QModelIndexList>
#include "flowchart/blocktype.h"

class QMimeData;

class BlockTypeListModel : public QAbstractListModel {
public:
    BlockTypeListModel(QObject *parent = 0);
    BlockTypeListModel(QList<BlockType> blockTypes, QObject *parent = 0);
    BlockType blockTypeAt(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
private:
    QList<BlockType> m_blockTypes;
};

#endif // MYITEMMODEL_H
