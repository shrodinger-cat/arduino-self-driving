int pwmA = 3;

int pwmB = 11;

int brakePin = 9;

int dirB = 13;

int dirA = 12;

int left = 0;

int right = 0;

int object = false;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(dirA, OUTPUT);
}

void loop()
{
  if (0.006783 * readUltrasonicDistance(4, 5) < 5)   
  {
    object = true;
    Serial.println("object detected");
    analogWrite(pwmA, 0);
    analogWrite(pwmB, 0);
    Serial.println("right");      
    digitalWrite(dirB,  HIGH);
    analogWrite(pwmA, 200);
    analogWrite(pwmB, 230);
    delay(600);
    right = 0.006783 * readUltrasonicDistance(4, 5);
    Serial.println("left");
    digitalWrite(dirB, LOW);
    analogWrite(pwmA, 200);
    analogWrite(pwmB, 230);      
    delay(1200);
    left = 0.006783 * readUltrasonicDistance(4, 5);
    
    if (right < left)
    {
      
      Serial.println("turning left");
      digitalWrite(dirA, LOW);
      digitalWrite(dirB, HIGH);
      analogWrite(pwmA, 200);
      analogWrite(pwmB, 230);
      object = false;
    }
    else if (right > left)
    {     
      Serial.println("turning right");
      digitalWrite(dirA, HIGH);
      digitalWrite(dirB, LOW);
      analogWrite(pwmA, 200);
      analogWrite(pwmB, 230);
      object = false;
    }
    
  }
  else if (object != true)
  {
    Serial.println("forward");
    digitalWrite(dirB, HIGH);
    digitalWrite(dirA, LOW);
    analogWrite(pwmB, 230);
    analogWrite(pwmA, 200);
  }
}
