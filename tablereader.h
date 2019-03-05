#ifndef TABLEREADER_H
#define TABLEREADER_H

#include <QObject>
#include <QtCore>

class TableReader : public QObject
{
    Q_OBJECT
    QFile *file;
    QTextStream *textStream;
    QString path;

public:
    explicit TableReader(QObject *parent = nullptr);
    ~TableReader();
    void initFile(QString path);
signals:

public slots:
};

#endif // TABLEREADER_H
