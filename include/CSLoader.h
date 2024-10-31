#ifndef _CS_Loader_
#define _CS_Loader_

#include <filesystem>

#include "CSPlaylist.h"

void func( LPCWSTR data, wchar_t* resoult ){    
    int index = 0;
    for( ; data[index]; ++index)
        resoult[index] = (wchar_t)data[index];
    resoult[index] = '\0';
}

class Loader {
    
public:

    void LoadPlaylist( CSPlaylist& );
    
};

void Loader::LoadPlaylist( CSPlaylist& Playlist ){
    SystemLog( tier2, "CSLoader.h", "24", "Loader::LoadPlaylist");
    
	std::filesystem::path path("..\\sound");
    std::filesystem::recursive_directory_iterator rec(path);
    std::filesystem::directory_entry wav(".wav");
	std::filesystem::directory_entry mp3(".mp3");
	
    for (auto p : rec) {
        
        std::filesystem::path tmp(p);
		if((tmp.extension() == wav) || (tmp.extension() == mp3))
			Playlist.playlist.push_back(tmp.wstring());
		
    }
    
    if( !Playlist.playlist.size() ) {
        ErrorLog( tier2, "CSLoader.h", "40", "not element for playing", 999 );
        newLog.fileWrite();
    }
    
    Playlist.soundcount = Playlist.playlist.size() - 1;
}

#endif //_CS_Loader_