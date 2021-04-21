#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "mygraphicview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dial_XRotation_valueChanged(int value);

    void on_dial_YRotation_valueChanged(int value);

    void on_spinBox_XRotation_valueChanged(int arg1);

    void on_spinBox_YRotation_valueChanged(int arg1);

    void on_spinBox_X00_valueChanged(int arg1);

    void on_spinBox_Y00_valueChanged(int arg1);

    void on_spinBox_Z00_valueChanged(int arg1);

    void on_spinBox_X01_valueChanged(int arg1);

    void on_spinBox_Y01_valueChanged(int arg1);

    void on_spinBox_Z01_valueChanged(int arg1);

    void on_spinBox_X11_valueChanged(int arg1);

    void on_spinBox_Y11_valueChanged(int arg1);

    void on_spinBox_Z11_valueChanged(int arg1);

    void on_spinBox_X10_valueChanged(int arg1);

    void on_spinBox_Y10_valueChanged(int arg1);

    void on_spinBox_Z10_valueChanged(int arg1);

    void on_pushButton_restart_clicked();

    void on_spinBox_X00_editingFinished();

private:
    Ui::MainWindow *ui;

    MyGraphicView *myPicture;

    void updateDots();
    void update00();
    void update01();
    void update11();
    void update10();
    void updateSpinboxes(QVector<QVector3D> newDots);
};
#endif // MAINWINDOW_H
