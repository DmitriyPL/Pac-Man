#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <iostream>
#include <fstream>

#include <pconsts.h>
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

    void LoadMap();

    void FillMapPoint();

    void SetWallRepel(int newValue);

signals:

    void signalGameOver();

private slots:
    void slotCheckItem(QGraphicsItem *itemy, double x, double y);

    void on_pushButton_StartGame_clicked();

    void slotGameOver();

private:
    Ui::GameField *ui;

    QGraphicsScene *scene;

    PacMan         *pacman;
    Points         *point;
    Wall           *wallSegment;

    QList<QGraphicsItem * > points;
    QList<QGraphicsItem * > wallSegments;

    QTimer *timer;

    double count;

    int wallRepel;
    int gameState;

};
#endif // GAMEFIELD_H
