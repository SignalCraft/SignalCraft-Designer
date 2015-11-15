#include "gui/myitemmodel.h"

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <QModelIndexList>
#include "flowchart/blocktype.h"
#include <QMimeData>

MyItemModel::MyItemModel(QObject *parent) : QAbstractListModel(parent) { }

MyItemModel::MyItemModel(QList<BlockType> blockTypes, QObject *parent) : MyItemModel(parent) {
    m_blockTypes = blockTypes;
}

BlockType MyItemModel::blockTypeAt(const QModelIndex &index) const {
    return m_blockTypes[index.row()];
}

int MyItemModel::rowCount(const QModelIndex &parent) const {
    return m_blockTypes.size();
}

QVariant MyItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= rowCount()) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        return QVariant(blockTypeAt(index).name());
    } else {
        return QVariant();
    }
}

Qt::ItemFlags MyItemModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData *MyItemModel::mimeData(const QModelIndexList &indexes) const {
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
