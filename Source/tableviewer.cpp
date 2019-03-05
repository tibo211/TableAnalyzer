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
}

TableReader *TableViewer::getReader() const { return reader; }
