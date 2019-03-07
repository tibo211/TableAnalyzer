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

    static QString separator;
    static QString endofline;

    QStringList headers;

    bool addFile(QString path);

private:
    QString path;
    QFile *file;
    QTextStream *textStream;
    QStringList *rows;
    int rowIdx;

signals:
    void addRows(QStringList *rows, int length);
    void finished();

public slots:
    void startRead();
};

#endif // TABLEREADER_H
