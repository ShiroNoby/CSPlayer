#ifndef _CS_Player_
#define _CS_Player_

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "CSLoader.h"

bool CSIsPlaying = false;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        ErrorLog( tier1, "CSPlayer.h", "14", "pDecoder is null", 999 );
        return; 
    }
    
    ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
    
    if( result == MA_AT_END )
        CSIsPlaying = false;

    (void)pInput;
}

class CSPlayer {

    CSPlayer( const CSPlayer& ) = delete;
    CSPlayer& operator=( const CSPlayer& ) = delete;
    
    CSPlayer( CSPlayer&& ) = delete;
    CSPlayer& operator=( CSPlayer&& ) = delete;
    
public:

    CSPlayer(); //load playlist default directory
    ~CSPlayer();
    
    int play();
    int pause();
    int next();
    int prev();
    int setBuffer( const std::wstring& str ); ////wstring
    
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;
    CSPlaylist playlist;
    bool CSdevice = false;
    bool CSdecoder = false;
    bool& isPlaying = CSIsPlaying;    
};

//load playlist default directory
CSPlayer::CSPlayer(){
    SystemLog( tier1, "CSPlayer.h", "55", "CSPlayer create start\n");
    
    Loader loader; 
    loader.LoadPlaylist(playlist);
}

int CSPlayer::setBuffer( const std::wstring& str ){ ////wstring
    SystemLog( tier1, "CSPlayer.h", "62", "CSPlayer setBuffer start");
    
    ma_result result;
    
    if(CSdevice){
        ma_device_uninit(&device);
        CSdevice = false;
    }
        
    if(CSdecoder) {
        ma_decoder_uninit(&decoder); 
        CSdecoder = false;        
    }
    
    result = ma_decoder_init_file_w( str.data(), NULL, &decoder );     //ma_decoder_init_file_w
    if (result != MA_SUCCESS) {
        ErrorLog( tier1, "CSPlayer.h", "78", "Could not load file", 200 );
        return 200; //error code?
    }
    
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;
    
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        ErrorLog( tier1, "CSPlayer.h", "78", "Failed to open playback device", 300 );
        ma_decoder_uninit(&decoder);
        return 300; //error code? 
    }
    
    CSdevice = true;
    CSdecoder = true;
    
    SystemLog( tier1, "CSPlayer.h", "62", "CSPlayer setBuffer end\n");
    
    return 0; //error code?
}

int CSPlayer::play(){
    SystemLog( tier1, "CSPlayer.h", "104", "CSPlayer play()");
    
    if (ma_device_start(&device) != MA_SUCCESS) {
        ErrorLog( tier1, "CSPlayer.h", "122", "Failed to start playback device", 400 );
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        
        CSdevice = false;
        CSdecoder = false; 
        return 400; //error code?
    }
    
    isPlaying = true;
    
    return 0; //error code?
}

int CSPlayer::pause(){
    SystemLog( tier1, "CSPlayer.h", "122", "CSPlayer pause()");
    
    if (ma_device_stop(&device) != MA_SUCCESS) {
        ErrorLog( tier1, "CSPlayer.h", "122", "Failed to start playback device", 500 );
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        
        CSdevice = false;
        CSdecoder = false;
        return 500; //error code?
    }
    
    isPlaying = false;
    
    return 0; //error code?
}

int CSPlayer::next(){
    SystemLog( tier1, "CSPlayer.h", "140", "CSPlayer next()");
    
    setBuffer( playlist.next() );
    
    return 0;
}

int CSPlayer::prev(){
    SystemLog( tier1, "CSPlayer.h", "148", "CSPlayer prev()");
    
    setBuffer( playlist.prev() );
    
    return 0;
}

CSPlayer::~CSPlayer() {
    SystemLog( tier1, "CSPlayer.h", "166", "CSPlayer destroy");
    
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}

#endif //_CS_Player_