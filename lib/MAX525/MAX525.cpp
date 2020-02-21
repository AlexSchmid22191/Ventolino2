//
// Created by Alex on 30/10/2018.
//

#include "Arduino.h"
#include "MAX525.h"
#include "SPI.h"

const byte MAX525::CHA = 0;
const byte MAX525::CHB = 1;
const byte MAX525::CHC = 2;
const byte MAX525::CHD = 3;

const byte MAX525::LOAD_NC = 1;
const byte MAX525::LOAD_UD = 3;

const byte MAX525::UP_LOW = 0;
const byte MAX525::UP_HIGH = 1;

const byte MAX525::_ADDR = 14;
const byte MAX525::_CTRL = 12;


MAX525::MAX525(byte CS, byte CL, byte PDL, float V_ref, float gain)
{
    _CS_PIN = CS;
    _CL_PIN = CL;
    _PDL_PIN = PDL;
    _VREF = V_ref;
    _GAIN = gain;
}

void MAX525::begin()
{
    SPI.begin();
    pinMode(_CS_PIN, OUTPUT);
    digitalWrite(_CS_PIN, HIGH);

    pinMode(_CL_PIN, OUTPUT);
    digitalWrite(_CL_PIN, HIGH);

    pinMode(_PDL_PIN, OUTPUT);
    digitalWrite(_PDL_PIN, HIGH);
}

void MAX525::set_UPO(byte state)
{
    //Control word
    uint16_t ctrl = (uint16_t) 0 | (state << MAX525::_ADDR) | (2 << MAX525::_CTRL);

    //Send control word
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_CS_PIN, LOW);
    SPI.transfer16(ctrl);
    digitalWrite(_CS_PIN, HIGH);
    SPI.endTransaction();
}

void MAX525::write_DAC(byte channel, float voltage, byte update)
{
    //DAC code
    uint16_t code = calc_codec(voltage);

    //Control word
    uint16_t ctrl = 0 | (channel << MAX525::_ADDR) | (update << MAX525::_CTRL) | code;

    //Send control word
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_CS_PIN, LOW);
    SPI.transfer16(ctrl);
    digitalWrite(_CS_PIN, HIGH);
    SPI.endTransaction();
}

void MAX525::power_down()
{
    //Control word
    uint16_t ctrl = (uint16_t) 0u | (3u << MAX525::_ADDR) | (0u<< MAX525::_CTRL);

    //Send control word
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_CS_PIN, LOW);
    SPI.transfer16(ctrl);
    digitalWrite(_CS_PIN, HIGH);
    SPI.endTransaction();
}

void MAX525::update_all()
{
    //Control word
    uint16_t ctrl = (uint16_t) 0u | (1u << MAX525::_ADDR) | (0u<< MAX525::_CTRL);

    //Send control word
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_CS_PIN, LOW);
    SPI.transfer16(ctrl);
    digitalWrite(_CS_PIN, HIGH);
    SPI.endTransaction();
}

void MAX525::write_all(float voltage)
{
    //DAC codec
    uint16_t codec = calc_codec(voltage);

    //Control word
    uint16_t ctrl = (uint16_t) 0 | (2u << MAX525::_ADDR) | (0u<< MAX525::_CTRL) | codec;

    //Send control word
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_CS_PIN, LOW);
    SPI.transfer16(ctrl);
    digitalWrite(_CS_PIN, HIGH);
    SPI.endTransaction();
}

void MAX525::clear_all()
{
    digitalWrite(_CL_PIN, LOW);
    digitalWrite(_CL_PIN, HIGH);
}

uint16_t MAX525::calc_codec(float voltage)
{
    return (uint16_t) (voltage / _VREF / _GAIN * 4095);
}

void MAX525::setVref(float vref)
{
    _VREF = vref;
}

void MAX525::setGain(float gain)
{
    _GAIN = gain;
}