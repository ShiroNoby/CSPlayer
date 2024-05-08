#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include <windows.h>
#include <WinBase.h>
#include <iostream>
#include <vector>

///////**********************************************************************\\\\\\\\config
enum error {
    success = 0,
    no_imput_argument = 100,
    fail_load_WAV = 200,
    fail_load_png = 300
};

int soundcount = 0;

LPCWSTR dir1 = L"../WAV/*.wav*";   // for search
LPCWSTR dir2 = L"../WAV/";         // for add

char resoult[MAX_PATH];
HANDLE path;

///////**********************************************************************\\\\\\\\

void func( LPCWSTR data, char* resoult ){    
    int index = 0;
    for( ; data[index]; ++index)
        resoult[index] = (char)data[index];
    resoult[index] = '\0';
}

int main(){  
    ///////**********************************************************************\\\\\\\\playlist
    std::vector<sf::String> playlist;      
    
    _WIN32_FIND_DATAW SPath;
    path = FindFirstFile(dir1, &SPath);
    do{
        func(dir2, resoult);
        std::string str = resoult;

        func(SPath.cFileName, resoult);
        str += resoult;

        std::cout << str.data() << std::endl;

        playlist.push_back(str);

        if(path == INVALID_HANDLE_VALUE)//no treck
            break;
    }while( FindNextFile(path, &SPath) );

    sf::SoundBuffer sb;
    sf::Sound sound;

    //first trek
    if ( !sb.loadFromFile(playlist[soundcount]) ){
        std::cout << fail_load_WAV << std::endl;
        return fail_load_WAV;
    }
    sound.setBuffer(sb);

    ///////**********************************************************************\\\\\\\\window
    
    //make window 300,100
    sf::RenderWindow window(sf::VideoMode(300,100),"test");

    ///////**********************************************************************\\\\\\\\player

    //load texture1
    sf::Texture texture1;
    if( !texture1.loadFromFile("../elements/play.png" ) ){
        std::cout << fail_load_png << std::endl;
        return fail_load_png;
    }    

    //make some sprite
    sf::Sprite play(  texture1, sf::IntRect( { 11, 11 } , { 51, 56  } )); 
    sf::Sprite pause( texture1, sf::IntRect( { 70, 11 } , { 35, 45 } )); 
    sf::Sprite next(  texture1, sf::IntRect( { 116, 11 }, { 64, 45 } )); 
    sf::Sprite prev(  texture1, sf::IntRect( { 180, 11 }, { -64, 45 } )); 

    //move some sprite
    play.setPosition( { 129, 28 } );
    pause.setPosition({ 129, 28 });
    next.setPosition( { 205, 28 });
    prev.setPosition( { 24, 28 });

    //play.setTextureRect(sf::IntRect());

    window.clear(sf::Color::Green);

    bool PlaySound = false;

    //draw sprite
    if( PlaySound ) {        
        window.draw(pause);
    }else{
        window.draw(play);
    }
    window.draw(next);
    window.draw(prev);

    window.display();

    ///////**********************************************************************\\\\\\\\logic

    while(window.isOpen()){
        sf::Event event;

        //ген-сообщ
        while (window.pollEvent(event)){
            switch( event.type ){
                case sf::Event::Closed: { window.close(); }
                case sf::Event::MouseButtonPressed: {
                    float x = event.mouseButton.x;
                    float y = event.mouseButton.y;

                    if( PlaySound ) {
                        //pause
                        if (pause.getGlobalBounds().contains(x, y)) {
                            PlaySound = false;
                            std::cout << "pause" << std::endl;

                            //somthing
                            sound.pause();

                            window.clear(sf::Color::Green);
                            window.draw(play);
                            window.draw(next);
                            window.draw(prev);
                            window.display();
                            break;
                        }
                    }else{ 
                        //play
                        if (play.getGlobalBounds().contains(x, y)) {
                            PlaySound = true;
                            std::cout << "play" << std::endl;

                            //somthing
                            sound.play();

                            window.clear(sf::Color::Green);
                            window.draw(pause);
                            window.draw(next);
                            window.draw(prev);
                            window.display();
                            break;
                        }
                    }

                    //next
                    if( next.getGlobalBounds().contains(x, y) ) {
                        std::cout << "next" << std::endl;

                        //somthing
                        sound.pause();
                        sound.setPlayingOffset(sf::Time::Zero);

                        ++soundcount;
                        if( soundcount >= playlist.size() ) soundcount = 0;

                        if (!sb.loadFromFile(playlist[soundcount])) {
                            return fail_load_WAV;
                        }
                        sound.setBuffer(sb);

                        sound.play();
                        std::cout << soundcount << std::endl;

                        break;
                    }

                    //prev
                    if( prev.getGlobalBounds().contains(x, y) ) {
                        std::cout << "prev" << std::endl;

                        //somthing
                        sound.pause();

                        if( ( (int)sound.getPlayingOffset().asSeconds() ) > 5 ){
                            sound.setPlayingOffset(sf::Time::Zero);
                            sound.play();
                            std::cout << soundcount << std::endl;

                            break;
                        }                           

                        --soundcount;
                        if (soundcount < 0) soundcount = playlist.size() - 1;
                        sound.setPlayingOffset(sf::Time::Zero);

                        if (!sb.loadFromFile(playlist[soundcount])) {
                            return fail_load_WAV;
                        }
                        sound.setBuffer(sb);
                        sound.play();
                        std::cout << soundcount << std::endl;

                        break;
                    }
                }
            }            
        }
    }

    return success;
}