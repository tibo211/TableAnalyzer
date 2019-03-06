#ifndef TABLEVIEWER_H
#define TABLEVIEWER_H

#include <QTableWidget>
#include <QtCore>
#include "tablereader.h"

class TableViewer : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableViewer(QWidget *parent = nullptr);
    ~TableViewer();

    void setFile(QString path);
    TableReader *getReader() const;

public slots:
    void addRows(QStringList *rows, int length);

signals:
    void startRead();

private:
    TableReader *reader;
    QThread readThread;
};

#endif // TABLEVIEWER_H
