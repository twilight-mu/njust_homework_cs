#include "zhujiemian.h"
#include "ui_widget.h"
#include "board.h"
#include <QMessageBox>
#include <QPainter>
#include <SingleGame.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("中国象棋");
    setWindowIcon(QIcon("://image/download.jpg"));
    QFont font ("Microsoft YaHei",30,75);
    ui->biaoti->setFont(font);
    this->setMaximumHeight(500);
    this->setMaximumWidth(500);
    this->setFixedSize(this->width(),this->height());
    ui->shuangren->setStyleSheet("background-color:rgb(205,133,63)");
    ui->danren->setStyleSheet("background-color:rgb(205,133,63)");
    ui->tuichu->setStyleSheet("background-color:rgb(205,133,63)");
    connect(ui->shuangren,&QPushButton::clicked,
            [=]()
    {
       if(h==NULL)
        delete h;
       h=new Board;
       h->GetParent(this);
       h->setWindowIcon(QIcon("://image/download.jpg"));
       h->setMaximumHeight(450);
       h->setMaximumWidth(500);
       h->setFixedSize(500,450);
       h->show();
       this->hide();
    }
            );
    connect(ui->danren,&QPushButton::clicked,
            [=]()
    {
       if(h==NULL)
        delete h;
       h=new SingleGame;
       h->GetParent(this);
       h->setWindowIcon(QIcon("://image/download.jpg"));
       h->setMaximumHeight(450);
       h->setMaximumWidth(500);
       h->setFixedSize(500,450);
       h->show();
       this->hide();
    }
            );
    connect(ui->tuichu,&QPushButton::clicked,
            [=]()
    {
        int ret=QMessageBox::question(this,"退出游戏","确定要退出游戏吗?",QMessageBox::Yes|QMessageBox::No);
        switch (ret)
        {
        case QMessageBox::Yes:
            this->close();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
    }
            );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);
    p.drawPixmap(rect(),QPixmap("://image/timg.jpg"));
    p.end();
}
