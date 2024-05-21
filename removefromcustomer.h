#ifndef REMOVEFROMCUSTOMER_H  // Preprocessor directive to prevent multiple
                              // inclusions of this header file
#define REMOVEFROMCUSTOMER_H  // Defines REMOVEFROMCUSTOMER_H symbol to indicate
                              // that this header file has been included

// Include necessary header files
#include <QDialog>      // Includes QDialog class from Qt Widgets module
#include <QMessageBox>  // Includes QMessageBox class for displaying messages

#include "SQLheader.h"   // Includes custom SQLheader file
#include "validation.h"  // Includes custom header file for the Validation class

namespace Ui {
class RemoveFromCustomer;  // Forward declaration of the RemoveFromCustomer
                           // class in the Ui namespace
}

// Define the RemoveFromCustomer class, which inherits from QDialog and
// Validation
class RemoveFromCustomer : public QDialog, Validation {
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public : explicit RemoveFromCustomer(
                   QWidget *parent =
                       nullptr);  // Constructor declaration, takes a QWidget
                                  // pointer as an argument, default is nullptr
  bool validateUserInput();       // Function to validate user input
  void loadBox();                 // Function to load items into a combo box
  void showEvent(QShowEvent *event);    // Overridden function from QWidget to
                                        // handle show events
  ~RemoveFromCustomer();                // Destructor declaration
  friend class TestRemoveFromCustomer;  // Friend class declaration for testing

 signals:
  void customerRemoved();  // Signal that is emitted when a customer is removed

 private slots:
  // Slots for various button clicked signals and text changes
  void on_removeList_currentTextChanged(const QString &text);
  void on_removeBtn_clicked();
  void on_cancelBtn_clicked();

 private:
  Ui::RemoveFromCustomer
      *ui;                // Pointer to the UI for the RemoveFromCustomer class
  QSqlDatabase database;  // QSqlDatabase object for the database connection
};

#endif  // REMOVEFROMCUSTOMER_H  // End of preprocessor conditional directive