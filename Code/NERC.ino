#include <Encoder.h>
#include <Servo.h>

Servo myservo; 
int pos = 65;
// Define the pins for the encoders
#define ENCODER1_A 2
#define ENCODER1_B 5
#define ENCODER2_A 3
#define ENCODER2_B 4

// Define the pins for the motor control
#define L_in1 42// LEFT MOTOR
#define L_in2 43 // LEFT MOTOR reverse
#define R_in1 40 // right MOTOR
#define R_in2 41// RIGHT MOTOR reverse
#define LEFT_Motor_PWM 7
#define RIGHT_Motor_PWM 6

// Define the pins for the sensors
#define MS 23 // right MOTOR
#define RS 24
#define RRS 25
#define LS 26
#define LLS 27
#define S1 28
#define S2 29
#define LBACK 36
#define RBACK 37
#define LMBACK 34
#define RMBACK 35

int map_arr[] = {48,46,47,
                 49,51,50};
                 
int map_arr_value[6];

int pulsel=0;
int pulser=0;
// Create instances of the Encoder class
Encoder encoder1(ENCODER1_A, ENCODER1_B);
Encoder encoder2(ENCODER2_A, ENCODER2_B);
int counter= -2;
int lspd=160;
int rspd=160;
int ll=210;
int rr=210;
int stop_forward_speed=110;

void setup() 
{ // Set motor control pins as outputs
  Serial.begin(9600);
  pinMode(R_in1, OUTPUT);
  pinMode(L_in2, OUTPUT);
  pinMode(R_in2, OUTPUT);
  pinMode(L_in1, OUTPUT);
  pinMode(LEFT_Motor_PWM, OUTPUT);
  pinMode(RIGHT_Motor_PWM, OUTPUT);
  // Set all of the sensor pins to inputs
  pinMode(LS, INPUT);
  pinMode(LLS, INPUT);
  pinMode(RS, INPUT);
  pinMode(RRS, INPUT);
  pinMode(MS,INPUT);
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(RBACK,INPUT);
  pinMode(LBACK,INPUT);
  for(int i = 0;i<6;i++)
  {
    pinMode(map_arr[i],INPUT);
  }
  myservo.attach(10);
  // Servo is stationary.
  myservo.write(100);
}

void rotate180(int a, int b)
{
  stop();
  delay(500);
// Move motor 1 forward
  encoder1.write(0);
  encoder2.write(0);
  int encoder_L = encoder2.read();
  int encoder_R = encoder1.read();
  int middleSensor = digitalRead(MS);

  while(encoder_R<2050&&encoder_L>-2050)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1,HIGH);
    digitalWrite(L_in2, HIGH);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  while(encoder_L>-2050)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1,LOW);
    digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  while(encoder_R<2050)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1,HIGH);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }

  pulsel=encoder1.read();
  pulser=encoder2.read();
  Serial.print("Pulse left Count: " );
  Serial.println(pulsel);
  Serial.print("Pulse right Count: " );
  Serial.println(pulser);
  encoder1.write(0);
  encoder2.write(0);
   encoder_L = encoder2.read();
   encoder_R = encoder1.read();
  
  while(encoder_L<50 && encoder_R<50 )
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, HIGH);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, stop_forward_speed);
    analogWrite(RIGHT_Motor_PWM, stop_forward_speed);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  stop();  
}

void rotateRight11(int a, int b)
{
  stop();
  delay(300);

  encoder1.write(0);
  encoder2.write(0);
  int encoder_L = encoder2.read();
  int encoder_R = encoder1.read();
  
  while(encoder_L<250 && encoder_R<250)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, HIGH);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, stop_forward_speed);
    analogWrite(RIGHT_Motor_PWM, stop_forward_speed);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }

  encoder1.write(0);
  encoder2.write(0);
  encoder_L = encoder2.read();
  encoder_R = encoder1.read();
  int rightSensor = digitalRead(RS);

  while(encoder_L<1050 && encoder_R>-950 )
  {
    digitalWrite(R_in2, HIGH);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
    rightSensor = digitalRead(RS);
  }
  while(encoder_R>-950 )
  {
    digitalWrite(R_in2, HIGH);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  while(encoder_L<1050)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  stop();
  pulser=encoder1.read();
  pulsel=encoder2.read();
  Serial.print("Pulse left Count: " );
  Serial.println(pulsel);
  Serial.print("Pulse right Count: " );
  Serial.println(pulser);
}

