#include "tablereader.h"

#include <QMessageBox>

TableReader::TableReader(QObject *parent) : QObject(parent)
{

}

void TableReader::initFile(QString path){
    this->path = path;
    file = new QFile(path);
    if(!file->open(QIODevice::WriteOnly)){
        QMessageBox::information(nullptr,"error", file->errorString());
        return;
    }

    textStream = new QTextStream(file);
    textStream->setCodec("UTF-8");                          //Change this for different encoding
}
