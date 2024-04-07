#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qsqldatabase.h"
#include <QMainWindow>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include "storage.h"
#include "entitylist.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Customer_clicked();

    void on_Maintenance_clicked();

    void on_Staff_clicked();

    void on_Storage_clicked();

    void on_Task_clicked();

private:
    Ui::MainWindow *ui;
    Storage* storage_ptr;
    EntityList* entityList_ptr;
    QSqlDatabase database;
};
#endif // MAINWINDOW_H
