
#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);

    // Optional UI defaults
    ui->lineName->setPlaceholderText("Part name");
    ui->checkVisible->setText("Visible");
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::setName(const QString &name)
{
    ui->lineName->setText(name);
}

QString OptionDialog::name() const
{
    return ui->lineName->text();
}

void OptionDialog::setVisibleChecked(bool v)
{
    ui->checkVisible->setChecked(v);
}

bool OptionDialog::isVisibleChecked() const
{
    return ui->checkVisible->isChecked();
}
