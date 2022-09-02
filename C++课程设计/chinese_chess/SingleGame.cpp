#include<QMessageBox>
#include <Step.h>
#include <QPoint>
#include <QMouseEvent>
#include <Board.h>
#include <stone.h>
#include <vector>
#include "SingleGame.h"
#include <QTimer>
int _level=3;
SingleGame::SingleGame(QWidget *parent) : Board(parent)
{
  b1.hide();b2.hide();
  b3.setText("悔棋");
  b3.move(400,100);
  b3.setParent(this);
  b3.setStyleSheet("background-color:rgb(205,133,63)");
  connect(&b3,&QPushButton::clicked,
          [=]()
  {
      if(_turn=false)
          return;
      s[_step._moveid]._row=_step._rowFrom;
      s[_step._moveid]._col=_step._colFrom;
      if(_step._killid!=-1)
          s[_step._killid]._dead=false;
      s[_step1._moveid]._row=_step1._rowFrom;
      s[_step1._moveid]._col=_step1._colFrom;
      if(_step1._killid!=-1)
          s[_step1._killid]._dead=false;
      update();
  });
}
void SingleGame::computerMove()
{
    Step *step=getBestMove();
    _step1._colFrom=step->_colFrom;
    _step1._colTo=step->_colTo;
    _step1._rowFrom=step->_rowFrom;
    _step1._rowTo=step->_rowTo;
    _step1._moveid=step->_moveid;
    _step1._killid=step->_killid;
    s[step->_moveid]._row=step->_rowTo;
    s[step->_moveid]._col=step->_colTo;
    if(step->_killid!=-1)
    s[step->_killid]._dead=true;
    Board::_selectedid=-1;
    if(s[step->_killid]._dead==true&&s[step->_killid].type==Stone::JIANG)//
        {
            update();
            QMessageBox::about(this,"提示","黑方获胜!");
            _this->show();
            delete this;
        }
    _turn=true;
    update();
}
 void SingleGame::mouseReleaseEvent(QMouseEvent* ev)
{
     if(_turn=1)
     {
     Board::mouseReleaseEvent(ev);
     if(_turn==true)
         return;
     }
     if(_turn==false)
     {
         QTimer::singleShot(100,this,SLOT(computerMove()));
         return;
     }
 }
Step* SingleGame::getBestMove()
{
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    Step *step;
    Step *ret=NULL;
    int s,max;
    max=-1000000;
    while(steps.count())
    {
        step=steps.back();
        steps.removeLast();
        fakeMove(step);
        s=getMinScore(_level-1,max);
        unfakeMove(step);
        if(s>=max)
        {
          max=s;
          ret=step;
        }
    }
    return ret;

}
void SingleGame::saveStep(int moveid, int row, int col, int killed,QVector<Step*>& steps)
{
    Step *step=new Step;
    step->_rowFrom=s[moveid]._row;
    step->_colFrom=s[moveid]._col;
    step->_rowTo=row;
    step->_colTo=col;
    step->_killid=killed;
    step->_moveid=moveid;
    steps.append(step);
}
void SingleGame::fakeMove(Step *step)
{
    if(step->_killid!=-1)
        s[step->_killid]._dead=true;
    s[step->_moveid]._row=step->_rowTo;
    s[step->_moveid]._col=step->_colTo;
}
void SingleGame::unfakeMove(Step *step)
{
    s[step->_moveid]._row=step->_rowFrom;
    s[step->_moveid]._col=step->_colFrom;
    if(step->_killid!=-1)
        s[step->_killid]._dead=false;
}
int SingleGame::score()
{
    //JIANG,CHE,PAO,MA,BING,SHI,XIANG
    static int t[]={1000000,3000,1000,500,100,300,100};
    int i,sumblack,sumred;
    for(i=16,sumblack=0;i<32;i++)
    {
        if(s[i]._dead==true)
            continue;
        sumblack+=t[s[i].type];
    }
    for(i=0,sumred=0;i<16;i++)
    {
        if(s[i]._dead==true)
            continue;
        sumred+=t[s[i].type];
    }
    return sumblack-sumred;
}
int SingleGame::getMinScore(int level,int Maxcur)
{
    if(level==0) return score();
    QVector<Step*> steps;
    Step *step;
    _turn=1;
    getAllPossibleMove(steps);
    _turn=0;
    int min=10000,s;
        while(steps.count())
        {
            step=steps.back();
            steps.removeLast();
            fakeMove(step);
            s=getMaxScore(level-1,min);
            unfakeMove(step);
            if(s<Maxcur)
            {
                while(steps.count()) {
                    step=steps.back();
                    steps.removeLast();
                    delete step;
                }
                return s;
            }
            if(s<min)
            {
              min=s;
            }
        }
         return min;
}
int SingleGame::getMaxScore(int level,int Mincur)
{
    if(level==0) return score();
    QVector<Step*> steps;
    Step *step;
    _turn=0;
    getAllPossibleMove(steps);
    _turn=1;
    int max=-10000,s;
        while(steps.count())
        {
            step=steps.back();
            steps.removeLast();
            fakeMove(step);
            s=getMinScore(level-1,max);
            unfakeMove(step);
            if(s>Mincur)
            {
                while(steps.count()) {
                    step=steps.back();
                    steps.removeLast();
                    delete step;
                }
                return s;
            }
            if(s>max)
            {
              max=s;
            }
        }
         return max;
}
bool SingleGame::judgesame(int i, int killed)
{
    if(killed==-1) return false;
    if(s[killed].type==s[i].type) return true;
    return false;
}
void SingleGame::getAllPossibleMove(QVector<Step*>& steps)
{
    int  killed;
    int max,min;
    if(_turn==1)
    {
        max=16;min=0;
    }
    else
    {
        max=32;min=16;
    }
    for(int i=min;i<max;i++)
    {
        if(s[i]._dead==true)
            continue;
        for(int row=0;row<=9;row++)
        {
            for(int col=0;col<=8;col++)
            {
                killed=getStoneid(row,col);
                if(judgesame(i,killed))
                continue;
                if(CanMove(i,row,col,killed))
                 saveStep(i,row,col,killed,steps);
            }
        }
    }
}
