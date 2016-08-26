#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#include <SFE_BMP180.h>

SFE_BMP180 pressure;


#define debug 1 // 0: don't print anything out; 1: print out debugging statements

// logger

// Set the pins used
#define cardSelect 4


#define chipSelect 7
#define SDpower 6



    
File logfile;


// This line is not needed if you have Adafruit SAMD board package 1.6.2+
//   #define Serial SerialUSB

void setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out

digitalWrite(9, HIGH);
    delay(10);
    digitalWrite(9, LOW);
    
  
  pinMode(SDpower,OUTPUT);
  digitalWrite(SDpower,LOW);
  
  if(debug) Serial.begin(9600);

 // Serial.println("\r\nAnalog logger test");

  delay(1000);
  
  if (debug) Serial.println("\r\nAnalog logger test");
  pinMode(9, OUTPUT);


  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
 if(debug) Serial.println("Card init. failed!");
  }
  char filename[15];
  strcpy(filename, "ANALOG00.TXT");
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = '0' + i/10;
    filename[7] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  logfile = SD.open(filename, FILE_WRITE);
  if( ! logfile ) {
    if(debug) 
    {Serial.print("Couldnt create "); 
    Serial.println(filename);}
//    error(3);
  }
  if (debug) {
    Serial.print("Writing to "); 
  
  Serial.println(filename);
  }

 // pinMode(13, OUTPUT);
 // pinMode(8, OUTPUT);
 if(debug) Serial.println("Ready!");


  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    // Serial.println("BMP180 init success");
    int k = 0;
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    //Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }

  
}

uint8_t i=0;
void loop() {

char status;
  double T,P,p0,a;


  status = pressure.startTemperature();
 if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    status = pressure.getTemperature(T);

 if (status != 0)
    {

    int k=0;
 //Serial.print("temperature: ");
    //  Serial.print(T,2);
    //  Serial.print(" deg C, ");

  
status = pressure.startPressure(3);
      if (status != 0)
      {

 // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);

         if (status != 0)
        {
          int y = 3;

           }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");




        String dataString = "";
  
    dataString += micros();
    dataString += " ";
    dataString += P;
    dataString += " ";
    dataString += T;
    
      logfile.println(dataString);


    

      
      
      logfile.flush();

if(debug) Serial.println(dataString);

 digitalWrite(9, HIGH);
    delay(10);
    digitalWrite(9, LOW);



// otherwise we've pulled up the stoppin 
//error(5); // flash 5 times to indicate stop condition

  delay(200);

}


String padInt(int x, int pad) {
  String strInt = String(x);
  
  String str = "";
  
  if (strInt.length() >= pad) {
    return strInt;
  }
  
  for (int i=0; i < (pad-strInt.length()); i++) {
    str += "0";
  }
  
  str += strInt;
  
  return str;
}

String int2string(int x) {
  // formats an integer as a string assuming x is in 1/100ths
  String str = String(x);
  int strLen = str.length();
  if (strLen <= 2) {
    str = "0." + str;
  } else if (strLen <= 3) {
    str = str.substring(0, 1) + "." + str.substring(1);
  } else if (strLen <= 4) {
    str = str.substring(0, 2) + "." + str.substring(2);
  } else {
    str = "-9999";
  }
  
  return str;
}
