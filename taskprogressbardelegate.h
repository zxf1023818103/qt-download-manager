#ifndef TASKPROGRESSBARDELEGATE_H
#define TASKPROGRESSBARDELEGATE_H

#include <QApplication>
#include <QItemDelegate>

class TaskProgressBarDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TaskProgressBarDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == 0) {
            QStyleOptionProgressBar progressBarOption;

            int progress = index.model()->data(index).toInt();
            progressBarOption.rect = option.rect.adjusted(0, 0, 0, 0);
            progressBarOption.minimum = 0;
            progressBarOption.maximum = 100;
            progressBarOption.textAlignment = Qt::AlignCenter;
            progressBarOption.progress = progress;
            progressBarOption.text = tr("%1%").arg(progress);
            progressBarOption.textVisible = true;
            QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
        }
        else {
            QItemDelegate::paint(painter, option, index);
        }
    }
};

#endif // TASKPROGRESSBARDELEGATE_H
