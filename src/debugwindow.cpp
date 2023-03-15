#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);

    // After the setup of the designer;
    texts = new QTextEdit(ui->centralwidget);
    texts->setObjectName("textEdit");
    texts->setReadOnly(true);
    ui->verticalLayout->addWidget(texts);
}
void DebugWindow::appendMessage(const QString &message, const QString &color)
{
    QString html = QString("<font color=%1>%2</font>").arg(color, message);
    texts->append(html);
}



DebugWindow::~DebugWindow()
{
    delete ui;
    delete texts;
}

void DebugWindow::on_actionOpen_One_Note_Page_triggered()
{

}

void DebugWindow::setWindowPosition(QPoint &a) {
  move(a);
}

