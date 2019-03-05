#ifndef TABLEREADER_H
#define TABLEREADER_H

#include <QObject>

class TableReader : public QObject
{
    Q_OBJECT
public:
    explicit TableReader(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TABLEREADER_H