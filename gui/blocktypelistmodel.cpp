#include "gui/blocktypelistmodel.h"

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <QModelIndexList>
#include "flowchart/blocktype.h"
#include <QMimeData>

BlockTypeListModel::BlockTypeListModel(QObject *parent) : QAbstractListModel(parent) { }

BlockTypeListModel::BlockTypeListModel(QList<BlockType> blockTypes, QObject *parent) : BlockTypeListModel(parent) {
    m_blockTypes = blockTypes;
}

BlockType BlockTypeListModel::blockTypeAt(const QModelIndex &index) const {
    return m_blockTypes[index.row()];
}

int BlockTypeListModel::rowCount(const QModelIndex &parent) const {
    return m_blockTypes.size();
}

QVariant BlockTypeListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= rowCount()) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        return QVariant(blockTypeAt(index).displayName());
    } else {
        return QVariant();
    }
}

Qt::ItemFlags BlockTypeListModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData *BlockTypeListModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *m = QAbstractListModel::mimeData(indexes);
    if (indexes.isEmpty()) {
        return m;
    }
    if (indexes.size() > 1) {
        return m;
    }
    QModelIndex index = indexes.first();
    if (index.row() >= rowCount()) {
        return m;
    }
    m->setText(blockTypeAt(index).name());
    return m;
}
