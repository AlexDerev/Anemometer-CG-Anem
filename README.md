# Портативный анемометр

проект сделан на основе [Official CG-Anem library by ClimateGuard](https://github.com/climateguard/CG-Anem#official-library-for-cg-anem-by-climateguard) и [статьи на Хабре](https://habr.com/ru/post/676348/) 

Цель - попрактиковаться в 3D-моделировании в FreeCAD совместно с дизайном в в KiCAD. И сделать вариант компактного анемометра для параглайдинга.
Исходно набор деталей был взят из статьи:
1. [контроллер WEMOS D1 mini pro](https://aliexpress.ru/item/1005003763905349.html?sku_id=12000027084254255)
2. [USB Модуль зарядки с защитой](https://aliexpress.ru/item/1005003585993852.html?sku_id=12000026386522752)
3. [ADP3338AKC-3.3 регулятор напряжения с низким падением](https://aliexpress.ru/item/4000045988751.html?sku_id=10000000103095880) покупался по линку из статьи. В реальности оказалось подделкой из перепиленного 1117 с падением 1,04 V. В итоге использовался [регулятор MCP1700](https://www.chipdip.ru/product/mcp1700-3302e-to-microchip) в корпусе TO-92.
4. [Экран OLED 1.3"](https://aliexpress.ru/item/1005001621782442.html?sku_id=12000016846377326) вместо 0.96".
5. [Микрик с лапкой на плату](https://roboparts.ru/catalog/kommutatsiya/mikropereklyuchateli_kontsevye_vyklyuchateli/dm3_03p_125v_1a_mikropereklyuchatel/)
6. [Разъем PBS-04 для экрана](https://roboparts.ru/catalog/razemy/shtyrkovye_razyemy/pbs_1x06_razem_na_platu_2_54mm/)
7. [Держатель для 18650 с контактами](https://www.chipdip.ru/product1/8007238837)

## Сравнение с распростаненными у парапланеристов вертушечными анемометрами

### Достоинства
  - Нет вращающихся деталей, нет проблем с подшипниками 
  - Более точный (вероятно). Но нужен прецизионный регулятор напряжения!

### Недостатки

  - Дороже. Типичная вертушка 800 р на Али.
  - Тонкие чувствительные концы. В полевых условиях легко обломать, нужно дополнительно защищать.
  - Отноисительно долгий старт
  - Высокое потребление тока для нагрева горячего конца.
  
  ## Детали реализации
  
  1. Стойки для крепления OLED 11 mm с резьбой M3. Определялось высотой разъема под экран. Впаивать для уменьшения высоты не хотелось.
  2. Диина шурупов для корпуса не менее 20 mm. Исходно сделано под 2.5 mm, но можно рассверлить до 3 mm  в нижней половинке и 2.5 mm в верхней для 3 mm шурупов.
  3. Для кнопки можно использовать пружинку из ручки. Нужно аккуратно рассверлить отверстие в ней до 5 mm.
  4. Для крепления экрана, стоек к плате и сенсора к слайдеру нужны M3 винты с потайной головкой. Длина не более 5 mm.
  5. Исходно печатная плата делалась в Sprint Layout (OLD). В финальном варианте сделана в KiCAD.
  6. 3D модели деталей брались из Интернета, поэтому есть небольшие несостыковки в общей сборке. Дизайн корпуса основывался на реальных деталях. 
  
  ## Планы
  1. Перепроектировать корпус с ипользованием возможности сборки в FreeCAD
  2. Переделать прошивку с выводом графика скорости.
  2. Попробовать уменьшить корпус под использование BL-5C Nokia Li-Ion battery и менее острыми углами.

======================================================================================================
# Handheld Anemometer

Project is based on [Official CG-Anem library by ClimateGuard](https://github.com/climateguard/CG-Anem#official-library-for-cg-anem-by-climateguard) and [habr article](https://habr.com/ru/post/676348/) 

The aim of the project is to practice in 3D-modelling in FreeCAD and electronic design in KiCAD. And to construct the compact anemometer for paraglading.
Initial set of electronic parts was based on the article:
1. [WEMOS D1 mini pro controller](https://aliexpress.ru/item/1005003763905349.html?sku_id=12000027084254255)
2. [USB Li-Ion Charge module](https://aliexpress.ru/item/1005003585993852.html?sku_id=12000026386522752)
3. [ADP3338AKC-3.3 LDO voltage regulator](https://aliexpress.ru/item/4000045988751.html?sku_id=10000000103095880) was taken from the article link. Don't
buy here, it is a fake. Indeed it is remarked 1117 series vith 1,04 V dropout. The [MCP1700 regulator](https://www.chipdip.ru/product/mcp1700-3302e-to-microchip) in TO92 package was used finally.
4. [OLED 1.3" module](https://aliexpress.ru/item/1005001621782442.html?sku_id=12000016846377326) instead of 0.96".
5. [PCB mounted microswitch](https://roboparts.ru/catalog/kommutatsiya/mikropereklyuchateli_kontsevye_vyklyuchateli/dm3_03p_125v_1a_mikropereklyuchatel/)
6. [PBS-04 socket for OLED](https://roboparts.ru/catalog/razemy/shtyrkovye_razyemy/pbs_1x06_razem_na_platu_2_54mm/)
7. [18650 battery holder](https://www.chipdip.ru/product1/8007238837)

## Comparing with conventional rotary handheld anemometers

### Advantages
  - No moving parts - no problems with bearings
  - More accurate (probably). You do need high precision ldo voltage regulator!

### Disadvantages

  - More expensive
  - Sensor ends seem weak and can be broken easily. They need to be additionally protected
  - Relatively long start
  - High current consumption to heat a hotend.
  
  ## Detals
  
  1. OLED screen stands should be 11 mm high and have M3 thread.
  2. The length of case asembling screws should be no less 20 mm. Initially it was supposed to use 2.5 mm screws but you can drill holes up to 3 mm  in bottom part and 2.5 mm in top part to use 3 mm screws.
  3. You can use a spring for button from a pen. In this case you need to drill carefully a hole in the button up to 5 mm diam.
  4. You need to use the short M3 countersunk head screws to attach screen stands to PCB and a sensor plate to a slider. Length should be no more then 5 mm.
  5. PCB layout is designed in Sprint Layout software (OLD). PCB was redesigned in KiCAD.
  6. 3D models of electronic parts were taken from Internet and they seem slightly differ from real parts. The case design is based on the real ones. 
  
  ## TO-DO List
  1. Redesign the case in FreeCAD to use the assembling features
  2. Try to make a new compact case for BL-5C Nokia Li-Ion battery and without sharp corners.
