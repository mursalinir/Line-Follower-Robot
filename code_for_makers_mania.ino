//initialization of Arduino pin
int m_l,s0,s1,s2,s3,s4,m_r;
int sensval=450;
int rig_m_f=2;
int rig_m_b=3;
int lef_m_f=4;
int lef_m_b=5;
int left_m_speed,right_m_speed;
int left,right,allWhite;
int left_maxspeed=150;
int right_maxspeed=150;
int max_speed=60;
int turn_speed=90;
int motorstop_time;

//setup arduino pin
void setup()
{
  Serial.begin(9600);
  pinMode(m_l,INPUT);
  pinMode(s0,INPUT);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(m_r,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
starting_speed();
  
}
//main function
void loop()
{
  analog_read();
  speed_value();
  motor_action();
  if(allWhite==1){
    mstop(50);
    if(left==1){
      mstop(100);
      left_turning();
    }
    else if (right==1){
      mstop(50);
      right_turning();
    }
    else {
      while(s2>sensval){
        analogWrite(lef_m_f,80);
        analogWrite(rig_m_f,80);
        analog_read();
        if(s2<sensval || s1<sensval || s3<sensval || s4<sensval || s0<sensval) break;}
 
    }
  }
  
}
//////////////////////
///analog_speed
///////////////////
void analog_read()
{
  m_l = analogRead(A0);
  s0 = analogRead(A1);
  s1 = analogRead(A2);
  s2 =analogRead(A3);
  s3 =analogRead(A4);
  s4 =analogRead(A5);
  m_r = analogRead(A6);
  
  if(m_l<450) {left=1; right=0; }
  if(s4<280) {right=1; left=0;}
  if(s0>sensval && s1>sensval && s2>sensval && s3>sensval && s4>280) allWhite=1; else allWhite=0;
}
///////////////////////////
// speed_value
/////////////////
void speed_value()
{
}
/////////////////////////////////
// motor_action
////////////////////////
void motor_action()
{
  analogWrite(lef_m_f,left_m_speed);
  analogWrite(rig_m_f,right_m_speed);
}
///////////////////////
//strating_speed
///////////////////////
void starting_speed()
{
  for(int speedv =0; speedv<max_speed;speedv++)
  {
    analogWrite(lef_m_f,speedv);
    analogWrite(rig_m_f,speedv);
    delay(2);
}
}
///////////  Left Turning ////////
void left_turning(){
  while(s2>sensval)
  {
    analogWrite(lef_m_f,turn_speed);
    analogWrite(rig_m_f,turn_speed);
    analog_read();
    speed_value();
    left=0; right=0;
    
  }
  left=0; right=0;
  
  mstop(50);
}
//////////////|||||||stop
void mstop(int time)
{
  analogWrite(lef_m_f,0);
  analogWrite(lef_m_b,0);
  analogWrite(rig_m_f,0);
  analogWrite(rig_m_b,0);
  delay(time);
}

//////////||||||| right_turning|||||||||||||||////////////////////
void right_turning()
{
  analogWrite(lef_m_f,turn_speed);
}

