#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,   &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::handleButton1()
{
    QMessageBox::information(this, "Info", "Button 1 clicked");
}

void MainWindow::handleButton2()
{
    QMessageBox::information(this, "Info", "Button 2 clicked");
}
