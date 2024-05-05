// This is the header guard. It prevents the header file from being included more than once in the same file.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Include the necessary header files.
#include "SQLheader.h"

#include <QMainWindow>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include "storage.h"
#include "car.h"
#include "customer.h"
#include "staff.h"
#include "maintenance.h"
#include "maintenancetask.h"
#include "deliverytask.h"

// Begin the Qt namespace.
QT_BEGIN_NAMESPACE
namespace Ui {
// Forward declare the MainWindow class in the Ui namespace.
class MainWindow;
}
// End the Qt namespace.
QT_END_NAMESPACE

// Declare the MainWindow class, which inherits from QMainWindow.
class MainWindow : public QMainWindow
{
    // This macro declares several member functions that are used by Qt's meta-object system.
    Q_OBJECT

public:
    // Declare the constructor and destructor for the MainWindow class.
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Declare slots for the click events of the various buttons.
    void on_Customer_clicked();
    void on_Maintenance_clicked();
    void on_Staff_clicked();
    void on_Storage_clicked();
    void on_Task_clicked();
    void on_Car_clicked();

private:
    // Declare a pointer to the MainWindow class in the Ui namespace.
    Ui::MainWindow *ui;
    // Declare a QSqlDatabase object for the database connection.
    QSqlDatabase database;
    // Declare pointers to the various classes.
    Storage* storage_ptr;
    Car* car_ptr;
    Customer* customer_ptr;
    Staff* staff_ptr;
    Maintenance* maintenance_ptr;
    MaintenanceTask* maintenanceTask_ptr;
    DeliveryTask* deliveryTask_ptr;
};

// This is the end of the header guard.
#endif // MAINWINDOW_H
