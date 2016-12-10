#include "get_tag.h"

get_tag::get_tag(QWidget *parent) : QWidget(parent)
{

}
QString get_tag::gettags_title(QString mediafile)
{
    TagLib::FileRef file(mediafile.toStdString().c_str());
    TagLib::String title_string = file.tag()->title();
    QString title = QString::fromStdWString(title_string.toWString());
    return title;
}

QString get_tag::gettags_artist(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::String artist_string = file.tag()->artist();
    QString artist = QString::fromStdWString(artist_string.toWString());
    return artist;
}

QString get_tag::gettags_album(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::String album_string = file.tag()->album();
    QString album = QString::fromStdWString(album_string.toWString());

    return album;
}

QString get_tag::gettags_time(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::uint lenght = file.audioProperties()->lengthInSeconds();
    QString format = "mm:ss";
    QTime time(0,0);
    time = time.addSecs(lenght);


    //time = QString::number(lenght);
    return time.toString(format);;
}

QString get_tag::gettags_genre(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::String genre_string = file.tag()->genre();
    QString genre = QString::fromStdWString(genre_string.toWString());
    return genre;
}

QString get_tag::gettags_bitrate(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::uint properties_string = file.audioProperties()->bitrate();
    QString bitrate;
    bitrate.setNum(properties_string);
    return bitrate;

}

QString get_tag::gettags_sampleRate(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::uint properties_string = file.audioProperties()->sampleRate();
    QString sampleRate;
    sampleRate.setNum(properties_string);
    return sampleRate;
}

QString get_tag::gettags_year(QString mediafile)
{
    TagLib::FileRef file(mediafile.toUtf8());
    TagLib::uint year_string = file.tag()->year();
    QString year;
    year.setNum(year_string);
    return year;
}

QImage get_tag::gettags_cover(QString mediafile)
{
    TagLib::MPEG::File file(mediafile.toUtf8());
    TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);
    TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");
       if(frameList.isEmpty()) {
           QImage p(":/image/disc_cover.png");
           return p;
       }

       TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

       QImage coverQImg;
       coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
        if(!coverQImg.isNull())
        {
            return coverQImg;
        }



}


