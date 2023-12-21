#include <Arduino.h>

#define CLK 16
#define DT 17
#define SW 18

boolean button1WasUp = true;   // переменные для считывания нажатия на кнопки
boolean button2WasUp = true;

#include "GyverEncoder.h"
Encoder enc1(CLK, DT, SW);  // для работы c кнопкой

void setup() {
  Serial.begin(9600);
  enc1.setType(TYPE2);

  pinMode(2, INPUT_PULLUP);   // подключаем тактовые кнопки
  pinMode(3, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
	// обязательная функция отработки. Должна постоянно опрашиваться
  enc1.tick();
  
  if (enc1.isTurn()) {     // если был совершён поворот (индикатор поворота в любую сторону)
    // ваш код
  }
  
  if (enc1.isRight()) Serial.println("1002");         // если был поворот
  if (enc1.isLeft()) Serial.println("1001");
  
  if (enc1.isRightH()) Serial.println("1006"); // если было удержание + поворот
  if (enc1.isLeftH()) Serial.println("1005");
  
  //if (enc1.isPress()) Serial.println("Press");         // нажатие на кнопку (+ дебаунс)
  //if (enc1.isRelease()) Serial.println("Release");     // то же самое, что isClick
  
  // if (enc1.isClick()) Serial.println("Click");         // одиночный клик
  if (enc1.isSingle()) Serial.println("1003");       // одиночный клик (с таймаутом для двойного)
  if (enc1.isDouble()) Serial.println("1007");       // двойной клик
  
  
  if (enc1.isHolded()) Serial.println("1004");       // если была удержана и энк не поворачивался
  // if (enc1.isHold()) Serial.println("Hold");         // возвращает состояние кнопки

  boolean button1IsUp = digitalRead(2);   // узнаем текущее состояние кнопок
  boolean button2IsUp = digitalRead(3);

  // если кнопка 1 была нажата, увеличиваем переменную "x"
  if (button1WasUp && !button1IsUp) {
    delay(10);
    // button1IsUp = digitalRead(8);
    if (!button1IsUp) { Serial.println("2"); }
  }
  button1WasUp = button1IsUp; // запоминаем состояние кнопки 1

  // если кнопка 2 была нажата, уменьшаем переменную "x"
  if (button2WasUp && !button2IsUp) {
    delay(10);
    // button2IsUp = digitalRead(10);
    if (!button2IsUp) {Serial.println("3"); }
  }
  button2WasUp = button2IsUp; // запоминаем состояние кнопки 2
}