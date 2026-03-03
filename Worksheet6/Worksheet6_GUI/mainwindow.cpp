#include "mainwindow.h"
#include "ui_mainwindow.h"

// Your model headers (match your filenames)
#include "modelpartlist.h"
#include "modelpart.h"

#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- Status bar wiring (Exercise 3 style) ---
    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    // --- Buttons (Exercise 2 style) ---
    connect(ui->pushButton,   &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);

    // --- Tree model setup (Exercise 4/5 style) ---
    partList = new ModelPartList("PartsList", this);
    ui->treeView->setModel(partList);

    // Populate demo tree
    ModelPart *rootItem = partList->getRootItem();

    for (int i = 0; i < 3; ++i) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible = "true";
        ModelPart *childItem = new ModelPart(name, visible, rootItem);
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; ++j) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            QString subVisible = "true";
            ModelPart *subChild = new ModelPart(subName, subVisible, childItem);
            childItem->appendChild(subChild);
        }
    }

    ui->treeView->expandAll();

    // When user clicks an item -> show selected name in status bar
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

    // --- Menu/Toolbar action wiring (Exercise 6/7/8 style) ---
    // Force toolbar to show icons (so you don't get "text only")
    if (ui->toolBar) {
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }

    // Set icon (tries both common paths in case your .qrc prefix/file path is doubled)
    if (ui->actionOpen_File) {
        QIcon openIcon(":/icons/fileopen.png");
        if (openIcon.isNull())
            openIcon = QIcon(":/icons/icons/fileopen.png"); // fallback for your current qrc layout

        if (!openIcon.isNull())
            ui->actionOpen_File->setIcon(openIcon);
        else
            emit statusUpdateMessage("Icon not found in resources", 4000);

        // Connect action -> slot (avoids relying on auto-connect)
        connect(ui->actionOpen_File, &QAction::triggered,
                this, &MainWindow::on_actionOpen_File_triggered);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton1()
{
    QMessageBox::information(this, "Button", "Button 1 clicked");
    emit statusUpdateMessage("Button 1 was clicked", 2000);
}

void MainWindow::handleButton2()
{
    QMessageBox::information(this, "Button", "Button 2 clicked");
    emit statusUpdateMessage("Button 2 was clicked", 2000);
}

void MainWindow::handleTreeClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    auto *selectedPart = static_cast<ModelPart *>(index.internalPointer());
    if (!selectedPart) return;

    QString text = selectedPart->data(0).toString();
    emit statusUpdateMessage(QString("The selected item is: %1").arg(text), 2000);
}

void MainWindow::on_actionOpen_File_triggered(bool checked)
{
    Q_UNUSED(checked);

    const QString startDir = QStringLiteral("C:/");
    const QString filter   = tr("STL Files (*.stl);;Text Files (*.txt);;All Files (*.*)");

    const QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open File"), startDir, filter);

    if (fileName.isEmpty()) {
        emit statusUpdateMessage(tr("Open cancelled"), 2000);
        return;
    }

    emit statusUpdateMessage(tr("Selected: %1").arg(fileName), 0);
}