void rotateRight(int a, int b)
{
  stop();
  delay(350);
  int L_MS = digitalRead(S1);
  int R_MS = digitalRead(S2);
  
  while(R_MS==1 && L_MS == 1)
  {
    goStraightAlign(stop_forward_speed,stop_forward_speed);
    L_MS = digitalRead(S1);
    R_MS = digitalRead(S2);
  }

  encoder1.write(0);
  encoder2.write(0);
  int encoder_L = encoder2.read();
  int encoder_R = encoder1.read();
  
  /*while(encoder_L<10 && encoder_R<10 )
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, HIGH);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, stop_forward_speed);
    analogWrite(RIGHT_Motor_PWM, stop_forward_speed);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }*/

  encoder1.write(0);
  encoder2.write(0);
  encoder_L = encoder2.read();
  encoder_R = encoder1.read();
  int rightSensor = digitalRead(RS);

  while(encoder_L<500 && encoder_R>-500 )
  {
    digitalWrite(R_in2, HIGH);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
    rightSensor = digitalRead(RS);
  }
  while(rightSensor == 1)
  {
    digitalWrite(R_in2, HIGH);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, HIGH);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    rightSensor = digitalRead(RS);
  }

  stop();
  pulser=encoder1.read();
  pulsel=encoder2.read();
  Serial.print("Pulse left Count: " );
  Serial.println(pulsel);
  Serial.print("Pulse right Count: " );
  Serial.println(pulser);
}

void rotateLeft(int a, int b)
{
  stop();
  delay(300);
  int L_MS = digitalRead(S1);
  int R_MS = digitalRead(S2);
  
  while(R_MS==1 && L_MS == 1)
  {
    L_MS = digitalRead(S1);
    R_MS = digitalRead(S2);
    goStraightAlign(stop_forward_speed,stop_forward_speed);
  }
  encoder1.write(0);
  encoder2.write(0);
  int encoder_L = encoder2.read();
  int encoder_R = encoder1.read();
  
  while(encoder_R<1010 && encoder_L>-930)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, HIGH);
    digitalWrite(L_in2, HIGH);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a+20);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  while(encoder_L>-930)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, HIGH);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  while(encoder_R<1010)
  {
    digitalWrite(R_in2, LOW);
    digitalWrite(R_in1, HIGH);
    digitalWrite(L_in2, LOW);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }  
  stop();
  pulser=encoder1.read();
  pulsel=encoder2.read();
  Serial.print("Pulse left Count: " );
  Serial.println(pulsel);
  Serial.print("Pulse right Count: " );
  Serial.println(pulser);
}

void stop()
{
  digitalWrite(R_in2, LOW);
  digitalWrite(R_in1, LOW);
  digitalWrite(L_in2, LOW);
  digitalWrite(L_in1, LOW);
  analogWrite(LEFT_Motor_PWM, 0);
  analogWrite(RIGHT_Motor_PWM, 0);
}

void goStraightAlign(int a, int b) 
{
  digitalWrite(R_in2, LOW);
  digitalWrite(R_in1, HIGH);
  digitalWrite(L_in2, LOW);
  digitalWrite(L_in1, HIGH);
  analogWrite(LEFT_Motor_PWM, a);
  analogWrite(RIGHT_Motor_PWM, b);
}
void goback(int a, int b) 
{
  digitalWrite(R_in2, HIGH);
  digitalWrite(R_in1, LOW);
  digitalWrite(L_in2, HIGH);
  digitalWrite(L_in1, LOW);
  analogWrite(LEFT_Motor_PWM, a);
  analogWrite(RIGHT_Motor_PWM, b);
}

void goback1(int a, int b, int encoder_L_value, int encoder_R_value) 
{
  encoder1.write(0);
  encoder2.write(0);
  int encoder_L = encoder2.read();
  int encoder_R = encoder1.read();

  while(encoder_L> encoder_L_value && encoder_R> encoder_R_value)
  {
    digitalWrite(R_in2, HIGH);
    digitalWrite(R_in1, LOW);
    digitalWrite(L_in2, HIGH);
    digitalWrite(L_in1, LOW);
    analogWrite(LEFT_Motor_PWM, a);
    analogWrite(RIGHT_Motor_PWM, b);
    encoder_L = encoder2.read();
    encoder_R = encoder1.read();
  }
  stop();
  pulser=encoder1.read();
  pulsel=encoder2.read();
  Serial.print("Pulse left Count: " );
  Serial.println(pulsel);
  Serial.print("Pulse right Count: " );
  Serial.println(pulser);
}

