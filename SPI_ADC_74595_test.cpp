
// ldr 센서값을  아날로그-디지털-변환기(ADC)로 읽어서 숫자표시기에 출력하는 프로그램 
// 제작자: KYL, CSY, BDS
// 2022.2.24

/* 필요한 부품 

 아날로그 센서 입력부: 
    1.ADC     : MCP3008  ----------------- 1ea
    2.조도센서   : ldr     ----------------- 1ea
    3.풀다운저항 :  4.7kohm ------------------1ea
 숫자표시부: 
    1. 숫자표시기       : 공통 애노드 타입 7-Segment ------ 1ea 
    2. LED 바이어스 저항 : 330ohm ---------------------- 7ea, 
    3. 외부 디스플레이 레지스터 : ShiftRegister(74HC595)--- 1ea
 
 */



// 이코드는 익스플로링 라즈베리파이 (위키북스) <저자: Derek Molloy> 를 참고하였습니다.
// 원본 프로젝트 github 주소는 아래와 같습니다.
// https://github.com/derekmolloy/exploringrpi/tree/master/chp09/ldr

#include <iostream>
#include "bus/SPIDevice.h"
#include <unistd.h>
using namespace exploringRPi;


const unsigned char symbols[16] = {                   //(msb) HGFEDCBA (lsb)
     0b00111111, 0b00000110, 0b01011011, 0b01001111,  // 0123
     0b01100110, 0b01101101, 0b01111101, 0b00000111,  // 4567
     0b01111111, 0b01100111, 0b01110111, 0b01111100,  // 89Ab
     0b00111001, 0b01011110, 0b01111001, 0b01110001   // CdEF
};



const float lightRawValueTo16Level = 16.0/1024.0;  //반드시 분모나 분자중에서 하나는 소수점을 적어야함

// 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
int main(){
   std::cout << "Starting the RPi LDR ADC Example" << std::endl;
   
   
   SPIDevice *busDevice = new SPIDevice(0,0);
   busDevice->setSpeed(5000000);
   busDevice->setMode(SPIDevice::MODE0);
   
   SPIDevice *display = new SPIDevice(0,1);
   display->setSpeed(5000000);
   display->setMode(SPIDevice::MODE3);
   
   unsigned char txdata, rxdata;
   txdata = ~symbols[0xC];
   display->transfer(&txdata, &rxdata, 1);
   
   sleep(3);
   
     
   unsigned char send[3], receive[3];
   send[0] = 0b00000001;         // Start Bit followed by SGL/Diff=1
   send[1] = 0b10000000;         // MSB 000 is D1=0, D0=0 for channel 0
   while(true){
      busDevice->transfer(send, receive, 3);
      // MCP320X: use full second byte and the four LSBs of the first byte
      int value = ((receive[1]&0b00001111)<<8)|receive[2];
      
      
      int lightlevel = int(lightRawValueTo16Level * float(value));   // value = 0-1023  to 0 - 15 
      
      std::cout << "LDR value is " << value << '(' << lightlevel << ')' << " out of 1023." << std::endl;  
        
      if((lightlevel <= 15) && (lightlevel >= 0))
      {
         txdata =  ~symbols[lightlevel];      // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         
      }else{
         //(msb)  HGFEDCBA (lsb)
         txdata =  ~0b01111001;  // E         // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         sleep(2);
         
         txdata =  ~0b00000000;  // clear     // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         sleep(1);
         
         txdata =  ~0b01010000;  // r         // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         sleep(2);
         
         txdata =  ~0b00000000;  // clear     // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         sleep(1);
           
         txdata =  ~0b01010000;  // r         // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         sleep(2);
         
         txdata =  ~0b00000000;  // clear     // ~ 하는 이유는, 공통단자가 VCC로 연결되는 숫자표시기를 사용함 ---- 
         display->transfer(&txdata, &rxdata, 1);
         sleep(1);
      }
      
      sleep(0.5);
   }
}
