#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QStandardItemModel>

class QMimeData;

class MyItemModel : public QStandardItemModel
{
public:
    MyItemModel();
    QMimeData *mimeData(const QModelIndexList& indexes) const override;
};

#endif // MYITEMMODEL_H
