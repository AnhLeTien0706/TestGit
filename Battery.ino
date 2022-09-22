
#include <Arduino.h>
#include <daly-bms-uart.h> // This is where the library gets pulled in
#include <Wire.h>
#include "timer.h"

#define RXD1 23
#define TXD1 19
#define BMS_SERIAL Serial1 // Set the serial port for communication with the Daly BMS                           
Daly_BMS_UART bms(BMS_SERIAL);
String V, Dungluong, nhietdo, dongsacxa,Remain;
String Discharge, Charge;
String rmcell3,rmcell4, rmcell5, rmcell6,rmcell7, rmcell8;
int rmcell1,rmcell2;
String txString;
char buf[200];
String rmcell;
//2: GND: Green
//3: Rx: Tím
//4: Tx: Blue
void setup()
{
  Wire.begin();
 // Wire.setClock(200000);
  Serial.begin(9600); // Serial interface for the Arduino Serial Monitor
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
  bms.Init(); // This call sets up the driver
}

void loop()
{
  // Print a message and wait for input from the user
 // Serial.println("Press any key to query data from the BMS");
 /* while (Serial.available() == 0)
  {
  }
  Serial.read();
 
  Serial.read(); // To discard the new line that gets sent*/

  // call to update the data from the bms
  if (MilisTimer1( true, 1000) == true)
       {
            bms.update();
           MilisTimer1 (false,0);
       }
            
 //---------------------------------------------------------------- 
 //Pin hoạt động từ 23V đến 27.5V        
  V = bms.get.packVoltage;
//  float Dungluong = 100-((27.5-V)/4.5)*100;
 
 /* Dungluong = 100-((27.5-V)/4.5)*100;
     if(Dungluong > 100)
         {
          Dungluong = 100;
         }
     if(Dungluong < 0)
         {
          Dungluong = 0;
         }*/
  Discharge=bms.get.disChargeFetState;
  Charge=bms.get.chargeFetState;
  Remain=bms.get.resCapacitymAh;
  nhietdo = bms.get.tempAverage;
  dongsacxa = bms.get.packCurrent;

 /*if ((nhietdo>=40) or (dongsacxa>=15) or (V< 23))
     {
      bms.setDischargeMOS(false);  //disable xả
     }
 if ((nhietdo<40) && (dongsacxa<15))
     {
      bms.setDischargeMOS(true);  //enable xả
     }
     
  if (nhietdo>=55)
     {
      bms.setChargeMOS(false);    //disable sạc
     }
  if (nhietdo<55)
     {
      bms.setChargeMOS(true);    //enable sạc
     }*/
 
  /* rmcell="";
  for (size_t i = 0; i < size_t(bms.get.numberOfCells); i++)
  { 
    rmcell+=(String)bms.get.cellVmV[i]+",";
  }*/
  /*rmcell1=(int)bms.get.cellVmV[0];
  rmcell2=(int)bms.get.cellVmV[1];
  rmcell3=bms.get.cellVmV[2];
  rmcell4=bms.get.cellVmV[3];
  rmcell5=bms.get.cellVmV[4];
  rmcell6=bms.get.cellVmV[5];
  rmcell7=bms.get.cellVmV[6];
  rmcell8=bms.get.cellVmV[7];*/
 //----------------------------------------------------------------------------------------------------
     
   /*  Serial.print("Dien ap la: "); 
     Serial.println(V); 
     Serial.print("Nhiet do la: "); 
     Serial.println(nhietdo);
     Serial.print("Dong sac xa la: "); 
     Serial.println(dongsacxa);
     Serial.print("Discharge st: "); 
     Serial.println(Discharge);
     Serial.print("Charge st: "); 
     Serial.println(Charge);*/
     
//Master Write
      
      txString = V+","+Remain+","+nhietdo+","+dongsacxa+","+Discharge+","+Charge+"#";
      
     // Serial.println(txString.length());
      txString.toCharArray(buf,200);
if(txString.length()<28)
     { 
       if (MilisTimer2( true, 1000) == true)
       {
        Serial.println(txString);
      Wire.beginTransmission(1); // transmit to device #1
      Wire.write(buf);    
      Wire.endTransmission();
      MilisTimer2 (false,0);
       }
       } // stop transmitting  
      
                    
}
