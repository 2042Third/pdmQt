//
// Created by Yi Yang on 3/14/2023.
//

#ifndef PDM_QT_CUSTOMWINDOW_H
#define PDM_QT_CUSTOMWINDOW_H
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class CustomTitleBar : public QWidget {
  Q_OBJECT

public:
  explicit CustomTitleBar(QWidget *parent = nullptr)
      : QWidget(parent) {

    // Create a horizontal layout for the custom title bar
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create a QLabel for the window title
    QLabel *titleLabel = new QLabel("Custom Title Bar", this);
    layout->addWidget(titleLabel);

    // Create a custom button for the title bar
    QPushButton *customButton = new QPushButton("Custom", this);
    connect(customButton, &QPushButton::clicked, this, &CustomTitleBar::on_customButton_clicked);
    layout->addWidget(customButton);

    // Add spacer to push the custom button to the right side
    layout->addStretch(1);

    // Create the minimize, maximize, and close buttons
    QPushButton *minimizeButton = new QPushButton("Min", this);
    QPushButton *maximizeButton = new QPushButton("Max", this);
    QPushButton *closeButton = new QPushButton("Close", this);

    connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);
    connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeWindow);
    connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);

    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);
    layout->addWidget(closeButton);
  }

  signals:
    void minimizeWindow();
    void maximizeWindow();
    void closeWindow();

private slots:
  void on_customButton_clicked() {
    // Handle the custom button click event here
    qDebug() << "Custom button clicked";
  }
private:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  QPoint m_dragStartPosition;
  bool m_dragging = false;
};


#endif //PDM_QT_CUSTOMWINDOW_H
