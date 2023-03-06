#ifndef PDMRUNTIME_H
#define PDMRUNTIME_H

#include <QObject>
#include <src/handler/pdm_database.h>
#include <src/handler/pdm_status.h>
#include <src/handler/pdm_net.h>


  class PdmRunTime : public QObject,
      public PDM::Status,
      public PDM::network {
  Q_OBJECT
  public:
    explicit PdmRunTime(QObject *parent = nullptr);

  signals:

    void log(const QString &message, const QString &color);
  };
#endif // PDMRUNTIME_H
