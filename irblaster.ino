#include <ESP8266WiFi.h>
#include "buttons.cpp"
#include <PubSubClient.h>
#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
// The following are only needed for extended decoding of A/C Messages
#include <ir_Argo.h>
#include <ir_Coolix.h>
#include <ir_Daikin.h>
#include <ir_Fujitsu.h>
#include <ir_Goodweather.h>
#include <ir_Gree.h>
#include <ir_Haier.h>
#include <ir_Hitachi.h>
#include <ir_Kelvinator.h>
#include <ir_Midea.h>
#include <ir_Mitsubishi.h>
#include <ir_MitsubishiHeavy.h>
#include <ir_Panasonic.h>
#include <ir_Samsung.h>
#include <ir_Sharp.h>
#include <ir_Tcl.h>
#include <ir_Teco.h>
#include <ir_Toshiba.h>
#include <ir_Trotec.h>
#include <ir_Vestel.h>
#include <ir_Whirlpool.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>

#include <IRutils.h>
#include <IRsend.h>
const uint32_t kBaudRate = 115200;


const uint16_t kCaptureBufferSize = 1024;
int i=0;



#if DECODE_AC

const uint8_t kTimeout = 50;
#else   

const uint8_t kTimeout = 15;
#endif  

const uint16_t kMinUnknownSize = 12;
const uint16_t kRecvPin = 14;
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);

decode_results results; 
String myString;
WiFiClient espClient;
PubSubClient client(espClient);
const char* ssid = "MOTORINKZ";
const char* password = "password12345678";
const char* mqttServer = "postman.cloudmqtt.com";
const int mqttPort = 17443;
const char* mqttUser = "hgiyrifv";
const char* mqttPassword = "5S6Ps2ImHclC";
 String mystring;
  int len=0;
  int ending=0;
int starting=0;

const uint16_t kIrLed = 4;
IRsend irsend(kIrLed);
bool wb=true;
String Result;

