#include "tableviewer.h"

TableViewer::TableViewer(QWidget *parent):QTableWidget(parent){

}

TableViewer::~TableViewer(){
    if(reader != nullptr) delete reader;
}

void TableViewer::setFile(QString path){
    reader = new TableReader;
    if(!(reader->addFile(path))){
        hide();
        return;
    }

    setColumnCount(reader->headers.length());

    setHorizontalHeaderLabels(reader->headers);

    reader->moveToThread(&readThread);
    connect(&readThread,&QThread::started,reader,&TableReader::startRead);
    connect(reader, &TableReader::addRows, this, &TableViewer::addRows);
    connect(reader, &TableReader::finished, &readThread, &QThread::quit);

    readThread.start();
}

TableReader *TableViewer::getReader() const { return reader; }

void TableViewer::addRows(QStringList *rows, int length)
{
    for (int i = 0; i < length; ++i) {
        int rowID = rowCount();
        insertRow(rowID);
        for (int colID = 0; colID < columnCount(); ++colID) {
            QString value = rows[i][colID];
            setItem(rowID,colID, new QTableWidgetItem(value));
        }
        rows[i].clear();
    }

    delete [] rows;

}
