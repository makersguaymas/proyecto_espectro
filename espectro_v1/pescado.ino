// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#include <avr/interrupt.h>
#include <CapPin.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 11
// #define NUMPIXELS    22
#define NUMPIXELS 23
unsigned long tiempo = 0;
unsigned long t_actualizado = 0;
unsigned long t_delay = 1000;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 20; // delay for half a second
int rojo = 0;
int verde = 0;
int azul = 0;
int boton = 2;
int estado_boton = 0;
int numero_leds = 1;
int numero_clic = 0;
int total_clics = 0;
int segundos = 0;
void setup()
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket

#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif

  // End of trinket special code
  pinMode(boton, INPUT_PULLUP);
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  attachInterrupt(digitalPinToInterrupt(boton), contador_clics, RISING);
}

void loop()
{
  pescado();
}

void contador_clics()
{
  numero_clic++;
  total_clics++;
  t_delay = 1500;
  Serial.print("total clics ");
  Serial.println(total_clics);
  rojo++;
  if (numero_leds <= NUMPIXELS and numero_clic > 3)
  {
    if ((rojo + 3) <= 255)
    {
      rojo += 8;
    }
    else
    {
      rojo = 255;
    }
    numero_leds += 1;
    numero_clic = 0;
  }
}

void pescado()
{
  tiempo = millis();
  if (tiempo > t_actualizado + t_delay)
  {
    // Se actualiza el tiempo que ha de transcurrir para el próximo delay.
    t_actualizado = tiempo;
    // Serial.print("segundo ");  Serial.println(segundos); segundos++;
    if (rojo > 0)
    {
      if ((rojo - 12) < 0)
      {
        rojo = 0;
      }
      else
      {
        rojo = rojo - 12;
      }
    }
    if (numero_leds > 2)
    {
      numero_leds--;
    }
    t_delay = 200;
    Serial.print("rojo: ");
    Serial.println(rojo);
    Serial.print("n leds:");
    Serial.println(numero_leds);
    Serial.print("pin 2: ");
    Serial.println(analogRead(boton));
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
  }
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (int i = 0; i < numero_leds; i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(rojo, verde, azul)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  // delay(delayval); // Delay for a period of time (in milliseconds)
}

