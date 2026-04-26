#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenu>
#include "modelpartlist.h"
#include "modelpart.h"
#include "optiondialog.h"

#include <QFileDialog>
#include <QIcon>
#include <QStatusBar>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Make the TreeView show actions on right-click
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);

    // Ensure the action is attached to the TreeView
    ui->treeView->addAction(ui->actionItem_Options);
    ui->pushButton->setIcon(QIcon(":/fileopen.png"));
ui->treeView->addAction(ui->actionItem_Options);


    // Connect action to slot
    connect(ui->actionItem_Options, &QAction::triggered,
            this, &MainWindow::on_actionItem_Options_triggered);
    // Status bar hookup
    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    // Buttons
    connect(ui->pushButton,   &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);

    // TreeView click -> status bar
    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);

    // Model demo (Exercise 4/5)
    partList = new ModelPartList("PartsList", this);
    ui->treeView->setModel(partList);

    ModelPart *rootItem = partList->getRootItem();

    for (int i = 0; i < 3; ++i) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible = "true";

        ModelPart *childItem = new ModelPart(name, visible, rootItem);
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; ++j) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            ModelPart *subChild = new ModelPart(subName, visible, childItem);
            childItem->appendChild(subChild);
        }
    }

    ui->treeView->expandAll();

    // Exercise 7 (icon on action) - works even if action is only on toolbar
    if (ui->actionOpen_File) {
        ui->actionOpen_File->setIcon(QIcon(":/icons/fileopen.png"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton1()
{
    emit statusUpdateMessage(tr("Button 1 was clicked"), 2000);
}

void MainWindow::handleButton2()
{
    // Exercise 9: custom dialog
    OptionDialog dialog(this);
    dialog.setName("New part");
    dialog.setVisibleChecked(true);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(
            tr("Dialog accepted. Name=%1 Visible=%2")
                .arg(dialog.name())
                .arg(dialog.isVisibleChecked() ? "true" : "false"),
            0
            );
    } else {
        emit statusUpdateMessage(tr("Dialog rejected"), 2000);
    }
}

void MainWindow::handleTreeClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString text = selectedPart->data(0).toString();
    emit statusUpdateMessage(tr("The selected item is: %1").arg(text), 0);
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt);;All Files (*.*)")
        );

    if (fileName.isEmpty()) {
        emit statusUpdateMessage(tr("Open cancelled"), 2000);
    } else {
        emit statusUpdateMessage(tr("Selected: %1").arg(fileName), 0);
    }
}
void MainWindow::on_actionItem_Options_triggered(bool checked)
{
    Q_UNUSED(checked);
    emit statusUpdateMessage("Add Option triggered", 2000);
}
void MainWindow::on_actionItem_Options_triggered() {
    // 1. Create the dialog
    OptionDialog dialog(this);

    // 2. Show the dialog and wait for the user to click OK
    if (dialog.exec() == QDialog::Accepted) {

        // 3. Grab the RGB values from the dialog
        int r = dialog.getR();
        int g = dialog.getG();
        int b = dialog.getB();

        // 4. Update your status bar (Worksheet 6 requirement)
        QString msg = QString("Color set to RGB: %1, %2, %3").arg(r).arg(g).arg(b);
        emit statusUpdateMessage(msg, 0);

        // --- PREVIEW FOR WORKSHEET 7 ---
        // In Worksheet 7, you will add a line here like:
        // selectedPart->setColor(r, g, b);
        // renderer->Render();
    }
}
