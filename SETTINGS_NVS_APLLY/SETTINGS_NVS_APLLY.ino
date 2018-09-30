#include <Preferences.h>

Preferences preferences;

#define IPCONFIG 1
#define WIFICONFIG 3

#if (WIFICONFIG==0)
  const char* ssid = "LED";
  const char* password = "Soundcraft";  
#endif
#if (WIFICONFIG==1)
  const char* ssid = "X-WL Wireless";
  const char* password = "wolk244521240792";  
#endif
#if (WIFICONFIG==2)
  const char* ssid = "Xperia Z1 Compact";
  const char* password = "Soundcraft";  
#endif
#if (WIFICONFIG==3)
  const char* ssid = "Production";
  const char* password = "Soundcraft";  
#endif


#if (IPCONFIG==0) 
  byte mac[6] = {1,2,3,4,5,6};
  byte local_IP[4] = {2,0,0,30};
  byte broadcast_IP[4] = {192,168,0,255};
  byte gateway_IP[4] = {192,168,0,1};
  byte subnet_MASK[4] = {255,0,0,0};
  byte dns[4] = {192,168,0,1};
#endif
#if (IPCONFIG==1)
  byte mac[6] = {1,2,3,4,5,6};
  byte local_IP[4] = {192,168,0,40};
  byte broadcast_IP[4] = {192,168,0,255};
  byte gateway_IP[4] = {192,168,0,1};
  byte subnet_MASK[4] = {255,255,255,0};
  byte dns[4] = {192,168,0,1};
#endif

#define PARAMS_NUM 5
byte params[PARAMS_NUM] = {255, 60, 0, 0, 222};
/*  Params Value:
 *  0 - general_Bright
 *  1 - target_FPS
 *  2 - auto_reboot
 *  3 - use_osc
 *  4 - osc_port
 */

byte io_map[8] = {0,1,2,3,4,5,6,7};

void setup() {
  Serial.begin(115200);
  preferences.begin("settings",false);
  Serial.println("Ready NVS Utility!");
  Serial.println("Please enter:");
  Serial.println("\tr - read NVS");
  Serial.println("\tw - write NVS");
  Serial.println("\tc - clear NVS");
  Serial.println();
}

void loop() {
  if  (Serial.available()){
    int inByte = Serial.read();
    //Serial.write(inByte);  
    //Serial.println();
    if (inByte == 'w'){WriteData();}
    if (inByte == 'r'){ReadData();}
    if (inByte == 'c'){ClearData();}
  }
}

void ClearData(){
  Serial.println("Clear NVS");
  preferences.clear();
}

void WriteData(){
  Serial.println("Write NVS");
  preferences.putBytes("mac",mac,6);
  preferences.putBytes("l_ip",local_IP,4);
  preferences.putBytes("b_ip",broadcast_IP,4);
  preferences.putBytes("g_ip",gateway_IP,4);
  preferences.putBytes("s_msk",subnet_MASK,4);
  preferences.putBytes("dns",dns,4);

  preferences.putString("ssid",ssid);
  preferences.putString("password",password);

  preferences.putBytes("params",params,PARAMS_NUM);
  preferences.putBytes("io_map",io_map,8);
  Serial.println("Write NVS complite!");
  Serial.println("");
}

void ReadData(){
  Serial.println("Read NVS");
  
  #if (PARAMS_NUM > 8)
    int n = PARAMS_NUM; 
  #else
    int n = 8;
  #endif
  //byte temp[n]={0,0,0,0,0,0,0,0};
  //byte temp[8]={0,0,0,0,0,0,0,0};
  byte temp[n];
  //byte temp[5]={0,0,0,0,0};
  preferences.getBytes("mac",temp,6);
  Serial.print("MAC: \t\t");
  Serial.print(temp[0]); Serial.print(":");
  Serial.print(temp[1]); Serial.print(":");
  Serial.print(temp[2]); Serial.print(":");
  Serial.print(temp[3]); Serial.print(":");
  Serial.print(temp[4]); Serial.print(":");
  Serial.println(temp[5]);

  preferences.getBytes("l_ip",temp,4);
  Serial.print("Local IP: \t");
  Serial.print(temp[0]); Serial.print(".");
  Serial.print(temp[1]); Serial.print(".");
  Serial.print(temp[2]); Serial.print(".");
  Serial.println(temp[3]);

  preferences.getBytes("b_ip",temp,4);
  Serial.print("Broadcast IP: \t");
  Serial.print(temp[0]); Serial.print(".");
  Serial.print(temp[1]); Serial.print(".");
  Serial.print(temp[2]); Serial.print(".");
  Serial.println(temp[3]);

  preferences.getBytes("g_ip",temp,4);
  Serial.print("Gateway IP: \t");
  Serial.print(temp[0]); Serial.print(".");
  Serial.print(temp[1]); Serial.print(".");
  Serial.print(temp[2]); Serial.print(".");
  Serial.println(temp[3]);

  preferences.getBytes("s_msk",temp,4);
  Serial.print("Subnet MASK: \t");
  Serial.print(temp[0]); Serial.print(".");
  Serial.print(temp[1]); Serial.print(".");
  Serial.print(temp[2]); Serial.print(".");
  Serial.println(temp[3]);

  preferences.getBytes("dns",temp,4);
  Serial.print("DNS IP: \t");
  Serial.print(temp[0]); Serial.print(".");
  Serial.print(temp[1]); Serial.print(".");
  Serial.print(temp[2]); Serial.print(".");
  Serial.println(temp[3]);
  
  String str = preferences.getString("ssid",str);
  unsigned char* buf = new unsigned char[100];
  str.getBytes(buf, 100, 0);
  const char* str2 = (const char*)buf;
  Serial.print("SSID: \t\t");
  Serial.println(str2);
  str = preferences.getString("password",str);
  buf = new unsigned char[100];
  str.getBytes(buf, 100, 0);
  str2 = (const char*)buf;
  Serial.print("Password: \t");
  Serial.println(str2);

  preferences.getBytes("params",temp,PARAMS_NUM);
  Serial.print("General Brightness: \t");
  Serial.println(temp[0]);
  Serial.print("Target FPS: \t");
  Serial.println(temp[1]);
  Serial.print("Auto Reboot: \t");
  Serial.println(temp[2]);
  Serial.print("Use OSC: \t");
  Serial.println(temp[3]);
  Serial.print("OSC Port: \t");
  Serial.println(temp[4]);
  
  Serial.println("IO Mapping:");
  preferences.getBytes("io_map",temp,8);
  for (int i = 0; i < 8; i++)
  {
    Serial.print("\tIO");
    Serial.print(i);
    Serial.print("\: \t");
    Serial.println(temp[i]);
  }
  
  Serial.println();
}

