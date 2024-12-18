#ifndef ECHOBSE_H
#define ECHOBSE_H

#include <Arduino.h>
#include <Wire.h>
#include <FS.h>
#include "es8311.h"
#include "driver/i2s.h"

class M5EchoBase {
public:
    M5EchoBase();

    /**
     * @brief Initialize M5EchoBase with the specified sample rate and IO pins.
     * 
     * @param sample_rate Sampling rate in Hz (default: 32000)
     * @param i2c_sda I2C SDA pin
     * @param i2c_scl I2C SCL pin
     * @param i2s_di I2S Data In pin
     * @param i2s_ws I2S Word Select pin
     * @param i2s_do I2S Data Out pin
     * @param i2s_bck I2S Bit Clock pin
     * @param wire Wire object (default: Wire)
     * @return true Initialization successful
     * @return false Initialization failed
     */
    bool init(int sample_rate = 32000,
              int i2c_sda = GPIO_NUM_38,
              int i2c_scl = GPIO_NUM_39,
              int i2s_di = GPIO_NUM_7,
              int i2s_ws = GPIO_NUM_6,
              int i2s_do = GPIO_NUM_5,
              int i2s_bck = GPIO_NUM_8,
              TwoWire& wire = Wire); // 默认使用 Wire

    /**
     * @brief Set the speaker volume.
     * 
     * @param volume Volume level (0-100)
     * @return true Volume set successfully
     * @return false Failed to set volume
     */
    bool setSpeakerVolume(int volume);

    /**
     * @brief Set the microphone gain.
     * 
     * @param gain Microphone gain level
     * @return true Gain set successfully
     * @return false Failed to set gain
     */
    bool setMicGain(es8311_mic_gain_t gain);

    /**
     * @brief Mute or unmute the speaker.
     * 
     * @param mute true to mute, false to unmute
     * @return true Mute state set successfully
     * @return false Failed to set mute state
     */
    bool setMute(bool mute);

    /**
     * @brief Get the buffer size required for a recording of the specified duration.
     * 
     * @param duration Duration of the recording in seconds
     * @param sample_rate Sampling rate in Hz (default: 0)
     * @return int Size of the buffer in bytes
     */
    int getBufferSize(int duration, int sample_rate = 0);

    /**
     * @brief Get the duration of a recording of the specified size.
     * 
     * @param size Size of the recording in bytes
     * @param sample_rate Sampling rate in Hz (default: 0)
     * @return int Duration of the recording in seconds
     */
    int getDuration(int size, int sample_rate = 0);

    /**
     * @brief Record audio to a file.
     * 
     * @param fs Filesystem reference
     * @param filename Name of the file to save
     * @param size Size of the recording in bytes, can be calculated using getBufferSize()
     * @return true Recording successful
     * @return false Recording failed
     */
    bool record(FS& fs, const char* filename, int size);

    /**
     * @brief Record audio to a buffer.
     * 
     * @param buffer Pointer to the buffer to store audio data
     * @param size Size of the recording in bytes, can be calculated using getBufferSize()
     * @return true Recording successful
     * @return false Recording failed
     */
    bool record(uint8_t* buffer, int size);

    /**
     * @brief Play audio from a file.
     * 
     * @param fs Filesystem reference
     * @param filename Name of the file to play
     * @return true Playback successful
     * @return false Playback failed
     */
    bool play(FS& fs, const char* filename);

    /**
     * @brief Play audio from a buffer.
     * 
     * @param buffer Pointer to the audio buffer
     * @param size size of the audio buffer in bytes
     * @return true Playback successful
     * @return false Playback failed
     */
    bool play(const uint8_t* buffer, int size);

private:
    // ES8311 codec handle
    es8311_handle_t es_handle;

    // I2S configuration
    i2s_port_t i2s_num;
    i2s_config_t i2s_cfg;
    i2s_pin_config_t i2s_pin_cfg;

    // I2C and I2S pins
    int _i2c_sda;
    int _i2c_scl;
    int _i2s_di;
    int _i2s_ws;
    int _i2s_do;
    int _i2s_bck;

    TwoWire* _wire;

    // Initialize ES8311 codec
    bool es8311_codec_init(int sample_rate);

    // Initialize I2S driver
    bool i2s_driver_init(int sample_rate);

    // Initialize PI4IOE5V6408 I2C expander
    bool pi4ioe_init();

    // I2C read function
    uint8_t wire_read_byte(uint8_t i2c_addr, uint8_t reg_addr);

    // I2C write function
    void wire_write_byte(uint8_t i2c_addr, uint8_t reg_addr, uint8_t value);
};

#endif // ECHOBSE_H
