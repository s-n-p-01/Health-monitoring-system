//rfid libraries
#include<SPI.h>
#include<RFID.h>
//heart rate sensor libraries
#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>
//infrared temperature sensor libraries
#include <Adafruit_MLX90614.h>
//LCD libraries
#include <LiquidCrystal.h>



// rfid constants
#define SDA_DIO A1
#define RESET_DIO 9
RFID RC522(SDA_DIO, RESET_DIO);

// heart rate sensor constants
const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_INPUT = A0;
const int PULSE_BLINK = LED_BUILTIN;
const int PULSE_FADE = 5;
const int THRESHOLD = 1023;
byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;
PulseSensorPlayground pulseSensor;

//infrared temperature sensor constants
Adafruit_MLX90614 mlx = Adafruit_MLX90614();




void setup() {


  Serial.begin(9600);
  SPI.begin();
  RC522.init();

  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);
  
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
  

}

void loop() {
  
  if (RC522.isCard()){
    RC522.readCardSerial();
    Serial.println("Card Detected");
    for ( int i=0 ; i<12 ;i++){
      Serial.print(RC522.serNum[i],DEC);
      Serial.print(" ");
    } 
   Serial.println(" ");
   int code=RC522.serNum[0];


  if (code == 16){
    Serial.println("User not registered");
  }


  

  if (code==179){
    
    Serial.println("Registerd user: Saima");
    
    
    while (!Serial);
    Serial.println("Heart rate / temperature  check up");
    
    if (!mlx.begin()) {
      Serial.println("Error connecting to MLX sensor. Check wiring.");
      while (1);
      };

    Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
    Serial.println("================================================");

    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
    Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");


    if (pulseSensor.sawNewSample()) {
    /*
       Every so often, send the latest Sample.
       We don't print every sample, because our baud rate
       won't support that much I/O.
    */
    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

      pulseSensor.outputSample();

      /*
         At about the beginning of every heartbeat,
         report the heart rate and inter-beat-interval.
      */
      if (pulseSensor.sawStartOfBeat()) {
        pulseSensor.outputBeat();
      }
    }
  


  }
 

}}}
