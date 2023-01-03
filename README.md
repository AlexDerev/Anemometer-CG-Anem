# Handheld Anemometer

Project is based on [Official CG-Anem library by ClimateGuard](https://github.com/climateguard/CG-Anem#official-library-for-cg-anem-by-climateguard) and [habr article](https://habr.com/ru/post/676348/) 

The aim of the project is to practice in 3D-modelling (FreeCAD) and to construct the compact anemometer for paraglading.
Initial set of electronic parts was initially based on the article:
1. [WEMOS D1 mini pro controller](https://aliexpress.ru/item/1005003763905349.html?sku_id=12000027084254255)
2. [USB Li-Ion Charge module](https://aliexpress.ru/item/1005003585993852.html?sku_id=12000026386522752)
3. [ADP3338AKC-3.3 LDO voltage regulator](https://aliexpress.ru/item/4000045988751.html?sku_id=10000000103095880) was taken from the article link. Don't
buy here, it is a fake. Indeed it is remarked 1117 series vith 1,04 V dropout.
4. [OLED 1.3" module](https://aliexpress.ru/item/1005001621782442.html?sku_id=12000016846377326) instead of 0.96".
5. [PCB mounted microswitch](https://roboparts.ru/catalog/kommutatsiya/mikropereklyuchateli_kontsevye_vyklyuchateli/dm3_03p_125v_1a_mikropereklyuchatel/)
6. [PBS-04 socket for OLED](https://roboparts.ru/catalog/razemy/shtyrkovye_razyemy/pbs_1x06_razem_na_platu_2_54mm/)
7. [18650 battery holder](https://www.chipdip.ru/product1/8007238837)

## Comparing with conventional rotary handheld anemometers

### Advantages

  No moving parts - no problems with bearings;

  More accurate (probably).

### Disadvantages

  More expensive;

  Sensor ends seem weak and can be broken easily. They need to be additionally protected;

  Relatively long start;

  High current consumption to heat the hotend.
  
  ## Detals
  
  1. OLED screen stands should be 11 mm high and have M3 thread.
  2. The lengthof case asembling screws should be no less 20 mm. Initially it was supposed to use 2.5 mm screws but you can drill it up to 3 mm holes in bottom part and 2.5 mm in top part to use 3 mm screws.
  3. You can use a spring for button from a pen then you need to drill carefully up a hole in the button to 5 mm diam.
