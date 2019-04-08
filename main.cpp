#include "gamefield.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameField w;
    w.show();

    return a.exec();
}
