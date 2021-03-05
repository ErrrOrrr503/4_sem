#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "opendialog.h"
#include <fstream>
#include <filesystem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum edit_mode {
    sel,
    draw
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void print_console (const std::string &s);

    void change_mode (edit_mode in_mode);

    void open_file_dialog(flag_saveload flag);

private slots:
    void on_drawButton_clicked();

    void on_selectButton_clicked();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_opendialog_finish(const std::string &filename, flag_saveload flag);

private:
    Ui::MainWindow *ui;
    OpenDialog *opendialog;
    edit_mode mode;
    std::ofstream outfile;
};
#endif // MAINWINDOW_H
