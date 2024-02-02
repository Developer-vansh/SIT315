
int pir=2;
int buzzer=12;
void setup() {
  // put your setup code here, to run once:
  pinMode(pir,INPUT);
   pinMode(buzzer,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pir),Act,CHANGE);
}

void loop() 
{
  delay(500);
}
void Act() 
{
  if(digitalRead(pir)==HIGH){
    Serial.println("Motion Detected");
    digitalWrite(13,LOW);
  digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
        digitalWrite(13,HIGH);
  }
}

