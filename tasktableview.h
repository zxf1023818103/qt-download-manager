#ifndef TASKTABLEVIEW_H
#define TASKTABLEVIEW_H

#include "taskprogressbardelegate.h"
#include "tasktablemodel.h"
#include <QTableView>

class TaskTableView : public QTableView
{
    Q_OBJECT

public:
    explicit TaskTableView(QWidget *parent = nullptr) : QTableView(parent)
    {
        m_model = new TaskTableModel(this);
        this->setModel(m_model);
        m_progressBarDelegate = new TaskProgressBarDelegate(this);
        this->setItemDelegate(m_progressBarDelegate);
        emit m_model->layoutChanged();
        this->setColumnWidth(1, 500);
    }

private:
    TaskProgressBarDelegate *m_progressBarDelegate = nullptr;

    TaskTableModel *m_model = nullptr;

    QVector<QStringList> data;
};

#endif // TASKTABLEVIEW_H
