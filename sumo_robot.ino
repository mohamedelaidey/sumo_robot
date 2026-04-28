#include <NewPing.h>

#define max_distance 100

NewPing sonic_right(2,3,max_distance);
NewPing sonic_left(4,5, max_distance);


int dist_left = 0;
int dist_right = 0;

int ir_right=A0;
int ir_left=A1;
int ir_back=A2;

int ena=10;
int enb=11;

int in13_1=6;
int in24_1=7; //دول الماتورين الشمال

int in13_2=8;
int in24_2=9; //دول الماتورين اليمين

//كده معانا بينات فاضيه 12,13//



unsigned long last_time = 0;  //ده متغير عامله عشان يقري الالترا سونيك كل .05 ثانيه في الif//
int currentSonic = 0;  //ده متغير عامله عشان لو صفر يقري الالترا الاول ولو1 يقري التاني//
unsigned long lastseen=0;  //ده متغير انا عامله عشان لو الروبوت قدامه فعلا ساعه الهجوم ولسبب ما سواء نويز او غيره القراءه بقت0 ف هقوله كمل هجوم لان دي قرايه غلط لانه ساعتها قدامه فعلا//
int speed_attack = 0;




void moveforward(int speed){
  analogWrite(ena,speed);
  analogWrite(enb,speed);
  digitalWrite(in13_1,HIGH);
  digitalWrite(in24_1,LOW);
  digitalWrite(in13_2,HIGH);
  digitalWrite(in24_2,LOW);
}
void attack(){
  if(speed_attack < 255)
    speed_attack += 5;

  analogWrite(ena, speed_attack);
  analogWrite(enb, speed_attack);

  digitalWrite(in13_1,HIGH);
  digitalWrite(in24_1,LOW);
  digitalWrite(in13_2,HIGH);
  digitalWrite(in24_2,LOW);
} 

void moveright(int speed){
  analogWrite(ena,speed);
  analogWrite(enb, speed);
  digitalWrite(in13_1,HIGH);
  digitalWrite(in24_1,LOW);
  digitalWrite(in13_2,LOW);
  digitalWrite(in24_2,HIGH);

}
void moveleft(int speed){
  analogWrite(ena, speed);
  analogWrite(enb, speed);
  digitalWrite(in13_1,LOW);
  digitalWrite(in24_1,HIGH);
  digitalWrite(in13_2,HIGH);
  digitalWrite(in24_2,LOW);
}
void search(){
  analogWrite(ena, 120);
  analogWrite(enb, 120);
  if (millis() % 4000 < 2000) //كدا بدل ما بسيرش في اتجاه واحد بقوله ف اول ثانيتين بص يمين وبعدها ب ثانيتين لو ملقيتوش دور شمال وهكذا
   moveright(120);
  else
   moveleft(120);
}



void setup() {
  Serial.begin(9600);
  pinMode(ir_right,INPUT);
  pinMode(ir_left,INPUT);
  pinMode(ir_back,INPUT);
  

  pinMode(in13_1,OUTPUT);
  pinMode(in24_1,OUTPUT);
  pinMode(in13_2,OUTPUT);
  pinMode(in24_2,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
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

  int irR=digitalRead(ir_right);
  int irL=digitalRead(ir_left);
  int irB=digitalRead(ir_back);

  if(irR==1 ){
    if(digitalRead(ir_right)==1){  //عملتها مرتين عشان اتاكد انه قاري حاجه فعلا وابقي متجنب النويز
    speed_attack=0;
    moveleft(255);
  }}

  else if(irL==1){
    if(digitalRead(ir_left)==1){
    speed_attack=0;
    moveright(255);
  }}
  else if(irB==1){
    moveforward(255);

  }


  else if ((dist_left >0 && dist_left < 30) || (dist_right >0 && dist_right < 30)) {
     lastseen=millis();
     attack();
  }

  else if(millis()-lastseen <1000){
    attack(); //ده السبب اللي انا عامله عشانه عشان لو القرايه اختفت فجاه بعد ما كان قاري انه قدامه فعلا ف كده الاختفاء ده مش صح والروبوت قدامه ف يكمل هجوم
  }

  else if ((dist_left >=30 && dist_left < 60) || (dist_right >=30 && dist_right < 60)) {
     speed_attack=0;
     moveforward(150);
  }
  else  {
    speed_attack=0;
    search();
  }
  
  }
   







   






