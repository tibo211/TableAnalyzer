#ifndef TABLEVIEWER_H
#define TABLEVIEWER_H

#include <QTableWidget>
#include <QHeaderView>
#include <QtCore>
#include <QQueue>
#include "tablereader.h"

class TableViewer : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableViewer(QWidget *parent = nullptr);
    ~TableViewer();

    void setFile(QString path);
    void setTableSize();
    TableReader *getReader() const;

public slots:
    void addRows(QStringList *rows, int length);
    void doneReading();
    void update();

signals:
    void startRead();

private:
    TableReader *reader;
    QThread readThread;
    int *maxColWidth;
    bool isReading;
    QQueue<QStringList> *rowQueue;

};

#endif // TABLEVIEWER_H
