#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    this->resize(900, 900);
    this->setFixedSize(900, 900);


    scene  = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setBackgroundBrush(Qt::black);

    timer = new QTimer();

    gameState = GAME_STOPED;

}

GameField::~GameField()
{
    delete ui;
}

void GameField::LoadMap()
{
    QFile fileMap(":/sources/map1.txt");

    if ( !fileMap.open(QFile::ReadOnly | QFile::Text) )
        qDebug() << " Map doesn't loaded! ";

    char symbol;

    QTextStream readStream(&fileMap);

    for (int i = 1; i <= 21; i++)
    {
        for (int j = 1; j <= 38; j++)
        {
            readStream >> symbol;

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

void GameField::SetWallRepel(int newValue)
{
    wallRepel = newValue;
}

void GameField::slotCheckItem(QGraphicsItem *item, double x, double y)
{
    foreach (QGraphicsItem *point, points)
    {
        if (point == item)
        {
            scene->removeItem(point);
            points.removeOne(item);
            delete point;
            ui->lcdNumber->display(count++);

            QMediaPlayer   *m_player   = new QMediaPlayer(this);
            QMediaPlaylist *m_playlist = new QMediaPlaylist(m_player);

            m_player->setPlaylist(m_playlist);
            m_playlist->addMedia(QUrl("qrc:/sources/pacman_eatfruit.wav"));
            m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            m_player->play();
        }

        if (points.empty())
        {
            QMediaPlayer   *m_player   = new QMediaPlayer(this);
            QMediaPlaylist *m_playlist = new QMediaPlaylist(m_player);

            m_player->setPlaylist(m_playlist);
            m_playlist->addMedia(QUrl("qrc:/sources/pacman_intermission.wav"));
            m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            m_player->play();

            emit signalGameOver();
        }
    }

    foreach (QGraphicsItem *segment, wallSegments)
    {
        if (segment == item)
        {
            if (pacman->GetDir() == pconsts::direction::RIGHT){

                pacman->setX( pacman->x() - pacman->GetPacmanSpeed() + wallRepel );
                if (!pacman->collidingItems().isEmpty()) pacman->setX(x);
            }

            if (pacman->GetDir() == pconsts::direction::LEFT){

                pacman->setX( pacman->x() + pacman->GetPacmanSpeed() + wallRepel );
                if (!pacman->collidingItems().isEmpty()) pacman->setX(x);
            }

            if (pacman->GetDir() == pconsts::direction::UP){
                pacman->setY( pacman->y() + pacman->GetPacmanSpeed() + wallRepel  );
                if (!pacman->collidingItems().isEmpty()) pacman->setY(y);
            }

            if (pacman->GetDir() == pconsts::direction::DOWN){
                pacman->setY( pacman->y() - pacman->GetPacmanSpeed() + wallRepel  );
                if (!pacman->collidingItems().isEmpty()) pacman->setY(y);
            }
        }
    }

}

void GameField::on_pushButton_StartGame_clicked()
{
    QMediaPlayer   *m_player   = new QMediaPlayer(this);
    QMediaPlaylist *m_playlist = new QMediaPlaylist(m_player);

    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sources/pacman_beginning.wav"));
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    m_player->play();

    //LoadMap( R"(D:\Qt\GameDev\Pac-Man\map1.txt)" );
    LoadMap();

    FillMapPoint();
    wallRepel = 0;

    count = 0;
    ui->lcdNumber->display(count);

    pacman = new PacMan();
    this->installEventFilter(pacman);

    scene->addItem(pacman);
    pacman->setPos(-16,-36);

    connect(timer, &QTimer::timeout, pacman, &PacMan::slotGameTimer);
    timer->start(2);

    connect(pacman, &PacMan   ::signalCheckItem, this, &GameField::slotCheckItem);
    connect(this  , &GameField::signalGameOver , this, &GameField::slotGameOver);

    ui->pushButton_StartGame->setEnabled(false);

    gameState = GAME_STARTED;
}

void GameField::slotGameOver()
{
    timer->stop();

    QMessageBox::information(this, "Game Over", "My respect =)");

    disconnect(pacman, &PacMan   ::signalCheckItem, this, &GameField::slotCheckItem);
    disconnect(this  , &GameField::signalGameOver , this, &GameField::slotGameOver);

    pacman->deleteLater();

    foreach(QGraphicsItem *point, points)
    {
        scene->removeItem(point);
        points.removeOne(point);
        delete point;
    }

    ui->pushButton_StartGame->setEnabled(true);

    gameState = GAME_STOPED;

}
