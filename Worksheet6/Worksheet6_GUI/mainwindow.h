#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>

class vtkRenderer;
class vtkGenericOpenGLRenderWindow;
class vtkActor;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ModelPartList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void statusUpdateMessage(const QString &message, int timeout);

private slots:
    void handleButton1();
    void handleButton2();
    void handleTreeClicked(const QModelIndex &index);

    void on_actionOpen_File_triggered();
    void on_actionItem_Options_triggered();

private:
    Ui::MainWindow *ui;

    ModelPartList *partList;

    // 🔥 VTK
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkActor> actor;
};

#endif // MAINWINDOW_H
