int analogPin = 0;
int analogValue = 0;
int ledPin = 7;

void setup() {
Serial.begin(9600);
pinMode(ledPin,OUTPUT);
}

void loop() {
  analogValue = analogRead(analogPin);
  Serial.println(analogValue);

  if(analogValue > 400)
  {
    analogWrite(ledPin,0);
  }else if(analogValue>350 && analogValue<400)
    {
    analogWrite(ledPin,31);
    }else if(analogValue>300 && analogValue<350)
    {
    analogWrite(ledPin,63);
    }else if(analogValue>250 && analogValue<300)
    {
    analogWrite(ledPin,95);
    }else if(analogValue>200 && analogValue<250)
    {
    analogWrite(ledPin,127);
    }else if(analogValue>150 && analogValue<200)
    {
    analogWrite(ledPin,159);
    }else if(analogValue>100 && analogValue<150)
    {
    analogWrite(ledPin,191);
    }else if(analogValue>50 && analogValue<100)
    {
    analogWrite(ledPin,223);
    }else if(analogValue>0 && analogValue<50)
    {
    analogWrite(ledPin,255);
    }

}
