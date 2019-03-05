#include "tableanalyzerwindow.h"
#include "ui_tableanalyzerwindow.h"

TableAnalyzerWindow::TableAnalyzerWindow(QWidget *parent):QMainWindow(parent),
    ui(new Ui::TableAnalyzerWindow) {
    ui->setupUi(this);
    setAcceptDrops(true);
}

TableAnalyzerWindow::~TableAnalyzerWindow() {
    foreach(auto tableViewer, tableViewers){
        if(tableViewer != nullptr) delete tableViewer;
    }
    tableViewers.clear();
    delete ui;
}

void TableAnalyzerWindow::dragEnterEvent(QDragEnterEvent *event) {
    if(event->mimeData()->hasUrls()) event->acceptProposedAction();
}

//Opens new table viewer
//Set the file for the table viewer
//Starts reading
void TableAnalyzerWindow::dropEvent(QDropEvent *event){
    foreach(auto url, event->mimeData()->urls()){
        QString path = url.toLocalFile();
        QString filename = url.fileName();
        TableViewer *tableViewer = new TableViewer;
        tableViewer->setWindowTitle("Table [" + filename + "]");
        tableViewer->show();
        tableViewer->setFile(path);
        tableViewers.append(tableViewer);
    }
}
