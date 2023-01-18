int motorA1 = 5;
int motorA2 = 6;  //Left Motor
int motorB1 = 9;
int motorB2 = 10; //Right Motor
int sensorL = A0; //Left sensor
int sensorR = A5; //Right sensor

void setup ( ) {  
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  pinMode(motorA1 , OUTPUT);
  pinMode(motorA2 , OUTPUT);
  pinMode(motorB1 , OUTPUT);
  pinMode(motorB2 , OUTPUT);
  pinMode(sensorL, INPUT);  
  pinMode(sensorR, INPUT);  
}

void loop ( )  {
  if(Serial.available()){
    char control = Serial.read();  // 자동차 동작 제어 + LED로 에너지상태 표시
    if(control == 'F'){              // control 값이 F이면 정지
        MotionControl(0, 0, 0, 0);
    }
    else if(control == 'T'){         // control 값이 T이면 라인을 따라 직진
      while(control == 'T'){
         int val1 = digitalRead(sensorL);
         int val2 = digitalRead(sensorR);
        if (val1 == 0 && val2 == 0) {                   // 직진
          MotionControl(110, 0 , 110, 0);
          }
        else if (val1 == 0 && val2 == 1) {              // 우회전
          MotionControl(230, 0 , 0 , 0);
          }
        else if (val1 == 1 && val2 == 0) {              // 좌회전
          MotionControl(0, 0, 230, 0);
         } 
        else if (val1 == 1 && val2 == 1){               // 정지
          MotionControl(0, 0, 0, 0);
         }
         char control = Serial.read();
        if (control == 'F'){
          MotionControl(0, 0, 0, 0);
          break;
        }
        }
      }
}
}

void MotionControl( int A1HL, int A2HL, int B1HL, int B2HL ){
  analogWrite( motorA1, A1HL );
  analogWrite( motorA2, A2HL );
  analogWrite( motorB1, B1HL );
  analogWrite( motorB2, B2HL );  
}
