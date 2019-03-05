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
    static char *encoding;

    QStringList headers;

    bool addFile(QString path);

private:
    QString path;
    QFile *file;
    QTextStream *textStream;


signals:

public slots:
};

#endif // TABLEREADER_H
