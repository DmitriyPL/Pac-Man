#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->resize(900, 900);
    this->setFixedSize(900, 900);

    count = 0;

    scene  = new QGraphicsScene();
    pacman = new PacMan();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setBackgroundBrush(Qt::black);

    LoadMap(R"(D:\Qt\GameDev\Pac-Man\map1.txt)");
    FillMapPoint();


    scene->addItem(pacman);
    pacman->setPos(-16,-36);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, pacman, &PacMan::slotGameTimer);
    timer->start(1000/80);

//    timerCreatePoints = new QTimer();
//    connect(timerCreatePoints, &QTimer::timeout, this, &GameField::slotCreatePoint);
//    timerCreatePoints->start(1000);

    connect(pacman, &PacMan::signalCheckItem, this, &GameField::slotCheckItem);
}

GameField::~GameField()
{
    delete ui;
}

void GameField::LoadMap(const QString &path)
{
    std::ifstream fileMap;
    fileMap.open(path.toStdString(), std::ios_base::out);

    if ( !fileMap.is_open() ) qDebug() << " Map doesn't loaded! ";

    char symbol;

    for (int i = 1; i <= 21; i++)
    {
        for (int j = 1; j <= 38; j++)
        {
            fileMap.get(symbol);

            if (symbol == '*' )
            {
                wallSegment = new Wall();
                scene->addItem(wallSegment);
                wallSegment->setPos(-72 + j*18, -108 + i*36 );
                wallSegments.append(wallSegment);
            }

            if (symbol == '-' )
            {
                wallSegment = new Wall();
                wallSegment->SetWallColor(1);
                scene->addItem(wallSegment);
                wallSegment->setPos(-72 + j*18, -108 + i*36 );
                wallSegments.append(wallSegment);
            }
        }
    }
}

void GameField::FillMapPoint()
{
    for (int i = 1; i <= 37; i++)
    {
        for (int j = 1; j <= 37; j++)
        {
            point = new Points();
            scene->addItem(point);
            point->setPos(-70 + j*18, -52 + i*18 );

            if(!scene->collidingItems(point).isEmpty())
                delete point;
            else
            {
                point->setZValue(-1);
                points.append(point);
            }
        }
    }
}

void GameField::slotCheckItem(QGraphicsItem *item)
{
    foreach (QGraphicsItem *point, points)
    {
        if (point == item)
        {
            scene->removeItem(point);
            points.removeOne(item);
            delete point;
            ui->lcdNumber->display(count++);
        }
    }

    foreach (QGraphicsItem *segment, wallSegments)
    {
        if (segment == item)
        {
            if (pacman->GetDir() == right)
                pacman->setX( pacman->x() - 2 );

            if (pacman->GetDir() == left)
                pacman->setX( pacman->x() + 2 );

            if (pacman->GetDir() == up)
                pacman->setY( pacman->y() + 2  );

            if (pacman->GetDir() == down)
                pacman->setY( pacman->y() - 2  );

        }
    }


}

void GameField::slotCreatePoint()
{
    Points *point = new Points();

    scene->addItem(point);

    point->setPos( ( qrand() % (251) ) * ( (qrand() % 2 == 1 ) ? 1 : -1 ),
                   ( qrand() % (251) ) * ( (qrand() % 2 == 1 ) ? 1 : -1 ) );

    point->setZValue(-1);

    points.append(point);
}
