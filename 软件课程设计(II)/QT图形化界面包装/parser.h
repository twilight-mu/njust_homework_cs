#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

namespace Ui {
class Parser;
}

class Parser : public QWidget
{
    Q_OBJECT

public:
    explicit Parser(QWidget *parent = 0);
    ~Parser();
    void Sendslot2();

private:
    Ui::Parser *ui;

signals:
    void Mysignal2();
};

#endif // PARSER_H
