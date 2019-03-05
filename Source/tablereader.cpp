#include "tablereader.h"

TableReader::TableReader(QObject *parent) : QObject(parent)
{

}

bool TableReader::addFile(QString path){
    this->path = path;
    file = new QFile(path);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(nullptr, "error", file->errorString());
        return false;
    }
    textStream = new QTextStream(file);
    textStream->setCodec(encoding);
    QString line;
    if(!textStream->readLineInto(&line)){
        QMessageBox::information(nullptr, "error", "Cannot read the header row");
        return false;
    }

    if(!endofline.contains("\n")){
        if(line.right(endofline.length()) != endofline){
            QMessageBox::information(nullptr, "error", "Cannot find the end of the header line\r\nMissing line separator?");
            return false;
        }

        line = line.replace(endofline, "");
    }
    headers = line.split(separator);

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
