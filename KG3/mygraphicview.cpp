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

    lastX = true;

    rotX = 0;
    rotY = 0;
    cacheX = 0;
    cacheY = 0;
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

QVector<QVector3D> MyGraphicView::turnX(int degree)
{
    if (lastX == false)
        updateTurnData();


    double controlDeg = degree - rotX;
    double A = qDegreesToRadians(controlDeg);

    QVector<QVector3D> result;

    for (int i = 0; i < 4; i++)
    {
        double newY = dots[i]->originalCoords.y() * qCos(A) + dots[i]->originalCoords.z() * qSin(A);
        dots[i]->rotatedCoords.setY(newY);

        double newZ = - dots[i]->originalCoords.y() * qSin(A) + dots[i]->originalCoords.z() * qCos(A);
        dots[i]->rotatedCoords.setZ(newZ);


        dots[i]->setPos(to2D(dots[i]->rotatedCoords));

        result.push_back(dots[i]->rotatedCoords);
    }

    cacheX = degree;

    restart();

    return result;
}

QVector<QVector3D> MyGraphicView::turnY(int degree)
{
    if (lastX == true)
            updateTurnData();

    double controlDeg = degree - rotY;
    double A = qDegreesToRadians(controlDeg);

    QVector<QVector3D> result;

    for (int i = 0; i < 4; i++)
    {
        double newX = dots[i]->originalCoords.x() * qCos(A) + dots[i]->originalCoords.z() * qSin(A);
        dots[i]->rotatedCoords.setX(newX);

        double newZ = - dots[i]->originalCoords.x() * qSin(A) + dots[i]->originalCoords.z() * qCos(A);
        dots[i]->rotatedCoords.setZ(newZ);


        dots[i]->setPos(to2D(dots[i]->rotatedCoords));

        result.push_back(dots[i]->rotatedCoords);
    }

    cacheY = degree;

    restart();

    return result;
}

QVector3D MyGraphicView::getP00()
{
    return dots[0]->rotatedCoords;
}

QVector3D MyGraphicView::getP01()
{
    return dots[1]->rotatedCoords;
}

QVector3D MyGraphicView::getP11()
{
    return dots[2]->rotatedCoords;
}

QVector3D MyGraphicView::getP10()
{
    return dots[3]->rotatedCoords;
}

void MyGraphicView::setCoord(int pos, QVector3D newCoord)
{
    dots[pos]->rotatedCoords = newCoord;

    updateTurnData();


    dots[pos]->setPos(to2D(dots[pos]->rotatedCoords));

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

    // /*

    for (float u = 0.05; u < 1; u += 0.05) // vertical lines
    {
        float w;

        w = 0;
        QVector3D dot1 = dots[0]->rotatedCoords * ((1 - u) * (1 - w)) + dots[1]->rotatedCoords * (1 - u) * w + dots[3]->rotatedCoords * u * (1 - w) + dots[2]->rotatedCoords * u * w;

        w = 1;
        QVector3D dot2 = dots[0]->rotatedCoords * ((1 - u) * (1 - w)) + dots[1]->rotatedCoords * (1 - u) * w + dots[3]->rotatedCoords * u * (1 - w) + dots[2]->rotatedCoords * u * w;

        scene->addLine(QLineF(to2D(dot1), to2D(dot2)), pen);
    }

    for (float w = 0.05; w < 1; w += 0.05) // horizontal lines
    {
        float u;

        u = 0;
        QVector3D dot1 = dots[0]->rotatedCoords * ((1 - u) * (1 - w)) + dots[1]->rotatedCoords * (1 - u) * w + dots[3]->rotatedCoords * u * (1 - w) + dots[2]->rotatedCoords * u * w;

        u = 1;
        QVector3D dot2 = dots[0]->rotatedCoords * ((1 - u) * (1 - w)) + dots[1]->rotatedCoords * (1 - u) * w + dots[3]->rotatedCoords * u * (1 - w) + dots[2]->rotatedCoords * u * w;

        scene->addLine(QLineF(to2D(dot1), to2D(dot2)), pen);
    }
    // */

}

void MyGraphicView::updateTurnData()
{
    for (int i = 0; i < 4; i++)
        dots[i]->originalCoords = dots[i]->rotatedCoords;

    lastX = !lastX;

    rotX = cacheX;
    rotY = cacheY;
}
