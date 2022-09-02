#ifndef ZHUJIEMIAN_H
#define ZHUJIEMIAN_H

#include <QWidget>
#include "board.h"
#include "SingleGame.h"
#include <QPushButton>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    Ui::Widget *ui;
    Board* h;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // ZHUJIEMIAN_H
