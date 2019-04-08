#ifndef POINTS_H
#define POINTS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

class Points : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Points(QObject *parent = nullptr);
    ~Points();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // POINTS_H
