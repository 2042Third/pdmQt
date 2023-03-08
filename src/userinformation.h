#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QWidget>
#include "PdmRuntimeRef.h"

namespace Ui {
class UserInformation;
}

class UserInformation : public QWidget, public PdmRuntimeRef
{
    Q_OBJECT

public:
    explicit UserInformation(QWidget *parent = nullptr);
    ~UserInformation();

private:
    Ui::UserInformation *ui;
};

#endif // USERINFORMATION_H
