#include "parser.h"
#include "ui_parser.h"
#include "widget.h"
#include <QFile>
#include <QFileDialog>
#include <QTime>
#include <QDesktopServices>


Parser::Parser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Parser)
{
    ui->setupUi(this);
    setWindowTitle("语法分析器");
    this->setFixedSize(this->width(),this->height());
    connect(ui->fanhui,&QPushButton::clicked,this,&Parser::Sendslot2);
    connect(ui->wenfa,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
        ui->jieguo->setText("");
        ui->jieguo->append("开始读入文法！\n");
        if(filename.isEmpty()==false)
        {
            QFile file(filename);
            bool isOK =file.open(QIODevice::ReadOnly);
            if(isOK==true)
            {
                QByteArray array;
                array=file.readAll();
                QString temp=array;
                QFile filesave("C:/Users/Twilight/Desktop/keshe2/LexerParser/driver/phaser_grammar.txt");
                filesave.open(QIODevice::WriteOnly);
                filesave.write(temp.toUtf8());
                filesave.close();
            }
            file.close();
            ui->jieguo->append("文法读入完成！");
        }

    }
            );

    connect(ui->token,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
        ui->jieguo->setText("");
        ui->jieguo->append("开始读入token!\n");
        if(filename.isEmpty()==false)
        {
            QFile file(filename);
            bool isOK =file.open(QIODevice::ReadOnly);
            if(isOK==true)
            {
                QByteArray array;
                array=file.readAll();
                QString temp=array;
                QFile filesave("C:/Users/Twilight/Desktop/keshe2/LexerParser/driver/lexer_out.txt");
                filesave.open(QIODevice::WriteOnly);
                filesave.write(temp.toUtf8());
                filesave.close();
            }
            file.close();
            ui->jieguo->append("token读入完成！");
        }
    }
            );

    connect(ui->duru,&QPushButton::clicked,
            [=]()
    {
            QFile file1("C:/Users/Twilight/Desktop/keshe2/LexerParser/driver/action_goto.txt");
            bool isOK1 =file1.open(QIODevice::ReadOnly);
            if(isOK1==true)
            {
            QByteArray array1;
            array1=file1.readAll();
            QString temp1=array1;
            ui->agtable->setText(temp1.toUtf8());
            }
            file1.close();

            QFile file2("C:/Users/Twilight/Desktop/keshe2/LexerParser/driver/project_set.txt");
            bool isOK2 =file2.open(QIODevice::ReadOnly);
            if(isOK2==true)
            {
            QByteArray array2;
            array2=file2.readAll();
            QString temp2=array2;
            ui->pstable->setText(temp2.toUtf8());
            }
            file2.close();

            QFile file3("C:/Users/Twilight/Desktop/keshe2/LexerParser/driver/phaser_out.txt");
            bool isOK3 =file3.open(QIODevice::ReadOnly);
            if(isOK3==true)
            {
            QByteArray array3;
            array3=file3.readAll();
            QString temp3=array3;
            ui->jieguo->setText(temp3.toUtf8());
            }
            file3.close();
    }
            );

    connect(ui->driver,&QPushButton::clicked,
            [=]()
    {
        QString path="C:/Users/Twilight/Desktop/keshe2/LexerParser/driver";
        QDesktopServices::openUrl(path);
    }
            );

    connect(ui->agsave,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
        if(filename.isEmpty()==false)
        {
            QFile file;
            file.setFileName(filename);
            bool isOK =file.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString temp=ui->agtable->toPlainText();
                file.write(temp.toUtf8());
            }
            file.close();
        }
    }
            );

    connect(ui->pssave,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
        if(filename.isEmpty()==false)
        {
            QFile file;
            file.setFileName(filename);
            bool isOK =file.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString temp=ui->pstable->toPlainText();
                file.write(temp.toUtf8());
            }
            file.close();
        }
    }
            );

    connect(ui->jieguosave,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
        if(filename.isEmpty()==false)
        {
            QFile file;
            file.setFileName(filename);
            bool isOK =file.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString temp=ui->jieguo->toPlainText();
                file.write(temp.toUtf8());
            }
            file.close();
        }
    }
            );

}

Parser::~Parser()
{
    delete ui;
}

void Parser::Sendslot2()
{
    emit Mysignal2();
}
