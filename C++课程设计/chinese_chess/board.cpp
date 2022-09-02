#include "Board.h"
#include <QPainter>
#include <QMouseEvent>
#include<bits/stdc++.h>
#include <QPushButton>
#include <QMessageBox>
Board::Board(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("中国象棋");
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background,QColor(218,165,32));
    this->setPalette(palette);
    _return.setText("返回");
    _return.move(400,200);
    _return.setParent(this);
    for(int i=0;i<32;i++)
    {
        s[i].init(i);//棋子初始化
    }
    _selectedid=-1;
    _turn=true;
    b2.setParent(this);
    b2.move(400,300);
    b2.setText("黑方悔棋");
    b1.setParent(this);
    b1.move(400,100);
    b1.setText("红方悔棋");
    b1.setStyleSheet("background-color:rgb(205,133,63)");
    b2.setStyleSheet("background-color:rgb(205,133,63)");
    _return.setStyleSheet("background-color:rgb(205,133,63)");
    connect(&b1,&QPushButton::clicked,
            [=]()
    {
        if(_turn==true)
            return;
        _turn=true;
        s[_step._moveid]._row=_step._rowFrom;
        s[_step._moveid]._col=_step._colFrom;
        if(_step._killid!=-1)
            s[_step._killid]._dead=false;
        update();
    });
    connect(&b2,&QPushButton::clicked,
            [=]()
    {
        if(_turn==false)
            return;
        _turn=false;
        s[_step._moveid]._row=_step._rowFrom;
        s[_step._moveid]._col=_step._colFrom;
        if(_step._killid!=-1)
            s[_step._killid]._dead=false;
        update();
    });
    connect(&_return,&QPushButton::clicked,
            [=]()
    {
        _this->show();
        delete this;
    });
}
void drawbiao(QPainter& painter,int i,int j)
{
    painter.drawLine(QPoint(i-3,j-10),QPoint(i-3,j-3));
    painter.drawLine(QPoint(i-10,j-3),QPoint(i-3,j-3));
    painter.drawLine(QPoint(i+3,j-10),QPoint(i+3,j-3));
    painter.drawLine(QPoint(i+3,j-3),QPoint(i+10,j-3));
    painter.drawLine(QPoint(i+3,j+3),QPoint(i+3,j+10));
    painter.drawLine(QPoint(i+3,j+3),QPoint(i+10,j+3));
    painter.drawLine(QPoint(i-10,j+3),QPoint(i-3,j+3));
    painter.drawLine(QPoint(i-3,j+3),QPoint(i-3,j+10));
}

