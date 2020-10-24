#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private:
        QString wkhtmltopdf_path;
        QString wkhtmltoimage_path;

        Ui::MainWindow* ui;
        void window_setup();
        QString find_wkhtmltopdf_path() const;
        QString find_wkhtmltoimage_path() const;

    private slots:
        void on_actionAbout_triggered();


};
#endif // MAINWINDOW_H