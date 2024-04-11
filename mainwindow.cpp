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

}

MainWindow::~MainWindow()
{
    database.close();
    QSqlDatabase::removeDatabase(database.connectionName());
    delete ui;
    delete storage_ptr;
    delete car_ptr;
    delete customer_ptr;
}

void MainWindow::on_Customer_clicked()
{
    customer_ptr->setWindowTitle("Customer");
    customer_ptr->show();
}

void MainWindow::on_Maintenance_clicked()
{

}


void MainWindow::on_Staff_clicked()
{

}


void MainWindow::on_Storage_clicked()
{
    storage_ptr->setWindowTitle("Storage");
    storage_ptr->show();
}


void MainWindow::on_Task_clicked()
{

}



void MainWindow::on_Car_clicked()
{
    car_ptr->setWindowTitle("Car");
    car_ptr->show();
}

