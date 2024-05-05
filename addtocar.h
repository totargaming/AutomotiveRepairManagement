#ifndef ADDTOCAR_H
#define ADDTOCAR_H

// Include necessary Qt classes and custom header files
#include <QDialog> // Provides functionality to create dialog windows
#include "SQLheader.h" // Custom header file for SQL related operations
#include "validation.h" // Custom header file for input validation
#include <QMessageBox> // Provides functionality to create message box

// Forward declaration of Ui::AddToCar class
// This is done to reduce compile time and prevent circular dependencies
namespace Ui {
class AddToCar;
}

// AddToCar class definition
// It inherits from QDialog (for the dialog window functionality) and Validation (for input validation functionality)
class AddToCar : public QDialog, public Validation
{
    Q_OBJECT // This macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system.

public:
    // Constructor and destructor declaration
    explicit AddToCar(QWidget *parent = nullptr);
    ~AddToCar();

    // Public member function declarations
    bool validateUserInput(); // Function to validate user input
    void reset(); // Function to reset the form
    friend class TestAddToCar;

signals:
    // Signal that is emitted when a car is added
    void carAdded();

private slots:
    // Slot that is connected to the click event of the add button
    void on_addBtn_clicked();

private:
    // Private member variables
    Ui::AddToCar *ui; // Pointer to the user interface
    QSqlDatabase database; // Database object
};

#endif // ADDTOCAR_H
