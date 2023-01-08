/*Warning! After the power on the sensor need 10-15 seconds for heating. During that period, module doesn't' update data*/
#include <Arduino.h>
#include <Wire.h>
#include "cgAnem.h"

CG_Anem cgAnem(ANEM_I2C_ADDR);
float firmWareVer;
float voltage;
float coldEndTemp;
float hotEndTemp;
float power;
boolean unsteady;
const char* result;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  if (cgAnem.init()) // try to init the sensor module
    Serial.println("Sensor secsessfully found");
  else
    Serial.println("Sensor wiring error");

  uint8_t sensorChipId = cgAnem.getChipId(); /*Returns chip id, default value: 0x11.*/

  Serial.print("Chip id: 0x");
  Serial.println(sensorChipId, HEX);
  firmWareVer = cgAnem.getFirmwareVersion(); /*Returns firmware version.*/

  Serial.print("Firmware version: ");
  Serial.println(String(firmWareVer));

  delay(3000);
}

/*Warning! After the power on the sensor need 10-15 seconds for heating. During that period, module doesn't' update data*/
void loop()
{
  voltage = cgAnem.getRegisterValue8(i2c_reg_SUPPLY_V);
  power = cgAnem.getRegisterValue8(i2c_reg_PWR_WT);
  coldEndTemp = cgAnem.getRegisterValue16(i2c_reg_TEMP_COLD_H);
  hotEndTemp = cgAnem.getRegisterValue16(i2c_reg_TEMP_HOT_H);
  result = cgAnem.data_update() ? "OK" : "UNSTEADY";
  
  Serial.println("Rate: " + String(cgAnem.airflowRate) + " m/s; Temp: " + String(cgAnem.temperature) + " C; Volt:" + String(voltage) + " V; Power:" + String(power) + " Wt; coldT:" + String(coldEndTemp) + " C; hotT:" + String(hotEndTemp) + " C; " + result);

  if (firmWareVer > 0.9)//all the methods below work with anemometers version 1.0 and higher
  { 
    Serial.println("Max rate:" + String(cgAnem.getMaxAirFlowRate()) + " m/s");
    //cgAnem.resetMinMaxValues(); // to reset max min values uncoment it
  }

  delay(1000);
}