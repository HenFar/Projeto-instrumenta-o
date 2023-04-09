#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  lcd.begin(16,02);
  lcd.clear();
  lcd.setBacklight(HIGH);
}

void loop() {

  int a;
  int b;
  int c;
  int d;

  int luz = 0;
  int q = 0;

  double v_audio = analogRead(0);  // audio setup
  Serial.print("audio: ");
  //Serial.println(v_audio);
  double v_a = v_audio * 5 / 1023;
  double db = map(v_a, 0, 1023, 0, 10);
  Serial.println(db);
  if (db > 70){
    a = 1;  // nivel amarelo
  }
  else if (db > 95){
    a = 2;  // nivel vermelho
  }
  else {
    a = 0;
  }

//Serial.print("\n");

  double v_light = analogRead(2);
  double r_v = v_light / 1023 * 5;
  double r_v_ldr = 5 - r_v;
  double r_ldr = r_v_ldr / r_v * 1000;
  double m = -1.4;
  double B = 12518931;
  double lx = B * pow(r_ldr, m);
  Serial.print("light: ");
  //Serial.println(v_light);
  Serial.println(lx);
  if (lx > 5000){
    b = 1;  // nivel amarelo
  }
  else if (lx > 10000){
    b = 2;  // nivel vermelho
  }
  else {
    b = 0;
  }

//Serial.print("\n");  

  double v_temp = analogRead(4);
  Serial.print("temp: ");
  //Serial.println(v_temp);
  double v_outT = v_temp * 5 / 1024;
  double temp = 100 * v_outT;  // LM35 muda 10mV/ºC começando em 0.25V para 25ºC
  Serial.println(temp);
  if (temp > 35){
    c = 1;  // nivel amarelo
  }
  else if (temp > 45){
    c = 2;  // nivel vermelho 
  }
  else{
    c = 0;
  }
  Serial.println(c);

//Serial.print("\n");  

  double v_fire = analogRead(6);
  //Serial.print("fire: ");
  //Serial.println(v_fire);
  if (v_fire < 1010){
    Serial.print("fogo!\n");
    d = 2;  // nivel vermelho
    //Serial.println(d);
  }
  else {
    d = 0;
  }

Serial.print("\n");

if (a==0 || b==0 || c==0 || d==0){
  luz = 0;
  q = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Safe");
  aviso(q);
}

if (a==1 || b==1 || c==1){
  luz = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aviso");
  if (a == 1){
    q = 1;
  }
  if (b == 1){
    q = 2;
  }
  if (c == 1){
    q = 3;
  }
  aviso(q);
}

if (a==2 || b==2 || c==2 || d==2){
  luz = 2;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Perigo");
  if (a == 2){
    q = 1;
  }
  if (b == 2){
    q = 2;
  }
  if (c == 2){
    q = 3;
  }
  if (d == 2){
    q = 4;
  }
  aviso(q);
}

Serial.println(luz);

if (luz == 0){
  verde();
  apagar_buzzer();
  Serial.print("verde \n");
}
else if (luz == 1){
  amarelo();
  apagar_buzzer();
  Serial.print("amarelo \n");
}
else if (luz == 2){
  vermelho();
  buzzer();
  Serial.print("vermelho \n");
}

  delay(1000);
}

void apagar(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void apagar_buzzer(){
  noTone(5);
}

void verde(){
  apagar();
  digitalWrite(3, HIGH);
}

void vermelho(){
  apagar();
  digitalWrite(2, HIGH);
}

void amarelo(){
  apagar();
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
}

void buzzer(){
  tone(5, 262);
  delay(500);
  tone(5, 370);
  delay(500);
}

int aviso(int x){
  switch (x){
      case 0:
        lcd.setCursor(0,1);
        lcd.print("Niveis normais");
        break;
      case 1:
        lcd.setCursor(0,1);
        lcd.print("Som elevado");
        break;
      case 2:
        lcd.setCursor(0,1);
        lcd.print("Int lumi elev");
        break;
      case 3:
        lcd.setCursor(0,1);
        lcd.print("Temp elevada");
        break;
      case 4:
        lcd.setCursor(0,1);
        lcd.print("Fogo");
        break;
  }
}
