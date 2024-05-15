// Include the necessary header files.
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Define the constructor for the MainWindow class. It inherits from QMainWindow.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    // Set up the user interface for this window.
    ui->setupUi(this);
    // Add a SQLite database connection named "DB".
    database = QSqlDatabase::addDatabase("QSQLITE", "DB");
    // Set the database name (i.e., the path to the database file).
    database.setDatabaseName("E:\\Workspace\\AutomotiveRepairManagement\\database.db");
    // Try to open the database.
    if(!database.open()){
        // If the database fails to open, output a debug message and return from the constructor.
        qDebug() << "MainWindow: Error: Unable to open database..";
        return;
    }
    else{
        // If the database opens successfully, output a debug message.
        qDebug() << "MainWindow: Database open successfully..";
    }
    // Initialize the pointers to the various classes.
    storage_ptr = new Storage();
    car_ptr = new Car();
    customer_ptr = new Customer();
    staff_ptr = new Staff();
    maintenance_ptr = new Maintenance();
    maintenanceTask_ptr = new MaintenanceTask();
    deliveryTask_ptr = new DeliveryTask();
    connect(maintenanceTask_ptr, &MaintenanceTask::forwardedToDelivery, this, [this]() {
        this->deliveryTask_ptr->loadList();
    });}

// Define the destructor for the MainWindow class.
MainWindow::~MainWindow()
{
    // Close the database connection and remove it.
    database.close();
    QSqlDatabase::removeDatabase(database.connectionName());
    // Delete the user interface and the pointers to the various classes.
    delete ui;
    delete storage_ptr;
    delete car_ptr;
    delete customer_ptr;
    delete staff_ptr;
    delete maintenance_ptr;
    delete maintenanceTask_ptr;
    delete deliveryTask_ptr;
}

// Define the slot for the Customer button click event.
void MainWindow::on_Customer_clicked()
{
    // Set the window title and show the window.
    customer_ptr->setWindowTitle("Customer");
    customer_ptr->show();
}

// Define the slot for the Maintenance button click event.
void MainWindow::on_Maintenance_clicked()
{
    // Set the window title and show the window.
    maintenance_ptr->setWindowTitle("Customer");
    maintenance_ptr->show();
}

// Define the slot for the Staff button click event.
void MainWindow::on_Staff_clicked()
{
    // Set the window title and show the window.
    staff_ptr->setWindowTitle("Staff");
    staff_ptr->show();
}

// Define the slot for the Storage button click event.
void MainWindow::on_Storage_clicked()
{
    // Set the window title and show the window.
    storage_ptr->setWindowTitle("Storage");
    storage_ptr->show();
}

// Define the slot for the Task button click event.
void MainWindow::on_Task_clicked()
{
    // Get the primary screen's geometry.
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    // Calculate the width, height, and positioning for both windows.
    int windowWidth = 604; // Adjust to your window width.
    int windowHeight = 396; // Adjust to your window height.
    int gap = 10; // Adjust the gap as needed.

    // Calculate the position for the first window (centered).
    int x1 = (screenGeometry.width() - (windowWidth * 2 + gap)) / 2;
    int y1 = (screenGeometry.height() - windowHeight) / 2;

    // Calculate the position for the second window (next to the first window).
    int x2 = x1 + windowWidth + gap;

    // Set the geometry for the first window.
    maintenanceTask_ptr->setGeometry(x1, y1, windowWidth, windowHeight);

    // Set the geometry for the second window.
    deliveryTask_ptr->setGeometry(x2, y1, windowWidth, windowHeight);

    // Set the window titles and show the windows.
    maintenanceTask_ptr->setWindowTitle("Maintenance Task Window");
    deliveryTask_ptr->setWindowTitle("Delivery Task Window");
    maintenanceTask_ptr->show();
    deliveryTask_ptr->show();
}

// Define the slot for the Car button click event.
void MainWindow::on_Car_clicked()
{
    // Set the window title and show the window.
    car_ptr->setWindowTitle("Car");
    car_ptr->show();
}
