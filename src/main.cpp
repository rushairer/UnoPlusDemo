#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel rgbLed = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);

uint8_t pins[] = {A0, A1, A2, A3, A4, A5, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
uint8_t group1Pins[] = {A0, A1, A2, A3, A4, A5};
uint8_t group2Pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void setup()
{
    rgbLed.begin();

    for (uint8_t i = 0; i < sizeof(pins) / sizeof(uint8_t); i++)
    {
        pinMode(pins[i], OUTPUT);
    }
}

void loopAllLeds(uint8_t wait);
void rainbow(uint8_t wait);
void loopGroupLeds(uint8_t wait);

void loop()
{
    rgbLed.show();
    rainbow(5);
    loopAllLeds(100);
    loopAllLeds(50);
    loopAllLeds(20);
    loopGroupLeds(50);
    loopGroupLeds(20);
    loopGroupLeds(10);
}

void loopGroupLeds(uint8_t wait)
{

    uint8_t l1 = sizeof(group1Pins) / sizeof(uint8_t);
    uint8_t l2 = sizeof(group2Pins) / sizeof(uint8_t);
    for (uint8_t i = 0; i < l1; i++)
    {
        digitalWrite(group1Pins[i], LOW);
    }
    for (uint8_t i = 0; i < l2; i++)
    {
        digitalWrite(group2Pins[i], LOW);
    }
    for (uint8_t i = 0; i < l1 + 1; i++)
    {
        for (uint8_t j = 0; j < l2 / 2; j++)
        {
            delay(wait);

            for (uint8_t k = 0; k < l2 / 2; k++)
            {
                digitalWrite(group2Pins[k], j == k || l2 / 2 - k <= i + 1);
                digitalWrite(group2Pins[l2 - k - 1], j == k || l2 / 2 - k <= i + 1);
            }
        }

        if (i < l1)
        {
            digitalWrite(group1Pins[i], HIGH);
        }
        delay(wait * 6);
    }
    for (uint8_t i = 0; i < l1; i++)
    {
        digitalWrite(group1Pins[i], LOW);
    }
    for (uint8_t i = 0; i < l2; i++)
    {
        digitalWrite(group2Pins[i], LOW);
    }
}

void loopAllLeds(uint8_t wait)
{
    for (uint8_t i = 0; i < sizeof(pins) / sizeof(uint8_t); i++)
    {
        for (uint8_t j = 0; j < sizeof(pins) / sizeof(uint8_t); j++)
        {
            digitalWrite(pins[j], i == j);
        }
        delay(wait);
    }
}

uint32_t Wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return rgbLed.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return rgbLed.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return rgbLed.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

void rainbow(uint8_t wait)
{
    uint16_t i, j;
    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < rgbLed.numPixels(); i++)
        {
            rgbLed.setPixelColor(i, Wheel((i + j) & 255));
        }
        rgbLed.show();
        delay(wait);
    }
}
