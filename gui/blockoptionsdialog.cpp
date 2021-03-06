#include "blockoptionsdialog.h"
#include "ui_blockoptionsdialog.h"
#include "flowchart.h"
#include "blocktype.h"
#include "blockoption.h"
#include "blockoptioncontrol.h"
#include "blockoptioncontrolcombobox.h"
#include "blockoptioncontrolinteger.h"
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QHash>

BlockOptionsDialog::BlockOptionsDialog(const FlowChart& flow, int blockIndex, QWidget *parent) : QDialog(parent), ui(new Ui::BlockOptionsDialog) {
    ui->setupUi(this);
    BlockType bt = flow.blockType(blockIndex);
    for (QString blockOptionName : bt.options().keys()) {
        QString optionValue = flow.blockOptionValue(blockIndex, blockOptionName, bt.defaultOptionValues().value(blockOptionName));
        m_optionValues.insert(blockOptionName, optionValue);
        BlockOption blockOption = bt.options()[blockOptionName];
        BlockOptionControl *control;
        switch (blockOption.type()) {
        case BLOCK_OPTION_TYPE_COMBOBOX:
            control = new BlockOptionControlComboBox(blockOption.displayName(), blockOption.choices());
            break;
        case BLOCK_OPTION_TYPE_INTEGER:
            control = new BlockOptionControlInteger(blockOption.displayName(), blockOption.minimum(), blockOption.maximum());
            break;
        }
        control->setCurrentValue(optionValue);
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
