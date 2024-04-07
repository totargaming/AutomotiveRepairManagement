#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),storage_ptr(new Storage()), car_ptr(new Car())
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE", "DB");
    database.setDatabaseName("E:/Workspace/AutomotiveRepairManagement/database.db");
    // database.setDatabaseName("/mnt/nvme0n1p5/Workspace/AutomotiveRepairManagement/database.db");
    if(!database.open()){
        qDebug() << "Error: Unable to open database..";
    }
    else{
        qDebug() << "Database open successfully..";
    }
}

MainWindow::~MainWindow()
{
    database.close();
    QSqlDatabase::removeDatabase(database.connectionName());
    delete ui;
    delete storage_ptr;
}

void MainWindow::on_Customer_clicked()
{

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

