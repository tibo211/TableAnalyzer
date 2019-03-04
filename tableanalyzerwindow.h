#ifndef TABLEANALYZERWINDOW_H
#define TABLEANALYZERWINDOW_H

#include <QMainWindow>

namespace Ui {
class TableAnalyzerWindow;
}

class TableAnalyzerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableAnalyzerWindow(QWidget *parent = nullptr);
    ~TableAnalyzerWindow();

private:
    Ui::TableAnalyzerWindow *ui;
};

#endif // TABLEANALYZERWINDOW_H
