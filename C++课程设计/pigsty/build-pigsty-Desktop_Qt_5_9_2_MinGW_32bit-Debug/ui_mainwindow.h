/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *biaoti;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *kaishi;
    QPushButton *load;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *store;
    QPushButton *tuichu;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QPushButton *pig;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pigsty;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pigchang;
    QPushButton *fanhui;
    QWidget *widget_4;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_6;
    QTextBrowser *daynum;
    QLabel *label_3;
    QLabel *label;
    QTextBrowser *pignum;
    QLabel *label_2;
    QTextBrowser *goldnum;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_2;
    QPushButton *growday;
    QSpacerItem *verticalSpacer_11;
    QPushButton *sellpig;
    QSpacerItem *verticalSpacer_10;
    QPushButton *buypig;
    QPushButton *bangzhu;
    QPushButton *jixu;
    QPushButton *randominfect;
    QPushButton *mockinfect;
    QTextBrowser *textout;
    QPushButton *tongji;
    QWidget *widget_6;
    QWidget *widget_7;
    QPushButton *weight;
    QPushButton *days;
    QPushButton *species;
    QPushButton *back;
    QLabel *tushi;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(616, 557);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 100, 591, 111));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(244, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        biaoti = new QLabel(widget);
        biaoti->setObjectName(QStringLiteral("biaoti"));

        horizontalLayout_2->addWidget(biaoti);

        horizontalSpacer_5 = new QSpacerItem(245, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(10, 320, 591, 61));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        kaishi = new QPushButton(widget_2);
        kaishi->setObjectName(QStringLiteral("kaishi"));
        kaishi->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(kaishi);

        load = new QPushButton(widget_2);
        load->setObjectName(QStringLiteral("load"));

        horizontalLayout->addWidget(load);

        horizontalSpacer_2 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        store = new QPushButton(widget_2);
        store->setObjectName(QStringLiteral("store"));

        horizontalLayout->addWidget(store);

        tuichu = new QPushButton(widget_2);
        tuichu->setObjectName(QStringLiteral("tuichu"));

        horizontalLayout->addWidget(tuichu);

        horizontalSpacer_3 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget_3 = new QWidget(centralWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(10, 90, 161, 401));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pig = new QPushButton(widget_3);
        pig->setObjectName(QStringLiteral("pig"));

        verticalLayout->addWidget(pig);

        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pigsty = new QPushButton(widget_3);
        pigsty->setObjectName(QStringLiteral("pigsty"));

        verticalLayout->addWidget(pigsty);

        verticalSpacer_4 = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        pigchang = new QPushButton(widget_3);
        pigchang->setObjectName(QStringLiteral("pigchang"));

        verticalLayout->addWidget(pigchang);

        fanhui = new QPushButton(centralWidget);
        fanhui->setObjectName(QStringLiteral("fanhui"));
        fanhui->setGeometry(QRect(480, 40, 91, 31));
        widget_4 = new QWidget(centralWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(190, 260, 241, 181));
        gridLayout = new QGridLayout(widget_4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 1, 2, 2, 1);

        verticalSpacer_9 = new QSpacerItem(20, 19, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_9, 8, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 9, 2, 3, 1);

        verticalSpacer_8 = new QSpacerItem(20, 27, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_8, 3, 3, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 11, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_7, 7, 1, 3, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 4, 2, 3, 1);

        verticalSpacer_6 = new QSpacerItem(20, 11, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 2, 1, 3, 1);

        daynum = new QTextBrowser(widget_4);
        daynum->setObjectName(QStringLiteral("daynum"));

        gridLayout->addWidget(daynum, 11, 3, 1, 2);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        label = new QLabel(widget_4);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 2, 1);

        pignum = new QTextBrowser(widget_4);
        pignum->setObjectName(QStringLiteral("pignum"));

        gridLayout->addWidget(pignum, 1, 3, 1, 2);

        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 11, 1, 1, 1);

        goldnum = new QTextBrowser(widget_4);
        goldnum->setObjectName(QStringLiteral("goldnum"));

        gridLayout->addWidget(goldnum, 5, 3, 1, 2);

        widget_5 = new QWidget(centralWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(449, 89, 151, 401));
        verticalLayout_2 = new QVBoxLayout(widget_5);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        growday = new QPushButton(widget_5);
        growday->setObjectName(QStringLiteral("growday"));

        verticalLayout_2->addWidget(growday);

        verticalSpacer_11 = new QSpacerItem(20, 106, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_11);

        sellpig = new QPushButton(widget_5);
        sellpig->setObjectName(QStringLiteral("sellpig"));

        verticalLayout_2->addWidget(sellpig);

        verticalSpacer_10 = new QSpacerItem(20, 105, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_10);

        buypig = new QPushButton(widget_5);
        buypig->setObjectName(QStringLiteral("buypig"));

        verticalLayout_2->addWidget(buypig);

        bangzhu = new QPushButton(centralWidget);
        bangzhu->setObjectName(QStringLiteral("bangzhu"));
        bangzhu->setGeometry(QRect(40, 40, 101, 31));
        jixu = new QPushButton(centralWidget);
        jixu->setObjectName(QStringLiteral("jixu"));
        jixu->setGeometry(QRect(480, 40, 91, 31));
        randominfect = new QPushButton(centralWidget);
        randominfect->setObjectName(QStringLiteral("randominfect"));
        randominfect->setGeometry(QRect(190, 450, 93, 31));
        mockinfect = new QPushButton(centralWidget);
        mockinfect->setObjectName(QStringLiteral("mockinfect"));
        mockinfect->setGeometry(QRect(340, 450, 93, 31));
        textout = new QTextBrowser(centralWidget);
        textout->setObjectName(QStringLiteral("textout"));
        textout->setGeometry(QRect(190, 90, 241, 161));
        tongji = new QPushButton(centralWidget);
        tongji->setObjectName(QStringLiteral("tongji"));
        tongji->setGeometry(QRect(260, 40, 101, 28));
        widget_6 = new QWidget(centralWidget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setGeometry(QRect(10, 10, 601, 481));
        widget_7 = new QWidget(widget_6);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setGeometry(QRect(0, 270, 601, 131));
        weight = new QPushButton(widget_7);
        weight->setObjectName(QStringLiteral("weight"));
        weight->setGeometry(QRect(21, 8, 121, 111));
        days = new QPushButton(widget_7);
        days->setObjectName(QStringLiteral("days"));
        days->setGeometry(QRect(237, 8, 121, 111));
        species = new QPushButton(widget_7);
        species->setObjectName(QStringLiteral("species"));
        species->setGeometry(QRect(459, 8, 121, 111));
        back = new QPushButton(widget_6);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(250, 30, 101, 31));
        tushi = new QLabel(widget_6);
        tushi->setObjectName(QStringLiteral("tushi"));
        tushi->setGeometry(QRect(171, 134, 261, 91));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 616, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        biaoti->setText(QApplication::translate("MainWindow", "\346\254\242\344\271\220\347\214\252\345\234\272", Q_NULLPTR));
        kaishi->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
        load->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\346\270\270\346\210\217", Q_NULLPTR));
        store->setText(QApplication::translate("MainWindow", "\345\202\250\345\255\230\346\270\270\346\210\217", Q_NULLPTR));
        tuichu->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", Q_NULLPTR));
        pig->setText(QApplication::translate("MainWindow", "\347\214\252\344\277\241\346\201\257\346\237\245\350\257\242", Q_NULLPTR));
        pigsty->setText(QApplication::translate("MainWindow", "\347\214\252\345\234\210\344\277\241\346\201\257\346\237\245\350\257\242", Q_NULLPTR));
        pigchang->setText(QApplication::translate("MainWindow", "\347\214\252\345\234\272\344\277\241\346\201\257\346\237\245\350\257\242", Q_NULLPTR));
        fanhui->setText(QApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\351\207\221\345\270\201:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\214\252\346\225\260:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\244\251\346\225\260:", Q_NULLPTR));
        growday->setText(QApplication::translate("MainWindow", "\345\242\236\351\225\277\345\244\251\346\225\260", Q_NULLPTR));
        sellpig->setText(QApplication::translate("MainWindow", "\345\215\226\347\214\252", Q_NULLPTR));
        buypig->setText(QApplication::translate("MainWindow", "\350\264\255\347\214\252", Q_NULLPTR));
        bangzhu->setText(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
        jixu->setText(QApplication::translate("MainWindow", "\347\273\247\347\273\255\346\270\270\346\210\217", Q_NULLPTR));
        randominfect->setText(QApplication::translate("MainWindow", "\351\232\217\346\234\272\346\204\237\346\237\223", Q_NULLPTR));
        mockinfect->setText(QApplication::translate("MainWindow", "\346\204\237\346\237\223\346\250\241\346\213\237", Q_NULLPTR));
        tongji->setText(QApplication::translate("MainWindow", "\347\273\237\350\256\241\344\277\241\346\201\257\346\237\245\350\257\242", Q_NULLPTR));
        weight->setText(QApplication::translate("MainWindow", "\347\214\252\344\275\223\351\207\215\345\210\206\345\270\203", Q_NULLPTR));
        days->setText(QApplication::translate("MainWindow", "\347\214\252\346\210\220\351\225\277\345\244\251\346\225\260\345\210\206\345\270\203", Q_NULLPTR));
        species->setText(QApplication::translate("MainWindow", "\347\214\252\347\247\215\347\261\273\345\210\206\345\270\203", Q_NULLPTR));
        back->setText(QApplication::translate("MainWindow", "\350\277\224\345\233\236", Q_NULLPTR));
        tushi->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\344\275\240\346\203\263\346\237\245\350\257\242\347\232\204\346\225\260\346\215\256\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
