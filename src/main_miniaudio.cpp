#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "CSPlayer.h"


int main(){  

    //LAlt + Up|down mouseWheel => volume"
    ///////**********************************************************************\\\\\\\\window
    
    SystemLog( tier0, "main", "14", "window create end\n");
    //make window 300,100
    sf::RenderWindow window(sf::VideoMode(300,100),"test");

    ///////**********************************************************************\\\\\\\\player

    //load texture1
    SystemLog( tier0, "main", "20", "load texture1\n");
    sf::Texture texture1;
    if( !texture1.loadFromFile("../elements/play.png" ) ){
        ErrorLog( tier1, "CSPlayer.h", "122", "fail_load_png", fail_load_png );
        return fail_load_png;
    }    

    //make some sprite
    sf::Sprite play(  texture1, sf::IntRect( { 11, 11  }, { 51, 56  } )); 
    sf::Sprite pause( texture1, sf::IntRect( { 70, 11  }, { 35, 45  } )); 
    sf::Sprite next(  texture1, sf::IntRect( { 116, 11 }, { 64, 45  } )); 
    sf::Sprite prev(  texture1, sf::IntRect( { 180, 11 }, { -64, 45 } )); 

    //move some sprite
    play.setPosition( { 129, 28 });
    pause.setPosition({ 129, 28 });
    next.setPosition( { 205, 28 });
    prev.setPosition( { 24 , 28 });

    //play.setTextureRect(sf::IntRect());

    window.clear(sf::Color::White);

    bool PlaySound = false; //in CSPlayer
    float volume = 0.8F;

    //draw sprite
    if( PlaySound ) {        
        window.draw(pause);
    }else{
        window.draw(play);
    }
    window.draw(next);
    window.draw(prev);

    window.display();
    
    ///////**********************************************************************\\\\\\\\playlist
    
    SystemLog( tier0, "main", "59", "CSPlayer create start");
    CSPlayer player;
    player.setBuffer( player.playlist.now() ); //in CSPlayer

    ///////**********************************************************************\\\\\\\\logic


    while(window.isOpen()){
        sf::Event event;

        //ген-сообщ
        while (window.pollEvent(event)){
            switch( event.type ){
                case sf::Event::Closed : { window.close(); }
                
                case sf::Event::MouseButtonPressed : {
                    UserLog( tier0, "main", "73", "MouseButtonPressed");
                    
                    float x = event.mouseButton.x;
                    float y = event.mouseButton.y;

                    if( PlaySound ) { //спустить вниз
                        //pause
                        if (pause.getGlobalBounds().contains(x, y)) {
                            UserLog( tier0, "main", "81", "play to pause click");
                            
                            PlaySound = false;

                            SystemLog( tier0, "main", "87", "player.pause()");
                            player.pause();

                            window.clear(sf::Color::White);
                            window.draw(play);
                            window.draw(next);
                            window.draw(prev);
                            window.display();
                            break;
                        }
                    }else{ 
                        //play
                        if (play.getGlobalBounds().contains(x, y)) {
                            UserLog( tier0, "main", "98", "pause to play click");
                            
                            PlaySound = true;
                            
                            SystemLog( tier0, "main", "104", "player.play()");
                            player.play();

                            window.clear(sf::Color::White);
                            window.draw(pause);
                            window.draw(next);
                            window.draw(prev);
                            window.display();
                            break;
                        }
                    }

                    //next
                    if( next.getGlobalBounds().contains(x, y) ) {
                        UserLog( tier0, "main", "116", "next play click");

                        SystemLog( tier0, "main", "120", "player.pause()");
                        player.pause();

                        SystemLog( tier0, "main", "123", "player.next()");
                        player.next();

                        SystemLog( tier0, "main", "126", "player.play()");
                        player.play();
                        break;
                    }

                    //prev
                    if( prev.getGlobalBounds().contains(x, y) ) {
                        UserLog( tier0, "main", "131", "prev play click");
                        
                        SystemLog( tier0, "main", "135", "player.pause()");
                        player.pause();

                        SystemLog( tier0, "main", "136", "player.prev()");
                        player.prev();
                        
                        SystemLog( tier0, "main", "141", "player.play()");
                        player.play();
                        
                        break;
                    }
                    break;
                }
                
                case sf::Event::MouseWheelMoved : { //in CSPlayer
                    UserLog( tier0, "main", "148", "sf::Event::MouseWheelMoved");
                
                    if( event.key.alt ) {
                        UserLog( tier0, "main", "151", "event.key.alt");
                        
                        if( event.mouseWheel.delta > 0 ) {
                            UserLog( tier0, "main", "154", "delta > 0");
                            
                            SystemLog( tier0, "main", "158", "volume +");
                            volume += 0.1F;
                            ma_device_set_master_volume( &player.device, volume ); //in CSPlayer
                            
                            break;
                        }                            
                        
                        if( event.mouseWheel.delta < 0 ) {
                            UserLog( tier0, "main", "164", "delta < 0");
                            
                            SystemLog( tier0, "main", "169", "volume -");
                            volume -= 0.1F;
                            ma_device_set_master_volume( &player.device, volume ); //in CSPlayer
                            
                            break;
                        }                            
                    }
                    break;
                }
                
                default: break;
            }
            
            if( PlaySound && !player.isPlaying ){
                SystemLog( tier0, "main", "180", "auto_play");                
                
                SystemLog( tier0, "main", "184", "player.pause();"); 
                player.pause();

                SystemLog( tier0, "main", "187", "player.next();"); 
                player.next();

                SystemLog( tier0, "main", "190", "player.play();"); 
                player.play();
            }
        }
    }
    return success;
}