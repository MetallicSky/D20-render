#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPicture = new MyGraphicView();

    ui->graphicsView->setViewport(myPicture);

    ui->label_ZRotation->setDisabled(true);
    ui->spinBox_ZRotation->setDisabled(true);
    ui->dial_ZRotation->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dial_XRotation_valueChanged(int value)
{
    ui->spinBox_XRotation->setValue(value);
}

void MainWindow::on_dial_YRotation_valueChanged(int value)
{
    ui->spinBox_YRotation->setValue(value);
}

void MainWindow::on_dial_ZRotation_valueChanged(int value)
{
    ui->spinBox_ZRotation->setValue(value);
}

void MainWindow::on_spinBox_XRotation_valueChanged(int arg1)
{
    ui->dial_XRotation->setValue(arg1);

    myPicture->turnX(arg1);
}

void MainWindow::on_spinBox_YRotation_valueChanged(int arg1)
{
    ui->dial_YRotation->setValue(arg1);

    myPicture->turnY(arg1);
}

void MainWindow::on_spinBox_ZRotation_valueChanged(int arg1)
{
    ui->dial_ZRotation->setValue(arg1);

    myPicture->turnZ(arg1);
}

void MainWindow::on_pushButton_restart_clicked()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void MainWindow::on_verticalSlider_zoom_valueChanged(int value)
{
    myPicture->setScale(value);
}

void MainWindow::on_checkBox_colors_stateChanged(int arg1)
{
    myPicture->setColors(ui->checkBox_colors->isChecked());
}

void MainWindow::on_checkBox_XRay_stateChanged(int arg1)
{
    myPicture->setXRay(ui->checkBox_XRay->isChecked());
}
