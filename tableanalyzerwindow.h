#ifndef TABLEANALYZERWINDOW_H
#define TABLEANALYZERWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QDragEnterEvent>
#include "tableviewer.h"

namespace Ui {
class TableAnalyzerWindow;
}

class TableAnalyzerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TableAnalyzerWindow(QWidget *parent = nullptr);
    ~TableAnalyzerWindow() override;

private:
    TableViewer *tableViewer;
    Ui::TableAnalyzerWindow *ui;
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;

};

#endif // TABLEANALYZERWINDOW_H
