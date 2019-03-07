#include "tableviewer.h"

TableViewer::TableViewer(QWidget *parent):QTableWidget(parent){
    isReading = false;
    rowQueue = new QQueue<QStringList>;
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
    QTimer::singleShot(10,this, &TableViewer::update);
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
        rowQueue->enqueue(rows[i]);
    }

    delete [] rows;
}

void TableViewer::doneReading()
{
    isReading = false;
}

void TableViewer::update() {
    if (isReading || !rowQueue->isEmpty()) {
        if(!rowQueue->isEmpty()){
            QStringList row = rowQueue->dequeue();
            int rowID = rowCount();
            insertRow(rowID);
            if(row.length() != columnCount()) {
                QMessageBox::information(nullptr, "error", "columns error in row: " + QString::number(rowID));
                return;
            }
            int colID = 0;

            bool resizeRow = false;
            foreach (auto value, row) {
                bool changeColumnWidth = false;
                if(value.contains('\n')){
                    resizeRow = true;
                    foreach (auto v, value.split('\n')) {
                        if(v.count() > maxColWidth[colID]){
                            maxColWidth[colID] = v.count();
                            changeColumnWidth = true;
                        }
                    }
                } else {
                    if(value.count() > maxColWidth[colID]){
                        maxColWidth[colID] = value.count();
                        changeColumnWidth = true;
                    }
                }
                setItem(rowID,colID, new QTableWidgetItem(value));
                if(changeColumnWidth) resizeColumnToContents(colID);
                colID++;
            }

            if (resizeRow) resizeRowToContents(rowID);
            row.clear();
        }
        QTimer::singleShot(0.1,this, &TableViewer::update);
    }
}
