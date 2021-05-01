#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H


#include <QGraphicsView>
#include <QVector3D>
#include <QPointF>
#include <QtMath>
#include <QPen>
#include "polygon.h"

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

    void turnX(int degree);
    void turnY(int degree);
    void turnZ(int degree);
    void setScale(int newScale);
    void setXRay(bool value);
    void setColors(bool value);
private:

    Polygon polygons[20];

    QGraphicsScene *scene;

    bool xRay, colors;

    int rotX, rotY, rotZ, cacheX, cacheY, cacheZ, lastAxis;

    double xx, xy, yx, yy, zy, scale;

    QPointF to2D(QVector3D coord);
    void restart();
    void drawPolygons();
    void updateTurnData(int newLastAxis);

    void setPolygons();
    void setPolColors();
    void sortCloseness();

    void swap(int left, int right);
};

#endif // MYGRAPHICVIEW_H