void turnSlightlyLeft(int a, int b) 
{
  digitalWrite(R_in2, LOW);
  digitalWrite(R_in1, HIGH);
  digitalWrite(L_in2, LOW);
  digitalWrite(L_in1, HIGH);
  analogWrite(LEFT_Motor_PWM, a); 
  analogWrite(RIGHT_Motor_PWM, b); 
}

void turnSlightlyRight(int a, int b)
{
  digitalWrite(R_in2, LOW);
  digitalWrite(R_in1, HIGH);
  digitalWrite(L_in2, LOW);
  digitalWrite(L_in1, HIGH);
  analogWrite(LEFT_Motor_PWM, a); 
  analogWrite(RIGHT_Motor_PWM, b); 
}

void pick()
{
  myservo.write(0);
  delay(300);
  int L_BS = digitalRead(LBACK);
  int R_BS = digitalRead(RBACK); 
  while(L_BS == 1 && R_BS ==1 )
  {
    int leftSensor = digitalRead(LS);
    int rightSensor = digitalRead(RS);
    leftSensor = !leftSensor;
    rightSensor = !rightSensor;

    if (leftSensor == 0  && rightSensor == 0) 
    {  
        goStraightAlign(stop_forward_speed,stop_forward_speed);
    }
    else if (leftSensor==0 && rightSensor ==1 )
    {   
        turnSlightlyRight(lspd+20,0);
    }
          
    else if (leftSensor==1 && rightSensor ==0 )
    {
        turnSlightlyLeft(0,rspd+20);
    }
    else
    {
        goStraightAlign(stop_forward_speed,stop_forward_speed);
    }
    L_BS = digitalRead(LBACK);
    R_BS = digitalRead(RBACK);
  }
  stop();
  delay(300);
  myservo.write(pos);
  delay(600);
}

void drop() 
{
  int L_BS = digitalRead(LBACK);
  int R_BS = digitalRead(RBACK); 
  while(L_BS==1 && R_BS==1 )
  {
    int leftSensor = digitalRead(LS);
    int rightSensor = digitalRead(RS);
    leftSensor = !leftSensor;
    rightSensor = !rightSensor;
    if (leftSensor == 0  && rightSensor == 0) 
    {  
        goStraightAlign(stop_forward_speed,stop_forward_speed);
    }
    else if (leftSensor==0 && rightSensor ==1 )
    {   
        turnSlightlyRight(lspd+20,0);
    }
    else if (leftSensor==1 && rightSensor ==0 )
    {
        turnSlightlyLeft(0,rspd+20);
    }
    else
    {
        goStraightAlign(stop_forward_speed,stop_forward_speed);
    }
    L_BS = digitalRead(LBACK);
    R_BS = digitalRead(RBACK);
  }
  stop();
  delay(300);
  int i = 60;
  for (i = 60; i > 0; i-=4)
  {
      myservo.write(i);
      delay(80);
  }
  delay(300);
}

