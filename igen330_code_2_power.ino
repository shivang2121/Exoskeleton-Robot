

int M2A = 7; //when pin is HIGH the actuator extends
int M2B = 8; 
int M2PWM = 10;
int IN2 = 2; 
int IN1 = 4; //when pin is HIGH the actuator extends
int EN = 9;


void setup() {



  // put your setup code here, to run once:
pinMode(M2A,OUTPUT);
pinMode(M2B, OUTPUT);
pinMode(M2PWM, OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(EN, OUTPUT);
int i=0;
}

void loop() { 



digitalWrite(M2B,HIGH);
digitalWrite(M2A,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN1,HIGH);

analogWrite(M2PWM,175);
analogWrite(EN,255);
delay(1500);
analogWrite(M2PWM,0);
analogWrite(EN,0);
delay(10);

digitalWrite(M2B,LOW);
digitalWrite(M2A,HIGH);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);

analogWrite(M2PWM,175);
analogWrite(EN,255


);
delay(1500);
analogWrite(M2PWM,0);
analogWrite(EN,0);
delay(10);

} 
