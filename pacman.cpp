#include "pacman.h"

PacMan::PacMan(QObject *parent) :
    QObject (parent),
    QGraphicsItem()
{
    isPushedLeft  = false;
    isPushedRight = false;
    isPushedUp    = false;
    isPushedDown  = false;

    dir = right;

    angle = 0;
    setRotation(angle);

    agngleMouthOpening = 1;
    tickForMouthOpening = 0;
}

PacMan::~PacMan()
{}

QRectF PacMan::boundingRect() const
{
    return QRectF(-15, -15, 30, 30);
}

void PacMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::yellow));
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(-15, -15, 30, 30);

    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::black);

    if (dir == left) painter->drawEllipse(3,6,3,3);
    else painter->drawEllipse(3,-9,3,3);

    QPolygon mouth;

         if (agngleMouthOpening == 1) { mouth << QPoint(0,0) << QPoint(16 , 10) << QPoint(16 , -10); }
    else if (agngleMouthOpening == 2) { mouth << QPoint(0,0) << QPoint(16 , 10) << QPoint(16 , -10); }
    else if (agngleMouthOpening == 3) { mouth << QPoint(0,0) << QPoint(16 , 8 ) << QPoint(16 , -8 ); }
    else if (agngleMouthOpening == 4) { mouth << QPoint(0,0) << QPoint(16 , 6 ) << QPoint(16 , -6 ); }
    else if (agngleMouthOpening == 5) { mouth << QPoint(0,0) << QPoint(16 , 3 ) << QPoint(16 , -3 ); }
    else if (agngleMouthOpening == 6) { mouth << QPoint(0,0) << QPoint(16 , 0 ) << QPoint(16 ,  0 ); }

    painter->drawPolygon(mouth);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void PacMan::slotGameTimer()
{

    LeftButton();
    RightButton();
    UpButton();
    DownButton();

    tickForMouthOpening++;

    speedMouthOpening = 4;

    if (tickForMouthOpening == ( 2 + speedMouthOpening ) ){
        agngleMouthOpening = 2;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 4 + speedMouthOpening ) ){
        agngleMouthOpening = 3;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 8 + speedMouthOpening ) ){
        agngleMouthOpening = 4;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 10 + speedMouthOpening ) ){
        agngleMouthOpening = 5;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 12 + speedMouthOpening ) ){
        agngleMouthOpening = 6;
        update(QRectF(-15, -15, 30, 30));
        tickForMouthOpening = 0;
    }

    foundItems = scene()->items(QPolygonF()
                                << mapToScene( 0,  0 )
                                << mapToScene(15,  13)
                                << mapToScene(15, -13) );

    foreach (QGraphicsItem *item, foundItems)
    {
        if (item == this) continue;

        emit signalCheckItem(item);
    }

    if  (this->x() > 597 ) this->setX(-58);
    if  (this->x() < -58 ) this->setX(597);

}

void PacMan::LeftButton()
{
    if(GetAsyncKeyState(VK_LEFT))
    {
        isPushedRight = false;
        isPushedUp    = false;
        isPushedDown  = false;

        if (isPushedLeft)
        {
            if (dir == right) setPos(mapToParent(-2,0));
            else setPos(mapToParent(2,0));
        }
        else
        {
            switch (dir)
            {

            case right:
            {
                angle -= 180;
                setRotation(angle);
                dir = left;
            }
                break;

            case left:
            {
                angle = 0 ;
                setRotation(angle);
                dir = left;
            }
                break;

            case up:
            {
                angle -= 90 ;
                setRotation(angle);
                dir = left;
            }
                break;

            case down:
            {
                angle += 90 ;
                setRotation(angle);
                dir = left;
            }
                break;

            }
        }

        isPushedLeft = true;
    }

}

void PacMan::RightButton()
{
    if(GetAsyncKeyState(VK_RIGHT))
    {
        isPushedLeft = false;
        isPushedUp   = false;
        isPushedDown = false;

        if (isPushedRight)
        {
            setPos(mapToParent(2,0));
        }
        else
        {
            switch (dir)
            {

            case right:
            {
                angle = 0;
                setRotation(angle);
                dir = right;
            }
                break;

            case left:
            {
                angle += 180 ;
                setRotation(angle);
                dir = right;
            }
                break;

            case up:
            {
                angle += 90 ;
                setRotation(angle);
                dir = right;
            }
                break;

            case down:
            {
                angle -= 90 ;
                setRotation(angle);
                dir = right;
            }
                break;
            }
        }

        isPushedRight = true;
    }

}

void PacMan::UpButton()
{
    if(GetAsyncKeyState(VK_UP))
    {

        isPushedLeft  = false;
        isPushedRight = false;
        isPushedDown  = false;

        if (isPushedUp)
        {
            if (dir == right) setPos(mapToParent(-2,0));
            else setPos(mapToParent(2,0));
        }
        else
        {
            switch (dir)
            {

            case right:
            {
                angle -= 90 ;
                setRotation(angle);
                dir = up;
            }
                break;

            case left:
            {
                angle += 90 ;
                setRotation(angle);
                dir = up;
            }
                break;

            case up:
            {
                angle = 0 ;
                setRotation(angle);
                dir = up;
            }
                break;

            case down:
            {
                angle -= 180 ;
                setRotation(angle);
                dir = up;
            }
                break;
            }
        }

        isPushedUp = true;

    }

}

void PacMan::DownButton()
{
    if(GetAsyncKeyState(VK_DOWN))
    {

        isPushedLeft  = false;
        isPushedRight = false;
        isPushedUp    = false;

        if (isPushedDown)
        {
            if (dir == right) setPos(mapToParent(-2,0));
            else setPos(mapToParent(2,0));
        }
        else
        {
            switch (dir)
            {

            case right:
            {
                angle += 90 ;
                setRotation(angle);
                dir = down;
            }
                break;

            case left:
            {
                angle -= 90 ;
                setRotation(angle);
                dir = down;
            }
                break;

            case up:
            {
                angle += 180 ;
                setRotation(angle);
                dir = down;
            }
                break;

            case down:
            {
                angle = 0 ;
                setRotation(angle);
                dir = down;
            }
                break;
            }
        }

        isPushedDown = true;
    }
}

int PacMan::GetDir()
{
    return dir;
}
