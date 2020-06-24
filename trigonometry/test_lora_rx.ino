#include <SPI.h>
#include <LoRa.h>

int counter = 0;
int minimum = 0;
bool loop_out = 0;
void setup() {
  Serial.begin(250000);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  while(loop_out==0){
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
//       received a packet
      Serial.print("Received packet '");
  
      // read packet
//      while (LoRa.available()) {
//        Serial.print((char)LoRa.read());
//      }
      
      if(LoRa.packetRssi()<minimum){minimum = LoRa.packetRssi();}
      // print RSSI of packet
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());
      Serial.println(counter);
      counter++;
    }
    if(counter==50){
      if(minimum>=-33){Serial.println("Distance = 0m");}
      else if(minimum>=-57){Serial.println("Distance = 1m");}
      else if((minimum>=-65)&&(minimum<-63)){Serial.println("Distance = 2m");}
      else if((minimum>=-67)&&(minimum<-65)){Serial.println("Distance = 3m");}
      else if((minimum>=-69)&&(minimum<-67)){Serial.println("Distance = 4m");}
      else if((minimum>=-72)&&(minimum<-69)){Serial.println("Distance = 5m");}
      else if((minimum>=-74)&&(minimum<-72)){Serial.println("Distance = 6m");}
      else if((minimum>=-76)&&(minimum<-74)){Serial.println("Distance = 7m");}
      else if((minimum>=-78)&&(minimum<-76)){Serial.println("Distance = 8m");}
      else if((minimum>=-81)&&(minimum<-78)){Serial.println("Distance = 9m");}
      else if((minimum>=-84)&&(minimum<-81)){Serial.println("Distance = 10m");}
      else if((minimum>=-87)&&(minimum<-84)){Serial.println("Distance = 11m");}
      else if((minimum>=-89)&&(minimum<-87)){Serial.println("Distance = 12m");}
      else if((minimum>=-91)&&(minimum<-89)){Serial.println("Distance = 13m");}
      else if((minimum>=-93)&&(minimum<-91)){Serial.println("Distance = 14m");}
      else if((minimum>=-96)&&(minimum<-93)){Serial.println("Distance = 15m");}
      loop_out = 1;
    }
  }
}
