#include "tablepls.h"
#include "ui_tablepls.h"

tablePls::tablePls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tablePls)
{
    ui->setupUi(this);
    playlist = new QMediaPlaylist;
}

tablePls::~tablePls()
{
    delete ui;
}

