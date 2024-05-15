#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <QWidget> // Include the QWidget class from the Qt Widgets module
#include <QTableWidget> // Include the QTableWidget class from the Qt Widgets module
#include <SQLheader.h> // Include the SQLheader file

namespace Ui {
class EntityList; // Forward declaration of the EntityList class in the Ui namespace
}

// Define the EntityList class, which inherits from QWidget
class EntityList : public QWidget
{
    Q_OBJECT // Use the Q_OBJECT macro to enable signals and slots

public:
    // Constructor, takes a QWidget pointer as an argument with a default value of nullptr
    explicit EntityList(QWidget *parent = nullptr);

    // Pure virtual functions to be implemented by derived classes
    virtual void add() = 0;
    virtual void remove() = 0;
    virtual void showInfo(const QModelIndex &index) = 0;
    virtual void loadList() = 0;
    virtual void idSort() = 0;
    virtual void nameSort() = 0;

    // Destructor
    virtual ~EntityList();

private slots:
    // Slots for button clicked signals
    void on_addBtn_clicked();
    void on_removeBtn_clicked();
    void on_idSortBtn_clicked();
    void on_nameSortBtn_clicked();

    // Slot for the table view clicked signal
    void on_tableView_clicked(const QModelIndex &index);

protected:
    // Protected members
    Ui::EntityList *ui; // Pointer to the UI for the EntityList
    QSqlQueryModel* model; // Pointer to the SQL query model
};

#endif // ENTITYLIST_H
