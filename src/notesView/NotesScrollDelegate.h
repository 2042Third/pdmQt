//
// Created by Yi Yang on 5/10/2023.
//

#ifndef PDM_QT_NOTESSCROLLDELEGATE_H
#define PDM_QT_NOTESSCROLLDELEGATE_H


#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>

class NotesScrollDelegate : public QStyledItemDelegate {
public:
  using QStyledItemDelegate::QStyledItemDelegate;

  QIcon icon = QIcon(":/images/icon/file.svg");
  QPixmap pixmap = icon.pixmap(QSize(25, 25));

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
  {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // System pallete
    QPalette palette = QApplication::palette();

// get the color for the window text (usually this is the text color)
    QColor textColor = palette.color(QPalette::WindowText);

// get the color for the window background
    QColor backgroundColor = palette.color(QPalette::Window);

    // Draw item background
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, opt.widget);

    // Draw the icon
    QRect iconRect = QRect(option.rect.topLeft() + QPoint(5, (option.rect.height() - pixmap.height()) / 2), pixmap.size());
    painter->setBrush(textColor); // Added to draw the icon according to the system theme.
    painter->drawPixmap(iconRect, pixmap);

    // Adjust the rect for the text
    QRect textRect = option.rect.adjusted(pixmap.width() + 18, 0, 0, 0); // Adjust the left margin

    auto note = index.data(Qt::DisplayRole).toString();
    auto noteParts = note.split("\n\n");

    QFont font = painter->font();
    int originalPointSize = font.pointSize();
    font.setPointSize(14);
    painter->setFont(font);

    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, noteParts[0]);

    font.setPointSize(10);  // Change the size back or to a different value

    painter->setFont(font);
    painter->setPen(Qt::gray);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, noteParts[1]);
    painter->setPen(textColor);

    font.setPointSize(originalPointSize);
    painter->setFont(font);

  }

  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
  {
    return QSize(200, 50);  // Change the size to your preferred values
  }
};


#endif //PDM_QT_NOTESSCROLLDELEGATE_H