void dumpACInfo(const decode_results * const results) {
  String description = "";
#if DECODE_ARGO
  if (results->decode_type == ARGO) {
    IRArgoAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_ARGO
#if DECODE_DAIKIN
  if (results->decode_type == DAIKIN) {
    IRDaikinESP ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_DAIKIN
#if DECODE_DAIKIN2
  if (results->decode_type == DAIKIN2) {
    IRDaikin2 ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_DAIKIN2
#if DECODE_DAIKIN216
  if (results->decode_type == DAIKIN216) {
    IRDaikin216 ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_DAIKIN216
#if DECODE_FUJITSU_AC
  if (results->decode_type == FUJITSU_AC) {
    IRFujitsuAC ac(0);
    ac.setRaw(results->state, results->bits / 8);
    description = ac.toString();
  }
#endif  // DECODE_FUJITSU_AC
#if DECODE_KELVINATOR
  if (results->decode_type == KELVINATOR) {
    IRKelvinatorAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_KELVINATOR
#if DECODE_MITSUBISHI_AC
  if (results->decode_type == MITSUBISHI_AC) {
    IRMitsubishiAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_MITSUBISHI_AC
#if DECODE_MITSUBISHIHEAVY
  if (results->decode_type == MITSUBISHI_HEAVY_88) {
    IRMitsubishiHeavy88Ac ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
  if (results->decode_type == MITSUBISHI_HEAVY_152) {
    IRMitsubishiHeavy152Ac ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_MITSUBISHIHEAVY
#if DECODE_TOSHIBA_AC
  if (results->decode_type == TOSHIBA_AC) {
    IRToshibaAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_TOSHIBA_AC
#if DECODE_TROTEC
  if (results->decode_type == TROTEC) {
    IRTrotecESP ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_TROTEC
#if DECODE_GOODWEATHER
  if (results->decode_type == GOODWEATHER) {
    IRGoodweatherAc ac(0);
    ac.setRaw(results->value);  // Goodweather uses value instead of state.
    description = ac.toString();
  }
#endif  // DECODE_GOODWEATHER
#if DECODE_GREE
  if (results->decode_type == GREE) {
    IRGreeAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_GREE
#if DECODE_MIDEA
  if (results->decode_type == MIDEA) {
    IRMideaAC ac(0);
    ac.setRaw(results->value);  // Midea uses value instead of state.
    description = ac.toString();
  }
#endif  // DECODE_MIDEA
#if DECODE_HAIER_AC
  if (results->decode_type == HAIER_AC) {
    IRHaierAC ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_HAIER_AC
#if DECODE_HAIER_AC_YRW02
  if (results->decode_type == HAIER_AC_YRW02) {
    IRHaierACYRW02 ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_HAIER_AC_YRW02
#if DECODE_SAMSUNG_AC
  if (results->decode_type == SAMSUNG_AC) {
    IRSamsungAc ac(0);
    ac.setRaw(results->state, results->bits / 8);
    description = ac.toString();
  }
#endif  // DECODE_SAMSUNG_AC
#if DECODE_SHARP_AC
  if (results->decode_type == SHARP_AC) {
    IRSharpAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_SHARP_AC
#if DECODE_COOLIX
  if (results->decode_type == COOLIX) {
    IRCoolixAC ac(0);
    ac.setRaw(results->value);  // Coolix uses value instead of state.
    description = ac.toString();
  }
#endif  // DECODE_COOLIX
#if DECODE_PANASONIC_AC
  if (results->decode_type == PANASONIC_AC &&
      results->bits > kPanasonicAcShortBits) {
    IRPanasonicAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_PANASONIC_AC
#if DECODE_HITACHI_AC
  if (results->decode_type == HITACHI_AC) {
    IRHitachiAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_HITACHI_AC
#if DECODE_WHIRLPOOL_AC
  if (results->decode_type == WHIRLPOOL_AC) {
    IRWhirlpoolAc ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_WHIRLPOOL_AC
#if DECODE_VESTEL_AC
  if (results->decode_type == VESTEL_AC) {
    IRVestelAc ac(0);
    ac.setRaw(results->value);  // Like Coolix, use value instead of state.
    description = ac.toString();
  }
#endif  // DECODE_VESTEL_AC
#if DECODE_TECO
  if (results->decode_type == TECO) {
    IRTecoAc ac(0);
    ac.setRaw(results->value);  // Like Coolix, use value instead of state.
    description = ac.toString();
  }
#endif  // DECODE_TECO
#if DECODE_TCL112AC
  if (results->decode_type == TCL112AC) {
    IRTcl112Ac ac(0);
    ac.setRaw(results->state);
    description = ac.toString();
  }
#endif  // DECODE_TCL112AC
  // If we got a human-readable description of the message, display it.
  if (description != "") Serial.println("Mesg Desc.: " + description);
}





void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

  buttons a[25];
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

if((payload[0]=='R')&&(payload[1]=='E')&&(payload[2]=='A')&&(payload[3]=='D')&&(payload[4]=='M')&&(payload[5]=='O')&&(payload[6]=='D')&&(payload[7]=='E'))
{
 if(i==0)
  {
    
    client.publish("BUTTON","PRESS POWER BUTTON");
    
   
    button(i);
    i++;
  }
  if(i==1)
  {
    client.publish("BUTTON","PRESS VOLUME UP BUTTON");
 
   button(i);
    i++;
    
  }
  if(i==2)
  {client.publish("BUTTON","PRESS VOLUME DOWN BUTTON");
   
   button(i);
    i++;
    
  }
  if(i==3)
  {client.publish("BUTTON","PRESS CHANNEL UP BUTTON");
  
   button(i);
    i++;
    
  }
  if(i==4)
  {client.publish("BUTTON","PRESS CHANNEL DOWN BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==5)
  {client.publish("BUTTON","PRESS NAVIGATION UP BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==6)
  {client.publish("BUTTON","PRESS NAVIGATION DOWN BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==7)
  {client.publish("BUTTON","PRESS NAVIGATION RIGHT BUTTON");
    
 button(i);
    i++;
    
  }
  if(i==8)
  {client.publish("BUTTON","PRESS NAVIGATION LEFT BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==9)
  {client.publish("BUTTON","PRESS OK BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==10)
  {client.publish("BUTTON","PRESS MUTE BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==11)
  {client.publish("BUTTON","PRESS BACK BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==12)
  {client.publish("BUTTON","PRESS CHANNEL BACK BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==13)
  {client.publish("BUTTON","PRESS MENU BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==14)
  {client.publish("BUTTON","PRESS HOME BUTTON");
    
  button(i);
    i++;
    
  }
  if(i==15)
  {client.publish("BUTTON","PRESS NUMBER 1 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==16)
  {client.publish("BUTTON","PRESS NUMBER 2 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==17)
  {client.publish("BUTTON","PRESS NUMBER 3 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==18)
  {client.publish("BUTTON","PRESS NUMBER 4 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==19)
  {client.publish("BUTTON","PRESS NUMBER 5 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==20)
  {client.publish("BUTTON","PRESS NUMBER 6 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==21)
  {client.publish("BUTTON","PRESS NUMBER 7 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==22)
  {client.publish("BUTTON","PRESS NUMBER 8 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==23)
  {client.publish("BUTTON","PRESS NUMBER 9 BUTTON");
    
  button(i);
    i++;
    
  }
   if(i==24)
  {client.publish("BUTTON","PRESS NUMBER 0 BUTTON");
    
  button(i);
    i=0;
    
  }
}

if((payload[0]=='P')&&(payload[1]=='O')&&(payload[2]=='W')&&(payload[3]=='E')&&(payload[4]=='R'))
{
irsend.sendRaw(a[0].button1,a[0].lengt,38);
}
if((payload[0]=='V')&&(payload[1]=='O')&&(payload[2]=='L')&&(payload[3]=='+'))
{
irsend.sendRaw(a[1].button1,a[1].lengt,38);
}
if((payload[0]=='V')&&(payload[1]=='O')&&(payload[2]=='L')&&(payload[3]=='-'))
{
irsend.sendRaw(a[2].button1,a[2].lengt,38);
}
if((payload[0]=='C')&&(payload[1]=='H')&&(payload[2]=='+'))
{
irsend.sendRaw(a[3].button1,a[3].lengt,38);
}
if((payload[0]=='C')&&(payload[1]=='H')&&(payload[2]=='-'))
{
irsend.sendRaw(a[4].button1,a[4].lengt,38);
}
if((payload[0]=='N')&&(payload[1]=='U')&&(payload[2]=='P'))
{
irsend.sendRaw(a[5].button1,a[5].lengt,38);
}
if((payload[0]=='N')&&(payload[1]=='D')&&(payload[2]=='O')&&(payload[3]=='W')&&(payload[4]=='N'))
{
irsend.sendRaw(a[6].button1,a[6].lengt,38);
}
if((payload[0]=='N')&&(payload[1]=='R')&&(payload[2]=='I')&&(payload[3]=='G')&&(payload[4]=='H')&&(payload[5]=='T'))
{
irsend.sendRaw(a[7].button1,a[7].lengt,38);
}
if((payload[0]=='N')&&(payload[1]=='L')&&(payload[2]=='E')&&(payload[3]=='F')&&(payload[4]=='T'))
{
irsend.sendRaw(a[8].button1,a[8].lengt,38);
}
if((payload[0]=='O')&&(payload[1]=='K'))
{ irsend.sendRaw(a[9].button1,a[9].lengt,38); }
if((payload[0]=='M')&&(payload[1]=='U')&&(payload[2]=='T')&&(payload[3]=='E'))
{ irsend.sendRaw(a[10].button1,a[10].lengt,38); }
if((payload[0]=='B')&&(payload[1]=='A')&&(payload[2]=='C')&&(payload[3]=='K'))
{ irsend.sendRaw(a[11].button1,a[11].lengt,38); }
if((payload[0]=='C')&&(payload[1]=='H')&&(payload[2]=='B')&&(payload[3]=='A')&&(payload[4]=='C')&&(payload[5]=='K'))
{ irsend.sendRaw(a[12].button1,a[12].lengt,38); }
if((payload[0]=='M')&&(payload[1]=='E')&&(payload[2]=='N')&&(payload[3]=='U'))
{ irsend.sendRaw(a[13].button1,a[13].lengt,38); }
if((payload[0]=='H')&&(payload[1]=='O')&&(payload[2]=='M')&&(payload[3]=='E'))
{ irsend.sendRaw(a[14].button1,a[14].lengt,38); }
if((payload[0]=='1'))
{ irsend.sendRaw(a[15].button1,a[15].lengt,38); }
if((payload[0]=='2'))
{ irsend.sendRaw(a[16].button1,a[16].lengt,38); }
if((payload[0]=='3'))
{ irsend.sendRaw(a[17].button1,a[17].lengt,38); }
if((payload[0]=='4'))
{ irsend.sendRaw(a[18].button1,a[18].lengt,38); }
if((payload[0]=='5'))
{ irsend.sendRaw(a[19].button1,a[19].lengt,38); }
if((payload[0]=='6'))
{ irsend.sendRaw(a[20].button1,a[20].lengt,38); }
if((payload[0]=='7'))
{ irsend.sendRaw(a[21].button1,a[21].lengt,38); }
if((payload[0]=='8'))
{ irsend.sendRaw(a[22].button1,a[22].lengt,38); }
if((payload[0]=='9'))
{ irsend.sendRaw(a[23].button1,a[23].lengt,38); }
if((payload[0]=='0'))
{ irsend.sendRaw(a[24].button1,a[24].lengt,38); }
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void setup() {
  irsend.begin();
  
  // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
   client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
     
      Serial.println("connected"); 
    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
#if defined(ESP8266)
  Serial.begin(kBaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(kBaudRate, SERIAL_8N1);
#endif  // ESP8266
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDumpV2 is now running and waiting for IR input on Pin ");
  Serial.println(kRecvPin);


#if DECODE_HASH
  // Ignore messages with less than minimum on or off pulses.
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif             
// DECODE_HASH
  irrecv.enableIRIn();  // Start the receiver
 client.subscribe("IRBLASTER");
client.subscribe("BUTTON");
  
}

// Display the human readable state of an A/C message if we can.



    void loop() {

client.loop();

}
void button(int k)
  {
    while(wb)
   {

    
    if (irrecv.decode(&results)) {
      
      
    
    // Display a crude timestamp.
    uint32_t now = millis();
    Serial.printf("Timestamp : %06u.%03u\n", now / 1000, now % 1000);
    if (results.overflow)
      Serial.printf(
          "WARNING: IR code is too big for buffer (>= %d). "
          "This result shouldn't be trusted until this is resolved. "
          "Edit & increase kCaptureBufferSize.\n",
          kCaptureBufferSize);
    // Display the basic output of what we found.
    Serial.print(resultToHumanReadableBasic(&results));
    dumpACInfo(&results);  // Display any extra A/C info if we have it.
    yield();  // Feed the WDT as the text output can take a while to print.

    // Display the library version the message was captured with.
    Serial.print("Library   : v");
    Serial.println(_IRREMOTEESP8266_VERSION_);
    Serial.println();

    // Output RAW timing info of the result.
    Serial.println(resultToTimingInfo(&results));
    yield();  // Feed the WDT (again)

    // Output the results as source code
    Serial.println(resultToSourceCode(&results));
    Serial.println("");  // Blank line between entries
    yield();  
    Result=resultToSourceCode(&results);
    Serial.println("again");

  
    starting=Result.indexOf('{');
    ending=Result.indexOf('}'); 
    mystring=Result.substring(ending+1);
    Result=Result.substring((starting+1),ending);
 
    Serial.print("mystring");
    Serial.println(mystring);
    Serial.print("mystring length:");
    Serial.println(mystring.length());
    for(int i=0;i<Result.length();i++)
    {
      if(Result[i]==',')
      len++;
    
      }
     delay(100);
     Result=" "+Result;
     len+=1;
     a[k].lengt=len;
     Serial.println(" ");
     for(int i=0;i<len;i++)
                { 
                a[k].button1[i]=(Result.substring(1,Result.indexOf(','))).toInt();
        Result=Result.substring(Result.indexOf(',')+1);
        Serial.print(a[k].button1[i]);
         Serial.print(',');
                }
                Serial.println("");
                Serial.print("length:");
                Serial.println(len);
                wb=false;
    }
   delay(10);
   }
   wb=true;
   }
