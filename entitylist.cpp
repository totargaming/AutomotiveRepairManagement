#include "entitylist.h" // Include the header file for the EntityList class
#include "ui_entitylist.h" // Include the header file for the UI of the entity list

// Constructor for the EntityList class, which inherits from QWidget
EntityList::EntityList(QWidget *parent)
    : QWidget(parent) // Initialize the QWidget base class with the parent widget
    , ui(new Ui::EntityList) // Initialize the ui member with a new Ui::EntityList object
{
    ui->setupUi(this); // Set up the UI for this widget
}

// Destructor for the EntityList class
EntityList::~EntityList()
{
    delete ui; // Delete the ui member
}

// Slot for the add button clicked signal
void EntityList::on_addBtn_clicked()
{
    add(); // Call the add function
}

// Slot for the remove button clicked signal
void EntityList::on_removeBtn_clicked()
{
    remove(); // Call the remove function
}

// Slot for the id sort button clicked signal
void EntityList::on_idSortBtn_clicked()
{
    idSort(); // Call the idSort function
}

// Slot for the name sort button clicked signal
void EntityList::on_nameSortBtn_clicked()
{
    nameSort(); // Call the nameSort function
}

// Slot for the table view clicked signal
void EntityList::on_tableView_clicked(const QModelIndex &index)
{
    showInfo(index); // Call the showInfo function with the clicked index
}