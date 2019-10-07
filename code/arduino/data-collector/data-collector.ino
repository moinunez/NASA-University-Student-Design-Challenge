/* 
    Note: most of the code shown below comes from library examples released under the MIT license. 
    Credit goes to: 

    1) Joel Bartlett from SparkFun Electronics (Soil Mositure Basic Example; Aug 31, 2015)
    2) DHT sensor documentation 

    To run this, you'll need to install the DHT library
*/

#include "DHT.h"

#define DHTPIN 21     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

const int SensorNumber = 16;
int soilPin[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15}; // This connects to all 16 moisture sensors
int soilPower[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};               // Variable for Soil moisture Power
int val[SensorNumber];  // value to store all sensors


void setup() 
{
  Serial.begin(9600);   // open serial over USB

  // For loop that sets up all of the sensors to their appropriate ports.
  for (int i = 0; i < SensorNumber; i++)
  {
    pinMode(soilPower[i], OUTPUT);    //Set D7 as an OUTPUT
    digitalWrite(soilPower[i], LOW);  //Set to LOW so no power is flowing through the sensor
  }
    
    // The following statement shows the order of data being collected
    Serial.println("Humidity,T in C,T in F,mS1,mS2,mS3,mS4,mS5,mS6,mS7,mS8,mS9,mS10,mS11,mS12,mS13,mS14,mS15,mS16");
    dht.begin();
}

void loop(){
  delay(1000*15); // Collects sensor data every ~15 or so seconds
  
  //Temp data
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print the data on the serial port for the python script to collect it
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(f);
  Serial.print(",");
  
  // Print the data that each moisture sensor holds
  for(int i=0; i<SensorNumber; i++)
  {
    digitalWrite(soilPower[i], HIGH);
    delay(10);
    val[i]=analogRead(soilPin[i]);
    digitalWrite(soilPower[i], LOW);
    
    int number = i+1;
    int value = val[i];
  //  Serial.print("Sensor1, Sensor2, Sensor3, Sensor4, Sensor5, Sensor6, Sensor 7, Sensor
  //  Serial.print("Sensor");
  //  Serial.print(number);
  //  Serial.print(" = ");
    Serial.print(value);
    Serial.print(",");
    number++;
 } 

  // move to the next line and repeat
  Serial.println();
}
