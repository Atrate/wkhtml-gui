#include <QCloseEvent>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>
#include "AboutDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_wkhtmltopdf_path = find_wkhtmltopdf_path();
    m_wkhtmltoimage_path = find_wkhtmltoimage_path();
    m_process_running = false;
    window_setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::window_setup()
{
    if (m_wkhtmltopdf_path.isEmpty())
    {
        qInfo() << tr("Disabling PDF tab due to a lack of whktmltopdf");
        ui->tabPdf->setToolTip(
            tr("Disabled — please install wkhtmltopdf and relaunch this application or choose the installation path from File->Choose Installation Path"));
        ui->tabPdf->setEnabled(false);
    }
    else
    {
        qInfo() << QString(tr("wkhtmltopdf path is valid (") + m_wkhtmltopdf_path + tr("), enabling PDF tab"));
        ui->tabImage->setToolTip("Convert webpages to PDF");
        ui->tabImage->setEnabled(true);
    }

    if (m_wkhtmltoimage_path.isEmpty())
    {
        qInfo() << tr("Disabling image tab due to a lack of whktmltoimage");
        ui->tabImage->setToolTip(
            tr("Disabled — please install wkhtmltoimage and relaunch this application or choose the installation path from File->Choose Installation Path"));
        ui->tabImage->setEnabled(false);
    }
    else
    {
        qInfo() << QString(tr("wkhtmltoimage path is valid (") + m_wkhtmltoimage_path + tr("), enabling image tab"));
        ui->tabImage->setToolTip(tr("Convert webpages to images"));
        ui->tabImage->setEnabled(true);
    }
}

QString MainWindow::find_wkhtmltopdf_path() const
{
    for (QString path :
            {
                QString("/usr/bin/wkhtmltopdf"),
                QString("/usr/local/bin/wkhtmltopdf"),
                QString("/bin/wkhtmltopdf"),
                QString("/sbin/wkhtmltopdf"), // Can't see why someone would have it in /sbin/, but better safe than sorry
                QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/bin/wkhtmltopdf"),
                QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.local/bin/wkhtmltopdf")
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
                QString("/usr/bin/wkhtmltoimage"),
                QString("/usr/local/bin/wkhtmltoimage"),
                QString("/bin/wkhtmltoimage"),
                QString("/sbin/wkhtmltoimage"), // Can't see why someone would have it in /sbin/, but better safe than sorry
                QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/bin/wkhtmltoimage"),
                QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.local/bin/wkhtmltoimage")
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

void MainWindow::on_actionQuit_triggered() const
{
    QApplication::quit();
}

void MainWindow::on_actionwkhtmltopdf_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                        tr("Choose wkhtmltopdf installation location"), QStandardPaths::writableLocation(QStandardPaths::HomeLocation));

    if (!file_path.isEmpty())
    {
        if (QFileInfo(file_path).baseName() != "wkhtmltopdf")
        {
            if (QMessageBox::No == QMessageBox::question(this, tr("File Confirmation"),
                    QString(tr("Are you sure you want to use \"") + file_path + tr("\" as your wkhtmltopdf binary?")), QMessageBox::Yes | QMessageBox::No))
            {
                return;
            }
        }

        m_wkhtmltopdf_path = file_path;
        window_setup();
    }
}

void MainWindow::on_actionwkhtmltoimage_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                        tr("Choose wkhtmltoimage installation location"), QStandardPaths::writableLocation(QStandardPaths::HomeLocation));

    if (!file_path.isEmpty())
    {
        if (QFileInfo(file_path).baseName() != "wkhtmltoimage")
        {
            if (QMessageBox::No == QMessageBox::question(this, tr("File Confirmation"),
                    QString(tr("Are you sure you want to use \"") + file_path + tr("\" as your wkhtmltoimage binary?")), QMessageBox::Yes | QMessageBox::No))
            {
                return;
            }
        }

        m_wkhtmltoimage_path = file_path;
        window_setup();
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (m_process_running)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, tr("Close Confirmation"), tr("A process is still running. Are you sure you want to exit?"),
                QMessageBox::Yes | QMessageBox::No))
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}
