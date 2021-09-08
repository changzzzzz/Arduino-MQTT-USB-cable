#include <Servo.h>
int pinLB=6; // define pin6 as left back connect with IN1
int pinLF=9; // define pin9 as left forward connect with IN2
int pinRB=10; // define pin10 as right back connect with IN3
int pinRF=11; // define pin11 as right back connect with IN4
int pinLInfred=13;
int pinRinfred=0;
int soilServo = 3;
int utralSoincServo = 5;
int soilHumidity=A2;



int inputPin = A0; // define ultrasonic receive pin (Echo)
int outputPin =A1; // define ultrasonic send pin(Trig)


int Fspeedd = 0; // forward distance
int Rspeedd = 0; // right distance
int Lspeedd = 0; // left distance
int directionn = 0; //

const byte numChars = 30;
char receivedChars[numChars]; // an array to store the received data
String received; //The data as a string
boolean newData = false;
Servo myservo; // new myservo
int delay_time = 250; // set stable time
int Fgo = 8;
int Rgo = 6;
int Lgo = 4;
int Bgo = 2;
// forward
// turn right
// turn left
// back
void setup()
{
    Serial.begin(9600);
    pinMode(pinLB,OUTPUT);
    pinMode(pinLF,OUTPUT);
    pinMode(pinRB,OUTPUT);
    pinMode(pinRF,OUTPUT);
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
    myservo.attach(5); // define the servo pin(PWM)
}
void advance(int a) // forward
{
    digitalWrite(pinRB,HIGH);
    digitalWrite(pinRF,LOW);
    digitalWrite(pinLB,HIGH);
    digitalWrite(pinLF,LOW);
    delay(a * 40);
}


void stopp(int f) //stop
{
    digitalWrite(pinRB,HIGH);
    digitalWrite(pinRF,HIGH);
    digitalWrite(pinLB,HIGH);
    digitalWrite(pinLF,HIGH);
    delay(f * 100);
}
void back(int g) //back
{
    digitalWrite(pinRB,LOW);
    digitalWrite(pinRF,HIGH);
    digitalWrite(pinLB,LOW);
    digitalWrite(pinLF,HIGH);
    delay(g * 300);
}

     
    




void recvWithEndMarker() 
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  
  while (Serial.available() > 0 && newData == false) 
  {
    rc = Serial.read();
    
    if (rc != endMarker) 
    {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) 
        {
        ndx = numChars - 1;
        }
    }
    else 
    {
      receivedChars[ndx] = '\0'; // terminate the string
      received = String(receivedChars);
      ndx = 0;
      newData = true;
    }
  }
}
void loop()
{
    /*
    myservo.write(90);
    detection();
    if(directionn == 2)
    {
    back(8);
    turnL(2);
    Serial.print(" Reverse ");
    }
    if(directionn == 6)
    {
    back(1);
    turnR(6);
    Serial.print(" Right ");
    }
    if(directionn == 4)
    {
    back(1);
    turnL(6);
    Serial.print(" Left ");
    }
    if(directionn == 8)
    {
    advance(1);
    Serial.print(" Advance ");
    Serial.print(" ");
    }
    */
    Serial.println("hello from arduino!");
    delay(10000);
    recvWithEndMarker();
    if (newData == true)
    {
      String instruction = received.substring(0,4);
      Serial.println(instruction);
      if(instruction == "move")
      {
          advance(1);
      }
    if(instruction == "stop")
    {
         stopp(1);
    }
    if(instruction == "back")
    {
        back(1);
    }
    newData = false;
    }  
    
    
    
}
