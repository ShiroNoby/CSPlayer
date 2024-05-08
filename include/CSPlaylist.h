#ifndef _CS_Playlist_
#define _CS_Playlist_

#include "CSError.h"

class CSPlaylist{
    
    CSPlaylist( const CSPlaylist& ) = delete;
    CSPlaylist& operator=( const CSPlaylist& ) = delete;
    
    CSPlaylist( CSPlaylist&& ) = delete;
    CSPlaylist& operator=( CSPlaylist&& ) = delete;
    
public:

    CSPlaylist(){}
    ~CSPlaylist(){}
    
    const std::wstring& now();
    const std::wstring& next();
    const std::wstring& prev();
    
    std::vector<std::wstring> playlist;
    int soundcount; //init post init playlist with  playlist.size()
};

const std::wstring& CSPlaylist::now(){
    SystemLog( tier3, "CSPlaylist.h", "27", "CSPlaylist::now()");
    
    if( !soundcount ){
        ErrorLog( tier3, "CSPlaylist.h", "31", "error", 999 ); //unknow error;
    }
    
    return playlist[soundcount];
}

const std::wstring& CSPlaylist::next(){ 
    SystemLog( tier3, "CSPlaylist.h", "37", "CSPlaylist::next()");
   
    ++soundcount;
    if( soundcount >= playlist.size() ) soundcount = 0;    
    
    return playlist[soundcount];
}

const std::wstring& CSPlaylist::prev(){
    SystemLog( tier3, "CSPlaylist.h", "48", "CSPlaylist::prev()");
    
    --soundcount;
    if (soundcount < 0) soundcount = playlist.size() - 1;    
    
    return playlist[soundcount];
}

#endif //_CS_Playlist_