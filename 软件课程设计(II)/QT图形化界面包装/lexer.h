#ifndef LEXER_H
#define LEXER_H

#include <QWidget>

namespace Ui {
class Lexer;
}

class Lexer : public QWidget
{
    Q_OBJECT

public:
    explicit Lexer(QWidget *parent = 0);
    ~Lexer();
    void Sendslot1();

private:
    Ui::Lexer *ui;

signals:
    void Mysignal1();
};

#endif // LEXER_H
