#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>

int greenLED = 5; //D1
int redLED = 4; //D2
int thresholdValue = 800;
// WiFi network info.
char ssid[] = "EnGenius3B7DBA";
char wifiPassword[] = "JBX56FMSZLAZ";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "d15b2400-4f06-11e9-b85b-afa01d2216d6";
char password[] = "3b80134ee706d3e1c8c8a386bb65a538b37af943";
char clientID[] = "f5b308e0-4f06-11e9-ba40-5d168a516101";

 
unsigned long lastMillis = 0;

void setup() {
   pinMode(A0,INPUT);
   pinMode(16, OUTPUT);
   pinMode(16, OUTPUT);
   pinMode(greenLED, OUTPUT);
   pinMode(redLED, OUTPUT);
   digitalWrite(greenLED, LOW);
   digitalWrite(redLED, LOW);
   
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();

  /// ADC0 - CHANNEL 0  
  Cayenne.virtualWrite(0, analogRead(A0));
 Serial.println(analogRead(A0));
  // Cayenne.virtualWrite(1, 0  );
  
//  /// ADC0 - CHANNEL 2  
// Cayenne.virtualWrite(2, analogRead(A0));
// delay(500);

// read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
    Serial.println(" - Doesn't need watering");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  else {
    Serial.println(" - Time to water your plant");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  delay(500);
  
}


//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.

///  WRITE state LED  - Escribe estado LED  

CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");

   int i = getValue.asInt();
   digitalWrite(16, i);
 
}
