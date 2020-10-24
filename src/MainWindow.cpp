#include <QDebug>
#include <QFile>
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
        qInfo() << tr("Disabling PDF tab due to a lack of whktmltopdf");
        ui->tabPdf->setToolTip(
            tr("Disabled — please install wkhtmltopdf and relaunch this application or choose the installation path from File->Choose Custom Installation Path"));
        ui->tabPdf->setEnabled(false);
    }
    else
    {
        qInfo() << QString(tr("wkhtmltopdf path is valid (") + wkhtmltopdf_path + tr("), enabling PDF tab"));
        ui->tabImage->setToolTip("Convert webpages to PDF");
        ui->tabImage->setEnabled(true);
    }

    if (wkhtmltoimage_path.isEmpty())
    {
        qInfo() << tr("Disabling image tab due to a lack of whktmltoimage");
        ui->tabImage->setToolTip(
            tr("Disabled — please install wkhtmltoimage and relaunch this application or choose the installation path from File->Choose Custom Installation Path"));
        ui->tabImage->setEnabled(false);
    }
    else
    {
        qInfo() << QString(tr("wkhtmltoimage path is valid (") + wkhtmltoimage_path + tr("), enabling image tab"));
        ui->tabImage->setToolTip(tr("Convert webpages to images"));
        ui->tabImage->setEnabled(true);
    }
}

QString MainWindow::find_wkhtmltopdf_path() const
{
    for (QString path :
            {
                "/usr/bin/wkhtmltopdf",
                "/usr/local/bin/wkhtmltopdf",
                "/bin/wkhtmltopdf",
                "/sbin/wkhtmltopdf" // Can't see why someone would have it in /sbin/, but better safe than sorry
            })
    {
        if (QFile::exists(path))
        {
            return path;
        }
    }
    return "";
}

QString MainWindow::find_wkhtmltoimage_path() const
{
    for (QString path :
            {
                "/usr/bin/wkhtmltoimage",
                "/usr/local/bin/wkhtmltoimage",
                "/bin/wkhtmltoimage",
                "/sbin/wkhtmltoimage" // Can't see why someone would have it in /sbin/, but better safe than sorry
            })
    {
        if (QFile::exists(path))
        {
            return path;
        }
    }
    return "";
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog* about = new AboutDialog(this);
    about->show();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

