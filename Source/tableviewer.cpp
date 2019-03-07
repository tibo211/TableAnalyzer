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
    maxColWidth = new int[columnCount()];
    for (int i = 0; i < columnCount(); ++i) { maxColWidth[i] = 2; }

    int w = verticalHeader()->width() + 40;
    for (int i = 0; i < columnCount(); ++i) {
        w += columnWidth(i);
    }
    QSize maxsize(w,2*w);
    QSize minsize(w,w);
    setMaximumSize(maxsize);
    setMinimumSize(minsize);


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

            //resize columns
            if(value.contains("\n")){
                resizeRowToContents(rowID);
                foreach(auto v, value.split("\n")) {
                    if(v.length() > maxColWidth[colID]){
                        maxColWidth[colID] = value.length();
                        resizeColumnToContents(colID);
                    }
                }
            } else {
                if(value.length() > maxColWidth[colID]){
                    maxColWidth[colID] = value.length();
                    resizeColumnToContents(colID);
                }
            }
        }
        rows[i].clear();
    }

    delete [] rows;

}
