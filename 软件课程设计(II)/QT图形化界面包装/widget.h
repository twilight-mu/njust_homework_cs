#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "lexer.h"
#include "parser.h"
#include "analyzer.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void backmain1();
    void backmain2();
    void backmain3();

private:
    Ui::Widget *ui;
    Lexer w1;
    Parser w2;
    Analyzer w3;
};

#endif // WIDGET_H
