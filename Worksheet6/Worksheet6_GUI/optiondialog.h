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

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
