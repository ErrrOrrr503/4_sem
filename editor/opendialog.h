#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include <QDialog>

namespace Ui {
class OpenDialog;
}

enum flag_saveload {
    save,
    load
};

class OpenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDialog(QWidget *parent, flag_saveload in_flag);
    ~OpenDialog();

private slots:
    void on_opendialog_openButton_clicked();

    void on_opendialog_cancelButton_clicked();

    void on_actionMainAction_triggered();

private:
    Ui::OpenDialog *ui;
    flag_saveload flag;

signals:
    void filename_read(const std::string &filename, flag_saveload flag);
};

#endif // OPENDIALOG_H
