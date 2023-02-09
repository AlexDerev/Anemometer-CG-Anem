// Инициализируем библиотеки
#include "cgAnem.h"
#include <Wire.h>
#include <GyverOLED.h>

#include "FlowPlot.h"
#include "FlowPlot.cpp"

#define ADC_pin A0 // задаём значение пина АЦП
#define PLOT_LEFT   67  // левая граница графика
#define PLOT_TOP    10  // левая граница графика
#define PLOT_HEIGHT 50  // высота графика
#define PLOT_COUNTS 60  //количество отсчетов на графике

GyverOLED<SSH1106_128x64> oled; // Инициализируем OLED-экран
CG_Anem cgAnem(ANEM_I2C_ADDR); // Инициализируем CG_Anem
FlowPlot<PLOT_COUNTS> flowPlot;

uint16_t ADC; // Переменная для значений АЦП
uint32_t timer_cnt; // Таймер для измерений анемометра
uint32_t timer_bat; // Таймер для измерения заряда батареи
const uint8_t *p;
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
  flowPlot.init(PLOT_HEIGHT);
  p = flowPlot.getPoints();
}

void loop() {
  char buf[50];
  oled.setScale(1);
  if (millis() - timer_cnt > 1000) { // Снимаем показания с анемометра и выводим их на экран
    timer_cnt = millis();
    // Проверяем, обновляются ли данные с анемометра. Если да - выводим их, если нет - предупреждаем об ошибке
    if (cgAnem.data_update()) {
      flow = cgAnem.getAirflowRate();
      flowPlot.pushValue(flow);
      sprintf(buf, "T:%.1fC ", cgAnem.getTemperature()); // Собираем строку с показаниями температуры
      oled.setCursor(0, 0);
      oled.print(buf);
      
      // отрисовка графика
      oled.rect(PLOT_LEFT, PLOT_TOP, PLOT_LEFT + PLOT_COUNTS, PLOT_TOP + PLOT_HEIGHT, OLED_CLEAR); 
      oled.rect(PLOT_LEFT, PLOT_TOP, PLOT_LEFT + PLOT_COUNTS, PLOT_TOP + PLOT_HEIGHT, OLED_STROKE);
      for (uint8_t i = 0; i < PLOT_COUNTS; i++) {
        oled.dot(PLOT_LEFT + i, PLOT_TOP + p[i], OLED_FILL);
      }
  
      sprintf(buf, "%.1f", flowPlot.getMaxRange()); // Собираем строку со значением для верхней границы
      oled.setCursorXY(PLOT_LEFT - 20, PLOT_TOP);
      oled.print(buf);

      sprintf(buf, "%.1f", flowPlot.getMinRange()); // Собираем строку со значением для нижней границы
      oled.setCursorXY(PLOT_LEFT - 20, PLOT_TOP + PLOT_HEIGHT - 8);
      oled.print(buf);

      sprintf(buf, "M:%.1fm/s", flowPlot.getMeanFlow()); // Собираем строку со средним потоком
      oled.setCursor(55, 0);
      oled.print(buf);

      oled.setCursor(45, 4);
      oled.println("m/s");

      sprintf(buf, "%.1f", flow); // Собираем строку с показаниями скорости потока
      oled.setCursor(0, 3);
      oled.setScale(2);
      oled.print(buf);
    }
    else {
      oled.setCursor(35, 0);
      oled.print("*");
    }
  }

  if (millis() - timer_bat > 10000) { //
    timer_bat = millis();
    ADC = analogRead(ADC_pin); // Считываем показание с АЦП
    oled.rect(112, 0, 124, 3, OLED_STROKE); // Рисуем иконку батарейки
    oled.rect(125, 1, 127, 2, OLED_FILL);
    if (ADC >= 970) {
      oled.rect(112, 0, 124, 3, OLED_FILL);
    }
    if (ADC < 970 && ADC >= 870) {
      oled.rect(112, 0, 121, 3, OLED_FILL);
    }
    if (ADC < 870 && ADC >= 770) {
      oled.rect(112, 0, 118, 3, OLED_FILL);
    }
    if (ADC < 770 && ADC >= 670) {
      oled.rect(112, 0, 115, 3, OLED_FILL);
    }
  }

  oled.update();
}
