#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int value; 
volatile bool switchFlag = 0;
bool switchVal = 0;
int switchPin = 7;

void setup ()
{
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(switchPin), onoff, CHANGE);
  switchVal = digitalRead(switchPin);
}

void loop()
{
  value = CircuitPlayground.temperatureF();
  Serial.print("Temp (Farenheit): ");
  Serial.println(value);
  delay(100);

  if(value >= 84 && !switchVal)
  {
    CircuitPlayground.playTone(500, 100);
    delay(100);
  }  

// Soil Moisture
int val = CircuitPlayground.readCap(6);
  val = map(val, 550, 1023, 0, 255);
Serial.print("Soil Moisture: ");
Serial.println(CircuitPlayground.readCap(6));  


for (int i = 5; i < 10; i++)
{
  CircuitPlayground.setPixelColor(i, 0, val, val);
}

//Light
 int light = CircuitPlayground.lightSensor();
  light = map(light, 0, 1023, 0, 255);
  
  Serial.print("Light Sensor: ");
  Serial.println(light);

Serial.println(value);

int LED_num = random(5);
  CircuitPlayground.setPixelColor(LED_num, light, light, light);
  delay(150);
  CircuitPlayground.setPixelColor(LED_num, 0, 0, 0);



if(light < 20 && !switchVal)
{
  CircuitPlayground.playTone(70, 400);
  CircuitPlayground.playTone(60, 100);
  CircuitPlayground.playTone(50, 200);  
  Serial.println("Sound on");
}


if (switchFlag)
  {
    delay(5);
    switchVal = digitalRead(switchPin); 
    switchFlag = 0;              
  }
if(switchVal)
  {
    Serial.print("Night Mode: ");    
    Serial.println("on");
  } else if(!switchVal)
  {
    Serial.print("Night Mode: ");    
    Serial.println("off");    
  }

}


void onoff()
{
  switchFlag = 1;        
}

