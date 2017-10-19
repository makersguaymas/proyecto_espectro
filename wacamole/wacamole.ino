#include <Adafruit_NeoPixel.h>
#include <CapPin.h>

#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            8

#define NUMPIXELS      64
int randomPixel ;
int boton1 = 8;
int boton2 = 9;
int boton3 = 10;
int boton4 = 11;
int vidas = 3;
long tiempoPrevio = 0;
boolean fv = false;
long dificultad = 100;
long tiempoRespuestaP = 0;
int presionado;
long intervaloTiempo = 3000;
long sumatoria = 2999;
long intervaloRespuesta = 2900;


boolean retry = false;
boolean jugando = false;
/**
   Pads PIN
*/

CapPin cPin_7 = CapPin(7);    // read pin 10 (D10 on Flora) - connect to NES B
CapPin cPin_6  = CapPin(6);     // read pin 9 (D9 on Flora)   - connect to NES A
CapPin cPin_5  = CapPin(5);     // read pin 6 (D6 on Flora)   - connect to NES Start
CapPin cPin_4 = CapPin(4);    // read pin 12 (D12 on Flora) - connect to NES Select

CapPin pins[] = {cPin_7, cPin_6, cPin_5, cPin_4};

char pad = 'g';


/**
   Fin Pads PIN
*/

/**
   Keys para identificar los pads
*/
char Keys[] =   {  'a',    'b',    'c',    'd'  };

boolean currentPressed[] = {false, false, false, false};

/**
   Fin de keys
*/

/**
   Pads code
*/
// Capactive touch threashhold, you might want to mess with this if you find its too
// sensitive or not sensitive enough
#define THRESH 300

float smoothed[4] = {0, 0, 0, 0};

/**
   Fin de pads code
*/
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);
  pinMode(boton4, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("start");
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // This initializes the NeoPixel library.
  jugando = true;
}

void loop() {

  unsigned long tiempoTranscurrido = millis();
  unsigned long tiempoRespuesta = millis();

  



  if ( jugando == true ) {

    Serial.println("PLAYING");
    /****

      Logica para detectar los pads




    */
    for (int i = 0; i < 4; i++) {
      delay(1);
      long total1 = 0;
      long start = millis();
      long total =  pins[i].readPin(2000);

      // check if we are sensing that a finger is touching the pad
      // and that it wasnt already pressed
      if ((total > THRESH) && (! currentPressed[i])) {
        Serial.print("Key pressed #"); Serial.print(i);
        pad = Keys[i];
        Serial.print(" ("); Serial.print(pad); Serial.println(")");
        currentPressed[i] = true;


        //Keyboard.press(Keys[i]);
      }


      else if ((total <= THRESH) && (currentPressed[i])) {
        // key was released (no touch, and it was pressed before)
        Serial.print("Key released #"); Serial.print(i);
        Serial.print(" ("); Serial.print(pad); Serial.println(")");
        currentPressed[i] = false;

        //Keyboard.release(Keys[i]);
      }

      /**

         Aqui termina logica de los pads


      */
      delay(5);

      int colortime = 0;
      int constante ;
      pixels.setPixelColor(20, pixels.Color(0, 0, 0));
      pixels.show();


      if (tiempoTranscurrido - tiempoPrevio > intervaloTiempo && vidas > 0 ) {


        tiempoPrevio = tiempoTranscurrido;
        randomPixel = random(4);
        pixels.setPixelColor(19, pixels.Color(0, 0, 0));
        fv = false;
        intervaloTiempo -= dificultad;
        intervaloRespuesta -= dificultad;
        Serial.println(intervaloTiempo);
        Serial.println(intervaloRespuesta);
      }

      if (vidas <= 0) {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.setPixelColor(1, pixels.Color(255, 0, 0));
        pixels.setPixelColor(2, pixels.Color(255, 0, 0));
        pixels.setPixelColor(3, pixels.Color(255, 0, 0));

        pixels.show();
        delay(5000);
      }
      if (randomPixel == 0) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
        //presionado = digitalRead(boton1);
        Serial.println(pad);
        if (pad == 'a' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(0, 255, 0));
          pixels.show();

          Serial.println("Atinaste!");
          fv = true;
          tiempoTranscurrido = 0;


        }
        if (fv == false && tiempoTranscurrido - tiempoPrevio  > intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(255, 0, 0));

          pixels.show();
          delay(500);
          vidas --;
          Serial.print("vidas: ");Serial.println(vidas);
          Serial.println("Perdiste!");
        }



      }
      if (randomPixel == 1) {
        pixels.setPixelColor(1, pixels.Color(0, 0, 255));
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
        //presionado = digitalRead(boton2);
        Serial.println(pad);
        if (pad == 'b' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(0, 255, 0));
          pixels.show();
          fv = true;
          Serial.println("Atinaste!");

        }
        if (fv == false && tiempoTranscurrido - tiempoPrevio  > intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(255, 0, 0));

          pixels.show();
          delay(500);
          vidas --;
          Serial.print("vidas: ");Serial.println(vidas);
          Serial.println("Perdiste!");
        }
      }
      if (randomPixel == 2) {
        pixels.setPixelColor(2, pixels.Color(0, 0, 255));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
        //presionado = digitalRead(boton3);
        Serial.println(pad);
        if (pad == 'c' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(0, 255, 0));
          pixels.show();
          fv = true;
          Serial.println("Atinaste!");

        }
        if (fv == false && tiempoTranscurrido - tiempoPrevio  > intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(255, 0, 0));

          pixels.show();

          delay(500);
          vidas --;
          Serial.print("vidas: ");Serial.println(vidas);
          Serial.println("Perdiste!");
        }
      }
      if (randomPixel == 3) {
        pixels.setPixelColor(3, pixels.Color(0, 0, 255));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.show();
        //presionado = digitalRead(boton4);
        Serial.println(pad);
        if (pad == 'd' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(0, 255, 0));
          pixels.show();
          Serial.println("Atinaste!");
          fv = true;


        }
        if (fv == false && tiempoTranscurrido - tiempoPrevio  > intervaloRespuesta) {
          pixels.setPixelColor(19, pixels.Color(255, 0, 0));

          pixels.show();
          delay(500);
          Serial.println("Perdiste!");
          vidas --;
          Serial.print("vidas: ");Serial.println(vidas);
        }
      }
      if( vidas == 0 ){
        
        jugando = false;
        Serial.println("RETRY, PRESS C TO PLAY AGAIN");
     }
    }
  }

 

  for (int i = 0; i < 4; i++) {
      delay(1);
      long total1 = 0;
      long start = millis();
      long total =  pins[i].readPin(2000);

      // check if we are sensing that a finger is touching the pad
      // and that it wasnt already pressed
      if ((total > THRESH) && (! currentPressed[i])) {
        Serial.print("Key pressed #"); Serial.print(i);
        pad = Keys[i];
        Serial.print(" ("); Serial.print(pad); Serial.println(")");
        currentPressed[i] = true;
        //Keyboard.press(Keys[i]);
      }
  }

  if(pad ==  'c'){
    jugando = true;
    vidas = 3;
  }
}

// simple lowpass filter
// requires recycling the output in the "smoothedVal" param
int smooth(int data, float filterVal, float smoothedVal) {

  if (filterVal > 1) {     // check to make sure param's are within range
    filterVal = .999999;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}
