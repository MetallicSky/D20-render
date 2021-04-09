#include "mygraphicview.h"

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);


    this->setScene(scene);

    this->setRenderHint(QPainter::Antialiasing);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    this->setMinimumHeight(798);
    this->setMinimumWidth(798);

    scene->setSceneRect(0, 0, 798, 798);


    double deg30(30);
    double deg60(60);

    xx = -1 * qCos(qDegreesToRadians(deg30));
    xy = 1 * qSin(qDegreesToRadians(deg30));
    yx = 1 * qSin(qDegreesToRadians(deg60));
    yy = 1 * qCos(qDegreesToRadians(deg60));
    zy = -1;


    QBrush brush;
    brush.setStyle(Qt::DiagCrossPattern);
    brush.setColor(Qt::red);

    QVector<QPointF> dotRect;
    dotRect << QPoint(-5,-5)
              << QPointF(5, -5)
              << QPointF(5, 5)
              << QPointF(-5, 5);

    for (int i = 0; i < 4; i++)
    {
        dots[i] = new Dot;

        scene->addItem(dots[i]);

        dots[i]->setBrush(brush);

        dots[i]->setPolygon(dotRect);
    }


    rotX = 0;
    rotY = 0;
}

MyGraphicView::~MyGraphicView()
{

}

QPointF MyGraphicView::to2D(QVector3D coord)
{
    double x = coord.x();
    double y = coord.y();
    double z = coord.z();

    double newX = x * xx + y * yx;
    double newY = x * xy + y * yy + z * zy;

    QPointF result(scene->width() / 2 + newX, scene->height() / 2 + newY);

    return result;
}

void MyGraphicView::setP00(QVector3D newCoord)
{
    setCoord(0, newCoord);
}

void MyGraphicView::setP01(QVector3D newCoord)
{
    setCoord(1, newCoord);
}

void MyGraphicView::setP11(QVector3D newCoord)
{
    setCoord(2, newCoord);
}

void MyGraphicView::setP10(QVector3D newCoord)
{
    setCoord(3, newCoord);
}

void MyGraphicView::turnX(int degree)
{
    double controlDeg = degree - rotX;
    double A = qDegreesToRadians(controlDeg);

    if (controlDeg == 0)
        return;

    for (int i = 0; i < 4; i++)
    {
        double newY = dots[i]->coords.y() * qCos(A) + dots[i]->coords.z() * qSin(A);
        dots[i]->coords.setY(newY);

        double newZ = - dots[i]->coords.y() * qSin(A) + dots[i]->coords.z() * qCos(A);
        dots[i]->coords.setZ(newZ);


        dots[i]->setPos(to2D(dots[i]->coords));
    }

    rotX = degree;

    restart();
}

void MyGraphicView::turnY(int degree)
{
    double controlDeg = degree - rotY;
    double A = qDegreesToRadians(controlDeg);

    if (controlDeg == 0)
        return;

    for (int i = 0; i < 4; i++)
    {
        double newX = dots[i]->coords.x() * qCos(A) + dots[i]->coords.z() * qSin(A);
        dots[i]->coords.setX(newX);

        double newZ = - dots[i]->coords.x() * qSin(A) + dots[i]->coords.z() * qCos(A);
        dots[i]->coords.setZ(newZ);


        dots[i]->setPos(to2D(dots[i]->coords));
    }

    rotY = degree;

    restart();
}

void MyGraphicView::setCoord(int pos, QVector3D newCoord)
{
    dots[pos]->coords = newCoord;

    dots[pos]->setPos(to2D(dots[pos]->coords));

    restart();
}

void MyGraphicView::restart()
{
    for (int i = 0; i < 4; i++)
        scene->removeItem(dots[i]);

    scene->clear();

    for (int i = 0; i < 4; i++)
        scene->addItem(dots[i]);

    drawLines();
}

void MyGraphicView::drawLines()
{
    QPainter painter(this);

    // axis lines

    QPen axisPen(Qt::green, 3, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(axisPen);

    QPointF center(scene->width() / 2, scene->height() / 2);

    QPointF temp;

    temp = to2D(QVector3D(100, 0, 0));
    scene->addLine(QLineF(center, temp), axisPen);

    temp = to2D(QVector3D(0, 100, 0));
    scene->addLine(QLineF(center, temp), axisPen);

    temp = to2D(QVector3D(0, 0, 100));
    scene->addLine(QLineF(center, temp), axisPen);

    //

    QPen pen(Qt::green, 1, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(pen);

    // 4 border lines

    for (int i = 0; i < 4; i++)
        scene->addLine(QLineF(dots[i]->pos(), dots[(i + 1) % 4]->pos()), pen);

    // grid lines


    for (float u = 0.05; u < 1; u += 0.05) // vertical lines
    {
        float w;

        w = 0;
        QVector3D dot1 = dots[0]->coords * ((1 - u) * (1 - w)) + dots[1]->coords * (1 - u) * w + dots[3]->coords * u * (1 - w) + dots[2]->coords * u * w;

        w = 1;
        QVector3D dot2 = dots[0]->coords * ((1 - u) * (1 - w)) + dots[1]->coords * (1 - u) * w + dots[3]->coords * u * (1 - w) + dots[2]->coords * u * w;

        scene->addLine(QLineF(to2D(dot1), to2D(dot2)), pen);
    }

    for (float w = 0.05; w < 1; w += 0.05) // horizontal lines
    {
        float u;

        u = 0;
        QVector3D dot1 = dots[0]->coords * ((1 - u) * (1 - w)) + dots[1]->coords * (1 - u) * w + dots[3]->coords * u * (1 - w) + dots[2]->coords * u * w;

        u = 1;
        QVector3D dot2 = dots[0]->coords * ((1 - u) * (1 - w)) + dots[1]->coords * (1 - u) * w + dots[3]->coords * u * (1 - w) + dots[2]->coords * u * w;

        scene->addLine(QLineF(to2D(dot1), to2D(dot2)), pen);
    }

}
