#define REDPIN 11
#define GREENPIN 9
#define BLUEPIN 10

int r = 0;
int g = 0;
int b = 0;

void setup() {
  Serial.setTimeout(0);
  Serial.begin(9600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop(){
  if(Serial.available() > 4 && Serial.read() == 33){
    r = Serial.parseInt();
    g = Serial.parseInt();
    b = Serial.parseInt(); 

    analogWrite(REDPIN, r);
    analogWrite(GREENPIN, g);
    analogWrite(BLUEPIN, b);   

    /*Serial.println(r);
    Serial.println(g);
    Serial.println(b);*/
  }    
}




