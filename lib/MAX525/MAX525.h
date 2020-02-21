//
// Created by Alex on 30/10/2018.
//

//Class for interfacing an Arduino with the MAX525 4 channel 12-bit analog to digital converter.

#ifndef MAX525_H
#define MAX525_H

class MAX525
{
public:
    static const byte CHA;
    static const byte CHB;
    static const byte CHC;
    static const byte CHD;

    static const byte LOAD_NC;
    static const byte LOAD_UD;

    static const byte UP_LOW;
    static const byte UP_HIGH;

    MAX525(byte CS, byte CL, byte PDL, float V_ref);

    void begin();
    void write_DAC(byte channel, float voltage, float vref, float gain, byte update);
    void set_UPO(byte state);
    void power_down();
    void update_all();
    void write_all(float voltage, float vref, float gain);
    void clear_all();

private:
    //Chip select, clear and power down pins
    byte _CS_PIN;
    byte _CL_PIN;
    byte _PDL_PIN;
    float _VREF;

    //Bit masks for control byte
    static const byte _ADDR;
    static const byte _CTRL;
};

#endif //MAX525_H
