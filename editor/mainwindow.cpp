#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->console->setReadOnly(true);

    ogl_layout = new QHBoxLayout(ui->frame_ogl);
    ogl_layout->setContentsMargins(0, 0, 0, 0);
    ogl_layout->setSpacing(0);
    ogl_out = new oGL_out(ui->frame_ogl);
    QObject::connect(ogl_out, &oGL_out::print_console,
                     this, &MainWindow::print_console);
    ogl_layout->addWidget(ogl_out);
    ogl_out->show();

    change_mode(draw);
    print_console("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ogl_out;
    delete ogl_layout;
}


void MainWindow::on_drawButton_clicked()
{
    change_mode(draw);
}

void MainWindow::on_selectButton_clicked()
{
    change_mode(sel);
}

void MainWindow::print_console (const std::string &s)
{
    ui->console->insertPlainText("[");
    ui->console->insertPlainText(QTime::currentTime().toString("h:m:s"));
    ui->console->insertPlainText("]> ");
    ui->console->insertPlainText(QString::fromStdString(s));
    ui->console->insertPlainText("\n");
    ui->console->ensureCursorVisible();
}

void MainWindow::change_mode (edit_mode in_mode)
{
    mode = in_mode;
    std::string console = "switched to ";
    switch (in_mode) {
    case draw:
        console += "'draw'";
        ui->text_tool->setText("draw");
        ui->drawButton->setDown(1);
        ui->selectButton->setDown(0);
        break;
    case sel:
        console += "'select'";
        ui->text_tool->setText("select");
        ui->selectButton->setDown(1);
        ui->drawButton->setDown(0);
        break;
    default:
        break;
    }
    console += " mode";
    print_console(console);
}

void MainWindow::on_actionSave_triggered()
{
    if (outfile.is_open()) {
        print_console("fixme::save_when_opened");
    }
    else {
        open_file_dialog(save);
    }
}

void MainWindow::on_actionLoad_triggered()
{
    if (0){
        //fixme::unsaved dialog
    }
    else {
        open_file_dialog(load);
    }
}

void MainWindow::open_file_dialog(flag_saveload flag)
{
    opendialog = new OpenDialog(this, flag);
    QObject::connect(opendialog, &OpenDialog::filename_read,
                     this, &MainWindow::on_opendialog_finish);
    opendialog->show();

    //and where is delete?
}

void MainWindow::on_opendialog_finish(const std::string &filename, flag_saveload flag)
{
    std::string console;
    console = "opening for ";
    if (flag == save)
        console += "save '";
    else
        console += "load '";
    console += filename;
    console += "' ";
    if (!std::filesystem::exists(filename) && flag == load){ // if no file to load
        console += "FAILED: check existing";
        print_console(console);
        return;
    }
    //file exists - reopen as input or no file - create
    outfile.open(filename, outfile.out);
    if (!outfile.is_open()) {
        console += "FAILED";
        print_console(console);
        return;
    }
    console += "SUCCESS";
    print_console(console);
    console.clear();
    //hear load or store processing...
}
