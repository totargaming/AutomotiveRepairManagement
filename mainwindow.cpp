#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QSQLITE", "DB");
    database.setDatabaseName("E:/Workspace/AutomotiveRepairManagement/database.db");
    // database.setDatabaseName("/mnt/nvme0n1p5/Workspace/AutomotiveRepairManagement/database.db");
    if(!database.open()){
        qDebug() << "MainWindow: Error: Unable to open database..";
        return; // return from the constructor if the database connection fails
    }
    else{
        qDebug() << "MainWindow: Database open successfully..";
    }
    storage_ptr = new Storage();
    car_ptr = new Car();
    customer_ptr = new Customer();
    staff_ptr = new Staff();
    maintenance_ptr = new Maintenance();
    maintenanceTask_ptr = new MaintenanceTask();
    deliveryTask_ptr = new DeliveryTask();

}

MainWindow::~MainWindow()
{
    database.close();
    QSqlDatabase::removeDatabase(database.connectionName());
    delete ui;
    delete storage_ptr;
    delete car_ptr;
    delete customer_ptr;
    delete staff_ptr;
    delete maintenance_ptr;
    delete maintenanceTask_ptr;
    delete deliveryTask_ptr;
}

void MainWindow::on_Customer_clicked()
{
    customer_ptr->setWindowTitle("Customer");
    customer_ptr->show();
}

void MainWindow::on_Maintenance_clicked()
{
    maintenance_ptr->setWindowTitle("Customer");
    maintenance_ptr->show();
}


void MainWindow::on_Staff_clicked()
{
    staff_ptr->setWindowTitle("Staff");
    staff_ptr->show();
}


void MainWindow::on_Storage_clicked()
{
    storage_ptr->setWindowTitle("Storage");
    storage_ptr->show();
}


void MainWindow::on_Task_clicked()
{
    // Get the primary screen's geometry
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    // Calculate the width, height, and positioning for both windows
    int windowWidth = 604; // Adjust to your window width
    int windowHeight = 396; // Adjust to your window height
    int gap = 10; // Adjust the gap as needed

    // Calculate the position for the first window (centered)
    int x1 = (screenGeometry.width() - (windowWidth * 2 + gap)) / 2;
    int y1 = (screenGeometry.height() - windowHeight) / 2;

    // Calculate the position for the second window (next to the first window)
    int x2 = x1 + windowWidth + gap;

    // Set the geometry for the first window
    maintenanceTask_ptr->setGeometry(x1, y1, windowWidth, windowHeight);

    // Set the geometry for the second window
    deliveryTask_ptr->setGeometry(x2, y1, windowWidth, windowHeight);

    maintenanceTask_ptr->setWindowTitle("Maintenance Task Window");
    deliveryTask_ptr->setWindowTitle("Delivery Task Window");

    maintenanceTask_ptr->show();
    deliveryTask_ptr->show();
}



void MainWindow::on_Car_clicked()
{
    car_ptr->setWindowTitle("Car");
    car_ptr->show();
}

