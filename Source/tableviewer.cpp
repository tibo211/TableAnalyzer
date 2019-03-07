#include "tableviewer.h"

TableViewer::TableViewer(QWidget *parent):QTableWidget(parent){
    isReading = false;
}

TableViewer::~TableViewer(){
    if(reader != nullptr) delete reader;
}

void TableViewer::setFile(QString path) {
    reader = new TableReader;
    if(!(reader->addFile(path))){
        hide();
        return;
    }

    setColumnCount(reader->headers.length());
    setHorizontalHeaderLabels(reader->headers);
    maxColWidth = new int[columnCount()];
    for (int i = 0; i < columnCount(); ++i) { maxColWidth[i] = 2; }

    setTableSize();

    reader->moveToThread(&readThread);
    connect(&readThread,&QThread::started,reader,&TableReader::startRead);
    connect(reader, &TableReader::addRows, this, &TableViewer::addRows);
    connect(reader, &TableReader::finished, &readThread, &QThread::quit);
    connect(reader, &TableReader::finished, this, &TableViewer::doneReading);

    readThread.start();
    isReading = true;
}

void TableViewer::setTableSize()
{
    int w = verticalHeader()->width() + 40;
    for (int i = 0; i < columnCount(); ++i) {
        w += columnWidth(i);
    }
    QSize maxsize(w,2*w);
    QSize minsize(w,w);
    setMaximumSize(maxsize);
    setMinimumSize(minsize);
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

void TableViewer::doneReading()
{
    isReading = false;
}

void TableViewer::update() {
    while (isReading || !rowQueue->isEmpty()) {
        if(!rowQueue->isEmpty()){
            QStringList row = rowQueue->dequeue();
            int rowID = rowCount();
            if(row.length() != columnCount()) {
                QMessageBox::information(nullptr, "error", "columns error in row: ");
            }


        }

        QTimer::singleShot(10,this, &TableViewer::update);
    }
}
