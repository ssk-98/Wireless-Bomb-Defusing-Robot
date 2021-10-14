#include <ESP8266WiFi.h>  //header file to include NodeMCU libraries
#include<Servo.h>

char* ap ="poco"; //Enter the Phone wifi name
char* pass="243363592";
String recv="";
int count=0;
static int operation=0;
int SPEED=80,dir=1; //CLK = 1, AntiCLK = 0
//----------------------------------------
// operation = 1(CLK ON) 2(ACLK ON) 3(OFF)
Servo servo_top;
Servo servo_middle;
Servo servo_bottom;

WiFiServer wifiServer(5560);// Maintain this port always

int m[4]={16,5,4,0};
int middle_servo=0;
int bottom_servo=0;


void setup(){
  //Stircle 
 // pinMode(D1,OUTPUT);// PWM motor
  
  //

  
  for(int j=0;j<4;j++)
  {pinMode(m[j],OUTPUT);
  }
  servo_top.attach(12);
  servo_middle.attach(13);
  servo_bottom.attach(15);


 
  Serial.begin(115200);
  WiFi.begin(ap,pass);
  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting");
    } 
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  wifiServer.begin();

   

  }
  
  void loop(){
       get_data();

       if(recv=="forward")
       {
        
          move_forward();
          
       }

       else if(recv =="back")
       {
        move_backward();
       }
       
       else if(recv =="left")
       {
        move_left();
       }
       
       else if(recv =="right")
       {
        move_right();
       }
       
       else if(recv == "baseright")
       {
        turn_base_right();
       }
       
       else if(recv == "baseleft" )
       {
       turn_base_left();
       }
       
       else if(recv == "up" )
       {
        move_up();
       }
       else if(recv == "down" )
       {
        move_down();
       }
       else if(recv == "grip" )
       {
        grip();
       }
       else if(recv == "ungrip")
       {
        ungrip();
       }
       else if (recv[0]=='s')
       {
        stop_bot();
       }
  }

  void get_data(){ 
    WiFiClient client =  wifiServer.available();
    if(client){
      refresh();
      while(client.connected()){
        char c = client.read();
        if(int(c)>=10&&int(c)<=128){
            recv=recv+(String)c;
            }
      } 
    Serial.println(recv);
    client.stop();
             }         
       
  }

  void refresh(){
//    count=0;
//    for(int i=0;i<15;i++)
//        recv[i]=' ';
    recv="";
    }


  void move_forward()
  {refresh();
  digitalWrite(m[0],LOW);
  digitalWrite(m[1],HIGH);
  digitalWrite(m[2],HIGH);
  digitalWrite(m[3],LOW);
  
   Serial.println("123forward");
  }

  void move_backward()
  {refresh();
  digitalWrite(m[0],1);
  digitalWrite(m[1],0);
  digitalWrite(m[2],0);
  digitalWrite(m[3],1);
  
   Serial.println("123backward"); 
    
  }

  void move_left()
  {
refresh();
  digitalWrite(m[0],0);
  digitalWrite(m[1],1);
  digitalWrite(m[2],0);
  digitalWrite(m[3],1);
  Serial.println("123left"); 

  }

  void move_right()
  {refresh();
  digitalWrite(m[0],1);
  digitalWrite(m[1],0);
  digitalWrite(m[2],1);
  digitalWrite(m[3],0);
 Serial.println("123right"); 
    
  }
  

  void turn_base_right()
  {
   refresh();
Serial.println("baseright123");
if(bottom_servo<90){
for(int i=bottom_servo;i<=bottom_servo+10;i++)
{
  servo_bottom.write(i);
  delay(10);
  }
  bottom_servo+=10;
}
  }

  void turn_base_left()
  { refresh();
  if(bottom_servo>0){
    Serial.println("baseleft123");
    for(int i=bottom_servo;i>bottom_servo-10;i--)
  {
    servo_bottom.write(i);
    delay(10);
  }
  bottom_servo-=10;
  
  }

    
  }

  void move_up()
  {refresh();
    Serial.println("1231moveup");
    if(middle_servo>30){
     for(int i=middle_servo;i>middle_servo-10;i--)
  {
    servo_middle.write(i);
    delay(15);
  }
  middle_servo-=10;}
    
  }

  void move_down()
  {
  Serial.println("12movedown");
  refresh();
  if(middle_servo<100){ 
   for(int i=middle_servo;i<middle_servo+10;i++)
  {
    servo_middle.write(i);
    delay(15);
  }
  middle_servo+=10;}
  
  }

  void grip()
  {
   Serial.println("123grip"); 
   refresh();
    for(int i=90;i<120;i++)
  {
    servo_top.write(i);
    delay(10);
  }
  
  }

  void ungrip()
  {
 Serial.println("123ungrip");
 refresh();
 for(int i=120;i>90;i--)
  {
    servo_top.write(i);
    delay(10);
  }
  }

  void stop_bot()
  {refresh();
  digitalWrite(m[0],0);
  digitalWrite(m[1],0);
  digitalWrite(m[2],0);
  digitalWrite(m[3],0);
  Serial.println("123stop");
  }
