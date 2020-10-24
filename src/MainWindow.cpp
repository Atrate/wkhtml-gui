#include <QDebug>
#include "AboutDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wkhtmltopdf_path = find_wkhtmltopdf_path();
    wkhtmltoimage_path = find_wkhtmltoimage_path();
    window_setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::window_setup()
{
    if (wkhtmltopdf_path.isEmpty())
    {
        qInfo() << "Disabling PDF tab due to a lack of whktmltopdf";
        ui->tabPdf->setToolTip("Disabled"); // TODO: Write tooltip
        ui->tabPdf->setEnabled(false);
    }

    if (wkhtmltoimage_path.isEmpty())
    {
        qInfo() << "Disabling image tab due to a lack of whktmltoimage";
        ui->tabImage->setToolTip("Disabled"); // TODO: Write tooltip
        ui->tabImage->setEnabled(false);
    }
}

QString MainWindow::find_wkhtmltopdf_path() const
{
    // Temporary solution
    return "/usr/bin/wkhtmltopdf";
}

QString MainWindow::find_wkhtmltoimage_path() const
{
    // Temporary solution
    // return "/usr/bin/wkhtmltoimage";
    return "";
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog* about = new AboutDialog(this);
    about->show();
}
