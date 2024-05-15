// Ensure the header file is included only once by the preprocessor
#ifndef REMOVEFROMCUSTOMER_H
#define REMOVEFROMCUSTOMER_H

// Include necessary Qt libraries
#include <QDialog> // Provides functionality to create dialog windows
#include "SQLheader.h" // Custom header file for SQL related operations
#include "validation.h" // Custom header file for input validation
#include <QMessageBox> // Provides functionality to create message box

// Declare a namespace for the User Interface (UI)
namespace Ui {
class RemoveFromCustomer; // Forward declaration of the RemoveFromCustomer class in the Ui namespace
}

// Define the RemoveFromCustomer class, which inherits from QDialog and Validation
class RemoveFromCustomer : public QDialog, Validation
{
    Q_OBJECT // Macro that enables Qt's meta-object system

public:
    // Constructor declaration, takes a QWidget pointer as an argument with a default value of nullptr
    explicit RemoveFromCustomer(QWidget *parent = nullptr);
    
    // Function to validate user input, returns a boolean
    bool validateUserInput();
    
    // Function to load items into a combo box
    void loadBox();
    
    // Overridden function from QWidget to handle show events
    void showEvent(QShowEvent *event);

    // Destructor declaration
    ~RemoveFromCustomer();
    friend class TestRemoveFromCustomer;
    
signals:
    // Signal that is emitted when a customer is removed
    void customerRemoved();

private slots:
    // Slot that is invoked when the current text in the removeList combo box is changed
    void on_removeList_currentTextChanged(const QString &text);

    // Slot that is invoked when the remove button is clicked
    void on_removeBtn_clicked();

private:
    // Pointer to the UI object
    Ui::RemoveFromCustomer *ui;
    
    // Object for handling the SQL database connection
    QSqlDatabase database;
};

// End of the header file inclusion guard
#endif // REMOVEFROMCUSTOMER_H
