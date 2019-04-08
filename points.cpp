#include "points.h"

Points::Points(QObject *parent) :
    QObject (parent),
    QGraphicsItem ()
{}

Points::~Points()
{}

QRectF Points::boundingRect() const
{
    return QRectF(-4,-4,4,4);
}

void Points::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::yellow));
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(-4,-4,4,4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
