
#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

#include <pconsts.h>


class PacMan : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PacMan(QObject *parent = nullptr);
    ~PacMan();

    int GetDir();
    void SetPacmanSpeed(int newValue);
    int  GetPacmanSpeed();

//    void PacmanMoving(int x, int y, pconsts::direction currentDir);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void signalCheckItem(QGraphicsItem *item, double x, double y);

public slots:
    void slotGameTimer();


private:

    int pacmanSpeed;

    qreal angle;
    int dir;

    int agngleMouthOpening;
    int tickForMouthOpening;
    int speedMouthOpening;

    QList< QGraphicsItem * > foundItems;
};

#endif // PACMAN_H
