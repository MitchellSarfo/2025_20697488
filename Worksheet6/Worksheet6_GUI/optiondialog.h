#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();

    void setName(const QString &name);
    QString name() const;

    void setVisibleChecked(bool v);
    bool isVisibleChecked() const;
    // Add these to the 'public' section of your OptionDialog class
    int getR() const { return ui->spinBoxR->value(); }
    int getG() const { return ui->spinBoxG->value(); }
    int getB() const { return ui->spinBoxB->value(); }
    QString getName() const { return ui->lineEdit->text(); }

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
