#ifndef BLOCKOPTIONSDIALOG_H
#define BLOCKOPTIONSDIALOG_H

#include <QDialog>
#include "blocktype.h"
#include <QHash>
#include <QString>
#include "blockoptioncontrol.h"
#include "flowchart.h"

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
     * @param flow the flowchart containing the block in question
     * @param blockIndex the block's index in the flowchart
     * @param parent the optional parent widget
     */
    explicit BlockOptionsDialog(const FlowChart& flow, int blockIndex, QWidget *parent = 0);

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
