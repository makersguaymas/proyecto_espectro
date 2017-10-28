#include <CapPin.h>
#include <CapScroll.h>
#include <CapSlider.h>
#include <CapTouch.h>
#include <Adafruit_NeoPixel.h>

#define OJOIZQ            3
#define OJODER            5
#define CORAZON           6
#define PESCADO           11
#define NUMPIXELS      16
#define THRESH 300


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, OJOIZQ, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, OJODER, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, CORAZON, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELS, PESCADO, NEO_GRB + NEO_KHZ800);

int randomPixel ;

CapPin cPin_10 = CapPin(8);    // read pin 10 (D10 on Flora) - connect to NES B
CapPin cPin_9  = CapPin(9);     // read pin 9 (D9 on Flora)   - connect to NES A
CapPin cPin_6  = CapPin(10);     // read pin 6 (D6 on Flora)   - connect to NES Start
CapPin cPin_12 = CapPin(12);    // read pin 12 (D12 on Flora) - connect to NES Select

CapPin pins[] = {cPin_10, cPin_9, cPin_6, cPin_12};

char Keys[] =   {'a','b','c','d'};
char sensor = 'z';
boolean currentPressed[] = {false, false, false, false};
long tiempoPrevio = 0;
long intervaloRespuesta = 3000;

int experiencia = 0;
int dificultad = 0;

boolean sinGente = false;
boolean conGente = false;
boolean jugar = false;
boolean reproductor = false;
boolean reiniciar = false;
boolean ciclo = false;
long tiempoSinGente = 10000;
long tiempoPreguntar = 5000;
boolean preguntar = true;
void setup(){
  Serial.begin(115200);
  Serial.println("Start");
  
  pixels.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
 // randomPixel = random(4);
}

