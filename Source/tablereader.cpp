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
    textStream->setCodec("UTF-8");
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

void TableReader::startRead()
{
    rows = new QStringList[100];
    rowIdx = 0;

    const int eolLength = endofline.length();
    const int sepLength = separator.length();
    int sepIdx = 0;
    int eolIdx = 0;

    QStringList row;
    QString value;
    QChar character = ' ';
    while(!textStream->atEnd()){
        *textStream >> character;
        if((character == '\r' || character == '\n') && value.length() == 0) continue;
        value.append(character);

        if(character == separator[sepIdx])
            sepIdx++; else sepIdx = 0;
        if(character == endofline[eolIdx])
            eolIdx++; else eolIdx = 0;

        if(sepIdx == sepLength){
            row.append(value.left(value.length() - sepLength));
            value = "";
        }

        if(eolIdx == eolLength){
            row.append(value.left(value.length() - eolLength));
            value = "";
            rows[rowIdx++] = row;

            if(rowIdx == 100){
                emit addRows(rows,rowIdx);
                rows = new QStringList[100]();
                rowIdx = 0;
            }

            row.clear();
        }
    }

    if(rowIdx != 0) emit addRows(rows,rowIdx);

    emit finished();
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
