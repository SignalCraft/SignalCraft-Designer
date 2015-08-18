#include "gui/myitemmodel.h"

#include <QMimeData>

MyItemModel::MyItemModel() {}

QMimeData* MyItemModel::mimeData(const QModelIndexList & indexes) const {
    QMimeData *m = QStandardItemModel::mimeData(indexes);
    m->setText(this->itemFromIndex(indexes.first())->text());
    return m;
}
