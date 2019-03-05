#include "tableanalyzerwindow.h"
#include "ui_tableanalyzerwindow.h"

QString TableReader::separator;
QString TableReader::endofline;
char *TableReader::encoding;

TableAnalyzerWindow::TableAnalyzerWindow(QWidget *parent):QMainWindow(parent),
    ui(new Ui::TableAnalyzerWindow) {
    ui->setupUi(this);
    setAcceptDrops(true);

    //These should be set in the UI
    TableReader::separator = "<<DIV>>";
    TableReader::endofline = "<<EOL>>";
    TableReader::encoding = QString("UTF-8").toUtf8().data();
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
