#ifndef ADDTOMAINTENANCE_H
#define ADDTOMAINTENANCE_H

// Include necessary header files
#include <QDialog> // For QDialog class
#include "SQLheader.h" // For SQL related operations
#include "validation.h" // For validation related operations
#include <QMessageBox> // For QMessageBox class
#include <QDateEdit> // For QDateEdit class

// Declare the Ui namespace and the AddToMaintenance class
namespace Ui {
class AddToMaintenance;
}

// Declare the AddToMaintenance class, which inherits from QDialog and Validation
class AddToMaintenance : public QDialog, Validation
{
    Q_OBJECT // Enable Qt's meta-object system

public:
    // Declare the constructor and destructor
    explicit AddToMaintenance(QWidget *parent = nullptr);
    ~AddToMaintenance();

    // Declare public methods
    bool validateUserInput(); // Method to validate user input
    void loadBox(); // Method to load the combo box
    void showEvent(QShowEvent *event); // Method to handle the show event

signals:
    void assigned(); // Signal to be emitted when a vehicle is assigned

private slots:
    void on_addBtn_clicked(); // Slot to handle the add button click event

private:
    Ui::AddToMaintenance *ui; // Pointer to the UI
    QSqlDatabase database; // Database object

};

#endif // ADDTOMAINTENANCE_H