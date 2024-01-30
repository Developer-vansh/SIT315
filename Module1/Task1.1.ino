
int pir=2;
void setup() {
  // put your setup code here, to run once:
  pinMode(pir,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pir)==HIGH){
    Serial.println("Motion Detected");
    digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(13,LOW);
  }
  delay(1000);

}