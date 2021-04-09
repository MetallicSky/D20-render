#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPicture = new MyGraphicView();

    ui->graphicsView->setViewport(myPicture);

    update00();
    update01();
    update11();
    update10();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dial_XRotation_valueChanged(int value)
{
    ui->spinBox_XRotation->setValue(value);

    myPicture->turnX(value);
}

void MainWindow::on_dial_YRotation_valueChanged(int value)
{
    ui->spinBox_YRotation->setValue(value);

    myPicture->turnY(value);
}

void MainWindow::on_spinBox_XRotation_valueChanged(int arg1)
{
    ui->dial_XRotation->setValue(arg1);
}

void MainWindow::on_spinBox_YRotation_valueChanged(int arg1)
{
    ui->dial_YRotation->setValue(arg1);
}

void MainWindow::on_spinBox_X00_valueChanged(int arg1)
{
    update00();
}

void MainWindow::on_spinBox_Y00_valueChanged(int arg1)
{
     update00();
}

void MainWindow::on_spinBox_Z00_valueChanged(int arg1)
{
    update00();
}

void MainWindow::on_spinBox_X01_valueChanged(int arg1)
{
    update01();
}

void MainWindow::on_spinBox_Y01_valueChanged(int arg1)
{
    update01();
}

void MainWindow::on_spinBox_Z01_valueChanged(int arg1)
{
    update01();
}

void MainWindow::on_spinBox_X11_valueChanged(int arg1)
{
    update11();
}

void MainWindow::on_spinBox_Y11_valueChanged(int arg1)
{
    update11();
}

void MainWindow::on_spinBox_Z11_valueChanged(int arg1)
{
    update11();
}

void MainWindow::on_spinBox_X10_valueChanged(int arg1)
{
    update10();
}

void MainWindow::on_spinBox_Y10_valueChanged(int arg1)
{
    update10();
}

void MainWindow::on_spinBox_Z10_valueChanged(int arg1)
{
    update10();
}

void MainWindow::update00()
{
    float x = ui->spinBox_X00->value();
    float y = ui->spinBox_Y00->value();
    float z = ui->spinBox_Z00->value();
    QVector3D newDot(x, y, z);
    myPicture->setP00(newDot);
}

void MainWindow::update01()
{
    float x = ui->spinBox_X01->value();
    float y = ui->spinBox_Y01->value();
    float z = ui->spinBox_Z01->value();
    QVector3D newDot(x, y, z);
    myPicture->setP01(newDot);
}

void MainWindow::update11()
{
    float x = ui->spinBox_X11->value();
    float y = ui->spinBox_Y11->value();
    float z = ui->spinBox_Z11->value();
    QVector3D newDot(x, y, z);
    myPicture->setP11(newDot);
}

void MainWindow::update10()
{
    float x = ui->spinBox_X10->value();
    float y = ui->spinBox_Y10->value();
    float z = ui->spinBox_Z10->value();
    QVector3D newDot(x, y, z);
    myPicture->setP10(newDot);
}

void MainWindow::on_pushButton_restart_clicked()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void MainWindow::updateDots()
{
    update00();
    update01();
    update11();
    update10();
}
