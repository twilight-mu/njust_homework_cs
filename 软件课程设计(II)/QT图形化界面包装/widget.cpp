#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFont ft;
    ft.setPointSize(20);
    ui->biaoti->setFont(ft);
    setWindowTitle("软件课程设计(II)");
    this->setFixedSize(this->width(),this->height());

    connect(ui->Lexer,&QPushButton::clicked,
            [=]()
    {
        w1.show();
        this->hide();
    }
            );

    connect(&w1,&Lexer::Mysignal1,this,&Widget::backmain1);

    connect(ui->Parser,&QPushButton::clicked,
            [=]()
    {
        w2.show();
        this->hide();
    }
            );

    connect(&w2,&Parser::Mysignal2,this,&Widget::backmain2);

    connect(ui->Analyzer,&QPushButton::clicked,
            [=]()
    {
        w3.show();
        this->hide();
    }
            );

    connect(&w3,&Analyzer::Mysignal3,this,&Widget::backmain3);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::backmain1()
{
    //按钮回到主窗口
    w1.hide();
    this->show();

}

void Widget::backmain2()
{
    //按钮回到主窗口
    w2.hide();
    this->show();
}

void Widget::backmain3()
{
    //按钮回到主窗口
    w3.hide();
    this->show();
}
