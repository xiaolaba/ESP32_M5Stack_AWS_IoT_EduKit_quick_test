:: To erase esp32 completely, do not rely on Arduino IDE and code upload, it has cluster and odd thing when uses FATFS, 
:: unless format SPIFFS or FATFS everytime on the fly
:: xiaolaba, 2020-MAR-02
:: Arduino 1.8.13, esptool and path,



cls
@echo test AWS IoT Edukit core2, connect esp32 to PC
@echo read mac, read flash size
@echo xiaolaba, 2020-MAR-02
@echo.




@echo off

set comport=COM8
::set esptoolpath="C:\Users\user0\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\3.0.0/esptool.exe"
set esptoolpath="esptool.exe"
set project=FTBserver


set action=%esptoolpath% --chip esp32 ^
--port %comport% ^
--baud 115200 ^
read_mac

@echo.
 
::%esptoolpath% --chip esp32 --port %comport% --baud 921600 ^
::read_mac

:::: ESP32 has no chip_id, read_mac instead
::@echo.
::%esptoolpath% --chip esp32 --port %comport% --baud 921600 ^
::chip_id >> esp32_info.txt

@echo.

%esptoolpath% --chip esp32 --port %comport% --baud 115200 ^
flash_id


:: erase whole flash of esp32
::%esptoolpath% --chip esp32 ^
::--port %comport% ^
::--baud 921600 ^
::erase_flash

::pause

@echo delay 10sec, repeat again
timeout 10 >nul
test_com8.bat



