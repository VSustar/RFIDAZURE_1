/*Vid Sustar 28.02.2023
 REFERENCES:
 * RFID: https://github.com/miguelbalboa/rfid
* TIME https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
 */

#include <SPI.h>
#include <MFRC522.h> //RFID reader library
#include "AzureIotHub.h"
#include "Esp32MQTTClient.h"

#define SS_PIN 5
#define RST_PIN 2
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];
//###########################################################

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char* ssid     = "***";//"REPLACE_WITH_YOUR_SSID";
const char* password = "***";//"REPLACE_WITH_YOUR_PASSWORD";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;
//RFID Variables
String UIDtag;
String RFIDtype;//"

int messageCount = 1;    //initialize mesage to one
#define INTERVAL 10000  //time interval between two consecutive messages in milliseconds

#define DEVICE_ID "IoTEsp32device1"   //device Id you wish to give To identify the device

#define MESSAGE_MAX_LEN 256    //256 bytes is the maximum data
float Voltage =0;// do not change

static const char* connectionString = "HostName=***.azure-devices.net;DeviceId=***;SharedAccessKey=***="; //REPLACE WITH YOUR CREDENTIALS/CONNECTION STRING!

//Replace the above placeholder with the primary connection string of your IoT device.
const char *messageData = "{\"deviceId\":\"%s\", \"messageId\":%d,\"UIDtag\":\"%s\", \"RFIDtype\":\"%s\",\"Date\":\"%s\",\"Time\":\"%s\"}"; //message format or the format template

static bool messageSending = true;
static uint64_t send_interval_ms;
static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result)
{
  if (result == IOTHUB_CLIENT_CONFIRMATION_OK)
  {
    Serial.println("Send Confirmation Callback finished.");
  }
}

void setup() { 
  Serial.begin(9600);

  //RFID
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

  //datetime:
  // Initialize Serial Monitor
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +2 = 7200
  timeClient.setTimeOffset(7200);
  Esp32MQTTClient_Init((const uint8_t*)connectionString);
  Esp32MQTTClient_SetSendConfirmationCallback(SendConfirmationCallback);
//void Esp32MQTTClient_SetSendConfirmationCallback(SEND_CONFIRMATION_CALLBACK send_confirmation_callback);
/**
*    Sets up send confirmation status callback to be invoked representing the status of sending message to IOT Hub.
*/

  send_interval_ms = millis();

}
 
void loop() {
//DATE TIME:
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  timeClient.forceUpdate();
  formattedDate = timeClient.getFormattedDate();
  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);

//RFID:
  // Look for new RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  UIDtag=content.substring(1);
  if (UIDtag == "70 C3 D1 A0") //change here the UID of the card/cards that you want to give access
    {RFIDtype="keys";  } 
  if (UIDtag == "75 6A CF 28") //change here the UID of the card/cards that you want to give access
    {RFIDtype="wallet";  }   
  else   {RFIDtype="undefined";}
  
//converting to const char* to feed into message to the cloud
const char* UIDtagc     =  UIDtag.c_str();
const char* RFIDtypec     =  RFIDtype.c_str();
const char* dayStampc     =  dayStamp.c_str();
const char* timeStampc     =  timeStamp.c_str();
  
    Serial.println(RFIDtype);

  char messagePayload[MESSAGE_MAX_LEN];
      //snprintf(messagePayload,MESSAGE_MAX_LEN,messageData, DEVICE_ID, messageCount++, temperature,humidity,voltage);
      snprintf(messagePayload,MESSAGE_MAX_LEN,messageData, DEVICE_ID, messageCount++,UIDtagc,RFIDtypec,dayStampc,timeStampc);
      //snprintf(char *str, size_t size,  const char *format, ...)
      //snprintf(buffer,    maximum size, const char *format (i.e template), other arguments.....)
      Serial.println(messagePayload);
      EVENT_INSTANCE* message = Esp32MQTTClient_Event_Generate(messagePayload, MESSAGE);

                                //Esp32MQTTClient_Event_Generate(const char *eventString, EVENT_TYPE type);
/**
*    Generate an event with the event string specified by @p eventString.
*
*   eventString             The string of event.
*
*    EVENT_INSTANCE upon success or an error code upon failure.
*/
      Esp32MQTTClient_SendEventInstance(message);
//bool Esp32MQTTClient_SendEventInstance(EVENT_INSTANCE *event);
/**
*     Synchronous call to report the event specified by @p event.
*
*    event the event instance.
*
*    Return true if send successfully, or false if fails.
*/
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}