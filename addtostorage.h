#ifndef ADDTOSTORAGE_H
#define ADDTOSTORAGE_H

// Include necessary header files
#include <QDialog> // For QDialog class
#include "SQLheader.h" // For SQL related operations
#include "validation.h" // For validation related operations
#include <QMessageBox> // For QMessageBox class

// Declare the Ui namespace and the addToStorage class
namespace Ui {
class addToStorage;
}

// Declare the addToStorage class, which inherits from QDialog and Validation
class addToStorage : public QDialog, public Validation
{
    Q_OBJECT // Enable Qt's meta-object system

public:
    // Declare the constructor and destructor
    explicit addToStorage(QWidget *parent = nullptr);
    ~addToStorage();

    // Declare public methods
    bool validateUserInput(); // Method to validate user input
    void reset(); // Method to reset the input fields
    friend class TestAddToStorage;

signals:
    void partAdded(); // Signal to be emitted when a part is added

private slots:
    void on_addBtn_clicked(); // Slot to handle the add button click event

private:
    Ui::addToStorage *ui; // Pointer to the UI
    QSqlDatabase database; // Database object

};

#endif // ADDTOSTORAGE_H
