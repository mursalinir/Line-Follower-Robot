#include <NewPing.h>
#define trig_front 2
#define ech_front  51
#define max_front 300 

#define trig_left  3
#define ech_left 49
#define max_left 100

#define trig_right 4
#define ech_right  47
#define max_right   100

NewPing sonar_front(trig_front,ech_front,max_front);
NewPing sonar_left(trig_left, ech_left, max_left);
NewPing sonar_right(trig_right,ech_right, max_right);


int s0,s10,s1,s21,s2,s4,s34,s3,s23,x0,x10,x1,x21,x2,x4,x34,x3,x23,xL,xL0,xr,xr4,m_l,m_r,k=0,k_right=0;
int v0,v10,v1,v21,v2,v4,v34,v3,v23,vL,vL0,vr,vr4,left_m_speed,right_m_speed,sensval=150;
int temp2,temp1,s,t,sF,sL,sR;
int rig_m_b=2;
int rig_m_f=3;
int lef_m_f=4;
int lef_m_b=5;
const int Switch=12;
int left_maxspeed=170;  
int right_maxspeed=170;
int max_speed =100;
int c0,c1,m,c3,c4;
int l_sum,r_sum,cave;
int n,pin;
int turn_speed=90;
int motorstop_time =100;

void setup()
{  
  Serial.begin(9600);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s0,INPUT);
  digitalWrite(53,HIGH);
  pinMode(lef_m_f,OUTPUT);
  pinMode(lef_m_b,OUTPUT);
  pinMode(rig_m_f,OUTPUT);
  pinMode(rig_m_b,OUTPUT);
  pinMode(Switch,INPUT);
  digitalWrite(Switch,HIGH);
  while((digitalRead(Switch)));
  delay(1000);
  starting_speed();
 
}
void loop()
{
  analog_read();
  speed_value();
  motor_action();
  sL= sonar_left.ping_cm();
  Serial.println(sL);
  if(sL<45 && sL>1 && cave==1){
    analogWrite(lef_m_f,80);
    analogWrite(rig_m_f,80);
    delay(200);
    sL= sonar_left.ping_cm();
    if(sL<45 && sL>1){
    while(sL<50){
      temp1=1;
      analog_read();
    if(m_l>sensval || s0>sensval || s1>sensval || s2>sensval || s3>sensval || s4>sensval || m_r>sensval){break;}
    
      sL= sonar_left.ping_cm();
      Serial.print("left: ");
      Serial.println(sL);
      analogWrite(lef_m_f,90);
      analogWrite(rig_m_f,70);
    while(sL<18){
      analogWrite(lef_m_f,140);
      analogWrite(rig_m_f,60);
      sL= sonar_left.ping_cm();
      analog_read();
      if(sL>18|| m_l>sensval || s0>sensval || s1>sensval || s2>sensval || s3>sensval || s4>sensval || m_r>sensval ){break;}
    }
    while(sL>22){
      analogWrite(lef_m_f,60);
      analogWrite(rig_m_f,100);
      sL= sonar_left.ping_cm();
      analog_read();
      if(sL<22|| m_l>sensval || s0>sensval || s1>sensval || s2>sensval || s3>sensval || s4>sensval || m_r>sensval ){break;}
    }
    analog_read();
    if(m_l>sensval || s0>sensval || s1>sensval || s2>sensval || s3>sensval || s4>sensval || m_r>sensval){break;}
    }
    }
    mstop(50);
  }
 
  
/////////////////////////////////////////////////////////////////////////
//               LEFT TURNNING
//////////////////////////////////////////////////////////////////////////////////////////////
 if(m_l>sensval || s0>sensval)
 {
    n=1;
    t=1;
    analog_read();
    speed_value();
    motor_action();   
    
  }
   if((m_l<sensval && s0<sensval && s1<sensval && s2<sensval && s3<sensval && s4<sensval && m_r<sensval) && (n==1))
   { 
     mstop(50);
     left_turning();
    
  } 
   
   
   ////////////////////////////////////////////////////////////////////////////////////////
   //                          RIGHT TURNING
   ////////////////////////////////////////////////////////////////////////////////////////
   
    if(m_r>sensval || s4>sensval)
   {
    n=5;
    t=1;
    analog_read();
    speed_value();
    motor_action();
  }
   if((m_l<sensval && s0<sensval && s1<sensval && s2<sensval && s3<sensval && s4<sensval && m_r<sensval) && (n==5))
   { 
     mstop(50);
     right_turning();
  }
  
    
  
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//   speed value
//////////////////////////////////////////////////////////////////////////////////////////////////
void speed_value()
{
  //|||||||||||||||||||||||left sensot||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
if(s0>sensval && s1 <sensval && s2 <sensval){v0=left_maxspeed; c0 =0;x0=k;}      else {v0=0;}
if(s0>sensval && s1 >sensval && s2 <sensval){v10=left_maxspeed*3/4;x10=5;x10=k;} else {v10=0;}
if(s0<sensval && s1 >sensval && s2 <sensval){v1=left_maxspeed*1/2; c1=1;x1=k;}  else {v1=0;}
if(s0<sensval && s1 >sensval && s2 >sensval){v21=left_maxspeed*1/4;x21=k;} else {v21=0;}
/////////////////////////////////////midle/////////////////////////////////////////////////////////
if(s0<sensval && s1<sensval && s2 >sensval && s3<sensval && s4 <sensval){m=2;x0=0;x10=0;x1=0;x21=0;x2=0;x4=0;x34=0;x3=0;x23=0;}else {v4=0;}
// |||||||||||||||||||||||||| right side ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//if(s1>sensval && s2>sensval && s3 >sensval && s4>sensval && m_r<sensval){right_turning();}
if(s2<sensval && s3 <sensval && s4 >sensval){v4=right_maxspeed;c4=4;x4=k;}else {v4=0;}
if(s2<sensval && s3 >sensval && s4 >sensval){v34=right_maxspeed*3/4;x34=30;x34=k;}else {v34=0;}
if(s2<sensval && s3 >sensval && s4 <sensval){v3=right_maxspeed*1/2;c3=3;x3=k;}else {v3=0;}
if(s2>sensval && s3 >sensval && s4 <sensval){v23=right_maxspeed*1/4;x23=k;}else {v23=0;}

if(m_l>sensval && s0>sensval && s1>sensval && s2>sensval && s3>sensval && s4>sensval && m_r>sensval){cave=1;n=0;}

if(s2>sensval && s3>sensval && s4>sensval && temp1==1){
  temp2=1;
  temp1=2;
  mstop(1000);
  analogWrite(lef_m_f,100);
  analogWrite(rig_m_b,100);
  delay(450);
  mstop(50);
  //right_turning();
}



if(s0<sensval && s1<sensval && s2<sensval && s3<sensval && s4<sensval &&temp2==1 && n==0){
  delay(70); 
    analog_read();
    if(s0<sensval && s1<sensval && s2<sensval && s3<sensval && s4<sensval){ mstop(20000);}
}
right_m_speed = (right_maxspeed+x0+x10+x1+x21-v3-v4-v34-v23);
left_m_speed = (left_maxspeed+x3+x4+x34+x23-v0-v10-v1-v21);
}

// |||||||||||||||||| left turning ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void left_turning(){
  mstop(50);
   while(s2<sensval)
   {
    analogWrite(lef_m_b,turn_speed);
    analogWrite(rig_m_f,turn_speed);   // comeback in midle position
    analog_read();
    speed_value();
    }
    n=0;
   if(m==2 )  // m==2 comes from speed_value && analog read
   {
     n=0;
    mstop(100);
    starting_speed();
    
   m=3;
  }
}

