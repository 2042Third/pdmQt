#ifndef PDMRUNTIME_H
#define PDMRUNTIME_H

#include <QObject>

class PdmRunTime : public QObject
{
    Q_OBJECT
public:
    explicit PdmRunTime(QObject *parent = nullptr);

signals:
    void log(const QString &message, const QString &color);
};

#endif // PDMRUNTIME_H
