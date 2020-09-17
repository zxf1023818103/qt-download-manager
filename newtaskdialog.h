#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>
#include <QFile>

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QWidget *parent = nullptr);
    ~NewTaskDialog();

signals:
    void taskCreated(const QUrl &url, const QString &file);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_urlEdit_textChanged(const QString &text);

    void on_filenameEdit_textChanged(const QString &text);

private:
    Ui::NewTaskDialog *ui;
};

#endif // NEWTASKDIALOG_H
