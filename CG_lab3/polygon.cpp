#include "polygon.h"

Polygon::Polygon()
{

}

void Polygon::setOriginal(QVector3D dot1, QVector3D dot2, QVector3D dot3)
{
    originalDots[0] = dot1;
    originalDots[1] = dot2;
    originalDots[2] = dot3;
}

void Polygon::setRotated(QVector3D dot1, QVector3D dot2, QVector3D dot3)
{
    rotatedDots[0] = dot1;
    rotatedDots[1] = dot2;
    rotatedDots[2] = dot3;
}

QVector3D Polygon::getCenter()
{
    QVector3D center = (rotatedDots[0] + rotatedDots[1] + rotatedDots[2]) / 3;

    return center;
}
