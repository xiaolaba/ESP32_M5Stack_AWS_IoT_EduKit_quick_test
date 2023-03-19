/*
* modified code by xiaolaba, testing for TOUGH, esp32 core2 compatible with generic eps32
* SD card / LCD display, UART
* SD_MMC not tested, SD SPI mode used, GPIO4 is for CS/SS control
* 2023-03-18
*/

/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* Describe: TF Card. TF卡
* Date: 2022/3/25
*******************************************************************************
    In this example, we will detect the existence of a file and perform read and
    write operations on it
    在这个示例中,我们将会检测某文件是否存在,并进行读写文件操作
*/

// add SD card support
#include <SPI.h>
#include <SD.h>



//#include <M5Core2.h> // SD card ok, display NG
#include <M5Unified.h> //xiaolaba test, 2023-03-18 display ok, SD ok

//compiler frezzing ?
// display specific font used.
//#include "Free_Fonts.h"  // Include the header file attached to this sketch


void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.println("xiaolaba, M5Stack TOUGH, SD card test");  // Print a message to LCD

  // LCD display size 2.5 YELLOW
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("xiaolaba test\r\n");  // Print a message to LCD
  M5.Lcd.println("M5Stack TOUGH");  // Print a message to LCD

  //M5.Lcd.setTextColor(RED);
  //M5.Lcd.setTextSize(2.5);
  //M5.Lcd.println("TEST");  // Print a message to LCD

  // LCD display size 2.5 YELLOW
  //M5.Lcd.setTextColor(ORANGE);
  //M5.Lcd.setTextSize(5);
  //M5.Lcd.println("TEST");  // Print a message to LCD

  Serial.println("xiaolaba, M5Stack TOUGH, SD card test");

//  if (!SD.begin()) { // Initialize the SD card. 初始化SD卡 TOUGH, use <M5Core2.h> ok, but display NG, uses <M5Unified.h> display ok but SD card NG
  // Tough pinout, SPI,
  //  SD card,            ChipSelect= 4, SPI_CLK=18, SPI_MI=38, SPI_MO=23
  //  LCD (ILI9342C)      ChipSelect= 5, SPI_CLK=18, SPI_MI=38, SPI_MO=23
  // referece, 
  //  https://github.com/m5stack/M5Tough, M5Tough M-BUS Schematic diagram
  //  https://docs.m5stack.com/en/core/tough, Pin Mapping, LCD Display & TF Card
  //  
  if (!SD.begin(4)) {  // Initialize the SD card. 初始化SD卡 TOUGH, GPIO4 = SD card CS pin, ok, uses <M5Unified.h>
    Serial.println("SD Card failed, or not present");

    //compiler frezzing ?
    //M5.Lcd.setFreeFont(FSB24);        // Select Free Serif 24 point font
    //M5.Lcd.println();                 // Move cursor down a line
    //M5.Lcd.print("Serif Bold 24pt");  // Print the font name onto the TFT screen

    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(4);
    M5.Lcd.println(
        "\r\nNo SD Card!!\r\n\r\n   STOP");  // Print a message if the SD card
                                         // initialization fails or if the
                                         // SD card does not exist
    // 如果SD卡初始化失败或者SD卡不存在，则打印消息
    while (1)
      ;
  }
  M5.Lcd.println("SD/TF card initialized.");
  Serial.println("SD/TF card initialized.");

  if (SD.exists("/hello.txt")) {  // Check if the "/hello.txt" file
                                  // exists.查看是否存在"/hello.txt"文件
    M5.Lcd.println("hello.txt exists.");
    Serial.println("hello.txt exists.");

  } else {
    M5.Lcd.println("hello.txt doesn't exist.");
    Serial.println("hello.txt doesn't exist.");    
  }

  
  M5.Lcd.println("Creating hello.txt");
  Serial.println("Creating hello.txt");    

  File myFile = SD.open("/hello.txt",
                        FILE_WRITE);  // Create a new file "/hello.txt".
                                      // 创建一个新文件"/hello.txt"
  if (myFile) {                       // If the file is open, then write to it.
    // 如果文件打开,则进行写入操作
    //write to file
    M5.Lcd.println("Writing to test.txt...");
    Serial.println("Writing to test.txt...");    

    myFile.println("SD test.\r\n2nd line");
    myFile.close();  // Close the file. 关闭文件
    
    M5.Lcd.println("done.");
    Serial.println("done.");    

  } else {
    M5.Lcd.println("error opening test.txt");
    Serial.println("error opening test.txt");
  }
  delay(500);
  myFile = SD.open("/hello.txt",
                   FILE_READ);  // Open the file "/hello.txt" in read mode.
                                // 以读取模式打开文件"/hello.txt"
  if (myFile) {
    M5.Lcd.println("/hello.txt Content:");
    Serial.println("/hello.txt Content:");    
    
    // Read the data from the file and print it until the reading is
    // complete. 从文件里读取数据并打印到串口,直到读取完成.
    while (myFile.available()) {
      char r=myFile.read(); // read file stream to obtain each byte
      M5.Lcd.write(r);  //print to LCD
      Serial.write(r);  //print to UART
    }
    myFile.close();
  } else {
    M5.Lcd.println("error opening /hello.txt");  // If the file is not open.
                                                 // 如果文件没有打开
    Serial.println("error opening /hello.txt"); 
  }




  Serial.println("\r\nPress ENTER to test again\r\n");
  

}


void readfile()
{

  
}



String inputString = "";         // 缓存字符串
boolean stringComplete = false;  // 是否string已经完成缓存

void loop() {
  // 如果缓存string接收完成:
  if (stringComplete) {
    Serial.println(inputString);
    // 清空String:
    //inputString = "";
    //stringComplete = false;

    delay(2000); //delay 2 seconds
    ESP.restart();  // reboot MCU

  }
}

/*
  SerialEvent在arduino板上的RX引脚收到数据时会被系统自动调用。在系统内部，它是在每次loop函数执行时连带执行的。因此如果再loop使用delay,serialEvent的调用也会被延迟，这样就有可能一次收到>=2个字符。
 */
void serialEvent() {
  while (Serial.available()) {
    // 获取新的字符:
    char inChar = (char)Serial.read();
    // 将它加到inputString中:
    inputString += inChar;
    // 如果收到了换行符，就将一个“旗标”变量设置为true，这样loop函数就知道inputString已经缓存完成了:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}