#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStatusBar>
#include <QPushButton>

// Exercise 4
#include "ModelPartList.h"
#include "ModelPart.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // =========================
    // Exercise 2/3: Buttons + status bar
    // =========================
    connect(ui->pushButton,   &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    // =========================
    // Exercise 4: Model-based TreeView
    // =========================
    partList = new ModelPartList("PartsList", this);

    // Populate FIRST
    ModelPart *rootItem = partList->getRootItem();

    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible = "true";
        ModelPart *childItem = new ModelPart(name, visible, rootItem);
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            QString subVisible = "true";
            ModelPart *subChild = new ModelPart(subName, subVisible, childItem);
            childItem->appendChild(subChild);
        }
    }

    // Attach model
    ui->treeView->setModel(partList);
    ui->treeView->expandAll();
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->resizeColumnToContents(1);

    // =========================
    // Exercise 4.3.2: Detect TreeView selection (clicked)
    // =========================
    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton1()
{
    emit statusUpdateMessage("Button 1 was clicked", 2000);
}

void MainWindow::handleButton2()
{
    emit statusUpdateMessage("Button 2 was clicked", 2000);
}

// When the user clicks an item in the TreeView:
void MainWindow::handleTreeClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    // Get the ModelPart behind the clicked item
    ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());
    if (!selectedPart) return;

    // Column 0 = name
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: %1").arg(text), 2000);
}
