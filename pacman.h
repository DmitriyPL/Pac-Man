#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>

#include <windows.h>

class PacMan : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PacMan(QObject *parent = nullptr);
    ~PacMan();

    void LeftButton();
    void RightButton();
    void UpButton();
    void DownButton();

    int GetDir();

signals:
    void signalCheckItem(QGraphicsItem *item);

public slots:
    void slotGameTimer();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    qreal angle;
    bool isPushedLeft, isPushedRight, isPushedUp, isPushedDown;
    int dir;
    enum direction { left = 1, right, up, down };

    int agngleMouthOpening;
    int tickForMouthOpening;
    int speedMouthOpening;

    QList< QGraphicsItem * > foundItems;

};

#endif // PACMAN_H
