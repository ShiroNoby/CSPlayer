#ifndef _CS_Error_
#define _CS_Error_

#include "CSLog.h"

enum error {
    success = 0,
    
    no_imput_argument = 100,
    
    fail_load_WAV = 200,
    
    fail_device_init = 300,
    
    fail_device_start = 400,
    
    fail_device_stop = 500,
    
    fail_load_png = 600
};

///////**********************************************************************\\\\\\\\ErrorLog

void ErrorLog(Tier tier, char* file, char* line, char* msg, int code ){
    
    std::string str( tierToStr( tier ) );
    str += "ERROR_log"; str += ' ';
    str += file; str += ' ';
    str += line; str += ' ';
    str += msg;  str += ' ';
    str += std::to_string( code );
    
    newLog.write( str );
}

#endif //_CS_Error_