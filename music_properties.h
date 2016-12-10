#ifndef MUSIC_PROPERTIES_H
#define MUSIC_PROPERTIES_H

#include <QWidget>

namespace Ui {
class music_properties;
}

class music_properties : public QWidget
{
    Q_OBJECT

public:
    explicit music_properties(QWidget *parent = 0);
    ~music_properties();
    Ui::music_properties *ui;
private:

};

#endif // MUSIC_PROPERTIES_H
