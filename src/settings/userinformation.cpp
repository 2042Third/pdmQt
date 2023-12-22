#include "userinformation.h"
#include "ui_userinformation.h"
#include "handler/pdm_qt_helpers.h"
#include <QGridLayout>
#include <QPushButton>

UserInformation::UserInformation(QWidget *parent, PdmRunTime* rtIn  ) :
    QWidget(parent), PdmRunTimeRef(rtIn),
    ui(new Ui::UserInformation)
{
  ui->setupUi(this);

  usernameLabel = new QLabel("Username:");
  emailLabel = new QLabel("Email:");
  creationDateLabel = new QLabel("Account creation date:");

  usernameLineEdit = new QLabel("");
  emailLineEdit = new QLabel("");
  creationDateLineEdit = new QLabel("");

  // Set the line edits(QLabel) to be centered and bold, and
  // labels selectable, and labels' hover mouse cursor to I-beam.
  usernameLineEdit->setAlignment(Qt::AlignCenter);
  usernameLineEdit->setStyleSheet("font-weight: bold;");
  usernameLineEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
  usernameLineEdit->setCursor(Qt::IBeamCursor);

  emailLineEdit->setAlignment(Qt::AlignCenter);
  emailLineEdit->setStyleSheet("font-weight: bold;");
  emailLineEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
  emailLineEdit->setCursor(Qt::IBeamCursor);

  creationDateLineEdit->setAlignment(Qt::AlignCenter);
  creationDateLineEdit->setStyleSheet("font-weight: bold;");
  creationDateLineEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
  creationDateLineEdit->setCursor(Qt::IBeamCursor);

  QPushButton* signOutButton = new QPushButton("Sign Out and Delete Local Data");
  // connect the button's signal to some slot here if you want it to perform some action
  // connect(signOutButton, &QPushButton::clicked, this, &UserInformation::yourFunctionName);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(usernameLabel, 0, 0);
  layout->addWidget(usernameLineEdit, 0, 1);
  layout->addWidget(emailLabel, 1, 0);
  layout->addWidget(emailLineEdit, 1, 1);
  layout->addWidget(creationDateLabel, 2, 0);
  layout->addWidget(creationDateLineEdit, 2, 1);
  layout->addWidget(signOutButton, 3, 0, 1, 2);

  setLayout(layout);
}

UserInformation::~UserInformation()
{
  delete ui;
  // Child widgets will be automatically deleted by Qt. So, there's no need to delete them manually.
}

void UserInformation::displayUserInfo() {
  usernameLineEdit->setText(rt->wt.userinfo.username.c_str());
  emailLineEdit->setText(rt->wt.userinfo.email.c_str());
  creationDateLineEdit->setText(rt->wt.userinfo.ctime.c_str());
}


