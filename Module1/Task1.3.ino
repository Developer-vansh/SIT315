int pir1=2;
int pir2=3;
int buzzer=12;
int rLed=11;
int gLed=10;
void setup() {
  pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(rLed,OUTPUT);
  pinMode(gLed,OUTPUT);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pir1),Act1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pir2),Act2,CHANGE);
}

void loop() 
{
  delay(500);
}
void Act1() 
{
  if(digitalRead(pir1)==HIGH){
    Serial.println("Motion Detected at Pir1");
    digitalWrite(13,LOW);
     digitalWrite(rLed,HIGH);
  digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
    digitalWrite(rLed,LOW);
    digitalWrite(13,HIGH);
  }
}
void Act2() 
{
  if(digitalRead(pir2)==HIGH){
    Serial.println("Motion Detected at Pir2");
    digitalWrite(13,LOW);
     digitalWrite(gLed,HIGH);
  digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
    digitalWrite(gLed,LOW);
    digitalWrite(13,HIGH);
  }
}