// ||||||||||||||||||||||||||||||||||| Right Turning ||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void right_turning(){
  mstop(50);

   while(s2<sensval)
   {
    analogWrite(lef_m_f,turn_speed);  // come back in midle position
    analogWrite(rig_m_b,turn_speed);
    analog_read();
    speed_value();
  
  }
  n=0;
   if(m==2 )
   {
    n=0;
    mstop(100);
    starting_speed();
    m=3;
   // Serial.println("motor came back");
    
 }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// analogRead
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void analog_read()
{  
t++;
//if(t>90){n=0;}
m_r =analogRead(A0);  // most right
s4 =analogRead(A1);
s3 =analogRead(A2);
s2 =analogRead(A3);
s1 =analogRead(A4);  // most left
s0=analogRead(A5);
m_l= analogRead(A6);
  
}
//////////////////////////////////////////////////////////////////
// motor action
//////////////////////////////////////////////////////////////////
void motor_action()
{
  //Serial.println("Ok motor action");
analogWrite(lef_m_f,left_m_speed);
analogWrite(rig_m_f,right_m_speed);
  
}

//////////////////////////////////////////////////////////////////////
// stop
////////////////////////////////////////////////////////////////////////

void mstop(int time)
{
  analogWrite(lef_m_f,0);
   analogWrite(lef_m_b,0);
   analogWrite(rig_m_f,0);
  analogWrite(rig_m_b,0);
  delay(time);
}
/////////////////////////////////////////////////////////////////////////
//                    starting_speed
///////////////////////////////////////////////////////////////////////
void starting_speed()
{
  for(int speedv = 0;speedv<max_speed;speedv++)
  {
   analogWrite(lef_m_f,speedv);
   analogWrite(rig_m_f,speedv); 
   //delay(2);
    
  }
  
}

