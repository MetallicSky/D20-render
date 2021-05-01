#ifndef POLYGON_H
#define POLYGON_H

#include <QVector3D>
#include <QColor>

class Polygon
{
public:
    Polygon();

    void setOriginal(QVector3D dot1, QVector3D dot2, QVector3D dot3);
    void setRotated(QVector3D dot1, QVector3D dot2, QVector3D dot3);
    QVector3D getCenter();

    QVector3D originalDots[3];
    QVector3D rotatedDots[3];

    QColor color;

    double closeness;
};

#endif // POLYGON_H
