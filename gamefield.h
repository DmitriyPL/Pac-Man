#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QDebug>
#include <QTimer>

#include <iostream>
#include <fstream>

#include <pacman.h>
#include <points.h>
#include <wall.h>

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

private slots:
    void slotCheckItem(QGraphicsItem *item);
    void slotCreatePoint();

private:
    Ui::GameField *ui;

    QGraphicsScene *scene;
    PacMan         *pacman;
    Points         *point;
    Wall           *wallSegment;

    QList<QGraphicsItem * > points;
    QList<QGraphicsItem * > wallSegments;

    enum direction { left = 1, right, up, down };

    QTimer *timer;
    QTimer *timerCreatePoints;

    double count;
};

#endif // GAMEFIELD_H
