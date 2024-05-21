#ifndef ADDTOCAR_H  // Preprocessor directive to prevent multiple inclusions of
                    // this header file
#define ADDTOCAR_H  // Defines ADDTOCAR_H symbol to indicate that this header
                    // file has been included

// Include necessary Qt classes and custom header files
#include <QDialog>  // Includes QDialog class from Qt framework to create dialog windows
#include <QMessageBox>  // Includes QMessageBox class from Qt framework to create message boxes

#include "SQLheader.h"  // Includes custom header file for SQL related operations
#include "validation.h"  // Includes custom header file for input validation

// Forward declaration of Ui::AddToCar class
// This is done to reduce compile time and prevent circular dependencies
namespace Ui {
class AddToCar;  // Forward declaration of AddToCar class inside Ui namespace
}

// AddToCar class definition
// It inherits from QDialog (for the dialog window functionality) and Validation
// (for input validation functionality)
class AddToCar : public QDialog,
                 public Validation  // Class declaration, inheriting from
                                    // QDialog and Validation
{
  Q_OBJECT  // This macro must appear in the private section of a class
            // definition that declares its own signals and slots or that uses
            // other services provided by Qt's meta-object system.

      public :
      // Constructor and destructor declaration
      explicit AddToCar(
          QWidget *parent =
              nullptr);  // Constructor declaration, takes a QWidget pointer as
                         // an argument, default is nullptr
  ~AddToCar();           // Destructor declaration

  // Public member function declarations
  bool
  validateUserInput();  // Function to validate user input, returns a boolean
  void reset();         // Function to reset the form, returns void

  friend class TestAddToCar;  // Declares TestAddToCar as a friend class,
                              // allowing it to access private and protected
                              // members of AddToCar

 signals:
  // Signal that is emitted when a car is added
  void carAdded();  // Signal declaration, emitted when a car is added

 private slots:
  // Slot that is connected to the click event of the add button
  void on_addBtn_clicked();  // Slot declaration, connected to the click event
                             // of the add button

  void on_cancelBtn_clicked();  // Slot declaration, connected to the click
                                // event of the cancel button

 private:
  // Private member variables
  Ui::AddToCar *ui;       // Pointer to the user interface, of type Ui::AddToCar
  QSqlDatabase database;  // Database object, of type QSqlDatabase
};

#endif  // ADDTOCAR_H  // End of preprocessor conditional directive