#include "maintenance.h"
#include "ui_maintenance.h"

// Constructor for the Maintenance class
Maintenance::Maintenance(QWidget *parent)
    : QWidget(parent)  // Initialize the QWidget parent class
    , ui(new Ui::Maintenance)  // Initialize the UI for the Maintenance class
{
    ui->setupUi(this);  // Set up the UI for this instance of the class
    calendar = ui->calendarWidget;  // Get the calendar widget from the UI
    loadAll();  // Load all data

    // Initialize the pointers for adding and removing from maintenance
    addToMaintenance_ptr = new AddToMaintenance();
    removeFromMaintenance_ptr = new RemoveFromMaintenance();

    // Connect the signals and slots for adding and removing from maintenance
    connect(addToMaintenance_ptr,&AddToMaintenance::assigned, this, &Maintenance::loadAll);
    connect(removeFromMaintenance_ptr,&RemoveFromMaintenance::maintenanceRemoved, this, &Maintenance::loadAll);
}

// Destructor for the Maintenance class
Maintenance::~Maintenance()
{
    delete ui;  // Delete the UI
    delete addToMaintenance_ptr;  // Delete the pointer for adding to maintenance
    delete removeFromMaintenance_ptr;  // Delete the pointer for removing from maintenance
}
void Maintenance::showEvent(QShowEvent *event) {
    QWidget::showEvent(event); // Call base class implementation
    loadAll(); // Refresh the combo box
    qDebug() << "Maintenance Widget shown";
}

// Function to load all data
void Maintenance::loadAll() {
    qDebug() << "Maintenance: Entering loadAll";  // Debug statement indicating the start of the function
    QString selectedDate = calendar->selectedDate().toString("yyyy-MM-dd");  // Get the selected date from the calendar
    QSqlDatabase database = QSqlDatabase::database("DB");  // Get the database

    // Check if the database is open
    if (!database.isOpen()) {
        qDebug() << "Maintenance: Database is not open!";  // Debug statement indicating the database is not open
        return;
    }

    QSqlQuery query(database);  // Create a query on the database
    query.prepare("SELECT Model FROM Vehicle WHERE date(StartDate) = date(:selectedDate)");  // Prepare the query
    query.bindValue(":selectedDate", selectedDate);  // Bind the selected date to the query

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();  // Debug statement indicating the query failed
        return;
    }

    QSqlQueryModel* startDateModel = new QSqlQueryModel();  // Create a new model for the start date
    startDateModel->setQuery(query);  // Set the query for the model
    ui->startDateTable->setModel(startDateModel);  // Set the model for the start date table

    // Prepare the query for the deadline
    query.prepare("SELECT Model FROM Vehicle WHERE date(Deadline) = date(:selectedDate)");
    query.bindValue(":selectedDate", selectedDate);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();  // Debug statement indicating the query failed
        return;
    }

    QSqlQueryModel* deadlineModel = new QSqlQueryModel();  // Create a new model for the deadline
    deadlineModel->setQuery(query);  // Set the query for the model
    ui->deadlineTable->setModel(deadlineModel);  // Set the model for the deadline table

    qDebug() << "Maintenance: Exiting loadAll";  // Debug statement indicating the end of the function
}

// Function to handle the selection change event of the calendar widget
void Maintenance::on_calendarWidget_selectionChanged()
{
    ui->txtInfo->clear();
    qDebug() <<calendar->selectedDate().toString("yyyy-MM-dd");  // Debug statement showing the selected date
    loadAll();  // Load all data

}

// Function to handle the click event of the add button
void Maintenance::on_addBtn_clicked()
{
    addToMaintenance_ptr->setWindowTitle("Maintenance: Assign");  // Set the window title for the add to maintenance window
    addToMaintenance_ptr->show();  // Show the add to maintenance window
}

// Function to handle the click event of the remove button
void Maintenance::on_removeBtn_clicked()
{
    removeFromMaintenance_ptr->setWindowTitle("Maintenance: Dismiss");  // Set the window title for the remove from maintenance window
    removeFromMaintenance_ptr->show();  // Show the remove from maintenance window
    ui->txtInfo->clear();
}


