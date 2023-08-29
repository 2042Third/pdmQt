//
// Created by Mike Yang on 2023/8/23.
//

#ifndef PDM_QT_PDM_STATUS_QT_H
#define PDM_QT_PDM_STATUS_QT_H

#include <QObject>

#include "pdm_status.h"



class StatusQt : public QObject {
Q_OBJECT
public:
    StatusQt() = default;

    ~StatusQt() = default;
    void change(PDM::Status::State status) {
      statusInstance.change(status);
      emit statusChanged(statusInstance.text_status());
    }
signals:
    void statusChanged(const QString &status);

private:
    PDM::Status statusInstance;
};
#endif //PDM_QT_PDM_STATUS_QT_H
