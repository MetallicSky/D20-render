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

    void on_dial_ZRotation_valueChanged(int value);

    void on_spinBox_XRotation_valueChanged(int arg1);

    void on_spinBox_YRotation_valueChanged(int arg1);

    void on_spinBox_ZRotation_valueChanged(int arg1);

    void on_pushButton_restart_clicked();

    void on_verticalSlider_zoom_valueChanged(int value);

    void on_checkBox_colors_stateChanged(int arg1);

    void on_checkBox_XRay_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    MyGraphicView *myPicture;

};
#endif // MAINWINDOW_H
