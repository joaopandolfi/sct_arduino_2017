#include <Servo.h>

// ================ MOTORES ===========

//Constantes de Pinagem
#define PIN_MOTOR_ESQUERDA  3
#define PIN_MOTOR_DIREITA  4

#define PIN_SENSOR_1 A1

//Constantes de controle
#define STOP_MOTOR 0
#define STOPED_M  90
#define L_BACK_MOTOR 0
#define L_FRONT_MOTOR 180 //Acertamos agora
#define R_BACK_MOTOR 180
#define R_FRONT_MOTOR 0 //Acertamos agora


//Variaveis
Servo motorEsquerda;
Servo motorDireita;

//Variavel de controle

int valS1,lastValS1;

// ============== CODIGO =================

void motorSetup(){
  //set pin motors
  motorEsquerda.attach(PIN_MOTOR_ESQUERDA);
  motorDireita.attach(PIN_MOTOR_DIREITA);
  //initialize motors
  motorEsquerda.write(STOP_MOTOR);
  motorDireita.write(STOP_MOTOR);
}

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
   }else{
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


// ===== FUNCOES DO SENSOR =====

void sensorsSetup(){
  pinMode(PIN_SENSOR_1,INPUT);
  lastValS1 = 0;
  valS1 =0;
}

// === SETUP ===
void setup() {
  motorSetup();
  sensorsSetup();
   Serial.begin(9600);
}

// === MAIN ===
void loop() {
  valS1 = analogRead(PIN_SENSOR_1);
  if(valS1 - lastValS1 > 100){
    Serial.println("PRETO");
  }
  else
    Serial.println("BRANCO");
  lastValS1 = valS1;
  
  delay(1000);
}




