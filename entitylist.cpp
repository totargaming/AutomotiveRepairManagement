#include "entitylist.h"
#include "ui_entitylist.h"

EntityList::EntityList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EntityList)
{
    ui->setupUi(this);
}

EntityList::~EntityList()
{
    delete ui;
}
