#ifndef TASKTABLEMODEL_H
#define TASKTABLEMODEL_H

#include "task.h"
#include <QAbstractTableModel>

class TaskTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TaskTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {
    }

    int rowCount(const QModelIndex &parent) const {
        Q_UNUSED(parent);
        return m_data.size();
    }

    int columnCount(const QModelIndex &parent) const {
        Q_UNUSED(parent);
        return m_horizontalHeader.count();
    }

    QVariant data(const QModelIndex &index, int role) const {
        if (!index.isValid())
            return QVariant();
        if (role == Qt::DisplayRole) {
            int ncol = index.column();
            int nrow =  index.row();
            if (nrow < m_data.size() && ncol < m_horizontalHeader.size()) {
                Task *task = m_data.at(nrow);
                if (ncol == 0) {
                    return task->progress();
                }
                else if (ncol == 1) {
                    return task->url();
                }
                else {
                    return task->filename();
                }
            }
        }
        return QVariant();
    }

    Qt::ItemFlags flags(const QModelIndex &index) const {
        if (!index.isValid())
            return Qt::NoItemFlags;

        Qt::ItemFlags flag = QAbstractItemModel::flags(index);

        return flag;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            return m_horizontalHeader.at(section);
        }
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    Task* lastTask() {
        return m_data.last();
    }

public slots:
    void createTask(const QString &url, const QString &filename, QNetworkReply *reply) {
        Task *task = new Task(this);
        task->setUrl(url);
        task->setFilename(filename);
        task->setNetworkReply(reply);
        m_data.append(task);
        emit layoutChanged();
    }

private:
    const QStringList m_horizontalHeader = { tr("Progress"), tr("URL"), tr("Filename") };

    QVector<Task *> m_data;
};

#endif // TASKTABLEMODEL_H
