#include "tablereader.h"

TableReader::TableReader(QObject *parent) : QObject(parent)
{

}

bool TableReader::addFile(QString path){
    this->path = path;
    file = new QFile(path);
    if(!file->open(QIODevice::ReadOnly)){
        QMessageBox::information(nullptr, "error", file->errorString());
        return false;
    }
    textStream = new QTextStream(file);

    //change this for other encoding
    textStream->setCodec("UTF-8");

    return true;
}

TableReader::~TableReader(){
    if(file != nullptr){
        file->close();
        delete file;
    }
    if(textStream != nullptr){
        delete textStream;
    }
}
