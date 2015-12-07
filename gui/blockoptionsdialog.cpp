#include "blockoptionsdialog.h"
#include "ui_blockoptionsdialog.h"
#include "flowchart/blocktype.h"
#include "gui/blockoptioncontrol.h"
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QSharedPointer>
#include <QHash>

BlockOptionsDialog::BlockOptionsDialog(BlockType bt, QHash<QString, QString> optionValues, QWidget *parent) : QDialog(parent), ui(new Ui::BlockOptionsDialog) {
    ui->setupUi(this);
    m_optionValues = bt.resultingOptionValues(optionValues);
    for (QString blockOptionName : bt.options().keys()) {
        QSharedPointer<const BlockOption> blockOption = bt.options()[blockOptionName];
        BlockOptionControl *control = blockOption->makeControl(optionValues[blockOptionName]);
        ui->optionControlLayout->addWidget(control);
        m_optionControls[blockOptionName] = control;
    }
    ui->optionControlLayout->addStretch(0);
    setWindowTitle(bt.displayName() + " Options");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

BlockOptionsDialog::~BlockOptionsDialog() {
    delete ui;
}

void BlockOptionsDialog::accept() {
    for (QString optionName : m_optionControls.keys()) {
        BlockOptionControl *optionControl = m_optionControls[optionName];
        m_optionValues[optionName] = optionControl->textValue();
    }
    QDialog::accept();
}

void BlockOptionsDialog::reject() {
    // do nothing
    QDialog::reject();
}

QHash<QString, QString> BlockOptionsDialog::optionValues() const {
    return m_optionValues;
}
