#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qsqldatabase.h"
#include <QMainWindow>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include "storage.h"
#include "car.h"
#include "customer.h"
#include "staff.h"

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


    void on_Car_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    Storage* storage_ptr;
    Car* car_ptr;
    Customer* customer_ptr;
    Staff* staff_ptr;
};
#endif // MAINWINDOW_H
