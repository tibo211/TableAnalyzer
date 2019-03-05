#ifndef TANALYZER_H
#define TANALYZER_H

#include <QObject>

class TAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit TAnalyzer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TANALYZER_H