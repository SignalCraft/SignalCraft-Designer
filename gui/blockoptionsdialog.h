#ifndef BLOCKOPTIONSDIALOG_H
#define BLOCKOPTIONSDIALOG_H

#include <QDialog>
#include "flowchart/blocktype.h"
#include <QHash>
#include <QString>
#include "gui/blockoptioncontrol.h"

namespace Ui {
    class BlockOptionsDialog;
}

class BlockOptionsDialog : public QDialog {
    Q_OBJECT
public:
    explicit BlockOptionsDialog(BlockType bt, QHash<QString, QString> optionValues, QWidget *parent = 0);
    ~BlockOptionsDialog();
    QHash<QString, QString> optionValues() const;
protected slots:
    void accept();
    void reject();
private:
    Ui::BlockOptionsDialog *ui;
    QHash<QString, BlockOptionControl*> m_optionControls;
    QHash<QString, QString> m_optionValues;
};

#endif // BLOCKOPTIONSDIALOG_H
