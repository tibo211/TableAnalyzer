#ifndef TABLEANALYZERWINDOW_H
#define TABLEANALYZERWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QDragEnterEvent>
#include "tableviewer.h"
#include "tablereader.h"

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
    QList<TableViewer *> tableViewers;
    Ui::TableAnalyzerWindow *ui;

    //Accept drag and drop files
    void dropEvent(QDropEvent *event) override;

    //Opens new table viewer
    //Set the file for the table viewer
    //Starts reading
    void dragEnterEvent(QDragEnterEvent* event) override;
};

#endif // TABLEANALYZERWINDOW_H
