// Инициализируем библиотеки
#include "cgAnem.h"
#include <Wire.h>
#include <GyverOLED.h>

#include "FlowPlot.h"
#include "FlowPlot.cpp"

#define ADC_pin A0 // задаём значение пина АЦП
#define PLOT_COUNTS 60 //количество отсчетов на графике

GyverOLED<SSH1106_128x64> oled; // Инициализируем OLED-экран
CG_Anem cgAnem(ANEM_I2C_ADDR); // Инициализируем CG_Anem
FlowPlot<PLOT_COUNTS> flowPlot;

uint16_t ADC; // Переменная для значений АЦП
uint32_t timer_cnt; // Таймер для измерений анемометра
uint32_t timer_bat; // Таймер для измерения заряда батареи
const uint8_t *p;
uint8_t height = 40;
float flow;

void setup() {
  char buf[10];
  int8_t timeToWait = 10;
  int8_t warmRectWidth = 60;
  pinMode(ADC_pin, OUTPUT); // Инициализируем АЦП как получатель данных
  oled.init(); // Инициализируем OLED в коде
  oled.flipV(1); // Я перевернул экран для удобства
  oled.flipH(1); // Для нормального отображения после переворота нужно инвертировать текст по горизонтали
  oled.clear();

  oled.setCursor(0, 0);
  sprintf(buf, "HW: %.1f", cgAnem.getFirmwareVersion()); 
  oled.print(buf);

  oled.setCursor(0, 5);
  oled.print("Warming");

  oled.setScale(2); // Устанавливаем размер шрифта
  oled.setCursor(20, 2);
  oled.print("CG_Anem");

  oled.rect(45, 40, 45+warmRectWidth, 48, OLED_STROKE);
  oled.update();

  cgAnem.init();
  for (int i = 0; i <= timeToWait; i++) { // Функция таймера служит для предварительного нагрева анемометра перед использованием
    oled.rect(45, 40, 45+warmRectWidth/timeToWait*i, 48, OLED_FILL);
    oled.update();
    delay(1000);
    oled.update();
  }
  delay(1000);
  oled.clear();
  oled.update();
  oled.setScale(1);
  flowPlot.init(height);
  p = flowPlot.getPoints();
}

void loop() {
  char buf[50];
  if (millis() - timer_cnt > 1000) { // Снимаем показания с анемометра и выводим их на экран
    timer_cnt = millis();
    // Проверяем, обновляются ли данные с анемометра. Если да - выводим их, если нет - предупреждаем об ошибке
    if (cgAnem.data_update()) {
      flow = cgAnem.getAirflowRate();
      flowPlot.pushValue(flow);
      sprintf(buf, "V: %.1f m/s ", flow); // Собираем строку с показаниями скорости потока
      oled.setCursor(0, 1);
      oled.print(buf);
      sprintf(buf, "T: %.1f C ", cgAnem.getTemperature()); // Собираем строку с показаниями температуры
      oled.setCursor(0, 3);
      oled.print(buf);
    }
    else {
      oled.setCursor(45, 3);
      oled.print("*");
    }
  }

  if (millis() - timer_bat > 10000) { //
    timer_bat = millis();
    ADC = analogRead(ADC_pin); // Считываем показание с АЦП
    oled.rect(104, 3, 124, 10, OLED_STROKE); // Рисуем иконку батарейки
    oled.rect(125, 5, 127, 8, OLED_FILL);
    if (ADC >= 970) {
      oled.rect(104, 3, 124, 10, OLED_FILL);
    }
    if (ADC < 970 && ADC >= 870) {
      oled.rect(106, 3, 119, 10, OLED_FILL);
    }
    if (ADC < 870 && ADC >= 770) {
      oled.rect(106, 3, 114, 10, OLED_FILL);
    }
  }

  oled.rect(60, 10, 60 + PLOT_COUNTS, 10 + height, OLED_CLEAR);
  oled.rect(60, 10, 60 + PLOT_COUNTS, 10 + height, OLED_STROKE);
  for (uint8_t i = 0; i < PLOT_COUNTS; i++) {
    oled.dot(60 + i, 10 + p[i], OLED_FILL);
  }
  sprintf(buf, "M: %.1f m/s ", flowPlot.getMeanFlow()); // Собираем строку с показаниями температуры
  oled.setCursor(0, 5);
  oled.print(buf);
  oled.update();
}
