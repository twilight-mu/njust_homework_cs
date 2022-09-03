#ifndef ANALYZER_H
#define ANALYZER_H

#include <QWidget>
#include <bits/stdc++.h>
#include <string>
using namespace std;

namespace Ui {
class Analyzer;
}

class Analyzer : public QWidget
{
    Q_OBJECT

public:
    explicit Analyzer(QWidget *parent = 0);
    ~Analyzer();
    void Sendslot3();
    void solve_for(string s);
    void solve_while(string s);
    void solve_if(string s);
    void solve_other(string s);
    void solve_expression(string s);

private:
    Ui::Analyzer *ui;

signals:
    void Mysignal3();
};

#endif // ANALYZER_H
