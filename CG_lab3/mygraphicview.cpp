#include "mygraphicview.h"

const double goldenRatio =  (1 + sqrt(5)) / 2;

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


    setPolygons();
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 3; j++)
            polygons[i].rotatedDots[j] = polygons[i].originalDots[j];

    setPolColors();

    sortCloseness();


    lastAxis = 0;

    rotX = 0;
    rotY = 0;
    rotZ = 0;
    cacheX = 0;
    cacheY = 0;
    cacheZ = 0;

    scale = 50;

    xRay = false;
    colors = true;

    restart();
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

void MyGraphicView::turnX(int degree)
{
    if (lastAxis != 0)
        updateTurnData(0);


    double controlDeg = degree - rotX;
    double A = qDegreesToRadians(controlDeg);

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 3; j++)
        {
            double newY = polygons[i].originalDots[j].y() * qCos(A) + polygons[i].originalDots[j].z() * qSin(A);
            polygons[i].rotatedDots[j].setY(newY);

            double newZ = - polygons[i].originalDots[j].y() * qSin(A) + polygons[i].originalDots[j].z() * qCos(A);
            polygons[i].rotatedDots[j].setZ(newZ);
        }

    cacheX = degree;

    restart();
}

void MyGraphicView::turnY(int degree)
{
    if (lastAxis != 1)
        updateTurnData(1);

    double controlDeg = degree - rotY;
    double A = qDegreesToRadians(controlDeg);

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 3; j++)
        {
            double newX = polygons[i].originalDots[j].x() * qCos(A) + polygons[i].originalDots[j].z() * qSin(A);
            polygons[i].rotatedDots[j].setX(newX);

            double newZ = - polygons[i].originalDots[j].x() * qSin(A) + polygons[i].originalDots[j].z() * qCos(A);
            polygons[i].rotatedDots[j].setZ(newZ);
        }

    cacheY = degree;

    restart();
}

void MyGraphicView::turnZ(int degree)
{
    if (lastAxis != 2)
        updateTurnData(2);

    double controlDeg = degree - rotZ;
    double A = qDegreesToRadians(controlDeg);

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 3; j++)
        {
            double newX = polygons[i].originalDots[j].x() * qCos(A) - polygons[i].originalDots[j].y() * qSin(A);
            polygons[i].rotatedDots[j].setX(newX);

            double newY = - polygons[i].originalDots[j].x() * qSin(A) + polygons[i].originalDots[j].y() * qCos(A);
            polygons[i].rotatedDots[j].setY(newY);
        }

    cacheZ = degree;

    restart();
}

void MyGraphicView::setScale(int newScale)
{
    scale = newScale;
    restart();
}

void MyGraphicView::setXRay(bool value)
{
    xRay = value;
    restart();
}

void MyGraphicView::setColors(bool value)
{
    colors = value;
    restart();
}

void MyGraphicView::restart()
{
    sortCloseness();

    scene->clear();

    drawPolygons();
}

void MyGraphicView::drawPolygons()
{
    QPainter painter(this);

    QPointF center(scene->width() / 2, scene->height() / 2);

    QPointF temp;

    // axis lines
    /*
    QPen axisPen(Qt::green, 3, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(axisPen);

    temp = to2D(QVector3D(100, 0, 0));
    scene->addLine(QLineF(center, temp), axisPen);

    temp = to2D(QVector3D(0, 100, 0));
    scene->addLine(QLineF(center, temp), axisPen);

    temp = to2D(QVector3D(0, 0, 100));
    scene->addLine(QLineF(center, temp), axisPen);
    */
    //

    QPen pen(Qt::green, 1, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(pen);

    // polygons

    for (int i = 0; i < 20; i++)
    {
        QPolygonF poly;
        poly << to2D(polygons[i].rotatedDots[0]* scale) << to2D(polygons[i].rotatedDots[1] * scale) << to2D(polygons[i].rotatedDots[2] * scale);

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (colors == true)
            brush.setColor(polygons[i].color);
        else
            brush.setColor(Qt::black);


        scene->addPolygon(poly, pen, brush);
    }

    if (xRay == true)
        for (int i = 0; i < 20; i++)
        {
            QPolygonF poly;
            poly << to2D(polygons[i].rotatedDots[0]* scale) << to2D(polygons[i].rotatedDots[1] * scale) << to2D(polygons[i].rotatedDots[2] * scale);

            QBrush brush;


            scene->addPolygon(poly, pen, brush);
        }

}

void MyGraphicView::updateTurnData(int newLastAxis)
{
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 3; j++)
            polygons[i].originalDots[j] = polygons[i].rotatedDots[j];


    lastAxis = newLastAxis;

    rotX = cacheX;
    rotY = cacheY;
    rotZ = cacheZ;

}

