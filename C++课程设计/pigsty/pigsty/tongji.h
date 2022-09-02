#ifndef TONGJI_H
#define TONGJI_H

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
class tongji : public QWidget
{
    Q_OBJECT
public:
    explicit tongji(QWidget *parent = nullptr);
    void species(int a,int b,int c)
    {
        QPieSeries *series = new QPieSeries(this);
        if(a!=0)
        {
        QPieSlice *slice_1 = new QPieSlice(QStringLiteral("黑猪"), a, this);
        slice_1->setLabelVisible(true);
        slice_1->setBrush(Qt::green);
        series->append(slice_1);
        }
        if(b!=0)
        {
        QPieSlice *slice_2 = new QPieSlice(QStringLiteral("小花猪"), b, this);
        slice_2->setLabelVisible(true);
        slice_2->setBrush(Qt::blue);
        series->append(slice_2);
        }
        if(c!=0)
        {
        QPieSlice *slice_3 = new QPieSlice(QStringLiteral("大花白猪"), c, this);
        slice_3->setLabelVisible(true);
        slice_3->setBrush(Qt::red);
        series->append(slice_3);
        }
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::AllAnimations);

        QChartView *chartview = new QChartView(this);
        chartview->show();
        chartview->setChart(chart);

        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->addWidget(chartview,0);
    }

    void days(int a,int b,int c,int d)
    {
        QPieSeries *series = new QPieSeries(this);
        if(a!=0)
        {
        QPieSlice *slice_1 = new QPieSlice(QStringLiteral("0-30天"), a, this);
        slice_1->setLabelVisible(true);
        slice_1->setBrush(Qt::green);
        series->append(slice_1);
        }
        if(b!=0)
        {
        QPieSlice *slice_2 = new QPieSlice(QStringLiteral("31-60天"), b, this);
        slice_2->setLabelVisible(true);
        slice_2->setBrush(Qt::blue);
        series->append(slice_2);
        }
        if(c!=0)
        {
        QPieSlice *slice_3 = new QPieSlice(QStringLiteral("61-90天"), c, this);
        slice_3->setLabelVisible(true);
        slice_3->setBrush(Qt::red);
        series->append(slice_3);
        }
        if(d!=0)
        {
        QPieSlice *slice_4 = new QPieSlice(QStringLiteral(">90天"), d, this);
        slice_4->setLabelVisible(true);
        slice_4->setBrush(Qt::yellow);
        series->append(slice_4);
        }
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::AllAnimations);

        QChartView *chartview = new QChartView(this);
        chartview->show();
        chartview->setChart(chart);

        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->addWidget(chartview,0);

    }

    void weights(int a,int b ,int c,int d)
    {
        QPieSeries *series = new QPieSeries(this);
        if(a!=0)
        {
        QPieSlice *slice_1 = new QPieSlice(QStringLiteral("0-25kg"), a, this);
        slice_1->setLabelVisible(true);
        slice_1->setBrush(Qt::green);
        series->append(slice_1);
        }
        if(b!=0)
        {
        QPieSlice *slice_2 = new QPieSlice(QStringLiteral("25-50kg"), b, this);
        slice_2->setLabelVisible(true);
        slice_2->setBrush(Qt::blue);
        series->append(slice_2);
        }
        if(c!=0)
        {
        QPieSlice *slice_3 = new QPieSlice(QStringLiteral("50-75kg"), c, this);
        slice_3->setLabelVisible(true);
        slice_3->setBrush(Qt::red);
        series->append(slice_3);
        }
        if(d!=0)
        {
        QPieSlice *slice_4 = new QPieSlice(QStringLiteral(">75kg"), d, this);
        slice_4->setLabelVisible(true);
        slice_4->setBrush(Qt::yellow);
        series->append(slice_4);
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::AllAnimations);


        QChartView *chartview = new QChartView(this);
        chartview->show();
        chartview->setChart(chart);


        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->addWidget(chartview,0);
    }

signals:

public slots:
};

#endif // TONGJI_H