void Board::paintEvent(QPaintEvent *)//绘制棋盘、棋子
{
    QPainter painter(this);
    int d=40;
    _r=d/2;
    for(int i=1;i<=10;i++)//横线
    {
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }
    painter.setFont(QFont("楷体",20,30));
    painter.drawText(QPoint(d,d*6-7), "   楚河     汉界   ");

    painter.drawLine(QPoint(9*d-3,4*d-10),QPoint(9*d-3,4*d-3));
    painter.drawLine(QPoint(9*d-10,4*d-3),QPoint(9*d-3,4*d-3));
    painter.drawLine(QPoint(9*d-10,4*d+3),QPoint(9*d-3,4*d+3));
    painter.drawLine(QPoint(9*d-3,4*d+3),QPoint(9*d-3,4*d+10));

    painter.drawLine(QPoint(d+3,4*d-10),QPoint(d+3,4*d-3));
    painter.drawLine(QPoint(d+3,4*d-3),QPoint(d+10,4*d-3));
    painter.drawLine(QPoint(d+3,4*d+3),QPoint(d+3,4*d+10));
    painter.drawLine(QPoint(d+3,4*d+3),QPoint(d+10,4*d+3));

    painter.drawLine(QPoint(9*d-3,7*d-10),QPoint(9*d-3,7*d-3));
    painter.drawLine(QPoint(9*d-10,7*d-3),QPoint(9*d-3,7*d-3));
    painter.drawLine(QPoint(9*d-10,7*d+3),QPoint(9*d-3,7*d+3));
    painter.drawLine(QPoint(9*d-3,7*d+3),QPoint(9*d-3,7*d+10));

    painter.drawLine(QPoint(d+3,7*d-10),QPoint(d+3,7*d-3));
    painter.drawLine(QPoint(d+3,7*d-3),QPoint(d+10,7*d-3));
    painter.drawLine(QPoint(d+3,7*d+3),QPoint(d+3,7*d+10));
    painter.drawLine(QPoint(d+3,7*d+3),QPoint(d+10,7*d+3));

    drawbiao(painter,2*d,3*d);
    drawbiao(painter,8*d,3*d);
    drawbiao(painter,2*d,8*d);
    drawbiao(painter,8*d,8*d);
    drawbiao(painter,3*d,4*d);
    drawbiao(painter,5*d,4*d);
    drawbiao(painter,7*d,4*d);
    drawbiao(painter,3*d,7*d);
    drawbiao(painter,5*d,7*d);
    drawbiao(painter,7*d,7*d);


    for(int i=1;i<=9;i++)//竖线
    {
        if(i==1||i==9)
        painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else
        {
        painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
        painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }
    painter.drawLine(QPoint(4*d,1*d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,1*d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    for(int i=0;i<32;i++) //画棋子
    {
        drawStone(painter,i);
    }
}

QPoint Board::center(int row, int col) //获取棋盘行列对应坐标
{
    QPoint ret;
    ret.rx()=(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;
}

QPoint Board::center(int id)//获取棋子的中心坐标
{
    return center(s[id]._row,s[id]._col);
}

void Board::drawStone(QPainter& painter,int id)//画棋子
{
    if(s[id]._dead)//棋子被吃则直接返回
        return;

    QPoint c= center(id);
    QRect rect=QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    if(id==_selectedid)
    painter.setBrush(QBrush(QColor(Qt::gray)));
    else
    painter.setBrush(QBrush(QColor(205,133,63)));

    painter.setPen(Qt::black);
    painter.drawEllipse(center(id),_r,_r);
    if(s[id]._color==1)
        painter.setPen(Qt::red);
    painter.setFont(QFont("楷体",_r,700));
    painter.drawText(rect,s[id].getText(),QTextOption(Qt::AlignCenter));
}

bool Board::getRowCol(QPoint pt, int &row, int &col)//每个点定义一个鼠标获取区间
{
    for(row=0;row<=9;row++)
    {
        for(col=0;col<=8;col++)
        {
            QPoint c=center(row,col);
            int x=c.x()-pt.x();
            int y=c.y()-pt.y();
            int len=x*x+y*y;
            if(len<_r*_r)
                return true;
        }
    }
    return false;
}

int Board::getStoneid(int row, int col)
{
    for(int i=0;i<32;i++)
    {
        if(s[i]._row==row&&s[i]._col==col&&s[i]._dead==false)
            return s[i]._id;
    }
    return -1;
}

int Board::getStoneCountAtLine(int row1, int col1, int row2, int col2)//判断选中的两点是否在同一行或同一列，且获取一行或一列上的棋子数
{
    int ret=0;
    if(row1!=row2&&col1!=col2)
        return -1;
    if(row1==row2&&col1==col2)
        return -1;
    if(row1 == row2)//同一行
    {
        int min=col1<col2?col1:col2;
        int max=col1<col2?col2:col1;
        for(int col=min+1;col<max;col++)
        {
            if(getStoneid(row1,col)!=-1)
                ret++;
        }
    }
    else//同一列
    {
        int min=row1<row2?row1:row2;
        int max=row1<row2?row2:row1;
        for(int row=min+1;row<max;row++)
        {
            if(getStoneid(row,col1)!=-1)
                ret++;
        }
    }
    return ret;
}

bool Board::CanMoveChe(int moveid,int row,int col,int killid)
{
    int row1=s[moveid]._row;
    int col1=s[moveid]._col;
    int ret=getStoneCountAtLine(row1,col1,row,col);
    if(ret==0) //如果选中的是一横行或一竖行且路径上没有棋子则可以走
        return true;
    else
        return false;
}
bool Board::CanMoveJiang(int moveid,int row,int col,int killid)
{
    if(killid!=-1&&s[killid].type==Stone::JIANG)//两将之间无棋子可以飞将
        return CanMoveChe(moveid,row,col,killid);
    if(col<3||col>5)
        return false;
    if(s[moveid]._color==1)
    {
        if(row>2)
            return false;
    }
    else
    {
        if(row<7)
            return false;
    }
    int dr=s[moveid]._row-row;
    int dc=s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d==1||d==10)
        return true;
    else
        return false;
}
bool Board::CanMovePao(int moveid,int row,int col,int killid)
{
    int row1=s[moveid]._row;
    int col1=s[moveid]._col;
    int ret=getStoneCountAtLine(row,col,row1,col1);
    if(killid==-1)
    {
        if(ret!=0) return false;
    }
    else
    {
        if(ret!=1) return false;
    }
    return true;
}
bool Board::CanMoveShi(int moveid,int row,int col,int killid)
{
    if(col<3||col>5)
        return false;
    if(s[moveid]._color==1)
    {
        if(row>2)
            return false;
    }
    else
    {
        if(row<7)
            return false;
    }
    int dr=s[moveid]._row-row;
    int dc=s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d==11)
        return true;
    else
        return false;
}
bool Board::CanMoveXiang(int moveid,int row,int col,int killid)
{
    int row1=s[moveid]._row;
    int col1=s[moveid]._col;
    int r=10*abs(row1-row)+abs(col1-col);
    if(r!=22) return false;
    if(getStoneid((row1+row)/2,(col+col1)/2)!=-1)
    {
        return false;//蹩相腿
    }
    if(s[moveid]._color==1)
    {
        if(row>4) return false;
    }
    else
    {
        if(row<5) return false;
    }
    return true;
}
bool Board::CanMoveMa(int moveid,int row,int col,int killid)
{
    int row1=s[moveid]._row;
    int col1=s[moveid]._col;
    int r=10*abs(row1-row)+abs(col1-col);
    if(r!=12&&r!=21)
        return false;
    if(r==12)
    {
        if(getStoneid(row1,(col+col1)/2)!=-1)//蹩马腿
            return false;
    }
    else
    {
        if(getStoneid((row+row1)/2,col1)!=-1)//蹩马腿
            return false;
    }
    return true;
}
bool Board::CanMoveBing(int moveid, int row, int col, int killid)
{
    int row1=s[moveid]._row;
    int col1=s[moveid]._col;
     int d=abs(row-row1)*10+abs(col-col1);
     if(d!=1&&d!=10) return false;
     if(s[moveid]._color==1&&row1>row)
         return false;
     if(s[moveid]._color!=1&&row1<row)
         return false;
     if(s[moveid]._color==1&&row<5&&d==1)
     {
         return false;
     }
     if(s[moveid]._color!=1&&row>4&&d==1)
     {
         return false;
     }
 return true;
}
bool Board::CanMove(int moveid, int row, int col, int killid)
{
    if(killid!=-1)
    {
        if(s[moveid]._color==s[killid]._color)//两棋子颜色相同不会吃子，且切换选择的棋子
        {
            _selectedid=killid;
            update();
            return false;
        }
    }
    switch(s[moveid].type)
    {
        case Stone::JIANG:
            return CanMoveJiang(moveid,row,col,killid);
            break;
        case Stone::CHE:
            return CanMoveChe(moveid,row,col,killid);
            break;
        case Stone::BING:
             return CanMoveBing(moveid,row,col,killid);
            break;
        case Stone::MA:
            return CanMoveMa(moveid,row,col,killid);
            break;
        case Stone::PAO:
            return CanMovePao(moveid,row,col,killid);
            break;
        case Stone::SHI:
            return CanMoveShi(moveid,row,col,killid);
            break;
        case Stone::XIANG:
            return CanMoveXiang(moveid,row,col,killid);
            break;
    }

    return true;
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt= ev->pos();//获取鼠标选中的点信息
    int row,col;
    bool bret=getRowCol(pt,row,col);
    if(bret==false)//获取不到点信息，点到棋盘外
        return;
    int i;
    int clickedid=-1;//获取每次点击时是否选中棋子,选中棋子则赋值棋子id,若没有选中棋子则为-1
    for(i=0;i<32;i++)
    {
        if(s[i]._row==row&&s[i]._col==col&&s[i]._dead==false)
        {
            break;
        }
    }
    if(i<32)
    {
        clickedid=i;
    }
    if(_selectedid==-1)//还没有选择任何棋子,则选择棋子
    {
        if(clickedid!=-1)
        {
            if(_turn==s[clickedid]._color)
            {
                _selectedid=clickedid;
                update();
            }
        }

    }
    else//已经选择过棋子则移动棋子
    {
        if(CanMove(_selectedid,row,col,clickedid))//判断棋子走动是否合法
        {
            _step._colFrom=s[_selectedid]._col;
            _step._rowFrom=s[_selectedid]._row;
            _step._colTo=col;
            _step._rowTo=row;
            _step._killid=clickedid;
            _step._moveid=_selectedid;
            s[_selectedid]._row=row;
            s[_selectedid]._col=col;
            if(clickedid!=-1)//当前选中棋子移动到位置有棋子，则吃棋
                s[clickedid]._dead=true;
            if(s[clickedid]._dead==true&&s[clickedid].type==Stone::JIANG)
            {
                _selectedid=-1;//刷新获取棋子信息
                _turn=!_turn;
                update();
                if(_turn==1)
                {
                    QMessageBox::about(this,"提示","黑方获胜!");
                }
                else
                {
                    QMessageBox::about(this,"提示","红方获胜!");
                }
                _this->show();
                delete this;

            }
            _selectedid=-1;//刷新获取棋子信息
            _turn=!_turn;
            update();
        }
    }
}
void Board::GetParent(QWidget *a)
{
    _this=a;
}
