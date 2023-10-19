//
// Created by Yi Yang on 9/8/2023.
//


#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
  QAction *actionAbout;
  QAction *actionSave;
  QAction *actionAccount;
  QAction *actionSettings;
  QAction *actionDebug_Messages;
  QAction *actionOpen;
  QAction *actionZoom_In;
  QAction *actionZoom_Out;
  QWidget *centralwidget;
  QHBoxLayout *horizontalLayout;
  QSplitter *splitter;
  QTabWidget *tabWidget_2;
  QWidget *notesListTab;
  QTabWidget *tabWidget;
  QWidget *notesList;
  QHBoxLayout *horizontalLayout_2;
  QTextEdit *textEdit;
  QMenuBar *menubar;
  QMenu *menuFiles;
  QMenu *menuHelp;
  QMenu *menuUser;
  QMenu *menuEditor;
  QMenu *menuView;
  QStatusBar *statusbar;

  void setupUi(QMainWindow *MainWindow)
  {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName("MainWindow");
    MainWindow->resize(866, 905);
    MainWindow->setDocumentMode(false);
    actionAbout = new QAction(MainWindow);
    actionAbout->setObjectName("actionAbout");
    actionSave = new QAction(MainWindow);
    actionSave->setObjectName("actionSave");
    QIcon icon;
    QString iconThemeName = QString::fromUtf8("document-save");
    if (QIcon::hasThemeIcon(iconThemeName)) {
      icon = QIcon::fromTheme(iconThemeName);
    } else {
      icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    actionSave->setIcon(icon);
    actionAccount = new QAction(MainWindow);
    actionAccount->setObjectName("actionAccount");
    actionSettings = new QAction(MainWindow);
    actionSettings->setObjectName("actionSettings");
    actionDebug_Messages = new QAction(MainWindow);
    actionDebug_Messages->setObjectName("actionDebug_Messages");
    actionOpen = new QAction(MainWindow);
    actionOpen->setObjectName("actionOpen");
    actionZoom_In = new QAction(MainWindow);
    actionZoom_In->setObjectName("actionZoom_In");
    actionZoom_Out = new QAction(MainWindow);
    actionZoom_Out->setObjectName("actionZoom_Out");
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName("centralwidget");
    horizontalLayout = new QHBoxLayout(centralwidget);
    horizontalLayout->setObjectName("horizontalLayout");
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    splitter = new QSplitter(centralwidget);
    splitter->setObjectName("splitter");
    splitter->setOrientation(Qt::Horizontal);
    splitter->setOpaqueResize(true);
    splitter->setHandleWidth(7);
    tabWidget_2 = new QTabWidget(splitter);
    tabWidget_2->setObjectName("tabWidget_2");
    tabWidget_2->setTabsClosable(false);
    tabWidget_2->setMovable(true);
    notesListTab = new QWidget();
    notesListTab->setObjectName("notesListTab");
    tabWidget_2->addTab(notesListTab, QString());
    splitter->addWidget(tabWidget_2);
    tabWidget = new QTabWidget(splitter);
    tabWidget->setObjectName("tabWidget");
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    notesList = new QWidget();
    notesList->setObjectName("notesList");
    horizontalLayout_2 = new QHBoxLayout(notesList);
    horizontalLayout_2->setObjectName("horizontalLayout_2");
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    textEdit = new QTextEdit(notesList);
    textEdit->setObjectName("textEdit");
    QFont font;
    font.setFamilies({QString::fromUtf8(".AppleSystemUIFont")});
    textEdit->setFont(font);

    horizontalLayout_2->addWidget(textEdit);

    tabWidget->addTab(notesList, QString());
    splitter->addWidget(tabWidget);

    horizontalLayout->addWidget(splitter);

#ifdef PDM_USE_FRAMELESSHELPER
    MainWindow->setCentralWidget(centralwidget);
#endif // PDM_USE_FRAMELESSHELPER
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, 866, 37));
    menuFiles = new QMenu(menubar);
    menuFiles->setObjectName("menuFiles");
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName("menuHelp");
    menuUser = new QMenu(menubar);
    menuUser->setObjectName("menuUser");
    menuEditor = new QMenu(menubar);
    menuEditor->setObjectName("menuEditor");
    menuView = new QMenu(menuEditor);
    menuView->setObjectName("menuView");
#ifdef PDM_USE_FRAMELESSHELPER
    MainWindow->setMenuBar(menubar);
#endif // PDM_USE_FRAMELESSHELPER
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName("statusbar");
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuFiles->menuAction());
    menubar->addAction(menuEditor->menuAction());
    menubar->addAction(menuUser->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuFiles->addAction(actionOpen);
    menuFiles->addAction(actionSave);
    menuFiles->addSeparator();
    menuFiles->addAction(actionSettings);
    menuHelp->addAction(actionAbout);
    menuHelp->addSeparator();
    menuHelp->addAction(actionDebug_Messages);
    menuUser->addAction(actionAccount);
    menuEditor->addAction(menuView->menuAction());
    menuView->addAction(actionZoom_In);
    menuView->addAction(actionZoom_Out);

    retranslateUi(MainWindow);

    tabWidget_2->setCurrentIndex(0);
    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi

  void retranslateUi(QMainWindow *MainWindow)
  {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PDM Notes", nullptr));
    actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
    actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
    actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
    actionAccount->setText(QCoreApplication::translate("MainWindow", "Account", nullptr));
    actionSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
#if QT_CONFIG(shortcut)
    actionSettings->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
    actionDebug_Messages->setText(QCoreApplication::translate("MainWindow", "Debug Messages", nullptr));
#if QT_CONFIG(shortcut)
    actionDebug_Messages->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Alt+D", nullptr));
#endif // QT_CONFIG(shortcut)
    actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
    actionZoom_In->setText(QCoreApplication::translate("MainWindow", "Zoom In", nullptr));
#if QT_CONFIG(shortcut)
    actionZoom_In->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+=", nullptr));
#endif // QT_CONFIG(shortcut)
    actionZoom_Out->setText(QCoreApplication::translate("MainWindow", "Zoom Out", nullptr));
#if QT_CONFIG(shortcut)
    actionZoom_Out->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+-", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(accessibility)
    tabWidget_2->setAccessibleName(QCoreApplication::translate("MainWindow", "notes", nullptr));
#endif // QT_CONFIG(accessibility)
    tabWidget_2->setTabText(tabWidget_2->indexOf(notesListTab), QCoreApplication::translate("MainWindow", "Notes", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(notesList), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
    menuFiles->setTitle(QCoreApplication::translate("MainWindow", "Files", nullptr));
    menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    menuUser->setTitle(QCoreApplication::translate("MainWindow", "User", nullptr));
    menuEditor->setTitle(QCoreApplication::translate("MainWindow", "Editor", nullptr));
    menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
  } // retranslateUi

};

namespace Ui {
  class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
