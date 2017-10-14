// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <SoftwareSerial.h>
#include <MP3.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
/** define mp3 class */
MP3 mp3;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  /** begin function */
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  //  mp3.begin();                       // select hardware serial(or mp3.begin(MP3_HARDWARE_SERIAL);)
  
  /** set volum to the MAX */
  mp3.volume(0x1F);
}

void loop() {

  
  
  /** set MP3 Shield CYCLE mode */
  mp3.set_mode(MP3::CYCLE);
  
  /** play music in sd, '0001' for first music */
  //mp3.play_sd(0x0001);
  
  
  
  /** play music in SPI FLASH */ 
  //mp3.play_spi_flash(0x0001);
  
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  
  if(sonar.ping_cm() <= 150){
    Serial.println("Jugador detectado");
    /** play music in USB-disk */ 
    mp3.play_usb_disk(0x0001);

    delay(8000);
  }
 
}
