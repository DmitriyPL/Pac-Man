#include "wall.h"

Wall::Wall(QObject *parent) :
    QObject (parent),
    QGraphicsItem (),
    wallColor(0)
{}

Wall::~Wall()
{}

void Wall::SetWallColor(int color)
{
    wallColor = color;
}

QRectF Wall::boundingRect() const
{
    return QRectF(-18, -18, 36, 36);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if (wallColor == 0)
    {
        painter->setPen(QPen(Qt::blue));
        painter->setBrush(Qt::blue);
        painter->drawRect(-18, -18, 36, 36);
    }

    if (wallColor == 1)
    {
        painter->setPen(QPen(Qt::black));
        painter->setBrush(Qt::black);
        painter->drawRect(-18, -18, 36, 36);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
