#include "task.h"
#include "tasktablemodel.h"
#include <QNetworkReply>

Task::Task(TaskTableModel *parent) : QObject(parent) {
    m_model = parent;
    m_id = m_model->rowCount(m_model->index(0, 0));
}

QString Task::progress() const {
    if (m_bytesTotal != 0) {
        qint64 value = m_bytesReceived * 100 / m_bytesTotal;
        qDebug() << value << "%\t" << m_bytesReceived << "/" << m_bytesTotal;
        return QString::number(value);
    }
    return "0";
}

const QString& Task::filename() const {
    return m_filename;
}

const QString& Task::url() const {
    return m_url;
}

QNetworkReply *Task::networkReply() const {
    return m_networkReply;
}

void Task::setFilename(const QString& filename) {
    m_filename = filename;
}

void Task::setUrl(const QString& url) {
    m_url = url;
}

void Task::setNetworkReply(QNetworkReply *networkReply) {
    m_networkReply = networkReply;
    connect(m_networkReply, &QNetworkReply::downloadProgress, this, &Task::onProgress);
    connect(m_networkReply, &QNetworkReply::finished, this, &Task::onFinished);
}

void Task::onFinished() {
    emit onProgress(m_bytesReceived = m_bytesTotal, m_bytesTotal);
}

void Task::onProgress(qint64 bytesReceived, qint64 bytesTotal) {
    m_bytesTotal = bytesTotal;
    m_bytesReceived = bytesReceived;
    if (m_model != nullptr) {
        emit m_model->layoutChanged();
    }
}
