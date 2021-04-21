#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H


#include <QGraphicsView>
#include <QVector3D>
#include <QPointF>
#include <QtMath>
#include <QPen>
#include "dot.h"

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();


    void setP00(QVector3D newCoord);
    void setP01(QVector3D newCoord);
    void setP11(QVector3D newCoord);
    void setP10(QVector3D newCoord);
    QVector<QVector3D> turnX(int degree);
    QVector<QVector3D> turnY(int degree);
    QVector3D getP00();
    QVector3D getP01();
    QVector3D getP11();
    QVector3D getP10();

private:
    Dot* dots[4];

    QGraphicsScene *scene;

    bool lastX;

    int rotX, rotY, cacheX, cacheY;

    double xx, xy, yx, yy, zy;

    QPointF to2D(QVector3D coord);
    void setCoord(int pos, QVector3D newCoord);
    void restart();
    void drawLines();
    void updateTurnData();
};

#endif // MYGRAPHICVIEW_H
