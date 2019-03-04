#include "tableanalyzerwindow.h"
#include "ui_tableanalyzerwindow.h"

TableAnalyzerWindow::TableAnalyzerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableAnalyzerWindow)
{
    ui->setupUi(this);
}

TableAnalyzerWindow::~TableAnalyzerWindow()
{
    delete ui;
}
