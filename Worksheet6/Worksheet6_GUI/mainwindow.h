#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ModelPartList;
class QModelIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void statusUpdateMessage(const QString &message, int timeout);

private slots:
    void handleButton1();
    void handleButton2();
    void handleTreeClicked(const QModelIndex &index);
private slots:
    void on_actionItem_Options_triggered(bool checked);
    // IMPORTANT: keep ONLY this version (no bool) to avoid the “ambiguous overloaded” error
    void on_actionOpen_File_triggered();

private:
    Ui::MainWindow *ui;
    ModelPartList *partList = nullptr;
};

#endif // MAINWINDOW_H
