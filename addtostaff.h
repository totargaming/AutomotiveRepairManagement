#ifndef ADDTOSTAFF_H
#define ADDTOSTAFF_H

// Include necessary header files
#include <QDialog> // For QDialog class
#include "SQLheader.h" // For SQL related operations
#include "validation.h" // For validation related operations
#include <QMessageBox> // For QMessageBox class

// Declare the Ui namespace and the AddToStaff class
namespace Ui {
class AddToStaff;
}

// Declare the AddToStaff class, which inherits from QDialog and Validation
class AddToStaff : public QDialog, public Validation
{
    Q_OBJECT // Enable Qt's meta-object system

public:
    // Declare the constructor and destructor
    explicit AddToStaff(QWidget *parent = nullptr);
    ~AddToStaff();

    // Declare public methods
    bool validateUserInput() override; // Method to validate user input, overrides the method from Validation
    void reset(); // Method to reset the input fields
    friend class TestAddToStaff;

signals:
    void staffAdded(); // Signal to be emitted when a staff member is added

private slots:
    void on_addBtn_clicked(); // Slot to handle the add button click event

    void on_cancelBtn_clicked();

private:
    Ui::AddToStaff *ui; // Pointer to the UI
    QSqlDatabase database; // Database object

};

#endif // ADDTOSTAFF_H
