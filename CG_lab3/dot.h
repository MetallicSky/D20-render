#ifndef DOT_H
#define DOT_H

#include <QGraphicsItem>
#include <QVector3D>


class Dot : public QGraphicsPolygonItem
{
public:
    Dot();

    QVector3D coords;
private:

};

#endif // DOT_H
