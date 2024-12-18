#include <Arduino.h>

#include <M5EchoBase.h>

M5EchoBase echobase;

extern const uint8_t music_pcm_start[] asm("_binary_canon_pcm_start");
extern const uint8_t music_pcm_end[]   asm("_binary_canon_pcm_end");

extern "C" void app_main()
{
	echobase.init();
    echobase.setSpeakerVolume(50);
    echobase.play(music_pcm_start, music_pcm_end - music_pcm_start);
    uint8_t *buffer = (uint8_t *)malloc(1024 * 128);
    while (1)
    {
        echobase.record(buffer, 1024 * 128);
        echobase.play(buffer, 1024 * 128);
    }
}
