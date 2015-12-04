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

/**
 * The BlockTypeListModel class is a QAbstractListModel that wraps the list of
 * block types in a data model suitable for displaying with a list widget.
 */
class BlockTypeListModel : public QAbstractListModel {
public:
    /**
     * Construct a BlockTypeListModel with no block types.
     * @param parent the optional parent widget
     */
    BlockTypeListModel(QObject *parent = 0);

    /**
     * Construct a BlockTypeListModel.
     * @param blockTypes the list of BlockTypes
     * @param parent the optional parent widget
     */
    BlockTypeListModel(QList<BlockType> blockTypes, QObject *parent = 0);

    /**
     * Get the BlockType at the given index.
     * @param index the index to look at
     * @return the block type
     */
    BlockType blockTypeAt(const QModelIndex &index) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;

private:
    QList<BlockType> m_blockTypes;
};

#endif // MYITEMMODEL_H
