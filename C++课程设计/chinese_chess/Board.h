#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include "stone.h"
#include <QPainter>
#include <Step.h>
#include <QPushButton>
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    Stone s[32]; //定义三十二个棋子

    int _r;//棋子半径
    int _selectedid;//选中棋子id,若为-1则没有选中任何棋子
    bool _turn;//判断哪方走棋，1红方走棋，0黑方走棋
    Step _step;
    QWidget *_this;
    QPushButton b1,b2,_return;
    QPoint center(int row,int col);//获取棋盘行列对应坐标
    QPoint center(int id);//获取某一棋子的中心坐标
    bool getRowCol (QPoint pt,int &row,int &col);
    void drawStone(QPainter &painter,int id);//绘画棋子
    int getStoneid(int row,int col);//获取某一棋子的id
    int  getStoneCountAtLine(int row1, int col1, int row2, int col2);//判断选中的两点是否在同一行或同一列，且获取一行或一列上的棋子数
    bool CanMove(int moveid,int row,int col,int killid);//棋子移动合法性判断
    bool CanMoveJiang(int moveid,int row,int col,int killid);//将移动合法性判断
    bool CanMovePao(int moveid,int row,int col,int killid);//炮移动合法性判断
    bool CanMoveBing(int moveid,int row,int col,int killid);//兵移动合法性判断
    bool CanMoveShi(int moveid,int row,int col,int killid);//士移动合法性判断
    bool CanMoveXiang(int moveid,int row,int col,int killid);//象移动合法性判断
    bool CanMoveChe(int moveid,int row,int col,int killid);//车移动合法性判断
    bool CanMoveMa(int moveid,int row,int col,int killid);//马移动合法性判断
    void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent*);
    void GetParent(QWidget *a);
signals:

public slots:
};

#endif // BOARD_H
