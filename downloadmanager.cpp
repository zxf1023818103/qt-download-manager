#include "downloadmanager.h"
#include "task.h"
#include "tasktablemodel.h"
#include "ui_downloadmanager.h"
#include <QFile>

DownloadManager::DownloadManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DownloadManager)
{
    ui->setupUi(this);

    connect(&m_manager, &QNetworkAccessManager::finished,
            this, &DownloadManager::downloadFinished);
    connect(this, &DownloadManager::networkReplyCreated,
            static_cast<TaskTableModel*>(ui->tableView->model()), &TaskTableModel::createTask);
}

DownloadManager::~DownloadManager()
{
    delete m_dialog;
    delete ui;
}

void DownloadManager::doDownload(const QUrl &url, const QString &filename)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);
    reply->setProperty("filename", filename);
    emit networkReplyCreated(url.toString(), filename, reply);
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QString errorString;
        errorString.append(filename).append(": ").append(qPrintable(file.errorString()));
        ui->statusbar->showMessage(errorString);
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        statusBar()->showMessage(reply->errorString());
    }
    else {
        saveToDisk(reply->property("filename").toString(), reply);
        reply->deleteLater();
    }
}

void DownloadManager::on_newTaskButton_clicked()
{
    if (m_dialog == nullptr) {
        m_dialog = new NewTaskDialog(this);
        connect(m_dialog, &NewTaskDialog::taskCreated, this, &DownloadManager::doDownload);
    }
    m_dialog->hide();
    m_dialog->show();
}
