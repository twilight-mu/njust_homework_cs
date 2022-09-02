#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "tongji.h"
using namespace std;
#include<bits/stdc++.h>
#define random(a,b) (rand()%(b-a+1))+a
ofstream mycout("out.txt",ios::out);

struct pig
{
    int species; //黑猪为1 小花猪为2 大白花猪为3
    int id; 	//编号
    int styid;  //猪圈编号
    int gday; 	//成长天数(一个月按30天计)
    int infected=0; //被感染为1，没被感染为0
    double weight; //体重
    pig *next;
};
class pigsty
{
    private:
        pig *head=NULL;
        int isblack=0; //猪圈为黑猪圈为1，非黑为0
        int sum=0;      //当前猪圈猪数
        int isinfected=0; //猪圈有感染猪为1, 没有为0
        int infectsum=0;  //当前猪圈被感染的猪数
    public:
        int getspecies(int i);	//获取种类信息
        int getgday(int i);		//获取成长天数信息
        double getweight(int i);//获取重量
        double getprice();		//获取价钱
        void addpig(pig*p);		//加猪，主要用于初始化
        void insert(int i,int j);      //加猪，主要用于购买插入
        void clear();	             //出现感染猪，离开将该猪圈的猪全部清空
        int getsumspecies(int i);	//获取某种猪的数量
        int getsum()
        {
            return sum;
        }
        int getisblack()
        {
            return isblack;
        }
        int getisinfect()
        {
            return isinfected;
        }
        int getinfectsum()
        {
            return infectsum;
        }
        pig* gethead()
        {
            return head;
        }
        void setsum(int i)
        {
            sum=i;
        }
        void sethead(pig *p)
        {
            head=p;
        }
        void setisblack(int i)
        {
            isblack=i;
        }
        void setisinfect(int i)
        {
            isinfected=i;
        }
        void setinfectsum(int i)
        {
            infectsum=i;
        }
        void infectgame()
        {
            if(head==NULL)
            return;
            isinfected=1;
            infectsum++;
            pig *p;
            p=head;
            p->infected=1;
        }
        void addinfect()
        {
           // srand((unsigned)time(0));
            srand(time(0)+rand());
            pig *p;
            p=head;
            while(p)
            {
                if(p->infected!=1)
                {
                    if(random(1,100)<=50)
                    {
                        p->infected=1;
                        infectsum++;
                    }
                }
                p=p->next;
            }
        }
};
pigsty ps[100];
int sumday=0;
int growday=0;
double gold=200000;
int pigsty::getspecies(int i)
{
    pig *p=head;
    for(int k=0;k<i&&p!=NULL;k++)
    {
        p=p->next;
    }
    return p->species;
}
int pigsty::getgday(int i)
{
    pig *p=head;
    for(int k=0;k<i&&p!=NULL;k++)
    {
        p=p->next;
    }
    return p->gday;
}
double pigsty::getweight(int i)
{
    pig *p=head;
    for(int k=0;k<i&&p!=NULL;k++)
    {
        p=p->next;
    }
    return p->weight;
}
double pigsty::getprice()
{
    double sellprice=0;
    if(head==0)
    return 0;
    int day,flag=0;
    pig*p=head,*p1=p;
    while(p)
    {
        day=p->gday;
        if(day>=360||p->weight>75)
        {
            if(sum==1)
            {
                if(p->species==1)
                {
                    sellprice+=30*p->weight;
                }
                if(p->species==2)
                {
                    sellprice+=14*p->weight;
                }
                if(p->species==3)
                {
                    sellprice+=12*p->weight;
                }
                setisblack(0);
                head=NULL;
                delete p;
                sum--;
                break;
            }
            if(p->species==1)
            {
                sellprice+=30*p->weight;
            }
            if(p->species==2)
            {
                sellprice+=14*p->weight;
            }
            if(p->species==3)
            {
                sellprice+=12*p->weight;
            }
            p1->next=p->next;
            delete p;
            p=p1->next;
            sum--;
            continue;
        }
        else if(flag==0)
        {
            flag=1;
            head=p;
        }
        p1=p;
        p=p1->next;
    }
    return sellprice;
}
void pigsty::addpig(pig *p)
{
    sum++;
    p->next=NULL;
    if(head==NULL)
    {
        head=p;
    }
    else
    {
        pig*p1=head;
        while(p1->next)
        {
            p1=p1->next;
        }
    p1->next=p;
    }
}
int pigsty::getsumspecies(int i)
{
    int count=0;
    pig *p=head;
    for(int k=0;k<sum&&p!=NULL;k++)
    {
        if(p->species==i)
        count++;
        p=p->next;
    }
    return count;
}
void pigsty::clear()
{
    if(head==NULL)
    {
        return;
    }
    else
    {
        pig*p=head;
        pig*p1=p;
        sum=0;
        setisblack(0);
        head=NULL;
        while(p)
        {
            p1=p;
            p=p->next;
            delete p1;
        }
        delete p;
    }
}
int getallpig(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsum();
    }
    return count;
}
int getallinfectpig(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getinfectsum();
    }
    return count;
}
int getallpig1(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsumspecies(1);
    }
    return count;
}
int getallpig2(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsumspecies(2);
    }
    return count;
}
int getallpig3(pigsty ps[])
{
    int count=0;
    for(int i=0;i<100;i++)
    {
        count+=ps[i].getsumspecies(3);
    }
    return count;
}
void buypig(pigsty ps[],int i,int j,int k)
{
    int pig1=i;
    int pig2=j;
    int pig3=k;
    mycout<<"购入"<<pig1<<"只黑猪、"<<pig2<<"只小花猪、"<<pig3<<"只大花白猪。"<<endl;
    while(pig1--)
    {
        for(int i=0;i<100;i++)
        {
            if(ps[i].getisblack()==1&&ps[i].getsum()<10)
            {
                ps[i].insert(1,i);
                break;
            }
            if(ps[i].gethead()==NULL)
            {
                ps[i].insert(1,i);
                ps[i].setisblack(1);
                break;
            }
        }
    }

    while(pig2--)
    {
        int ave=getallpig(ps)/100+1;
        for(int i=0;i<100;i++)
        {
            if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
            {
                ps[i].insert(2,i);
                break;
            }
            if(ps[i].gethead()==NULL)
            {
                ps[i].insert(2,i);
                ps[i].setisblack(0);
                break;
            }
        }
    }
    while(pig3--)
    {
        int ave=getallpig(ps)/100+1;
        for(int i=0;i<100;i++)
        {
            if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
            {
                ps[i].insert(3,i);
                break;
            }
            if(ps[i].gethead()==NULL)
            {
                ps[i].insert(3,i);
                ps[i].setisblack(0);
                break;
            }
        }
    }
}
void start(pigsty ps[])//程序开始，猪圈初始化
{
    int count=1000;	//开始先放200只猪
    pig *p;
    srand((unsigned)time(0));
    while(count--)
    {
        p=new pig;
        p->species=random(1,3);
        p->weight=double(random(200,500))/10;
        p->gday=0;
        for(int i=0;i<100;i++)
        {
            if(p->species==1&&(ps[i].getisblack()==1||ps[i].gethead()==NULL)&&ps[i].getsum()<2)
            {
                p->id=ps[i].getsum();
                p->styid=i;
                ps[i].addpig(p);
                ps[i].setisblack(1);
                break;
            }
            if(p->species!=1&&ps[i].getisblack()==0&&ps[i].getsum()<2)
            {
                p->id=ps[i].getsum();
                p->styid=i;
                ps[i].addpig(p);
                break;
            }
        }
    }
}
void pigsty::insert(int i,int j)
{
    srand((unsigned)time(0));
    pig*p=new pig;
    p->species=i;
    p->styid=j;
    p->weight=random(20,30);
    p->gday=0;
    if(head==NULL)
    {
        p->id=0;
        p->next=NULL;
        head=p;
        sum++;
        return;
    }
    if(head->id!=0)
    {
        p->id=0;
        p->next=head;
        head=p;
        sum++;
        return;
    }
    else
    {
    pig*p1=head,*p2=p1;
    int k=0;
    while(p1->id==k&&p1->next)
    {
        k++;
        p2=p1;
        p1=p1->next;
    }
    if(p1->next==NULL)
    {
        p->id=sum;
        p->next=NULL;
        p1->next=p;
    }
    else
    {
        p->id=k;
        p2->next=p;
        p->next=p1;
    }
    sum++;
    }
}
void oneday(pigsty ps[])
{
    srand((unsigned)time(0));
    for(int i=0;i<100;i++)
    {
        pig *p;
        p=ps[i].gethead();
        while(p)
        {
            int w1=random(0,12);
            double w2=double(w1)/10.0;
            p->weight+=w2;
            p->gday++;
            p=p->next;
        }
    }
}
double getsumprice(pigsty ps[])
{
    double sumprice;
    for(int i=0;i<100;i++)
    {
        sumprice+=ps[i].getprice();
    }
    return sumprice;
}
void fend(pigsty ps[])
{
    ofstream myycout("read.txt",ios::out);
    myycout<<getallpig(ps)<<endl;
    myycout<<gold<<endl;
    myycout<<sumday<<endl;
    myycout<<growday<<endl;
    for(int i=0;i<100;i++)
    {
        pig *p=ps[i].gethead();
        while(p)
        {
            myycout<<p->styid<<" "<<p->id<<" "<<p->gday<<" "<<p->species<<" "<<p->weight<<endl;
            p=p->next;
        }
    }
    myycout.close();
}
void fstart(pigsty ps[])
{
    ifstream myycin("read.txt",ios::in);
    int allpig,thissumday,thisgrowday;
    double thisgold;
    myycin>>allpig;
    myycin>>thisgold;
    myycin>>thissumday;
    myycin>>thisgrowday;
    gold=thisgold;
    sumday=thissumday;
    growday=thisgrowday;
    int myid,mygday,mysp,mystyid;
    double myweight;
    pig *p;
    for(int i=0;i<allpig;i++)
    {
        p=new pig;
        myycin>>mystyid>>myid>>mygday>>mysp>>myweight;
        p->species=mysp;
        p->weight=myweight;
        p->styid=mystyid;
        p->id=myid;
        p->gday=mygday;
        ps[mystyid].addpig(p);
        if(mysp==1)
        {
            ps[mystyid].setisblack(1);
        }
        else
        {
            ps[mystyid].setisblack(0);
        }
    }
    myycin.close();
}
void infectday(pigsty ps[])
{
    //srand((unsigned)time(0));
    srand(time(0) + rand()); 
	for(int i=0;i<100;i++)
	{
		if(ps[i].getisinfect()==1&&ps[i].gethead()!=NULL)
		{
			
			if(ps[i+1].getisinfect()!=1&&(i+1)<=99)
			{
				int chance=random(1,100);
				if(chance<=15)
				{
					ps[i+1].infectgame();
				}	
			}
			
		}
	}
	for(int i=99;i>=0;i--)
	{
		if(ps[i].getisinfect()==1&&ps[i].gethead()!=NULL)
		{
			if(ps[i-1].getisinfect()!=1&&(i-1)>=0)
			{	
				int chance=random(1,100);
				if(chance<=15)
				{
					ps[i-1].infectgame();
				}
			}
		}
	}
	for(int i=0;i<100;i++)
        
	{
		if(ps[i].getisinfect()==1&&ps[i].gethead()!=NULL)
		{
		ps[i].addinfect();
		}
	}
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("欢乐猪场");
    setWindowIcon(QIcon("://image/tubiao.jpg"));
    this->setFixedSize(this->width(),this->height());

    //playlist= new QMediaPlaylist;
    //playlist->addMedia(QUrl("qrc:/image/商金玮 - 欢乐斗地主 (Piano Ver_).mp3"));
    //playlist->setCurrentIndex(1);
    //playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    //player = new QMediaPlayer;
    //player->setPlaylist(playlist);
    //player->play();

    QFont font1 ("Microsoft YaHei",40,75);
    font1.setItalic(true);
    ui->biaoti->setFont(font1);
    QFont font2 ("Microsoft YaHei",13,75);
    font2.setItalic(true);
    ui->tushi->setFont(font2);

    ui->kaishi->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->tuichu->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->load->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->store->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->pigsty->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->pigchang->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->pig->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->buypig->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->growday->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->sellpig->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->days->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->species->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->weight->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->bangzhu->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->jixu->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->fanhui->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->mockinfect->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->randominfect->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->back->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");
    ui->tongji->setStyleSheet("background-color:rgb(139,105,20);color:rgb(0,205,0)");


    ui->widget_3->hide();
    ui->widget_4->hide();
    ui->widget_5->hide();
    ui->fanhui->hide();
    ui->bangzhu->hide();
    ui->textout->hide();
    ui->jixu->hide();
    ui->mockinfect->hide();
    ui->randominfect->hide();
    ui->tongji->hide();
    ui->widget_6->hide();
    connect(ui->kaishi,&QPushButton::clicked,//开始游戏
            [=]()
    {
        start(ps);
        ui->widget->hide();
        ui->widget_2->hide();
        ui->widget_3->show();
        ui->widget_4->show();
        ui->widget_5->show();
        ui->fanhui->show();
        ui->bangzhu->show();
        ui->textout->show();
        ui->mockinfect->show();
        ui->randominfect->show();
        ui->tongji->show();
        QString temp;
        temp.sprintf("%d",getallpig(ps));
        ui->pignum->setText(temp);
        temp.sprintf("%d",sumday);
        ui->daynum->setText(temp);
        temp.sprintf("%.1f",gold);
        ui->goldnum->setText(temp);
    }

            );
    connect(ui->load,&QPushButton::clicked,//加载游戏
            [=]()
    {
        fstart(ps);
        ui->widget->hide();
        ui->widget_2->hide();
        ui->widget_3->show();
        ui->widget_4->show();
        ui->widget_5->show();
        ui->fanhui->show();
        ui->bangzhu->show();
        ui->textout->show();
        ui->mockinfect->show();
        ui->randominfect->show();
        ui->tongji->show();
        QString temp;
        temp.sprintf("%d",getallpig(ps));
        ui->pignum->setText(temp);
        temp.sprintf("%d",sumday);
        ui->daynum->setText(temp);
        temp.sprintf("%0.1f",gold);
        ui->goldnum->setText(temp);
    }
            );
    connect(ui->store,&QPushButton::clicked,//储存游戏
            [=]()
    {

        int ret=QMessageBox::question(this,"储存游戏","确定要储存游戏并退出吗?",QMessageBox::Yes|QMessageBox::No);
        switch (ret)
        {
        case QMessageBox::Yes:
        {   fend(ps);this->close();  }
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
    }
            );

    connect(ui->tuichu,&QPushButton::clicked,//关闭游戏
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

    connect(ui->fanhui,&QPushButton::clicked,//返回主界面
            [=]()
    {
        ui->fanhui->hide();
        ui->bangzhu->hide();
        ui->widget->show();
        ui->widget_2->show();
        ui->widget_3->hide();
        ui->widget_4->hide();
        ui->widget_5->hide();
        ui->textout->hide();
        ui->jixu->show();
        ui->randominfect->hide();
        ui->mockinfect->hide();
        ui->tongji->hide();
    }
            );

    connect(ui->jixu,&QPushButton::clicked,//继续游戏
            [=]()
    {
        ui->fanhui->show();
        ui->bangzhu->show();
        ui->widget->hide();
        ui->widget_2->hide();
        ui->widget_3->show();
        ui->widget_4->show();
        ui->widget_5->show();
        ui->textout->show();
        ui->jixu->hide();
        ui->randominfect->show();
        ui->mockinfect->show();
        ui->tongji->show();
    }
            );

    connect(ui->mockinfect,&QPushButton::clicked,//感染模拟
            [=]()
    {
        srand((unsigned)time(0));
        int j=0;
        int i;
        int ifbreak=0;
        while(true)
        {
            i=random(0,99);
            if(ps[i].gethead()!=NULL)
            {
                ps[i].infectgame();
                break;
            }
        }
        while(true)
        {
            if(getallinfectpig(ps)==getallpig(ps))
            {
                break;
            }
            infectday(ps);
            j++;
            if(j>=1000000)
            {
                ifbreak=1;
                break;
            }
        }
        if(ifbreak==1)
        {
            QString temp;
            temp.sprintf("可能由于有猪圈为空，而导致猪场不可能被全部感染！");
            ui->textout->setText(temp);
        }
        else
        {
            QString temp;
            temp.sprintf("%d号猪圈被感染了！如果不采取任何措施猪场将在%d天后全部感染！",i,j);
            ui->textout->setText(temp);
        }
        for(int i=0;i<100;i++)//模拟结束恢复健康
        {
            ps[i].setisinfect(0);
            ps[i].setinfectsum(0);
            pig *p=ps[i].gethead();
            while(p)
            {
                p->infected=0;
                p=p->next;
            }
        }
    }
            );

    connect(ui->randominfect,&QPushButton::clicked,//随机感染，被感染则清空猪圈，且每只猪的清理费用为500元
            [=]()
    {
        srand((unsigned)time(0));
        int i;
        double sunshig;
        int sunship;
        if(getallpig(ps)<=0)
        {
            QString temp;
            temp.sprintf("猪场已空，不可能再感染了！");
            ui->textout->setText(temp);
        }
        else
        {
        while(true)
        {
            i=random(0,99);
            if(ps[i].gethead()!=NULL)
            {
                sunship=ps[i].getsum();
                sunshig=500*ps[i].getsum();
                ps[i].clear();
                break;
            }
        }
        gold=gold-sunshig;
        QString temp;
        temp.sprintf("第%d个猪圈被感染，已将所有猪全部处理，共处理%d只猪，损失%.1f元",i,sunship,sunshig);
        ui->textout->setText(temp);
        temp.sprintf("%d",getallpig(ps));
        ui->pignum->setText(temp);
        temp.sprintf("%0.1f",gold);
        ui->goldnum->setText(temp);
        if(gold<0)
        {
            QMessageBox::about(this,"提示","你输了!");
            this->close();
        }
        }

    }
            );

    connect(ui->tongji,&QPushButton::clicked,
            [=]()
    {
        ui->widget_6->show();
        ui->fanhui->hide();
        ui->bangzhu->hide();
        ui->widget_3->hide();
        ui->widget_4->hide();
        ui->widget_5->hide();
        ui->textout->hide();
        ui->randominfect->hide();
        ui->mockinfect->hide();
        ui->tongji->hide();

    }
            );

    connect(ui->back,&QPushButton::clicked,
            [=]()
    {
        ui->widget_6->hide();
        ui->fanhui->show();
        ui->bangzhu->show();
        ui->widget_3->show();
        ui->widget_4->show();
        ui->widget_5->show();
        ui->textout->show();
        ui->randominfect->show();
        ui->mockinfect->show();
        ui->tongji->show();
    }
            );

    connect(ui->species,&QPushButton::clicked,//品种统计图绘制
            [=]()
    {
        tongji *h=new tongji;
        h->resize(600,600);
        h->setWindowTitle("种类分布");
        h->setWindowIcon(QIcon("://image/tongjitubiao.jpg"));
        h->species(getallpig1(ps),getallpig2(ps),getallpig3(ps));
        h->show();

    }
            );

    connect(ui->days,&QPushButton::clicked,//天数统计图绘制
            [=]()
    {
        int d1=0,d2=0,d3=0,d4=0;//d1饲养0-30，d2饲养31-60，d3饲养61-90，d4饲养>90
        for(int i=0;i<100;i++)
        {
            pig *p=ps[i].gethead();
            while(p)
            {
                int gd;
                gd=p->gday;
                if(gd>=0&&gd<=30)d1++;
                if(gd>30&&gd<=60)d2++;
                if(gd>60&&gd<=90)d3++;
                if(gd>90)d4++;
                p=p->next;
            }
        }
        tongji *h=new tongji;
        h->resize(600,600);
        h->setWindowTitle("成长天数分布");
        h->setWindowIcon(QIcon("://image/tongjitubiao.jpg"));
        h->days(d1,d2,d3,d4);
        h->show();
    }
            );

    connect(ui->weight,&QPushButton::clicked,//体重统计图绘制
            [=]()
    {
        int w1=0,w2=0,w3=0,w4=0;//w1体重0-25，w2体重25-50，w3体重50-75，w4体重>75
        for(int i=0;i<100;i++)
        {
            pig *p=ps[i].gethead();
            while(p)
            {
                double w;
                w=p->weight;
                if(w>=0&&w<=25)w1++;
                if(w>25&&w<=50)w2++;
                if(w>50&&w<=75)w3++;
                if(w>75)w4++;
                p=p->next;
            }
        }
        tongji *h=new tongji;
        h->resize(600,600);
        h->setWindowTitle("体重分布");
        h->setWindowIcon(QIcon("://image/tongjitubiao.jpg"));
        h->weights(w1,w2,w3,w4);
        h->show();
    }
            );

    connect(ui->bangzhu,&QPushButton::clicked,//输出帮助信息
            [=]()
    {
        QString temp;
        temp.sprintf("游戏开始时,猪圈中有随机的200头猪。您手上有200000元,当你的钱数为0时游戏结束,当你的钱数大于500000元时游戏胜利。您可以选择查看猪场的各种信息,"
                     "并进行饲养、购入猪、卖出猪操作。注意:当你购入新猪时,黑猪900元一只,小花猪420元一只,大花白猪360元一只。而当你增长天数时,每天黑猪的饲料费为10元、小白猪为8元"
                     "大花白猪为6元。每饲养90天,您可卖一次猪,系统将自动按照一定规则为您进行卖猪操作。");
        ui->textout->setText(temp);
    }
            );

    connect(ui->growday,&QPushButton::clicked,//增长天数,每天和黑猪的饲料费为10元,小白猪为8元,大花白猪为6元
            [=]()
    {
        bool ok;
        QString temp;
        int j = QInputDialog::getInt(this, tr("增长天数"),tr("请输入增长天数:"), 0, 0, 100, 1, &ok);
        if(ok)
        {
            for(int i=0;i<j;i++)
            {
                oneday(ps);
                gold=gold-10*getallpig1(ps)-8*getallpig2(ps)-6*getallpig3(ps);
            }
            sumday+=j;
            growday+=j;
            temp.sprintf("渡过了%d天,总计花费%.1f元用于猪的饲养.",j,j*(10.0*getallpig1(ps)+8.0*getallpig2(ps)+6.0*getallpig3(ps)));
            ui->textout->setText(temp);
            temp.sprintf("%d",sumday);
            ui->daynum->setText(temp);
            temp.sprintf("%.1f",gold);
            ui->goldnum->setText(temp);
            if(gold<0)
            {
                QMessageBox::about(this,"提示","你输了!");
                this->close();
            }
        }
    }
            );

    connect(ui->pigchang,&QPushButton::clicked,//输出猪场信息
            [=]()
    {
        int allpig1=0,allpig2=0,allpig3=0;
        int w1=0,w2=0,w3=0,w4=0;//w1体重0-25，w2体重25-50，w3体重50-75，w4体重>75
        int d1=0,d2=0,d3=0,d4=0;//d1饲养0-30，d2饲养31-60，d3饲养61-90，d4饲养>90
        int allpig=getallpig(ps);
        for(int i=0;i<100;i++)
        {
            pig *p=ps[i].gethead();
            while(p)
            {
                int sp,gd;
                double w;
                sp=p->species;
                gd=p->gday;
                w=p->weight;
                if(sp==1)allpig1++;
                if(sp==2)allpig2++;
                if(sp==3)allpig3++;
                if(gd>=0&&gd<=30)d1++;
                if(gd>30&&gd<=60)d2++;
                if(gd>60&&gd<=90)d3++;
                if(gd>90)d4++;
                if(w>=0&&w<=25)w1++;
                if(w>25&&w<=50)w2++;
                if(w>50&&w<=75)w3++;
                if(w>75)w4++;
                p=p->next;
            }
        }
        QString temp;
        temp.sprintf("总猪数:%d\n"
                     "黑猪数:%d\n"
                     "小白猪数:%d\n"
                     "大花白猪数:%d\n"
                     "体重分布情况:   0-25: %d\n"
                     "               25-50: %d\n"
                     "               50-75: %d\n"
                     "                 >75: %d\n"
                     "成长天数分布情况: 0-30: %d\n"
                     "                31-60: %d\n"
                     "                61-90: %d\n"
                     "                  >90: %d\n"
                     ,allpig,allpig1,allpig2,allpig3,w1,w2,w3,w4,d1,d2,d3,d4);
        ui->textout->setText(temp);
    }
            );

    connect(ui->pigsty,&QPushButton::clicked,//输出猪圈信息
            [=]()
    {
        bool ok;
        int i = QInputDialog::getInt(this, tr("猪圈查询"),tr("请输入猪圈编号:"), 0, 0, 99, 1, &ok);
        if(ok)
        {
            QString temp;
            int sum,isblack;
            pig *p;
            sum=ps[i].getsum();
            isblack=ps[i].getisblack();
            p=ps[i].gethead();
            if(p==NULL)
            {
                temp.sprintf("猪圈为空!");
                ui->textout->setText(temp);
            }
            else
            {
                if(isblack==1)
                {
                    temp.sprintf("此猪圈为黑猪圈,猪圈中共有%d只黑猪",sum);
                    ui->textout->setText(temp);
                }
                else
                {
                    int pig2=0,pig3=0;
                    while(p)
                    {
                        if(p->species==2)
                        pig2++;
                        if(p->species==3)
                        pig3++;
                        p=p->next;
                    }
                    temp.sprintf("此猪圈为非黑猪圈,共有%d只猪,其中有%d只小白猪、%d只大花白猪",sum,pig2,pig3);
                    ui->textout->setText(temp);
                }
            }
        }
    }
            );
    connect(ui->pig,&QPushButton::clicked,//输出猪信息
            [=]()
    {
        bool ok1,ok2;
        int i = QInputDialog::getInt(this, tr("猪查询"),tr("请输入猪圈编号:"), 0, 0, 99, 1, &ok1);
        int j = QInputDialog::getInt(this, tr("猪查询"),tr("请输入猪编号:"), 0, 0, 9, 1, &ok2);
        if(ok1&&ok2)
        {
            QString temp;
            pig *p;
            p=ps[i].gethead();
            if(p==NULL)
            {
                temp.sprintf("猪圈为空!");
                ui->textout->setText(temp);
            }
            int sp,gd,flag=0;
            double w;
            while(p)
            {
                if(p->id==j)
                {
                    flag=1;
                    break;
                }
                p=p->next;
            }
            if(flag==1)
            {
                sp=p->species;
                gd=p->gday;
                w=p->weight;
                if(sp==1)
                {
                    temp.sprintf("该猪是黑猪,成长天数为%d天,体重为%.1fkg",gd,w);
                }
                if(sp==2)
                {
                    temp.sprintf("该猪是小白猪,成长天数为%d天,体重为%.1fkg",gd,w);
                }
                if(sp==3)
                {
                    temp.sprintf("该猪是大花白猪,成长天数为%d天,体重为%.1fkg",gd,w);
                }
                ui->textout->setText(temp);
            }
            else
            {
                temp.sprintf("查无此猪!");
                ui->textout->setText(temp);
            }
        }
    }
            );

    connect(ui->buypig,&QPushButton::clicked,//购入新猪,黑猪900元一只,小花猪420元一只,大花白猪360元一斤
            [=]()
    {
        QMessageBox::about(this,"购猪提示","黑猪900元一只，小花猪420元一只，大花白猪360元一只");
        bool ok1,ok2,ok3;
        int i = QInputDialog::getInt(this, tr("购入新猪"),tr("购入黑猪数:"),0,0,50,1,&ok1);
        int j = QInputDialog::getInt(this, tr("购入新猪"),tr("购入小白猪数:"),0,0,50,1,&ok2);
        int k = QInputDialog::getInt(this, tr("购入新猪"),tr("购入大花白猪数:"),0,0,50,1,&ok3);
        QString temp;
        if((gold-i*900-j*420-k*360)<=0)
        {
            temp.sprintf("钱不够!");
            ui->textout->setText(temp);
        }
        else if(ok1&&ok2&&ok3)
        {
            gold=gold-i*900-j*420-k*360;
            buypig(ps,i,j,k);
            temp.sprintf("成功购入%d只黑猪,%d只小白猪,%d只大花白猪.共计花费%d元.",i,j,k,i*900+j*420+k*360);
            ui->textout->setText(temp);
            temp.sprintf("%d",getallpig(ps));
            ui->pignum->setText(temp);
            temp.sprintf("%0.1f",gold);
            ui->goldnum->setText(temp);
        }

    }
        );

    connect(ui->sellpig,&QPushButton::clicked,//卖猪
            [=]()
    {
        QString temp;
        if(growday<90)
        {
            temp.sprintf("距离上次卖猪饲养未满三个月,你无法卖猪!");
            ui->textout->setText(temp);
        }
        else
        {

            double sumprice=0;
            int sellpig1,sellpig2;
            int qianpig1,qianpig2,qianpig3;
            int houpig1,houpig2,houpig3;
            sellpig1=getallpig(ps);
            qianpig1=getallpig1(ps);
            qianpig2=getallpig2(ps);
            qianpig3=getallpig3(ps);
            for(int i=0;i<100;i++)
            {
                sumprice+=ps[i].getprice();
            }
            gold=gold+sumprice;
            sellpig2=getallpig(ps);
            houpig1=getallpig1(ps);
            houpig2=getallpig2(ps);
            houpig3=getallpig3(ps);
            temp.sprintf("卖出%d只黑猪、%d只小花猪、%d只大花白猪\n"
                         "总共卖出%d只猪,得到%.1f元",qianpig1-houpig1,qianpig2-houpig2,qianpig3-houpig3,sellpig1-sellpig2,sumprice);
            ui->textout->setText(temp);
            temp.sprintf("%d",sellpig2);
            ui->pignum->setText(temp);
            temp.sprintf("%0.1f",gold);
            ui->goldnum->setText(temp);
            growday=0;
            if(gold>500000)
            {
                QMessageBox::about(this,"提示","你赢了");
                this->close();
            }
        }
    }
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)//设置背景图
{
    QPainter p;
    p.begin(this);
    p.drawPixmap(rect(),QPixmap("://image/beijing.jpg"));
    p.end();
}