void Maintenance::on_startDateTable_clicked(const QModelIndex &index)
{
    // Get the model of the vehicle from the clicked cell.
    QString model = index.data().toString();

    // Connect to the database named "DB".
    QSqlDatabase database = QSqlDatabase::database("DB");

    // Check if the database is open.
    if (!database.isOpen()) {
        qDebug() << "Maintenance: Database is not open!";
        return;
    }

    // Prepare a SQL query to get vehicle and staff details based on the model and start date.
    QSqlQuery query(database);
    query.prepare("SELECT Vehicle.*, Staff.Name FROM Vehicle LEFT JOIN Staff ON Vehicle.StaffID = Staff.StaffID WHERE Model = :model AND date(StartDate) = date(:selectedDate)");
    query.bindValue(":model", model);
    query.bindValue(":selectedDate", calendar->selectedDate().toString("yyyy-MM-dd"));

    // Execute the query and check if it was successful.
    if (!query.exec() || !query.next()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();
        return;
    }

    // Get the staff name. If it's empty, set it to "Not assigned".
    QString staff = query.value("Name").toString();
    if (staff.isEmpty()) {
        staff = "Not assigned";
    }

    // Get the start date and format it to "dd/MM/yyyy".
    QString dateAssigned = query.value("StartDate").toString();
    if (!dateAssigned.isEmpty()) {
        dateAssigned = QDate::fromString(dateAssigned, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    // Get the deadline and format it to "dd/MM/yyyy".
    QString deadline = query.value("Deadline").toString();
    if (!deadline.isEmpty()) {
        deadline = QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    // Check if the vehicle is assigned and finished.
    QString assigned = query.value("Assigned").toBool() ? "Yes" : "No";
    QString finished = query.value("Finished").toBool() ? "Yes" : "No";

    // Calculate the remaining days to the deadline.
    QString dateRemaining;
    if (!deadline.isEmpty()) {
        dateRemaining = QString::number(QDate::currentDate().daysTo(QDate::fromString(deadline, "dd/MM/yyyy")));
    }

    // Display the information in the txtInfo field.
    ui->txtInfo->setText("Model: " + model + "\nStaff: " + staff + "\nDateAssigned: " + dateAssigned + "\nDeadline: " + deadline + "\nAssigned: " + assigned + "\nFinished: " + finished + "\nDateRemaining: " + dateRemaining);
}


void Maintenance::on_deadlineTable_clicked(const QModelIndex &index)
{
    QString model = index.data().toString();
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Maintenance: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT Vehicle.*, Staff.Name FROM Vehicle LEFT JOIN Staff ON Vehicle.StaffID = Staff.StaffID WHERE Model = :model AND date(Deadline) = date(:selectedDate)");
    query.bindValue(":model", model);
    query.bindValue(":selectedDate", calendar->selectedDate().toString("yyyy-MM-dd"));
    if (!query.exec() || !query.next()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();
        return;
    }

    QString staff = query.value("Name").toString();
    if (staff.isEmpty()) {
        staff = "Not assigned";
    }

    QString dateAssigned = query.value("StartDate").toString();
    if (!dateAssigned.isEmpty()) {
        dateAssigned = QDate::fromString(dateAssigned, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    QString deadline = query.value("Deadline").toString();
    if (!deadline.isEmpty()) {
        deadline = QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    QString assigned = query.value("Assigned").toBool() ? "Yes" : "No";
    QString finished = query.value("Finished").toBool() ? "Yes" : "No";

    QString dateRemaining;
    if (!deadline.isEmpty()) {
        dateRemaining = QString::number(QDate::currentDate().daysTo(QDate::fromString(deadline, "dd/MM/yyyy")));
    }

    ui->txtInfo->setText("Model: " + model + "\nStaff: " + staff + "\nDateAssigned: " + dateAssigned + "\nDeadline: " + deadline + "\nAssigned: " + assigned + "\nFinished: " + finished + "\nDateRemaining: " + dateRemaining);
}

