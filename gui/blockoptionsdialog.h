#ifndef BLOCKOPTIONSDIALOG_H
#define BLOCKOPTIONSDIALOG_H

#include <QDialog>
#include "blocktype.h"
#include <QHash>
#include <QString>
#include "blockoptioncontrol.h"

namespace Ui {
    class BlockOptionsDialog;
}

/**
 * A BlockOptionsDialog is a dialog box for setting a block's options.
 */
class BlockOptionsDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * Construct a BlockOptionsDialog.
     * @param bt the type of block to get options for
     * @param optionValues the mapping of option names to their current values
     * @param parent the optional parent widget
     */
    explicit BlockOptionsDialog(BlockType bt, QHash<QString, QString> optionValues, QWidget *parent = 0);

    ~BlockOptionsDialog();

    /**
     * @return the mapping of option names to the values set in this dialog
     */
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
