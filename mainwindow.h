#ifndef MAINWINDOW_H  // Preprocessor directive to prevent multiple inclusions
                      // of this header file
#define MAINWINDOW_H  // Defines MAINWINDOW_H symbol to indicate that this
                      // header file has been included

// Include necessary header files
#include <QDebug>  // Includes QDebug class for debugging
#include <QGuiApplication>  // Includes QGuiApplication class for GUI application management
#include <QMainWindow>  // Includes QMainWindow class from Qt Widgets module
#include <QScreen>      // Includes QScreen class for screen information

#include "SQLheader.h"  // Includes custom SQLheader file
#include "car.h"        // Includes custom header file for the Car class
#include "customer.h"   // Includes custom header file for the Customer class
#include "deliverytask.h"  // Includes custom header file for the DeliveryTask class
#include "maintenance.h"  // Includes custom header file for the Maintenance class
#include "maintenancetask.h"  // Includes custom header file for the MaintenanceTask class
#include "staff.h"            // Includes custom header file for the Staff class
#include "storage.h"  // Includes custom header file for the Storage class

QT_BEGIN_NAMESPACE  // Begin the Qt namespace
    namespace Ui {
  class MainWindow;  // Forward declaration of the MainWindow class in the Ui
                     // namespace
}
QT_END_NAMESPACE  // End the Qt namespace

    // Define the MainWindow class, which inherits from QMainWindow
    class MainWindow : public QMainWindow {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public
      : MainWindow(QWidget* parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  ~MainWindow();                  // Destructor declaration

 private slots:
  // Slots for various button clicked signals
  void on_Customer_clicked();
  void on_Maintenance_clicked();
  void on_Staff_clicked();
  void on_Storage_clicked();
  void on_Task_clicked();
  void on_Car_clicked();
  void on_exitBtn_clicked();

 private:
  Ui::MainWindow* ui;     // Pointer to the UI for the MainWindow class
  QSqlDatabase database;  // QSqlDatabase object for the database connection
  // Pointers to instances of various classes
  Storage* storage_ptr;
  Car* car_ptr;
  Customer* customer_ptr;
  Staff* staff_ptr;
  Maintenance* maintenance_ptr;
  MaintenanceTask* maintenanceTask_ptr;
  DeliveryTask* deliveryTask_ptr;
};

#endif  // MAINWINDOW_H  // End of preprocessor conditional directive