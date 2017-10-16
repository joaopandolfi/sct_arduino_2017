#include <Servo.h>

//[CALIBRATION - LINE_SENSOR]
#define SENSIBILITY 200 // 0 - 1023
#define DELAY_TO_READ 20 //ms

//Constantes de Pinagem
#define PIN_MOTOR_ESQUERDA  3
#define PIN_MOTOR_DIREITA  4

#define PIN_SENSOR_LEFT A3
#define PIN_SENSOR_MIDDLE A2
#define PIN_SENSOR_RIGHT A1

//Constantes de controle
#define STOP_MOTOR 95
#define STOPED_M  87
#define L_BACK_MOTOR 180
#define L_FRONT_MOTOR 0 
#define R_BACK_MOTOR 0
#define R_FRONT_MOTOR 180 

// ================ MOTORES ===========

//Variaveis
Servo motorEsquerda;
Servo motorDireita;

//Variavel de controle

int Right = 110, Left = 30, direita = 190, esquerda = 15;
int first_read_LEFT_s, first_read_MIDDLE_s, first_read_RIGHT_s;


//Inicialização dos motores
void motorSetup(){
  //set pin motors
  motorEsquerda.attach(PIN_MOTOR_ESQUERDA);
  motorDireita.attach(PIN_MOTOR_DIREITA);
  //initialize motors
  motorEsquerda.write(STOP_MOTOR);
  motorDireita.write(STOP_MOTOR);
}


// ====== CONTROLE DO MOTOR =======

void moveMotor(int left, int right){
  motorEsquerda.write(left);
  motorDireita.write(right);
}

void stopMotor(){
  motorEsquerda.detach();
  motorDireita.detach();
}

void unstopMotor(){
  motorEsquerda.attach(PIN_MOTOR_ESQUERDA);
  motorDireita.attach(PIN_MOTOR_DIREITA);
  
}

// ===== SENSORES =====

// ===== FUNCOES DOS SENSORES =====

//Inicialização dos sensores
void sensorsSetup() {
  //inicia os sensores
  pinMode(PIN_SENSOR_LEFT,INPUT);
  pinMode(PIN_SENSOR_MIDDLE,INPUT);
  pinMode(PIN_SENSOR_RIGHT,INPUT);
  // lê pela primeira vez os sensores
  first_read_LEFT_s = analogRead(PIN_SENSOR_LEFT);
  first_read_MIDDLE_s = analogRead(PIN_SENSOR_MIDDLE);
  first_read_RIGHT_s = analogRead(PIN_SENSOR_RIGHT);
}

//calc subtration module
int module(int a , int b){
  if(a>b)
    return a-b;
  return b-a;
}

// ===== BINARIZAÇÃO DAS LEITURAS ====

int sensor_linha_esquerda_reconheceu(){
  return (module(readLeftSensor(),first_read_LEFT_s) > SENSIBILITY);
}

int sensor_linha_meio_reconheceu(){
  return (module(readMiddleSensor(),first_read_MIDDLE_s) > SENSIBILITY);
}

int sensor_linha_direita_reconheceu(){
  return (module(readRightSensor(),first_read_RIGHT_s) > SENSIBILITY);
}


// ==== ENCAPSULAMENTO DA LEITURA DOS SENSORES =====

int readRightSensor(){
  return  analogRead(PIN_SENSOR_RIGHT);
}

int readMiddleSensor(){
  return analogRead(PIN_SENSOR_MIDDLE);
}

int readLeftSensor(){
  return analogRead(PIN_SENSOR_LEFT);
}


//========== TESTES ==========


