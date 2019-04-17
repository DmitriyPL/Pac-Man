#include "pacman.h"

PacMan::PacMan(QObject *parent) :
    QObject (parent),
    QGraphicsItem()
{
    dir = pconsts::direction::RIGHT;

    angle = 0;
    setRotation(angle);

    pacmanSpeed = 5;

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

    if (dir == pconsts::direction::RIGHT){

        painter->setPen(QPen(Qt::yellow));
        painter->setBrush(Qt::yellow);

        if ( agngleMouthOpening == 1 ) painter->drawPie(-15, -15, 30, 30, -55 * 16, -250 * 16);
        if ( agngleMouthOpening == 2 ) painter->drawPie(-15, -15, 30, 30, -45 * 16, -270 * 16);
        if ( agngleMouthOpening == 3 ) painter->drawPie(-15, -15, 30, 30, -35 * 16, -290 * 16);
        if ( agngleMouthOpening == 4 ) painter->drawPie(-15, -15, 30, 30, -25 * 16, -310 * 16);
        if ( agngleMouthOpening == 5 ) painter->drawPie(-15, -15, 30, 30, -15 * 16, -330 * 16);
        if ( agngleMouthOpening == 6 ) painter->drawPie(-15, -15, 30, 30, -5  * 16, -350 * 16);

        painter->setPen(QPen(Qt::black));
        painter->setBrush(Qt::black);

        painter->drawEllipse(3,-10,3,3);
    }

    if (dir == pconsts::direction::LEFT){

        painter->setPen(QPen(Qt::yellow));
        painter->setBrush(Qt::yellow);

        if ( agngleMouthOpening == 1 ) painter->drawPie(-15, -15, 30, 30, -125 * 16, 250 * 16);
        if ( agngleMouthOpening == 2 ) painter->drawPie(-15, -15, 30, 30, -135 * 16, 270 * 16);
        if ( agngleMouthOpening == 3 ) painter->drawPie(-15, -15, 30, 30, -145 * 16, 290 * 16);
        if ( agngleMouthOpening == 4 ) painter->drawPie(-15, -15, 30, 30, -155 * 16, 310 * 16);
        if ( agngleMouthOpening == 5 ) painter->drawPie(-15, -15, 30, 30, -165 * 16, 330 * 16);
        if ( agngleMouthOpening == 6 ) painter->drawPie(-15, -15, 30, 30, -175 * 16, 350 * 16);

        painter->setPen(QPen(Qt::black));
        painter->setBrush(Qt::black);

        painter->drawEllipse(-6,-10,3,3);
    }

    if (dir == pconsts::direction::UP){

        painter->setPen(QPen(Qt::yellow));
        painter->setBrush(Qt::yellow);

            if ( agngleMouthOpening == 1 ) painter->drawPie(-15, -15, 30, 30, 145 * 16, 240 * 16);
            if ( agngleMouthOpening == 2 ) painter->drawPie(-15, -15, 30, 30, 135 * 16, 260 * 16);
            if ( agngleMouthOpening == 3 ) painter->drawPie(-15, -15, 30, 30, 125 * 16, 280 * 16);
            if ( agngleMouthOpening == 4 ) painter->drawPie(-15, -15, 30, 30, 115 * 16, 300 * 16);
            if ( agngleMouthOpening == 5 ) painter->drawPie(-15, -15, 30, 30, 105 * 16, 330 * 16);
            if ( agngleMouthOpening == 6 ) painter->drawPie(-15, -15, 30, 30, 95  * 16, 350 * 16);

        painter->setPen(QPen(Qt::black));
        painter->setBrush(Qt::black);

        painter->drawEllipse(-10,-6,3,3);
    }

    if (dir == pconsts::direction::DOWN){

        painter->setPen(QPen(Qt::yellow));
        painter->setBrush(Qt::yellow);

            if ( agngleMouthOpening == 1 ) painter->drawPie(-15, -15, 30, 30, -35 * 16, 240 * 16);
            if ( agngleMouthOpening == 2 ) painter->drawPie(-15, -15, 30, 30, -45 * 16, 270 * 16);
            if ( agngleMouthOpening == 3 ) painter->drawPie(-15, -15, 30, 30, -55 * 16, 290 * 16);
            if ( agngleMouthOpening == 4 ) painter->drawPie(-15, -15, 30, 30, -65 * 16, 310 * 16);
            if ( agngleMouthOpening == 5 ) painter->drawPie(-15, -15, 30, 30, -75 * 16, 330 * 16);
            if ( agngleMouthOpening == 6 ) painter->drawPie(-15, -15, 30, 30, -85 * 16, 350 * 16);

        painter->setPen(QPen(Qt::black));
        painter->setBrush(Qt::black);

        painter->drawEllipse(-10,3,3,3);
    }


    Q_UNUSED(option);
    Q_UNUSED(widget);
}

bool PacMan::eventFilter(QObject *obj, QEvent *event)
{
    if ( (event->type() == QEvent::KeyPress) ){

        QKeyEvent *keyEvent = static_cast < QKeyEvent* > ( event );

        switch (keyEvent->key()) {

        case Qt::Key_Right:

            setPos( mapToParent( this->GetPacmanSpeed() , 0 ) );
            dir = pconsts::direction::RIGHT;
            return true;

        case Qt::Key_Left:

            setPos( mapToParent( - this->GetPacmanSpeed() , 0 ) );
            dir = pconsts::direction::LEFT;
            return true;

        case Qt::Key_Up:

            setPos( mapToParent( 0 , - this->GetPacmanSpeed() ) );
            dir = pconsts::direction::UP;
            return true;

        case Qt::Key_Down:

            setPos( mapToParent( 0 , this->GetPacmanSpeed() ) );
            dir = pconsts::direction::DOWN;
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}

void PacMan::slotGameTimer()
{
    tickForMouthOpening++;

    speedMouthOpening = 10;

    if (tickForMouthOpening == ( 2 * speedMouthOpening ) ){
        agngleMouthOpening = 2;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 3 * speedMouthOpening ) ){
        agngleMouthOpening = 3;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 4 * speedMouthOpening ) ){
        agngleMouthOpening = 4;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 5 * speedMouthOpening ) ){
        agngleMouthOpening = 5;
        update(QRectF(-15, -15, 30, 30));
    } else if (tickForMouthOpening == ( 6 * speedMouthOpening ) ){
        agngleMouthOpening = 6;
        update(QRectF(-15, -15, 30, 30));
        tickForMouthOpening = 0;
    }

    foundItems = this->collidingItems();

    foreach (QGraphicsItem *item, foundItems)
    {
        emit signalCheckItem(item, this->x(), this->y());
    }

    if  (this->x() > 600 ) this->setX(-58);
    if  (this->x() < -58 ) this->setX(600);
}

int PacMan::GetDir()
{
    return dir;
}

void PacMan::SetPacmanSpeed(int newValue)
{
    pacmanSpeed = newValue;
}

int PacMan::GetPacmanSpeed()
{
    return pacmanSpeed;
}