void map_reading()
{
  stop();
  delay(150);
  int a = 0;
  while (a < 2)
  {
    if (a == 0)
    {
      encoder1.write(0);
      encoder2.write(0);
      int encoder_L = encoder2.read();
      int encoder_R = encoder1.read();
      while(encoder_L<600 && encoder_R<600)
      {
        int leftSensor = digitalRead(LS);
        int rightSensor = digitalRead(RS);
        leftSensor = !leftSensor;
        rightSensor = !rightSensor;
        if (leftSensor == 0  && rightSensor == 0) 
        {  
            goStraightAlign(stop_forward_speed,stop_forward_speed);
        }
        else if (leftSensor==0 && rightSensor ==1 )
        {   
            turnSlightlyRight(lspd+20,0);
        }
        else if (leftSensor==1 && rightSensor ==0 )
        {
            turnSlightlyLeft(0,rspd+20);
        }
        else
        {
            goStraightAlign(stop_forward_speed,stop_forward_speed);
        }
        encoder_L = encoder2.read();
        encoder_R = encoder1.read();
      }
      stop();
    }
    if (a==1)
    {
      int L_BS = digitalRead(LBACK);
      int R_BS = digitalRead(RBACK); 
      while(L_BS == 1 && R_BS ==1 )
      {
        int leftSensor = digitalRead(LS);
        int rightSensor = digitalRead(RS);
        leftSensor = !leftSensor;
        rightSensor = !rightSensor;

        if (leftSensor == 0  && rightSensor == 0) 
        {  
            goStraightAlign(stop_forward_speed,stop_forward_speed);
        }
        else if (leftSensor==0 && rightSensor ==1 )
        {   
            turnSlightlyRight(lspd+20,0);
        }
              
        else if (leftSensor==1 && rightSensor ==0 )
        {
            turnSlightlyLeft(0,rspd+20);
        }
        else
        {
            goStraightAlign(stop_forward_speed,stop_forward_speed);
        }
        L_BS = digitalRead(LBACK);
        R_BS = digitalRead(RBACK);
      }
      stop();
      
    }

    encoder1.write(0);
    encoder2.write(0);
    int encoder_L = encoder2.read();
    int encoder_R = encoder1.read();
    
    while(encoder_L>-1150 && encoder_R>-1150 )
    {
      
      int leftSensor = digitalRead(LMBACK);
      int leftMostSensor = digitalRead(LBACK);
      int rightSensor = digitalRead(RMBACK);
      int rightMostSensor = digitalRead(RBACK);
      
      leftSensor = !leftSensor;
      leftMostSensor = !leftMostSensor;
      rightSensor = !rightSensor;
      rightMostSensor = !rightMostSensor;

      if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
      {  
        goback(stop_forward_speed,stop_forward_speed);
      }
      else if (leftSensor==0 && rightSensor ==1 )
      {   
        goback(0,rspd+10);
      }
            
      else if (leftSensor==1 && rightSensor ==0 )
      {
        goback(lspd+10,0);
      }
      
      else if (leftMostSensor==1 && rightSensor ==0 )
      { 
        goback(lspd+30,0);
      }
      else if (leftSensor==0 && rightMostSensor ==1 )
      {  
        goback(0,rspd+30);
      }
      else
      {
        goback(stop_forward_speed,stop_forward_speed);
      }
      encoder_L = encoder2.read();
      encoder_R = encoder1.read();
    }
    stop();
    delay(300);
    a++;
  }
  for(int i = 0; i<6; i++)
    {
      map_arr_value[i] = !digitalRead(map_arr[i]);
      Serial.print(map_arr_value[i]);
    }
}


