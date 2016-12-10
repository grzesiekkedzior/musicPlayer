#ifndef GET_TAG_H
#define GET_TAG_H

#include <QWidget>
#include <QString>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/audioproperties.h>
#include <taglib/attachedpictureframe.h>
#include <QTime>
#include <taglib/mpegfile.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/id3v2tag.h>
#include <taglib/mp4file.h>
#include <taglib/mp4tag.h>
#include <taglib/mp4coverart.h>


class get_tag : public QWidget
{
    Q_OBJECT
public:
    explicit get_tag(QWidget *parent = 0);

    QString gettags_title(QString mediafile);
    QString gettags_artist(QString mediafile);
    QString gettags_album(QString mediafile);
    QString gettags_time(QString mediafile);
    QString gettags_genre(QString mediafile);
    QString gettags_bitrate(QString mediafile);
    QString gettags_sampleRate(QString mediafile);
    QString gettags_year(QString mediafile);
    QImage gettags_cover(QString mediafile);

signals:

public slots:
};

#endif // GET_TAG_H
