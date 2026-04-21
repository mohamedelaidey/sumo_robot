#include <NewPing.h>



#define max_distance 100

NewPing sonic_right(4, 5,max_distance);
NewPing sonic_left(2,3, max_distance);


int dist_left = 0;
int dist_right = 0;

int ir_right1=6;
int ir_right2=7;
int ir_left1=8;
int ir_left2=9;

int ena=10;
int enb=11;
int in1=12;
int in2=13;
int in3=14;
int in4=15;


unsigned long last_time = 0;  //ده متغير عامله عشان يقري الالترا سونيك كل .05 ثانيه في الif//
int currentSonic = 0;  //ده متغير عامله عشان لو صفر يقري الالترا الاول ولو1 يقري التاني//
unsigned long lastseen=0;  //ده متغير انا عامله عشان لو الروبوت قدامه فعلا ساعه الهجوم ولسبب ما سواء نويز او غيره القراءه بقت0 ف هقوله كمل هجوم لان دي قرايه غلط لانه ساعتها قدامه فعلا//
int speed_attack = 0;



void moveforward(){
  analogWrite(ena,180);
  analogWrite(enb,180);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}
void attack(){
  if(speed_attack < 255)
    speed_attack += 5;

  analogWrite(ena, speed_attack);
  analogWrite(enb, speed_attack);

  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
} 

void moveright(){
  analogWrite(ena, 180);
  analogWrite(enb, 180);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);

}
void moveleft(){
  analogWrite(ena, 180);
  analogWrite(enb, 180);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void search(){
  analogWrite(ena, 120);
  analogWrite(enb, 120);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}



void setup() {
  Serial.begin(9600);
  pinMode(ir_right1,INPUT);
  pinMode(ir_right2,INPUT);
  pinMode(ir_left1,INPUT);
  pinMode(ir_left2,INPUT);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
 
  }



void loop() {

  if (millis() - last_time >= 50) {  // هنا اهو بقوله كل .05 ثانيه تعدي روح اقري الالترا التاني//
    last_time = millis();
    if (currentSonic == 0) {
      dist_left = sonic_left.ping_cm();
      currentSonic = 1;
    } else {
      dist_right = sonic_right.ping_cm();
      currentSonic = 0;
    }
  }

  int irR=digitalRead(ir_right1)|| digitalRead(ir_right2) ;
  int irL=digitalRead(ir_left1) || digitalRead(ir_left2);

  if(irR==1 ){
    delayMicroseconds(1000);
    if(digitalRead(ir_right1)==1 || digitalRead(ir_right2)==1){  //عملتها مرتين عشان اتاكد انه قاري حاجه فعلا وابقي متجنب النويز
    speed_attack=0;
    moveright();
  }}

  else if(irL==1){
    delayMicroseconds(1000);
    if(digitalRead(ir_left1)==1 || digitalRead(ir_left2)==1 ){
    speed_attack=0;
    moveleft();
  }}

  else if ((dist_left >=0 && dist_left < 30) || (dist_right >=0 && dist_right < 30)) {
     lastseen=millis();
     attack();
  }

  else if(millis()-lastseen <1000){
    attack(); //ده السبب اللي انا عامله عشانه عشان لو القرايه اختفت فجاه بعد ما كان قاري انه قدامه فعلا ف كده الاختفاء ده مش صح والروبوت قدامه ف يكمل هجوم
  }

  else if ((dist_left >=30 && dist_left < 60) || (dist_right >=30 && dist_right < 60)) {
     speed_attack=0;
     moveforward();
  }
  else  {
    speed_attack=0;
    search();
  }
  
  }
   






