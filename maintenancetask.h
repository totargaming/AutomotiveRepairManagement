#ifndef MAINTENANCETASK_H  // Preprocessor directive to prevent multiple
                           // inclusions of this header file
#define MAINTENANCETASK_H  // Defines MAINTENANCETASK_H symbol to indicate that
                           // this header file has been included

// Include necessary header files
#include "tasklist.h"  // Includes custom header file for the TaskList class

// Define the MaintenanceTask class, which inherits from TaskList
class MaintenanceTask : public TaskList {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit MaintenanceTask(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr

  // Overridden functions from the TaskList class
  void loadList() override;
  QString taskType() override;
  void remove() override;

  // Function to change the status of a task to delivery
  void changeToDelivery(const QModelIndex &index);
  void showEvent(QShowEvent *event);  // Function to handle the show event

  ~MaintenanceTask();  // Destructor declaration

 signals:
  void forwardedToDelivery();  // Signal that is emitted when a task is
                               // forwarded to delivery
};

#endif  // MAINTENANCETASK_H  // End of preprocessor conditional directive