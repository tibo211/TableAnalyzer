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
    delete ui;
}

void TableAnalyzerWindow::dragEnterEvent(QDragEnterEvent *event) {
    if(event->mimeData()->hasUrls()) event->acceptProposedAction();
}

void TableAnalyzerWindow::dropEvent(QDropEvent *event){
    foreach(auto url, event->mimeData()->urls()){
        QString path = url.toLocalFile();
        QString filename = url.fileName();
        TableViewer *tableViewer = new TableViewer;
        tableViewer->setWindowTitle("Table [" + filename + "]");
        tableViewer->show();
        tableViewers.append(tableViewer);
    }
}
