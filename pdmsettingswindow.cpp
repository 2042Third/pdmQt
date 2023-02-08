#include "pdmsettingswindow.h"
#include "ui_pdmsettingswindow.h"

PdmSettingsWindow::PdmSettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PdmSettingsWindow)
{
    ui->setupUi(this);
}

PdmSettingsWindow::~PdmSettingsWindow()
{
    delete ui;
}