//Testa os motores
void testMotor(){
  bool flag,flag2,flag3;
  flag = true;
  flag2 = false;
  while(1){
    //moveMotor(teste,teste);
    if(flag){
    //moveMotor(L_FRONT_MOTOR,R_FRONT_MOTOR);
      Serial.write("TESTE1\n");
    //motorSetup();
      moveMotor(L_BACK_MOTOR,R_BACK_MOTOR);
      flag = false;
      flag2 = false;
      Serial.write("FIm do 1\n");
    }
    else{
      if(flag2){
        Serial.write("TESTE2\n");
        motorSetup();
        moveMotor(L_FRONT_MOTOR,R_FRONT_MOTOR);
        flag = true;
        flag2 = false;
        Serial.write("FIM DO 2\n");
      }
      else{
        Serial.write("TESTE3\n");
        stopMotor();
        //moveMotor(STOP_MOTOR,STOP_MOTOR);
        flag2 = true;
        flag = false;
      }
    //
    //delay(1000);
    }
    delay(2000);
  }
}


//Testa os sensores
void testSensors(){
    Serial.write("\nDireito: ");
    Serial.println(analogRead(PIN_SENSOR_RIGHT));
    
    Serial.write("Meio: ");
    Serial.println(analogRead(PIN_SENSOR_MIDDLE));
    
    Serial.write("Esquerdo: ");
    Serial.println(analogRead(PIN_SENSOR_LEFT));

   delay(200);  

}


//=================================================================

//Serial.println(digitalRead(PIN_SENSOR_LEFT));

// === SETUP ===
void setup() {
  motorSetup();
  sensorsSetup();
   Serial.begin(9600);
}

void loop(){
    //Lê e printa os dados lidos dos sensores
    testSensors();
}

// === MAIN ===
void loop_old() {
  //moveMotor(Left,R_FRONT_MOTOR);
  if(sensor_linha_esquerda_reconheceu()){
    Serial.println(digitalRead(PIN_SENSOR_LEFT));
    Serial.write("Esquerdo.\n");
    moveMotor(Left,R_FRONT_MOTOR);
  }
  else if(sensor_linha_meio_reconheceu()){
    Serial.println(digitalRead(PIN_SENSOR_MIDDLE));
    Serial.write("Meio.\n");
    moveMotor(L_FRONT_MOTOR,R_FRONT_MOTOR);
  }
  else if(sensor_linha_direita_reconheceu()){
    Serial.println(digitalRead(PIN_SENSOR_RIGHT));
    Serial.write("Direito.\n");
    moveMotor(L_FRONT_MOTOR,Right);
  }
  else if((sensor_linha_direita_reconheceu())&&(sensor_linha_meio_reconheceu())){
    Serial.println(digitalRead(PIN_SENSOR_RIGHT));
    Serial.write("LEU O DIREITO E O DO MEIO.\n");
    moveMotor(L_FRONT_MOTOR,Right);
  }
  else if((sensor_linha_esquerda_reconheceu())&&(sensor_linha_meio_reconheceu())){
    Serial.println(digitalRead(PIN_SENSOR_LEFT));
    Serial.write("LEU O ESQUERDO E O DO MEIO.\n");
    moveMotor(Left,R_FRONT_MOTOR);
  }
  else{
    Serial.write("Nao reconheço porra nenhuma.\n");
    moveMotor(STOPED_M,STOP_MOTOR);
  }

    delay(DELAY_TO_READ);

  /*for(int x = 0; x>10;x++){
    moveMotor(Left,R_FRONT_MOTOR);
    delay(10000);
  }
  moveMotor(L_FRONT_MOTOR,direita);
  delay(1000);
  moveMotor(esquerda, R_FRONT_MOTOR);
  delay(1000);
  moveMotor(L_FRONT_MOTOR,direita);
  delay(1000);
  moveMotor(esquerda, R_FRONT_MOTOR);
  delay(1000);
  moveMotor(L_FRONT_MOTOR,direita);
  delay(1000);
  moveMotor(esquerda, R_FRONT_MOTOR);
  delay(1000);
  for(int x = 0; x>10;x++){
    moveMotor(esquerda,R_FRONT_MOTOR);
    delay(10000);
  }*/  
  //moveMotor(L_FRONT_MOTOR,Right);
}
