#include "statistiques.h"
#include "ui_statistiques.h"

statistiques::statistiques(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statistiques)
{
    ui->setupUi(this);
    QPieSeries *series=new QPieSeries();

    series->append("< 10",tmpr.calcul_type(0,10));
    series->append("[10..25]",tmpr.calcul_type(10,25));
    series->append("[25..50]",tmpr.calcul_type(25,50));
    series->append("[50..100]",tmpr.calcul_type(50,100));

    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre des personnes");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartview=new QChartView(chart);

    this->setCentralWidget(chartview);
}

statistiques::~statistiques()
{
    delete ui;
}
