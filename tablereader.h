#ifndef TABLEREADER_H
#define TABLEREADER_H

#include <QObject>
#include <QtCore>
#include <QMessageBox>

class TableReader : public QObject
{
    Q_OBJECT
public:
    explicit TableReader(QObject *parent = nullptr);
    ~TableReader();

private:
    QString path;
    QFile *file;
    QTextStream *textStream;
    bool addFile(QString path);

signals:

public slots:
};

#endif // TABLEREADER_H
