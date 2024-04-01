#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE", "DB");
    database.setDatabaseName("E:/Workspace/AutomotiveRepairManagement/database.db");
    if(!database.open()){
        qDebug() << "Error: Unable to open database..";
    }
    else{
        qDebug() << "Database open successfully..";
    }
    storage_ptr = new Storage();
}

MainWindow::~MainWindow()
{
    database.close();
    QSqlDatabase::removeDatabase(database.connectionName());
    delete ui;
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