void loop(){

  
  unsigned long tiempoTranscurrido = millis();
  unsigned long tiempoRespuesta = millis();

  if(jugar == false && sinGente == false && conGente == false && reproductor == false && reiniciar == false && ciclo == false && preguntar == true && tiempoTranscurrido - tiempoPrevio < tiempoPreguntar) {
    Serial.println("Quieres jugar?");
    Serial.print("Opcion");
    Serial.println(sensor);
  for (int i = 0; i<4; i++){
    delay(1);
    long total1 = 0;
    long start = millis();
    long total =  pins[i].readPin(300);
    //Serial.println(total);
    if((total > THRESH)){
      currentPressed[i] = true;
      sensor = Keys[i];
      Serial.println(sensor);
    }else if ((total <= THRESH)) {
      currentPressed[i] = false;
    }
    delay(100);
  }

      tiempoTranscurrido = tiempoPrevio;

} 

if (jugar == false && sinGente == false && conGente == false && reproductor == false && reiniciar == false && ciclo== false && preguntar == true && tiempoTranscurrido - tiempoPrevio > tiempoPreguntar) {
  ciclo = true;
  preguntar = false;
 tiempoTranscurrido = tiempoPrevio;
 Serial.println("tiempo");
 Serial.println(tiempoPrevio);
}

if (jugar == false && sinGente == false && conGente == false && reproductor == false && reiniciar == false && ciclo == true && preguntar == false && tiempoTranscurrido - tiempoPrevio > tiempoPreguntar && tiempoTranscurrido - tiempoPrevio <tiempoSinGente) {
   rainbow(10);
  rainbow2(10);
  rainbow3(10);
  rainbow4(10);
  Serial.print("o aqui");
  Serial.println(tiempoPrevio);
  tiempoTranscurrido = tiempoPrevio;
}
if (jugar == false && sinGente == false && conGente == false && reproductor == false && reiniciar == false && ciclo == true && preguntar == false && tiempoTranscurrido - tiempoPrevio >tiempoSinGente) {
    ciclo = false;
    preguntar == true;
 tiempoTranscurrido = 0;
 tiempoPrevio = 0;
}

if(jugar == true && sinGente == false && conGente == false && reproductor == false && reiniciar == false){
  if(randomPixel>=0 && randomPixel <1) {
      for(int i=0; i<pixels.numPixels(); i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
        pixels.show();
      }
      for(int i=0; i<pixels2.numPixels(); i++){
        pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
        pixels2.show();
      }
      for(int i=0; i<pixels3.numPixels(); i++){
        pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
        pixels3.show();
      }
      for(int i=0; i<pixels4.numPixels(); i++){
        pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
        pixels4.show();
      }
     if(sensor=='a' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta){
        for(int i=0; i<pixels.numPixels(); i++){
          pixels.setPixelColor(i, pixels.Color(0, 255, 0));
          pixels.show();
        }
                for(int i=0; i<pixels2.numPixels(); i++){
          pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
          pixels2.show();
        }
        for(int i=0; i<pixels3.numPixels(); i++){
          pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
          pixels3.show();
        }
        for(int i=0; i<pixels4.numPixels(); i++){
          pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
          pixels4.show();
        }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;
        experiencia++;
      } 
      if (tiempoTranscurrido - tiempoPrevio > intervaloRespuesta) {
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(255, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;
       }
  }
  if (randomPixel>=1 && randomPixel<2){
      for(int i=0; i<pixels.numPixels(); i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
      }
      for(int i=0; i<pixels2.numPixels(); i++){
        pixels2.setPixelColor(i, pixels2.Color(0, 0, 255));
        pixels2.show();
      }
      for(int i=0; i<pixels3.numPixels(); i++){
        pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
        pixels3.show();
      }
      for(int i=0; i<pixels4.numPixels(); i++){
        pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
        pixels4.show();
      }
     if(sensor=='b' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta){
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(0,255, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
       tiempoPrevio = tiempoTranscurrido;
       experiencia++;
      } else if (tiempoTranscurrido - tiempoPrevio > intervaloRespuesta) {
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(255, 0, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;       
      }
  } else if (randomPixel>=2 && randomPixel<3){
    for(int i=0; i<pixels.numPixels(); i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
      }
      for(int i=0; i<pixels2.numPixels(); i++){
        pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
        pixels2.show();
      }
      for(int i=0; i<pixels3.numPixels(); i++){
        pixels3.setPixelColor(i, pixels3.Color(0, 0, 255));
        pixels3.show();
      }
      for(int i=0; i<pixels4.numPixels(); i++){
        pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
        pixels4.show();
      }
     if(sensor=='c' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta){
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(0, 255, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;
        experiencia++;
      } else if (tiempoTranscurrido - tiempoPrevio > intervaloRespuesta) {
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(255,0, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;        
      }
  } else if (randomPixel>=3 && randomPixel<4) {
    for(int i=0; i<pixels.numPixels(); i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
      }
      for(int i=0; i<pixels2.numPixels(); i++){
        pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
        pixels2.show();
      }
      for(int i=0; i<pixels3.numPixels(); i++){
        pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
        pixels3.show();
      }
      for(int i=0; i<pixels4.numPixels(); i++){
        pixels4.setPixelColor(i, pixels4.Color(0, 0, 255));
        pixels4.show();
      }
     if(sensor=='d' && tiempoTranscurrido - tiempoPrevio <  intervaloRespuesta){
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(0, 255, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;
      } else if (tiempoTranscurrido - tiempoPrevio > intervaloRespuesta) {
          for(int i=0; i<pixels.numPixels(); i++){
            pixels.setPixelColor(i, pixels.Color(0, 0, 0));
            pixels.show();
          }
          for(int i=0; i<pixels2.numPixels(); i++){
            pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
            pixels2.show();
          }
          for(int i=0; i<pixels3.numPixels(); i++){
            pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
            pixels3.show();
          }
          for(int i=0; i<pixels4.numPixels(); i++){
            pixels4.setPixelColor(i, pixels4.Color(255, 0, 0));
            pixels4.show();
          }
        delay(100);
        randomPixel = random(4);
        tiempoPrevio = tiempoTranscurrido;  
        experiencia++;      
      }
  }

if(experiencia == 2) {
  dificultad = 30;
} else if(experiencia == 3) {
  dificultad = 50;
} else if(experiencia ==4){
  dificultad = 70;
} else if(experiencia ==5){
  dificultad = 90;
}

intervaloRespuesta = intervaloRespuesta - dificultad;
}
 
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
void rainbow2(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels2.numPixels(); i++) {
      pixels2.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels2.show();
    delay(wait);
  }
}

void rainbow3(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels3.numPixels(); i++) {
      pixels3.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels3.show();
    delay(wait);
  }
}

void rainbow4(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels4.numPixels(); i++) {
      pixels4.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels4.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    for(int index= 0; index< NUMPIXELS; index++){
      return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
    }
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    for(int index=0 ; index<NUMPIXELS; index++){
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
    }
  }
  WheelPos -= 170;
  for(int index= 0; index < NUMPIXELS; index++){
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
  }
}
