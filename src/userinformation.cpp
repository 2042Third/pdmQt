#include "userinformation.h"
#include "ui_userinformation.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QString>

UserInformation::UserInformation(QWidget *parent) :
    QWidget(parent), PdmRuntimeRef(),
    ui(new Ui::UserInformation)
{
    ui->setupUi(this);

  QLabel *usernameLabel = new QLabel("Username:");
  QLabel *emailLabel = new QLabel("Email:");
  QLabel *creationDateLabel = new QLabel("Account creation date:");

  QLineEdit *usernameLineEdit = new QLineEdit("");
  QLineEdit *emailLineEdit = new QLineEdit("");
  QLineEdit *creationDateLineEdit = new QLineEdit("");

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(usernameLabel);
  layout->addWidget(usernameLineEdit);
  layout->addWidget(emailLabel);
  layout->addWidget(emailLineEdit);
  layout->addWidget(creationDateLabel);
  layout->addWidget(creationDateLineEdit);

  setLayout(layout);
}

UserInformation::~UserInformation()
{
    delete ui;
}
