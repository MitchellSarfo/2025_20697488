#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QIcon>
#include <QStatusBar>
#include <QTreeView>

#include "modelpartlist.h"
#include "modelpart.h"
#include "optiondialog.h"

// 🔥 VTK includes
#include <QVTKOpenGLNativeWidget.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 🔥 VTK setup
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->widget->setRenderWindow(renderWindow);

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
    actor->RotateX(30.0);
    actor->RotateY(45.0);

    renderer->AddActor(actor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

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
            child->appendChild(new ModelPart(QString("Item %1,%2").arg(i).arg(j), "true", child));
        }
    }

    ui->treeView->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 🔹 Buttons
void MainWindow::handleButton1()
{
    emit statusUpdateMessage("Button 1 clicked", 2000);
}

void MainWindow::handleButton2()
{
    OptionDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(
            QString("Name=%1 Visible=%2")
                .arg(dialog.name())
                .arg(dialog.isVisibleChecked() ? "true" : "false"),
            0
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
        this, "Open File", "C:\\",
        "STL Files (*.stl);;All Files (*.*)"
        );

    if (!fileName.isEmpty()) {
        emit statusUpdateMessage("Selected: " + fileName, 0);
    }
}

// 🔥 FINAL EXERCISE 3 FEATURE
void MainWindow::on_actionItem_Options_triggered()
{
    OptionDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {

        int r = dialog.getR();
        int g = dialog.getG();
        int b = dialog.getB();

        double red   = r / 255.0;
        double green = g / 255.0;
        double blue  = b / 255.0;

        actor->GetProperty()->SetColor(red, green, blue);
        renderWindow->Render();

        emit statusUpdateMessage(
            QString("Color set to RGB: %1, %2, %3").arg(r).arg(g).arg(b),
            0
            );
    }
}
