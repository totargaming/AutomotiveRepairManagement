#include "staff.h"
#include "ui_entitylist.h"
Staff::Staff(QWidget *parent): EntityList(parent) {
    qDebug() << "Staff: Initializing Staff";
    loadList();
    addToStaff_ptr = new AddToStaff();
}
void Staff::add() {
    qDebug() << "Staff: add() called";
    addToStaff_ptr->setWindowTitle("Staff: Hire");
    addToStaff_ptr->show();
}

void Staff::remove() {

}

void Staff::showInfo(const QModelIndex &index) {

}

void Staff::loadList() {
    qDebug() << "Staff: Entering loadList";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Staff: Database is not open!";
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery("SELECT StaffID, Name FROM Staff", database);
    ui->tableView->setModel(model);
    qDebug() << "Staff: Exiting loadList";
}

void Staff::idSort() {
    qDebug() << "Staff: Entering idSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT StaffID, Name FROM Staff ORDER BY StaffID", database);
    ui->tableView->setModel(model);
    qDebug() << "Staff: Exiting idSort";
}

void Staff::nameSort() {
    qDebug() << "Staff: Entering nameSort";
    QSqlDatabase database = QSqlDatabase::database("DB");
    model = new QSqlQueryModel();
    model->setQuery("SELECT StaffID, Name FROM Staff ORDER BY Name", database);
    ui->tableView->setModel(model);
    qDebug() << "Staff: Exiting nameSort";
}

Staff::~Staff() {
    qDebug() << "Car: Destructor called";
    delete addToStaff_ptr;
}
