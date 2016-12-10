#include "music_properties.h"
#include "ui_music_properties.h"

music_properties::music_properties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music_properties)
{
    ui->setupUi(this);
}

music_properties::~music_properties()
{
    delete ui;
}
