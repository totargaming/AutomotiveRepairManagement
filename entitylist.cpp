#include "entitylist.h"
#include "ui_entitylist.h"

EntityList::EntityList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EntityList)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
}

EntityList::~EntityList()
{
    delete ui;
}




void EntityList::on_addBtn_clicked()
{
    add();
}


void EntityList::on_removeBtn_clicked()
{
    remove();
}


void EntityList::on_idSortBtn_clicked()
{
    idSort();
}


void EntityList::on_nameSortBtn_clicked()
{
    nameSort();
}


void EntityList::on_listWidget_itemClicked(QListWidgetItem *item)
{
    showInfo();
}

