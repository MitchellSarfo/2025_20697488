#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ModelPartList;   // Exercise 4

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
void on_actionOpen_File_triggered();
    // Exercise 4.3.2: TreeView click handler
    void handleTreeClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    ModelPartList *partList = nullptr;
};

#endif // MAINWINDOW_H
