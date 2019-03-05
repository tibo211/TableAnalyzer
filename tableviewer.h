#ifndef TABLEVIEWER_H
#define TABLEVIEWER_H

#include <QTableWidget>
#include <QtCore>

class TableViewer : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableViewer(QWidget *parent = nullptr);
    ~TableViewer();

    void closing();
};

#endif // TABLEVIEWER_H
