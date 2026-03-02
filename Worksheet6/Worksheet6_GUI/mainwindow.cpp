#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to our slots
    connect(ui->pushButton,   &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);

    // Connect our custom signal to the status bar's showMessage slot
    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton1()
{
    emit statusUpdateMessage("Button 1 was clicked", 2000); // 2 seconds
}

void MainWindow::handleButton2()
{
    emit statusUpdateMessage("Button 2 was clicked", 2000); // 2 seconds
}
