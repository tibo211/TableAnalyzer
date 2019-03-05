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

private:
    TableReader *reader;
};

#endif // TABLEVIEWER_H
