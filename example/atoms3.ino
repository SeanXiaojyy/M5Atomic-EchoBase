#include <Arduino.h>

#include <M5EchoBase.h>

M5EchoBase echobase;

void setup()
{
	echobase.init();
    echobase.setSpeakerVolume(50);
    uint8_t *buffer = (uint8_t *)malloc(1024 * 128);
    while (1)
    {
        echobase.record(buffer, 1024 * 128);
        echobase.play(buffer, 1024 * 128);
    }
}

void loop()
{
	
}
