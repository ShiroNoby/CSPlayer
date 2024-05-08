#ifndef _CS_Loader_
#define _CS_Loader_

#include <windows.h>
#include <WinBase.h>

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
    
    HANDLE                  path;
    _WIN32_FIND_DATAW       SPath;
    wchar_t                 resoult[MAX_PATH];   
    
    /////////////**************************************\\\\\\\wav
    
    SystemLog( tier2, "CSLoader.h", "34", "load wav");
    path = FindFirstFile( L"../sound/*.wav*", &SPath);
    do {

        if (path == INVALID_HANDLE_VALUE) { //no treck
            ErrorLog( tier2, "CSLoader.h", "37", "FindFirstFile failed", 999 ); //unknow error
            break;
        }


        //func( CSPath[index], resoult);
        func( L"../sound/", resoult);
        std::wstring str = resoult;

        func(SPath.cFileName, resoult);
        str += resoult;

        Playlist.playlist.push_back(str);


    } while (FindNextFile(path, &SPath));

    //check correct path Wav

    FindClose(path);

    /////////////**************************************\\\\\\\mp3

    SystemLog( tier2, "CSLoader.h", "64", "load mp3");
    path = FindFirstFile(L"../sound/*.mp3*", &SPath);
    do {

        if (path == INVALID_HANDLE_VALUE) { //no treck
            ErrorLog( tier2, "CSLoader.h", "67", "FindFirstFile failed", 999 );
            break;
        }


        //func( CSPath[index], resoult);
        func( L"../sound/", resoult);
        std::wstring str = resoult;

        func(SPath.cFileName, resoult);
        str += resoult;

        Playlist.playlist.push_back(str);


    } while (FindNextFile(path, &SPath));

    //check correct path mp3

    FindClose(path);
    
    if( !Playlist.playlist.size() ) {
        ErrorLog( tier2, "CSLoader.h", "87", "not element for playing", 999 );
        newLog.fileWrite();
    }
    
    Playlist.soundcount = Playlist.playlist.size() - 1;
}

#endif //_CS_Loader_