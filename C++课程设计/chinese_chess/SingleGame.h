#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"
#include <Step.h>
#include <QPushButton>
class SingleGame : public Board
{
    Q_OBJECT
public:
    int _selectedid;

    QPushButton b3;
    Step _step1;
    explicit SingleGame(QWidget *parent = 0);
    bool judgesame(int i,int killed);
    void mouseReleaseEvent(QMouseEvent* ev);
    Step* getBestMove();
    void saveStep(int moveid ,int row,int col,int killed,QVector<Step*>& steps);
    void getAllPossibleMove(QVector<Step*>& steps);
    int score();
    void fakeMove(Step* step);
    void unfakeMove(Step* step);
     int getStone(int row,int col);
     int getMinScore(int level,int Maxcur);
     int getMaxScore(int level,int Mincur);
public slots:
     void computerMove();
signals:
};
#endif // SINGLEGAME_H
