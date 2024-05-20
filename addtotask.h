#ifndef ADDTOTASK_H
#define ADDTOTASK_H

// Include necessary header files
#include <QDialog> // For QDialog class
#include "SQLheader.h" // For SQL related classes
#include "validation.h" // For Validation class
#include <QMessageBox> // For QMessageBox class
#include <QDate> // For QDate class

// Forward declaration of the Ui::AddToTask class
namespace Ui
{
    class AddToTask;
}

// AddToTask class declaration
class AddToTask : public QDialog, Validation // Inherits from QDialog and Validation
{
    Q_OBJECT // Enable Qt's meta-object system

public:
    explicit AddToTask(QWidget *parent = nullptr); // Constructor
    bool validateUserInput(); // Method to validate user input
    void loadBox(); // Method to load the combo boxes
    void showEvent(QShowEvent *event); // Method to handle the show event
    ~AddToTask(); // Destructor
    friend class TestAddToTask;

signals:
    void taskAdded(); // Signal to be emitted when a task is added

private slots:
    void on_modelBox_currentTextChanged(const QString &text); // Slot to handle the currentTextChanged signal of the model combo box

    void on_addBtn_clicked(); // Slot to handle the clicked signal of the add button

    void on_cancelBtn_clicked();

private:
    Ui::AddToTask *ui; // Pointer to the UI
    QSqlDatabase database; // Database object
};

#endif // ADDTOTASK_H
