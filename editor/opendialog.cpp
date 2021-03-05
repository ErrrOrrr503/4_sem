#include "opendialog.h"
#include "ui_opendialog.h"

OpenDialog::OpenDialog(QWidget *parent, flag_saveload in_flag) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    flag = in_flag;
}

OpenDialog::~OpenDialog()
{
    delete ui;
}

void OpenDialog::on_opendialog_openButton_clicked()
{
    std::string filename = ui->filename->toPlainText().toStdString();
    emit filename_read(filename, flag);
    close();
}

void OpenDialog::on_opendialog_cancelButton_clicked()
{
    close();
}

void OpenDialog::on_actionMainAction_triggered()
{
    on_opendialog_openButton_clicked();
}
