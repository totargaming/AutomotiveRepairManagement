#ifndef DELIVERYTASK_H  // Preprocessor directive to prevent multiple inclusions
                        // of this header file
#define DELIVERYTASK_H  // Defines DELIVERYTASK_H symbol to indicate that this
                        // header file has been included

// Include necessary header files
#include "tasklist.h"  // Includes custom header file for the TaskList class

// Define the DeliveryTask class, which inherits from TaskList
class DeliveryTask : public TaskList {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : DeliveryTask(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  QString taskType() override;    // Overrides the taskType function from
                                  // TaskList, returns a QString
  void remove() override;         // Overrides the remove function from TaskList
  void add() override {
  }  // Overrides the add function from TaskList, but provides no implementation
  void showEvent(
      QShowEvent *event);  // Function to handle the show event, takes a pointer
                           // to a QShowEvent as an argument

  ~DeliveryTask();  // Destructor declaration
};

#endif  // DELIVERYTASK_H  // End of preprocessor conditional directive