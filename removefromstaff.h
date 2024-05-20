#ifndef REMOVEFROMSTAFF_H
#define REMOVEFROMSTAFF_H

// Include necessary header files
#include <QDialog> // For QDialog class
#include "SQLheader.h" // For SQL related classes
#include "validation.h" // For Validation class
#include <QMessageBox> // For QMessageBox class

// Declare UI namespace and forward declare RemoveFromStaff class in it
namespace Ui {
class RemoveFromStaff;
}

// Declare RemoveFromStaff class, which inherits from QDialog and Validation
class RemoveFromStaff : public QDialog, Validation
{
    Q_OBJECT // Enable QObject features

public:
    // Declare constructor and destructor
    explicit RemoveFromStaff(QWidget *parent = nullptr);
    ~RemoveFromStaff();

    // Declare public member functions
    bool validateUserInput(); // Function to validate user input
    void loadBox(); // Function to load items into combo box
    void showEvent(QShowEvent *event); // Function to handle show event
    friend class TestRemoveFromStaff;

signals:
    void staffRemoved(); // Signal to be emitted when a staff member is removed

private slots:
    // Declare slots for handling UI events
    void on_removeBtn_clicked(); // Slot for remove button click event
    void on_removeList_currentTextChanged(const QString &text); // Slot for change in selected item in combo box

    void on_cancelBtn_clicked();

private:
    // Declare private member variables
    Ui::RemoveFromStaff *ui; // Pointer to UI object
    QSqlDatabase database; // Object for database connection
};

#endif // REMOVEFROMSTAFF_H
