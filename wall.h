#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

class Wall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Wall(QObject *parent = nullptr);
    ~Wall();

    void SetWallColor(int color);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int wallColor;

};

#endif // WALL_H
