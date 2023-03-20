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

  // Set labels to be bold and right aligned.
  usernameLabel->setAlignment(Qt::AlignRight); usernameLabel->setFont(QFont("Arial", 10, QFont::Bold));
  emailLabel->setAlignment(Qt::AlignRight); emailLabel->setFont(QFont("Arial", 10, QFont::Bold));
  creationDateLabel->setAlignment(Qt::AlignRight); creationDateLabel->setFont(QFont("Arial", 10, QFont::Bold));

  usernameLineEdit = new QLabel("");
  emailLineEdit = new QLabel("");
  creationDateLineEdit = new QLabel("");

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


