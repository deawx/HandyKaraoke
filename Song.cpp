#include "Song.h"

Song::Song(QObject *parent) : QObject(parent)
{
    sId         = "";
    sName       = "";
    sArtist     = "";
    sKey        = "";
    sTempo      = 0;
    sSongType   = "";
    sLyrics     = "";
    sPath       = "";
}

Song::Song(const Song &s)
{
    sId         = s.sId;
    sName       = s.sName;
    sArtist     = s.sArtist;
    sKey        = s.sKey;
    sTempo      = s.sTempo;
    sSongType   = s.sSongType;
    sLyrics     = s.sLyrics;
    sPath       = s.sPath;
}

Song &Song::operator =(const Song &s)
{
    sId         = s.sId;
    sName       = s.sName;
    sArtist     = s.sArtist;
    sKey        = s.sKey;
    sTempo      = s.sTempo;
    sSongType   = s.sSongType;
    sLyrics     = s.sLyrics;
    sPath       = s.sPath;

    return *this;
}