void loop() 
{
  int leftSensor = digitalRead(LS);
  int leftMostSensor = digitalRead(LLS);
  int rightSensor = digitalRead(RS);
  int rightMostSensor = digitalRead(RRS);
  int middleSensor = digitalRead(MS);

  int L_MS = digitalRead(S1);
  int R_MS = digitalRead(S2);

  leftSensor = !leftSensor;
  leftMostSensor = !leftMostSensor;
  rightSensor = !rightSensor;
  rightMostSensor = !rightMostSensor;

  Serial.println(counter);
  if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
  {  
    goStraightAlign(100,100);
  }
  else if (leftSensor==0 && rightSensor ==1 )
  {   
    turnSlightlyRight(lspd+20,0);
  }
      
  else if (leftSensor==1 && rightSensor ==0 )
  {
    turnSlightlyLeft(0,rspd+20);
  }
 
  else if (leftMostSensor==1 && rightSensor ==0 )
  { 
    turnSlightlyLeft(0,rspd+50);
  }
  else if (leftSensor==0 && rightMostSensor ==1 )
  {  
    turnSlightlyRight(lspd+50,0);
  }
 
  // Juction
  else if  (rightMostSensor==1 && leftMostSensor==1 && rightSensor==1 && leftSensor==1)
  {
   if (counter < 0 )
   {
    goStraightAlign(100,100);
    delay(90);
    counter++;    
   }
   if (counter == 0)
   {
    stop();
    delay(300);
    rotateLeft(ll,rr);      
    map_reading();
    rotateRight11(ll,rr);
    counter = 2;
   }

   if (counter == 2)
   {
      goStraightAlign(lspd,rspd);
      delay(90);

      // CASE 1
      if (map_arr_value[2]==1 && map_arr_value[4]==1 )
      {
        while(1)
        {
          int leftSensor = digitalRead(LS);
          int leftMostSensor = digitalRead(LLS);
          int rightSensor = digitalRead(RS);
          int rightMostSensor = digitalRead(RRS);
          int middleSensor = digitalRead(MS);

          int L_MS = digitalRead(S1);
          int R_MS = digitalRead(S2);

          leftSensor = !leftSensor;
          leftMostSensor = !leftMostSensor;
          rightSensor = !rightSensor;
          rightMostSensor = !rightMostSensor;

          Serial.println(counter);
          if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
          {  
              goStraightAlign(lspd,rspd);
          }
          else if (leftSensor==0 && rightSensor ==1 )
          {   
              turnSlightlyRight(lspd+20,0);
          }
                
          else if (leftSensor==1 && rightSensor ==0 )
          {
              turnSlightlyLeft(0,rspd+20);
          }
          
          else if (leftMostSensor==1 && rightSensor ==0 )
          { 
              turnSlightlyLeft(0,rspd+50);
          }
          else if (leftSensor==0 && rightMostSensor ==1 )
          {  
              turnSlightlyRight(lspd+50,0);
          }
          
          // Juction
          else if  (rightMostSensor==1 && leftMostSensor==1 && rightSensor==1 && leftSensor==1)
          {
            if (counter < 3 )
            {
              goStraightAlign(lspd,rspd);
              delay(80);
              counter++;    
            }
            else if (counter==4||counter==6||counter==7||counter==11||counter==13||counter==14||counter==17||counter==20||counter==23||counter==24||
                    counter==28||counter==30||counter==33||counter==40||counter==44||counter==47||counter==49||counter==61||counter==62||counter==63)
            {
              goStraightAlign(lspd,rspd);
              delay(110);
              counter++;
            }
            else if ( counter==3||counter==5||counter==12||counter==26||counter==35||counter==46||counter==52||counter==60)
            {
              rotateRight(ll,rr);
              counter++;
            }
            else if (counter==8||counter==9||counter==18||counter==19||counter==27||counter==29||counter==31||counter==34||counter==37||counter==38||
                    counter==39||counter==41||counter==55||counter==56)
            {
              rotateLeft(ll,rr);
              /*goStraightAlign(lspd-50,rspd-50);
              delay(500);*/   
              counter++;
            }
            else if (counter==16||counter==22||counter==43||counter==48||counter==51||counter==54||counter==58)
            {
              rotate180(ll,rr);  
              counter++;
            }
            else if (counter==15||counter==25||counter==36||counter==45||counter==53||counter==59)
            {
              stop();
              delay(300);
              drop();
              goback1(lspd,rspd,-950,-950);
              delay(500);
              myservo.write(pos);
              delay(500);
              counter++;
            }
            else if (counter==10||counter==21||counter==32||counter==42||counter==50||counter==57)
            {
              stop();
              delay(300);
              pick();
              counter++;
            }

            else if (counter==64)
            {
              goStraightAlign(lspd,rspd);
              delay(450);   
              stop();
              while(1){}
            }
          }
          else
          {
            goStraightAlign(lspd,rspd);
          }
        }
      }
      // CASE 2
      else if (map_arr_value[0]==1 && map_arr_value[4]==1 )
      {
        while(1)
        {
          int leftSensor = digitalRead(LS);
          int leftMostSensor = digitalRead(LLS);
          int rightSensor = digitalRead(RS);
          int rightMostSensor = digitalRead(RRS);
          int middleSensor = digitalRead(MS);

          int L_MS = digitalRead(S1);
          int R_MS = digitalRead(S2);

          leftSensor = !leftSensor;
          leftMostSensor = !leftMostSensor;
          rightSensor = !rightSensor;
          rightMostSensor = !rightMostSensor;

          Serial.println(counter);
          if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
          {  
              goStraightAlign(lspd,rspd);
          }
          else if (leftSensor==0 && rightSensor ==1 )
          {   
              turnSlightlyRight(lspd+20,0);
          }
                
          else if (leftSensor==1 && rightSensor ==0 )
          {
              turnSlightlyLeft(0,rspd+20);
          }
          
          else if (leftMostSensor==1 && rightSensor ==0 )
          { 
              turnSlightlyLeft(0,rspd+50);
          }
          else if (leftSensor==0 && rightMostSensor ==1 )
          {  
              turnSlightlyRight(lspd+50,0);
          }
          
          // Juction
          else if  (rightMostSensor==1 && leftMostSensor==1 && rightSensor==1 && leftSensor==1)
          {
            if (counter < 3 )
            {
              goStraightAlign(lspd,rspd);
              delay(100);
              counter++;    
            }
            else if (counter==4||counter==5||counter==7||counter==10||counter==11||counter==13||counter==14||counter==17||counter==23||counter==24||counter==38
                    ||counter==53)
            {
              goStraightAlign(lspd,rspd);
              delay(130);
              counter++;
            }
            else if ( counter==3||counter==6||counter==12||counter==16||counter==18||counter==29||counter==30||counter==34||counter==35||counter==47||counter==48
                      ||counter==52)
            {
              rotateRight(ll,rr);
              counter++;
            }
            else if (counter==19||counter==20||counter==26||counter==31||counter==40||counter==44)
            {
              rotateLeft(ll,rr);
              /*goStraightAlign(lspd-50,rspd-50);
              delay(500);*/   
              counter++;
            }
            else if (counter==9||counter==22||counter==27||counter==33||counter==37||counter==41||counter==43||counter==46||counter==50)
            {
              rotate180(ll,rr);  
              counter++;
            }
            else if (counter==15||counter==25||counter==32||counter==39||counter==45||counter==51)
            {
              stop();
              delay(300);
              drop();
              goback1(lspd,rspd,-950,-950);
              delay(500);
              myservo.write(pos);
              delay(500);
              counter++;
            }
            else if (counter==8||counter==21||counter==28||counter==36||counter==42||counter==49)
            {
              stop();
              delay(300);
              pick();
              counter++;
            }

            else if (counter==54)
            {
              goStraightAlign(lspd,rspd);
              delay(450);   
              stop();
              while(1){}
            }
          }
          else
          {
            goStraightAlign(lspd,rspd);
          }
        }
      }
      // CASE 3
      else if (map_arr_value[1]==1 && map_arr_value[3]==1)
      {
        while(1)
        {
          int leftSensor = digitalRead(LS);
          int leftMostSensor = digitalRead(LLS);
          int rightSensor = digitalRead(RS);
          int rightMostSensor = digitalRead(RRS);
          int middleSensor = digitalRead(MS);

          int L_MS = digitalRead(S1);
          int R_MS = digitalRead(S2);

          leftSensor = !leftSensor;
          leftMostSensor = !leftMostSensor;
          rightSensor = !rightSensor;
          rightMostSensor = !rightMostSensor;

          Serial.println(counter);
          if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
          {  
              goStraightAlign(lspd,rspd);
          }
          else if (leftSensor==0 && rightSensor ==1 )
          {   
              turnSlightlyRight(lspd+20,0);
          }
                
          else if (leftSensor==1 && rightSensor ==0 )
          {
              turnSlightlyLeft(0,rspd+20);
          }
          
          else if (leftMostSensor==1 && rightSensor ==0 )
          { 
              turnSlightlyLeft(0,rspd+50);
          }
          else if (leftSensor==0 && rightMostSensor ==1 )
          {  
              turnSlightlyRight(lspd+50,0);
          }
          
          // Juction
          else if  (rightMostSensor==1 && leftMostSensor==1 && rightSensor==1 && leftSensor==1)
          {
            if (counter < 3 )
            {
              goStraightAlign(lspd,rspd);
              delay(80);
              counter++;    
            }
            else if (counter==4||counter==10||counter==17||counter==32||counter==34||counter==39||counter==49||counter==54||counter==56||counter==57||counter==58
                    ||counter==59)
            {
              goStraightAlign(lspd,rspd);
              delay(140);
              counter++;
            }
            else if ( counter==3||counter==5||counter==9||counter==19||counter==23||counter==25||counter==26||counter==33||counter==35||counter==41
                      ||counter==43||counter==48||counter==50)
            {
              rotateRight(ll,rr);
              counter++;
            }
            else if (counter==6||counter==8||counter==13||counter==14||counter==31||counter==38||counter==40||counter==47||counter==53||counter==55)
            {
              rotateLeft(ll,rr);
              /*goStraightAlign(lspd-50,rspd-50);
              delay(500);*/   
              counter++;
            }
            else if (counter==12||counter==16||counter==20||counter==22||counter==27||counter==29||counter==37||counter==44||counter==46||counter==52)
            {
              rotate180(ll,rr);  
              counter++;
            }
            else if (counter==11||counter==18||counter==24||counter==30||counter==51)
            {
              stop();
              delay(300);
              drop();
              goback1(lspd,rspd,-950,-950);
              delay(500);
              myservo.write(pos);
              delay(500);
              counter++;
            }
            else if (counter==7||counter==15||counter==21||counter==28||counter==36||counter==45)
            {
              stop();
              delay(500);
              pick();
              counter++;
            }

            else if (counter==42)
            {
              stop();
              delay(300);
              goback1(lspd,rspd, -300, -300);
              delay(500);
              int i = 60;
              for (i = 60; i > 0; i-=4)
              {
                myservo.write(i);
                delay(80);
              }
              delay(300);
              goback1(lspd,rspd, -600, -600);
              delay(500);
              myservo.write(pos);
              delay(500);
              rotateRight(ll,rr);
              counter++;
            }
            else if (counter==60)
            {
              goStraightAlign(lspd,rspd);
              delay(450);   
              stop();
              while(1){}
            }
          }
          else
          {
            goStraightAlign(lspd,rspd);
          }
        }
      }
      // CASE 4
      else if (map_arr_value[1]==1 && map_arr_value[5]==1)
      {
        while(1)
        {
          int leftSensor = digitalRead(LS);
          int leftMostSensor = digitalRead(LLS);
          int rightSensor = digitalRead(RS);
          int rightMostSensor = digitalRead(RRS);
          int middleSensor = digitalRead(MS);

          int L_MS = digitalRead(S1);
          int R_MS = digitalRead(S2);

          leftSensor = !leftSensor;
          leftMostSensor = !leftMostSensor;
          rightSensor = !rightSensor;
          rightMostSensor = !rightMostSensor;

          Serial.println(counter);
          if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
          {  
              goStraightAlign(lspd,rspd);
          }
          else if (leftSensor==0 && rightSensor ==1 )
          {   
              turnSlightlyRight(lspd+20,0);
          }
                
          else if (leftSensor==1 && rightSensor ==0 )
          {
              turnSlightlyLeft(0,rspd+20);
          }
          
          else if (leftMostSensor==1 && rightSensor ==0 )
          { 
              turnSlightlyLeft(0,rspd+50);
          }
          else if (leftSensor==0 && rightMostSensor ==1 )
          {  
              turnSlightlyRight(lspd+50,0);
          }
          
          // Juction
          else if  (rightMostSensor==1 && leftMostSensor==1 && rightSensor==1 && leftSensor==1)
          {
            if (counter < 3 )
            {
              goStraightAlign(lspd,rspd);
              delay(80);
              counter++;    
            }
            else if (counter==4||counter==6||counter==10||counter==12||counter==15||counter==18||counter==23||counter==27||counter==29||counter==34||
                    counter==36||counter==37||counter==40||counter==45||counter==60||counter==61)
            {
              goStraightAlign(lspd,rspd);
              delay(130);
              counter++;
            }
            else if ( counter==3||counter==5||counter==11||counter==21||counter==26||counter==33||counter==35||counter==39||counter==41||counter==54||
                      counter==55||counter==59)
            {
              rotateRight(ll,rr);
              counter++;
            }
            else if (counter==7||counter==9||counter==16||counter==17||counter==22||counter==24||counter==28||counter==30||counter==47||counter==51)
            {
              rotateLeft(ll,rr);
              /*goStraightAlign(lspd-50,rspd-50);
              delay(500);*/   
              counter++;
            }
            else if (counter==14||counter==20||counter==32||counter==42||counter==44||counter==48||counter==50||counter==53||counter==57)
            {
              rotate180(ll,rr);  
              counter++;
            }
            else if (counter==13||counter==25||counter==38||counter==46||counter==52||counter==58)
            {
              stop();
              delay(300);
              drop();
              goback1(lspd,rspd,-950,-950);
              delay(500);
              myservo.write(pos);
              delay(500);
              counter++;
            }
            else if (counter==8||counter==19||counter==31||counter==43||counter==49||counter==56)
            {
              stop();
              delay(300);
              pick();
              counter++;
            }

            else if (counter == 302)
            {
              stop();
              delay(300);
              goback1(lspd,rspd, -300, -300);
              delay(500);
              int i = 60;
              for (i = 60; i > 0; i-=4)
              {
                myservo.write(i);
                delay(80);
              }
              delay(500);
              goback1(lspd,rspd, -600, -600);
              delay(500);
              myservo.write(pos);
              delay(500);
              rotateRight(ll,rr);
              counter++;
            }
            else if (counter==62)
            {
              goStraightAlign(lspd,rspd);
              delay(450);   
              stop();
              while(1){}
            }
          }
          else
          {
            goStraightAlign(lspd,rspd);
          }
        }
      }
      // CASE 5
      else
      {
        while(1)
        {
          int leftSensor = digitalRead(LS);
          int leftMostSensor = digitalRead(LLS);
          int rightSensor = digitalRead(RS);
          int rightMostSensor = digitalRead(RRS);
          int middleSensor = digitalRead(MS);

          int L_MS = digitalRead(S1);
          int R_MS = digitalRead(S2);

          leftSensor = !leftSensor;
          leftMostSensor = !leftMostSensor;
          rightSensor = !rightSensor;
          rightMostSensor = !rightMostSensor;

          Serial.println(counter);
          if (leftSensor == 0  && rightSensor == 0 && leftMostSensor==0 && rightMostSensor ==0) 
          {  
              goStraightAlign(lspd,rspd);
          }
          else if (leftSensor==0 && rightSensor ==1 )
          {   
              turnSlightlyRight(lspd+20,0);
          }
                
          else if (leftSensor==1 && rightSensor ==0 )
          {
              turnSlightlyLeft(0,rspd+20);
          }
          
          else if (leftMostSensor==1 && rightSensor ==0 )
          { 
              turnSlightlyLeft(0,rspd+50);
          }
          else if (leftSensor==0 && rightMostSensor ==1 )
          {  
              turnSlightlyRight(lspd+50,0);
          }
          
          // Juction
          else if  (rightMostSensor==1 && leftMostSensor==1 && rightSensor==1 && leftSensor==1)
          {
              if (counter < 3 )
              {
                goStraightAlign(lspd,rspd);
                delay(80);
                counter++;    
              }
              else if (counter==4||counter==7||counter==13||counter==16||counter==22||counter==23||counter==25||counter==40||counter==41||
                      counter==28||counter==38||counter==45||counter==55||counter==56||counter==57)
              {
                goStraightAlign(lspd,rspd);
                delay(130);
                counter++;
              }
              else if ( counter==3||counter==5||counter==10||counter==20||counter==30||counter==32||counter==42||
                      counter==39||counter==43||counter==47||counter==49||counter==54)
              {
                rotateRight(ll,rr);
                counter++;
              }
              else if (counter==6||counter==9||counter==14||counter==15||counter==21||counter==24||counter==26||counter==29||counter==37||counter==46)
              {
                rotateLeft(ll,rr);
                /*goStraightAlign(lspd-50,rspd-50);
                delay(500);*/   
                counter++;
              }
              else if (counter==12||counter==18||counter==33||counter==35||counter==50||counter==52)
              {
                rotate180(ll,rr);  
                counter++;
              }
              else if (counter==11||counter==19||counter==36||counter==53)
              {
                stop();
                delay(300);
                drop();
                goback1(lspd,rspd,-950,-950);
                delay(500);
                myservo.write(pos);
                delay(500);
                counter++;
              }
              else if (counter==8||counter==17||counter==27||counter==34||counter==44||counter==51)
              {
                stop();
                delay(300);
                pick();
                counter++;
              }

              else if (counter==31||counter==48)
              {
                stop();
                delay(300);
                goback1(lspd,rspd, -300, -300);
                delay(500);
                int i = 60;
                for (i = 60; i > 0; i-=4)
                {
                  myservo.write(i);
                  delay(80);
                }
                delay(500);
                goback1(lspd,rspd, -600, -600);
                delay(500);
                myservo.write(pos);
                delay(300);
                rotateRight(ll,rr);
                counter++;
              }
              
              else if (counter==58)
              {
                goStraightAlign(lspd,rspd);
                delay(450);   
                stop();
                while(1){}
              }

          }
          else
          {
            goStraightAlign(lspd,rspd);
          }
        }
      }
   }
  }
   else
          {
            goStraightAlign(lspd,rspd);
          }
}
  


