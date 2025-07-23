#include <SoftwareSerial.h>
const byte TX = 10; //pin10 is TX
const byte RX = 11; //pin11 is RX
const byte RTS = 12; //pin12 is RTS
const byte CTS = 13; //pin13 is CTS
char message; //сообщение
byte count = 0;
bool firstTimeInclude = true;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
void setup() {
Serial.begin(4800);
mySerial.begin(4800); //скорость передачи данных для com порта
pinMode(RTS, INPUT);
pinMode(CTS, OUTPUT);
}
void loop() {
if(firstTimeInclude){
while (true){
if(digitalRead(RTS) == HIGH){
digitalWrite(CTS, HIGH);
while (true){
if(mySerial.available() > 0){
message = mySerial.read(); //сообщение от
мастера
digitalWrite(CTS, LOW);
break;
}
}
break;
}
}
firstTimeInclude = false;
Serial.print(message);
Serial.print(' ');
}
else {
if(digitalRead(RTS) == HIGH){
digitalWrite(CTS, HIGH);
delay(1);
if(mySerial.available() > 0){
message = mySerial.read(); //сообщение от мастера
digitalWrite(CTS, LOW);
Serial.print("Recieved\n");
Serial.print(message);
while(true){
if(digitalRead(RTS) == HIGH){
mySerial.write(message); //отправляем
мастеру значение
break;
}
}
}
}
}
digitalWrite(CTS, LOW);
}
