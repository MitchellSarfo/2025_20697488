#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVTKOpenGLNativeWidget.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QIcon>
#include <QStatusBar>
#include <QTreeView>

#include "modelpartlist.h"
#include "modelpart.h"
#include "optiondialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 🔥 VTK SETUP
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    // Cylinder
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cylinder->GetOutputPort());

    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.3);

    renderer->AddActor(actor);
    renderer->ResetCamera();
    // UI setup
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->treeView->addAction(ui->actionItem_Options);

    ui->pushButton->setIcon(QIcon(":/fileopen.png"));

    connect(ui->actionItem_Options, &QAction::triggered,
            this, &MainWindow::on_actionItem_Options_triggered);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    connect(ui->pushButton,   &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);

    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);

    // Model demo
    partList = new ModelPartList("PartsList", this);
    ui->treeView->setModel(partList);

    ModelPart *rootItem = partList->getRootItem();

    for (int i = 0; i < 3; ++i) {
        ModelPart *child = new ModelPart(QString("TopLevel %1").arg(i), "true", rootItem);
        rootItem->appendChild(child);

        for (int j = 0; j < 5; ++j) {
            child->appendChild(
                new ModelPart(QString("Item %1,%2").arg(i).arg(j), "true", child)
                );
        }
    }

    ui->treeView->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 🔹 Button 1
void MainWindow::handleButton1()
{
    emit statusUpdateMessage("Button 1 clicked", 2000);
}


// 🔹 Button 2 (FIXED)
void MainWindow::handleButton2()
{
    OptionDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {

        QString name = dialog.getName();
        bool visible = dialog.getVisible();

        emit statusUpdateMessage(
            QString("Name: %1 | Visible: %2")
                .arg(name)
                .arg(visible ? "true" : "false"),
            3000
            );
    }
}


// 🔹 Tree click
void MainWindow::handleTreeClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    ModelPart *part = static_cast<ModelPart*>(index.internalPointer());
    emit statusUpdateMessage("Selected: " + part->data(0).toString(), 0);
}


// 🔹 File open
void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "C:\\",
        "STL Files (*.stl);;All Files (*.*)"
        );

    if (!fileName.isEmpty()) {
        emit statusUpdateMessage("Selected: " + fileName, 0);
    }
}


// 🔹 Options dialog (FIXED)
void MainWindow::on_actionItem_Options_triggered()
{
    OptionDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {

        QString name = dialog.getName();
        bool visible = dialog.getVisible();

        emit statusUpdateMessage(
            QString("Name: %1 | Visible: %2")
                .arg(name)
                .arg(visible ? "true" : "false"),
            3000
            );
    }
}
