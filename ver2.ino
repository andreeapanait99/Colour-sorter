#include <Servo.h>

#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define SENSOR_OUT 2
#define ORANGE_MIN_GREEN 43
#define ORANGE_MAX_GREEN 55
#define ORANGE_MIN_BLUE 35
#define ORANGE_MAX_BLUE 47
#define GREEN_MIN_RED 35
#define GREEN_MAX_RED 53
#define GREEN_MIN_GREEN 40
#define GREEN_MAX_GREEN 50
#define YELLOW_MIN_RED 24
#define YELLOW_MAX_RED 38
#define YELLOW_MIN_GREEN 30
#define YELLOW_MAX_GREEN 44
#define BLUE_MIN_GREEN 45
#define BLUE_MAX_GREEN 58
#define BLUE_MIN_BLUE 26
#define BLUE_MAX_BLUE 40
#define TOPSERVO_PIN 7
#define BOTTOMSERVO_PIN 8
#define TOPSERVO_LOW 60
#define TOPSERVO_MIDDLE 20
#define TOPSERVO_HIGH -30
#define TOPSERVO_INIT 115
#define BOTTOMSERVO_ORANGE 65
#define BOTTOMSERVO_GREEN 95
#define BOTTOMSERVO_YELLOW 125
#define BOTTOMSERVO_BLUE 150

Servo topServo;
Servo bottomServo;

int color = 0;

//function that reads colour
int readColor() 
{
  //Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  //Reading the output frequency
  int redFrequency = pulseIn(SENSOR_OUT, LOW);
  //Printing the value on the serial monitor
  Serial.print("R = "); 
  Serial.print(redFrequency); 
  Serial.print("  ");
  delay(50);
  //Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  //Reading the output frequency
  int greenFrequency = pulseIn(SENSOR_OUT, LOW);
  //Printing the value on the serial monitor
  Serial.print("G = ");
  Serial.print(greenFrequency);
  Serial.print("  ");
  delay(50);
  //Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  //Reading the output frequency
  int blueFrequency = pulseIn(SENSOR_OUT, LOW);
  //Printing the value on the serial monitor
  Serial.print("B = ");
  Serial.print(blueFrequency);
  Serial.println("  ");
  delay(50);
  if(greenFrequency < ORANGE_MAX_GREEN & greenFrequency > ORANGE_MIN_GREEN & blueFrequency < ORANGE_MAX_BLUE & blueFrequency > ORANGE_MIN_BLUE)
  {
    color = 1; // Orange
  }
  if(redFrequency < GREEN_MAX_RED & redFrequency > GREEN_MIN_RED & greenFrequency < GREEN_MAX_GREEN & greenFrequency > GREEN_MIN_GREEN)
  {
    color = 2; // Green
  }
  if(redFrequency < YELLOW_MAX_RED & redFrequency > YELLOW_MIN_RED & greenFrequency < YELLOW_MAX_GREEN & greenFrequency > YELLOW_MIN_GREEN)
  {
    color = 3; // Yellow
  }
  if (greenFrequency < BLUE_MAX_GREEN & greenFrequency > BLUE_MIN_GREEN & blueFrequency < BLUE_MAX_BLUE & blueFrequency > BLUE_MIN_BLUE)
  {
    color = 4; // Blue
  }
  return color;  
}

void setup() 
{
  //Setting the color sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);
  //Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
}
void loop() 
{
  //I attached and detached the servos because the vibrations interfered with the color sensor
  //Moving the top servo to retrieve the candy and to move it in front of the sensor
  topServo.attach(TOPSERVO_PIN);
  topServo.write(TOPSERVO_INIT);
  delay(500);
  for(int i = TOPSERVO_LOW; i > TOPSERVO_MIDDLE; i--) 
  {
    topServo.write(i);
    delay(2);
  }
  topServo.detach();
  delay(500);
  //reading the color
  color = readColor();
  //moving the bottom servo to the respective container
  bottomServo.attach(BOTTOMSERVO_PIN);
  delay(50);
  switch (color) 
  {
    case 1:
      bottomServo.write(BOTTOMSERVO_ORANGE);
      Serial.println("Orange");
      break;
    case 2:
      bottomServo.write(BOTTOMSERVO_GREEN);
      Serial.println("Green");
      break;
    case 3:
      bottomServo.write(BOTTOMSERVO_YELLOW);
      Serial.println("Yellow");
      break;
    case 4:
      bottomServo.write(BOTTOMSERVO_BLUE);
      Serial.println("Blue");
      break;
    default:
      break;
  }
  delay(300);
  bottomServo.detach();
  //moving the candy to the slider
  topServo.attach(TOPSERVO_PIN);
  for(int i = TOPSERVO_MIDDLE; i > TOPSERVO_HIGH; i--) 
  {
    topServo.write(i);
    delay(2);
  } 
  topServo.detach();
  delay(200);
  //moving the top servo back to the initial position
  topServo.attach(TOPSERVO_PIN);
  for(int i = TOPSERVO_HIGH; i < TOPSERVO_LOW; i++) 
  {
    topServo.write(i);
    delay(2);
  }
  topServo.detach();
  //reinitializing the color
  color = 0;
}
