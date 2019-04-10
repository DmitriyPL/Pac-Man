#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <iostream>
#include <fstream>

#include <pacman.h>
#include <points.h>
#include <wall.h>

#define GAME_STOPED  0
#define GAME_STARTED 1

namespace Ui {
class GameField;
}

class GameField : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

    void LoadMap(const QString &path);
    void FillMapPoint();

    void SetWallRepel(int newValue);

signals:

    void signalGameOver();

private slots:
    void slotCheckItem(QGraphicsItem *item);

    void on_pushButton_StartGame_clicked();

    void slotGameOver();
//    void slotPause();

private:
    Ui::GameField *ui;

    QGraphicsScene *scene;
    PacMan         *pacman;
    Points         *point;
    Wall           *wallSegment;

    QList<QGraphicsItem * > points;
    QList<QGraphicsItem * > wallSegments;

//    QShortcut *pauseKey;

    enum direction { left = 1, right, up, down };

    QTimer *timer;

    double count;

    int wallRepel;
    int gameState;

//    QMediaPlayer   *m_player;
    //    QMediaPlaylist *m_playlist;
};
#endif // GAMEFIELD_H
