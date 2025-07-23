#include <SoftwareSerial.h>
const byte RX = 10; //pin10 is RX
const byte TX = 11; //pin11 is TX
const byte RTS = 12; //pin12 is RTS
const byte CTS = 13; //pin13 is CTS
char message; //сообщение
bool firstTimeInclude = true;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
void setup() {
Serial.begin(4800);
5
mySerial.begin(4800); //скорость передачи данных для com порта
pinMode(RTS, OUTPUT);
pinMode(CTS, INPUT);
}
void loop() {
if (Serial.available() > 0){
digitalWrite(RTS, HIGH); //сигнал о готовности к приему (мастер готов
принимать данные)
message = Serial.read();
if (firstTimeInclude){
Serial.print(message);
Serial.print(' ');
firstTimeInclude = false;
}
while(true){
if (digitalRead(CTS) == HIGH){ //slave готов принимать данные
digitalWrite(RTS, LOW);
mySerial.write(message); //отправляем слэйву предыдущее
считанное сообщение
digitalWrite(RTS, HIGH);
break;
}
}
}
if (mySerial.available() > 0){
digitalWrite(RTS, LOW);
message = mySerial.read();
Serial.print(message);
Serial.print(" recieved frome slave\n");
digitalWrite(RTS, HIGH);
}
}
