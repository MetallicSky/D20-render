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

    QVector<QVector3D> newDots;

    newDots = myPicture->turnX(value);

    updateSpinboxes(newDots);
}

void MainWindow::on_dial_YRotation_valueChanged(int value)
{
    ui->spinBox_YRotation->setValue(value);

    QVector<QVector3D> newDots;

    newDots = myPicture->turnY(value);

    updateSpinboxes(newDots);
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

void MainWindow::updateSpinboxes(QVector<QVector3D> newDots)
{
    // block signals to prevent unwanted valueChanged() signals

    ui->spinBox_X00->blockSignals(true);
    ui->spinBox_Y00->blockSignals(true);
    ui->spinBox_Z00->blockSignals(true);

    ui->spinBox_X01->blockSignals(true);
    ui->spinBox_Y01->blockSignals(true);
    ui->spinBox_Z01->blockSignals(true);

    ui->spinBox_X11->blockSignals(true);
    ui->spinBox_Y11->blockSignals(true);
    ui->spinBox_Z11->blockSignals(true);

    ui->spinBox_X10->blockSignals(true);
    ui->spinBox_Y10->blockSignals(true);
    ui->spinBox_Z10->blockSignals(true);

    // change values in peace

    ui->spinBox_X00->setValue(newDots[0].x());
    ui->spinBox_Y00->setValue(newDots[0].y());
    ui->spinBox_Z00->setValue(newDots[0].z());

    ui->spinBox_X01->setValue(newDots[1].x());
    ui->spinBox_Y01->setValue(newDots[1].y());
    ui->spinBox_Z01->setValue(newDots[1].z());

    ui->spinBox_X11->setValue(newDots[2].x());
    ui->spinBox_Y11->setValue(newDots[2].y());
    ui->spinBox_Z11->setValue(newDots[2].z());

    ui->spinBox_X10->setValue(newDots[3].x());
    ui->spinBox_Y10->setValue(newDots[3].y());
    ui->spinBox_Z10->setValue(newDots[3].z());

    // return everything to normal

    ui->spinBox_X00->blockSignals(false);
    ui->spinBox_Y00->blockSignals(false);
    ui->spinBox_Z00->blockSignals(false);

    ui->spinBox_X01->blockSignals(false);
    ui->spinBox_Y01->blockSignals(false);
    ui->spinBox_Z01->blockSignals(false);

    ui->spinBox_X11->blockSignals(false);
    ui->spinBox_Y11->blockSignals(false);
    ui->spinBox_Z11->blockSignals(false);

    ui->spinBox_X10->blockSignals(false);
    ui->spinBox_Y10->blockSignals(false);
    ui->spinBox_Z10->blockSignals(false);
}

void MainWindow::on_pushButton_restart_clicked()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void MainWindow::updateDots()
{
    QVector3D temp;

    temp = myPicture->getP00();

    ui->spinBox_X00->setValue(temp.x());
    ui->spinBox_Y00->setValue(temp.y());
    ui->spinBox_Z00->setValue(temp.z());

    temp = myPicture->getP01();

    ui->spinBox_X01->setValue(temp.x());
    ui->spinBox_Y01->setValue(temp.y());
    ui->spinBox_Z01->setValue(temp.z());

    temp = myPicture->getP11();

    ui->spinBox_X11->setValue(temp.x());
    ui->spinBox_Y11->setValue(temp.y());
    ui->spinBox_Z11->setValue(temp.z());

    temp = myPicture->getP10();

    ui->spinBox_X10->setValue(temp.x());
    ui->spinBox_Y10->setValue(temp.y());
    ui->spinBox_Z10->setValue(temp.z());
}

void MainWindow::on_spinBox_X00_editingFinished()
{
    int i = 0;
}
