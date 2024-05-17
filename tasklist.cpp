#include "tasklist.h"
#include "ui_entitylist.h"

// Constructor for TaskList
TaskList::TaskList(QWidget* parent): EntityList(parent) {
    qDebug() << "TaskList: Initializing TaskList";
    addToTask_ptr = new AddToTask(); // Create a new AddToTask object
    ui->nameSortBtn->setText("Sort by Staff Name"); // Change the text of the remove button
    ui->idSortBtn->setText("Sort by Model Name"); // Change the text of the remove button

    // Connect the taskAdded signal from addToTask_ptr to a lambda function that loads the task list
    connect(addToTask_ptr, &AddToTask::taskAdded, this, [this]() {
        this->loadList(this->taskType());
    });
}

// Function to add a task
void TaskList::add() {
    addToTask_ptr->setWindowTitle("Maintenance Task: Assign"); // Set the window title
    addToTask_ptr->show(); // Show the addToTask_ptr window
}

// Function to show information about a task
void TaskList::showInfo(const QModelIndex &index) {
    qDebug() << "TaskList: Entering showInfo";

    int row = index.row(); // Get the row number from the index
    // Get the model name from the table view model
    QString modelName = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();

    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) { // If the database is not open
        qDebug() << "TaskList: Database is not open!";
        return;
    }

    // Prepare a query to select all from Vehicle where the model is the model name
    QSqlQuery query(database);
    query.prepare("SELECT * FROM Vehicle WHERE Model = :modelName");
    query.bindValue(":modelName", modelName); // Bind the model name to the query
    if (!query.exec()) { // If the query execution fails
        qDebug() << "TaskList: Failed to execute query(1)" << query.lastError();
        return;
    }

    // If the query returns a result
    if (query.next()) {
        // Get the start date, deadline, finished status, and user ID from the query result
        QString startDate = query.value("StartDate").toString();
        QString deadline = query.value("Deadline").toString();
        QString finished = (query.value("Finished").toInt() == 1) ? "Yes" : "No";
        QString userId = query.value("UserID").toString();

        // Calculate the number of days remaining until the deadline
        QDate deadlineDate = QDate::fromString(deadline, "yyyy-MM-dd");
        int daysRemaining = QDate::currentDate().daysTo(deadlineDate);

        // Prepare a query to select the name and phone from Customer where the user ID is the user ID
        QSqlQuery userQuery(database);
        userQuery.prepare("SELECT Name, Phone FROM Customer WHERE UserID = :userId");
        userQuery.bindValue(":userId", userId); // Bind the user ID to the query
        if (!userQuery.exec()) { // If the query execution fails
            qDebug() << "TaskList: Failed to execute user query(2)" << userQuery.lastError();
            return;
        }

        QString customerName;
        QString customerPhone;

        // If the user query returns a result
        if (userQuery.next()) {
            // Get the customer name and phone from the query result
            customerName = userQuery.value("Name").toString();
            customerPhone = userQuery.value("Phone").toString();
        }

        // Set the text in the txtInfo widget to the task information
        ui->txtInfo->setText("Start Date: " + startDate + "\nDeadline: " + deadline + "\nDays remaining: " + QString::number(daysRemaining) + "\nFinished: " + finished + "\nCustomer name: " + customerName + "\nCustomer's phone number: " + customerPhone);
    }

    qDebug() << "TaskList: Exiting showInfo";
}

// Function to load the task list
void TaskList::loadList(){
    qDebug() << taskType();
    loadList(taskType());
}

// Function to get the task type
QString TaskList::taskType() {
    return "";
}

// Function to load the task list based on the task type
void TaskList::loadList(QString taskType) {
    qDebug() << "TaskList: Entering loadList";
    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) { // If the database is not open
        qDebug() << "TaskList: Database is not open!";
        return;
    }
    model = new QSqlQueryModel(); // Create a new QSqlQueryModel

    // Prepare a query string to select the vehicle model and staff name from Vehicle and Staff
    QString queryString = "SELECT Vehicle.Model, Staff.Name "
                          "FROM Vehicle "
                          "INNER JOIN Staff ON Vehicle.StaffID = Staff.StaffID ";

    // If the task type is "Maintenance", add a WHERE clause to the query string
    if (taskType == "Maintenance") {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 0";
    } else {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 1";
    }

    model->setQuery(queryString, database); // Set the query for the model
    model->setHeaderData(1, Qt::Horizontal, "Staff Name");

    ui->tableView->setModel(model); // Set the model for the table view
    qDebug() << "TaskList: Exiting loadList";
}

// Function to sort the task list by ID
void TaskList::idSort(){
    qDebug() << taskType();
    idSort(taskType());
}

// Function to sort the task list by name
void TaskList::nameSort(){
    qDebug() << taskType();
    nameSort(taskType());
}

// Function to sort the task list by ID based on the task type
void TaskList::idSort(QString taskType) {
    qDebug() << "TaskList: Entering idSort";
    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel(); // Create a new QSqlQueryModel

    // Prepare a query string to select the vehicle model and staff name from Vehicle and Staff
    QString queryString = "SELECT Vehicle.Model, Staff.Name "
                          "FROM Vehicle "
                          "INNER JOIN Staff ON Vehicle.StaffID = Staff.StaffID ";

    // If the task type is "Maintenance", add a WHERE clause and an ORDER BY clause to the query string
    if (taskType == "Maintenance") {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 0 ORDER BY Vehicle.VehicleID";
    } else {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 1 ORDER BY Vehicle.VehicleID";
    }

    model->setQuery(queryString, database); // Set the query for the model
    ui->tableView->setModel(model); // Set the model for the table view
    qDebug() << "TaskList: Exiting idSort";
}

// Function to sort the task list by name based on the task type
void TaskList::nameSort(QString taskType) {
    qDebug() << "TaskList: Entering nameSort";
    // Get the database
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel(); // Create a new QSqlQueryModel

    // Prepare a query string to select the vehicle model and staff name from Vehicle and Staff
    QString queryString = "SELECT Vehicle.Model, Staff.Name "
                          "FROM Vehicle "
                          "INNER JOIN Staff ON Vehicle.StaffID = Staff.StaffID ";

    // If the task type is "Maintenance", add a WHERE clause and an ORDER BY clause to the query string
    if (taskType == "Maintenance") {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 0 ORDER BY Vehicle.Model";
    } else {
        queryString += "WHERE Vehicle.Assigned = 1 AND Vehicle.Finished = 1 ORDER BY Vehicle.Model";
    }

    model->setQuery(queryString, database); // Set the query for the model
    ui->tableView->setModel(model); // Set the model for the table view
    qDebug() << "TaskList: Exiting nameSort";
}

// Destructor for TaskList
TaskList::~TaskList(){
    delete addToTask_ptr; // Delete the addToTask_ptr object
}
