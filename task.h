#ifndef TASK_H
#define TASK_H

#include <QObject>

class TaskTableModel;
class QNetworkReply;

class Task : public QObject
{
    Q_OBJECT

public:
    explicit Task(TaskTableModel *parent = nullptr);

    QString progress() const;

    const QString& filename() const;

    const QString& url() const;

    QNetworkReply *networkReply() const;

    void setFilename(const QString& filename);

    void setUrl(const QString& url);

    void setNetworkReply(QNetworkReply *networkReply);

public slots:
    void onProgress(qint64 bytesReceived, qint64 bytesTotal);

    void onFinished();

private:
    int m_id;

    TaskTableModel *m_model;

    QNetworkReply *m_networkReply;

    qint64 m_bytesReceived = 0, m_bytesTotal = 100;

    QString m_filename, m_url;
};

#endif // TASK_H
