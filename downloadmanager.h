#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QMainWindow>

#include <QtCore>
#include <QtNetwork>

#include "newtaskdialog.h"
#include "taskprogressbardelegate.h"

QT_BEGIN_NAMESPACE
class QSslError;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class DownloadManager; }
QT_END_NAMESPACE

class Task;

class DownloadManager : public QMainWindow
{
    Q_OBJECT
public:
    DownloadManager(QWidget *parent = nullptr);

    ~DownloadManager();

    bool saveToDisk(const QString &filename, QIODevice *data);

signals:
    void networkReplyCreated(const QString &url, const QString &filename, QNetworkReply *reply);

public slots:
    void doDownload(const QUrl &url, const QString &filename);

    void downloadFinished(QNetworkReply *reply);

private slots:
    void on_newTaskButton_clicked();

private:
    Ui::DownloadManager *ui;

    QNetworkAccessManager m_manager;

    NewTaskDialog *m_dialog = nullptr;
};
#endif // DOWNLOADMANAGER_H