void MyGraphicView::setPolygons()
{
    QVector3D vertexes[12]; // generating vertexes for polygons (faces)

    vertexes[0].setX(pow(goldenRatio, 2));
    vertexes[0].setY(0);
    vertexes[0].setZ(pow(goldenRatio, 3));

    vertexes[1] = vertexes[0];
    vertexes[1].setX(-vertexes[1].x());

    vertexes[10] = vertexes[0];
    vertexes[10].setZ(-vertexes[10].z());

    vertexes[11] = vertexes[10];
    vertexes[11].setX(-vertexes[11].x());


    vertexes[2].setX(0);
    vertexes[2].setY(pow(goldenRatio, 3));
    vertexes[2].setZ(pow(goldenRatio, 2));

    vertexes[3] = vertexes[2];
    vertexes[3].setY(-vertexes[3].y());

    vertexes[8] = vertexes[2];
    vertexes[8].setZ(-vertexes[8].z());

    vertexes[9] = vertexes[8];
    vertexes[9].setY(-vertexes[9].y());


    vertexes[4].setX(pow(goldenRatio, 3));
    vertexes[4].setY(pow(goldenRatio, 2));
    vertexes[4].setZ(0);

    vertexes[5] = vertexes[4];
    vertexes[5].setX(-vertexes[5].x());

    vertexes[6] = -vertexes[4];

    vertexes[7] = vertexes[6];
    vertexes[7].setX(-vertexes[7].x());



    polygons[0].setOriginal(vertexes[0], vertexes[1], vertexes[3]);
    polygons[1].setOriginal(vertexes[0], vertexes[2], vertexes[1]);
    polygons[2].setOriginal(vertexes[0], vertexes[3], vertexes[7]);
    polygons[3].setOriginal(vertexes[0], vertexes[7], vertexes[4]);
    polygons[4].setOriginal(vertexes[0], vertexes[4], vertexes[2]);
    polygons[5].setOriginal(vertexes[7], vertexes[10], vertexes[4]);
    polygons[6].setOriginal(vertexes[4], vertexes[10], vertexes[8]);
    polygons[7].setOriginal(vertexes[4], vertexes[8], vertexes[2]);
    polygons[8].setOriginal(vertexes[2], vertexes[8], vertexes[5]);
    polygons[9].setOriginal(vertexes[2], vertexes[5], vertexes[1]);
    polygons[10].setOriginal(vertexes[1], vertexes[5], vertexes[6]);
    polygons[11].setOriginal(vertexes[1], vertexes[6], vertexes[3]);
    polygons[12].setOriginal(vertexes[3], vertexes[6], vertexes[9]);
    polygons[13].setOriginal(vertexes[3], vertexes[9], vertexes[7]);
    polygons[14].setOriginal(vertexes[7], vertexes[9], vertexes[10]);
    polygons[15].setOriginal(vertexes[11], vertexes[10], vertexes[9]);
    polygons[16].setOriginal(vertexes[11], vertexes[8], vertexes[10]);
    polygons[17].setOriginal(vertexes[11], vertexes[5], vertexes[8]);
    polygons[18].setOriginal(vertexes[11], vertexes[6], vertexes[5]);
    polygons[19].setOriginal(vertexes[11], vertexes[9], vertexes[6]);
}

void MyGraphicView::setPolColors()
{
    polygons[0].color = QColorConstants::Svg::maroon;
    polygons[1].color = QColorConstants::Svg::brown;
    polygons[2].color = QColorConstants::Svg::olive;
    polygons[3].color = QColorConstants::Svg::teal;
    polygons[4].color = QColorConstants::Svg::navy;
    polygons[5].color = QColorConstants::Svg::black;
    polygons[6].color = QColorConstants::Svg::red;
    polygons[7].color = QColorConstants::Svg::orange;
    polygons[8].color = QColorConstants::Svg::yellow;
    polygons[9].color = QColorConstants::Svg::lime;
    polygons[10].color = QColorConstants::Svg::green;
    polygons[11].color = QColorConstants::Svg::cyan;
    polygons[12].color = QColorConstants::Svg::blue;
    polygons[13].color = QColorConstants::Svg::purple;
    polygons[14].color = QColorConstants::Svg::magenta;
    polygons[15].color = QColorConstants::Svg::grey;
    polygons[16].color = QColorConstants::Svg::pink;
    polygons[17].color = QColorConstants::Svg::coral;
    polygons[18].color = QColorConstants::Svg::beige;
    polygons[19].color = QColorConstants::Svg::mediumspringgreen;
}

void MyGraphicView::sortCloseness()
{
    double minX, minY, minZ, maxX, maxY, maxZ;

    minX = 1000;
    minY = 1000;
    minZ = 1000;

    for (int i = 0; i < 20; i++)
    {
        QVector3D temp = polygons[i].getCenter();

        if (temp.x() < minX)
            minX = temp.x();

        if (temp.y() < minY)
            minY = temp.y();

        if (temp.z() < minZ)
            minZ = temp.z();
    }

    QVector3D backpoint(minX, minY, minZ);

    QVector3D planePoint1(backpoint.x() * 100, 0, 0);
    QVector3D planePoint2(0, backpoint.y() * 100, 0);
    QVector3D planePoint3(0, 0, backpoint.z() * 100);

    for (int i = 0; i < 20; i++)
    {
        double distance = polygons[i].getCenter().distanceToPlane(planePoint1, planePoint2, planePoint3);
        if (distance < 0)
            distance = -1 * distance;
        polygons[i].closeness = distance;

    }


    bool swapped = true; // bubble sort

    while (swapped != false)
    {
        swapped = false;
        for (int i = 1; i < 20; i++)
            if (polygons[i - 1].closeness > polygons[i].closeness)
            {
                swap(i - 1, i);
                swapped = true;
            }
    }
}

void MyGraphicView::swap(int left, int right)
{
    if (left != right)
    {
        Polygon temp = polygons[left];
        polygons[left] = polygons[right];
        polygons[right] = temp;
    }
}
