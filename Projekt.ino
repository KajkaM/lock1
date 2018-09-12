/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 *----------------------------------------------------------------------------- empty_skull 
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 ----------------------------------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               52                MOSI
 * SPI MISO   12               51                MISO
 * SPI SCK    13               50                SCK
 *
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

#include <SPI.h>
#include <MFRC522.h>

const byte UID[] ={0xFF, 0x55, 0x00, 0x78}; // zdefiniowanie tablicy z numerem legitymacji
const byte UID2[] = {0x9F, 0x7E, 0xFE, 0x77}; // zdefiniowanie Misia nr karty
// Create MFRC522 instance.
 
MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;
void setup() {
	Serial.begin(9600);	// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	// Init MFRC522 card
	Serial.println("Scan PICC to see UID and type...");
 rfid.PCD_Init();
 pinMode(3, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 
}

void loop() {
	/* Look for new cards
	if ( ! rfid.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! rfid.PICC_ReadCardSerial()) {
		return;
	}
 */
// rfid.PICC_DumpToSerial(&(rfid.uid));
 //int Card_Id =  rfid.PICC_ReadCardSerial();
 //int Card_Id2 =  rfid.PICC_IsNewCardPresent();

 if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
 {
  if(rfid.uid.uidByte[0] == UID[0] || UID2[0] && 
        rfid.uid.uidByte[1] == UID[1] || UID2[1] &&
        rfid.uid.uidByte[2] == UID[2] || UID2[2] &&
        rfid.uid.uidByte[3] == UID[3] || UID2[3])
        {
	// Dump debug info about the card. PICC_HaltA() is automatically called.
Serial.println("otwieram zamek");
digitalWrite(5, LOW);
digitalWrite(6, HIGH);
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(5000);                       // wait for a second
    digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(6, LOW);
    delay(700);    
  }
  else
 Serial.println("Zla karta...");
 digitalWrite(5, HIGH);
 }
 rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
 }
