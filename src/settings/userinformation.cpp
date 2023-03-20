#include "userinformation.h"
#include "ui_userinformation.h"
#include "handler/pdm_qt_helpers.h"
#include <QWidget>
#include <QString>

UserInformation::UserInformation(QWidget *parent) :
    QWidget(parent), PdmRuntimeRef(),
    ui(new Ui::UserInformation)
{
    ui->setupUi(this);

  usernameLabel = new QLabel("Username:");
  emailLabel = new QLabel("Email:");
  creationDateLabel = new QLabel("Account creation date:");

  usernameLineEdit = new QLabel("");
  emailLineEdit = new QLabel("");
  creationDateLineEdit = new QLabel("");

  // Set the line edits(QLabel) to be centered and bold. Also make these labels selectable.
  usernameLineEdit->setAlignment(Qt::AlignCenter); usernameLineEdit->setStyleSheet("font-weight: bold;"); usernameLineEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
  emailLineEdit->setAlignment(Qt::AlignCenter); emailLineEdit->setStyleSheet("font-weight: bold;"); emailLineEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
  creationDateLineEdit->setAlignment(Qt::AlignCenter); creationDateLineEdit->setStyleSheet("font-weight: bold;"); creationDateLineEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

  layout = new QVBoxLayout;
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

  delete usernameLabel;
  delete emailLabel;
  delete creationDateLabel;
  delete usernameLineEdit;
  delete emailLineEdit;
  delete creationDateLineEdit;
  delete layout;
}

void UserInformation::displayUserInfo() {
  usernameLineEdit->setText(rt->wt.userinfo.username.c_str());
  emailLineEdit->setText(rt->wt.userinfo.email.c_str());
  creationDateLineEdit->setText(rt->wt.userinfo.ctime.c_str());
}


