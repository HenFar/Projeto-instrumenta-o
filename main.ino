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
}

void loop() {

  int a;
  int b;
  int c;
  int d;

  int luz = 0;

  double v_audio = analogRead(0);  // audio setup
  Serial.print("audio: ");
  //Serial.println(v_audio);
  double v_a = v_audio * 5 / 1023;
  double db = map(v_audio, 0, 1023, 0, 10);
  Serial.println(db);
  if (db > 70){
    a = 1;  // nivel amarelo
  }
  if (db > 95){
    a = 2;  // nivel vermelho
  }
  else {
    a = 0;
  }

//Serial.print("\n");

  double v_light = analogRead(1);
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
  if (lx > 50000){
    b = 2;  // nivel vermelho
  }
  else {
    b = 0;
  }

//Serial.print("\n");  

  double v_temp = analogRead(2);
  Serial.print("temp: ");
  //Serial.println(v_temp);
  double v_outT = v_temp * 5 / 1024;
  double temp = 100 * v_outT;  // LM35 muda 10mV/ºC começando em 0.25V para 25ºC
  Serial.println(temp);
  if (temp > 35){
    c = 1;  // nivel amarelo
  }
  if (temp > 45){
    c = 2;  // nivel vermelho 
  }
  else {
    c = 0;
  }

//Serial.print("\n");  

  double v_fire = analogRead(3);
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
}

if (a==1 || b==1 || c==1){
  luz = 1;
}

if (a==2 || b==2 || c==2 || d==2){
  luz = 2;
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
  verde();
  vermelho();
}

void buzzer(){
  tone(5, 200);
}
