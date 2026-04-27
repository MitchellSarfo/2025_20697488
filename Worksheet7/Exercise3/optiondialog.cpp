#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

QString OptionDialog::getName() const
{
    return ui->lineName->text();   // ✅ matches UI
}

bool OptionDialog::getVisible() const
{
    return ui->checkVisible->isChecked();   // ✅ FIXED
}
