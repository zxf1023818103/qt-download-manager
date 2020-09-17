#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"
#include <QFile>
#include <QUrl>
#include <QPushButton>

NewTaskDialog::NewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}

void NewTaskDialog::on_buttonBox_accepted()
{
    const QString &urlText = ui->urlEdit->text();
    const QString &filenameText = ui->filenameEdit->text();

    QUrl url(urlText);

    emit taskCreated(url, filenameText);

    ui->urlEdit->clear();
    ui->filenameEdit->clear();
    close();
}

void NewTaskDialog::on_buttonBox_rejected()
{
    close();
}

void NewTaskDialog::on_urlEdit_textChanged(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty() || ui->filenameEdit->text().isEmpty());
}

void NewTaskDialog::on_filenameEdit_textChanged(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty() || ui->urlEdit->text().isEmpty());
}
