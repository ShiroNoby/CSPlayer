#ifndef _CS_LOG_
#define _CS_LOG_

#include "pch.h"

//|tier|type_log|file|line|massage|param-opt|

enum Tier {
    tier0 = 0,
    tier1,
    tier2,
    tier3
};

char* tierToStr( Tier tier ){
    switch( tier ){
        case tier0:
            return "";
        case tier1:
            return "\t";
        case tier2:
            return "\t\t";
        case tier3:
            return "\t\t\t";
        default: return "";
    }
}

///////**********************************************************************\\\\\\\\CSLog


class CSLog{
    
    size_t size;
    size_t max_size;
    std::vector< std::string > log;
    
    //bool available = true;
    
public:
    
    /* bool isAvailable(){ return available; }
    
    void setAvailable( bool Avlb ) { available = Avlb; } */
    
    CSLog();
    ~CSLog();
    
    void fileWrite();
    
    void write( const std::string& );   
};

CSLog::CSLog() : size(0), max_size(100), log(max_size) {
    
    std::fstream file("log.txt");
     
    if (!file.is_open())
    {
        file.clear();
        file.open( "log.txt" ); // create file
        file.close();
        file.open( "log.txt" );
    }
    
    file << "start app\n";
    
    file.close();
}

CSLog::~CSLog(){
    
    write("stop app");
    fileWrite();
}

void CSLog::fileWrite(){
    
    std::fstream file( "log.txt", std::fstream::app );
    
    if (!file.is_open())
    {
        file.clear();
        file.open( "log.txt", file.app ); // create file
        file.close();
        file.open( "log.txt", file.app );
    }
    
    for( size_t index = 0; index <= size; ++index ){
        file << log[index] << '\n';
    }  
    
    size = 0;
}

void CSLog::write( const std::string& str ){
    
    if( !str.size() ){ return; }
        
    if( size == max_size - 1 )
        fileWrite();
    
    log[size] = str;
    size += 1;
}

//|tier|type_log|file|line|massage|param-opt|
CSLog newLog;

///////**********************************************************************\\\\\\\\SystemLog

void SystemLog(Tier tier, char* file, char* line, char* msg ){
    
    std::string str( tierToStr( tier ) );
    str += "System_log"; str += ' ';
    str += file; str += ' ';
    str += line; str += ' ';
    str += msg;  str += ' ';
    
    newLog.write( str );
}

///////**********************************************************************\\\\\\\\UserLog

//|tier|file|line|massage|
void UserLog(Tier tier, char* file, char* line, char* msg ){
    
    std::string str( tierToStr( tier ) );
    str += "User_log"; str += ' ';
    str += file; str += ' ';
    str += line; str += ' ';
    str += msg;  str += ' ';
    
    newLog.write( str );
}
#endif //_CS_LOG_