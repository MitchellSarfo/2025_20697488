#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ModelPartList;   // forward decl (your model)

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

    // QAction triggered(bool) -> we accept the bool to avoid any connection issues
    void on_actionOpen_File_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    ModelPartList *partList = nullptr;
};

#endif // MAINWINDOW_H
