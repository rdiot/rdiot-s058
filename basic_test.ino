/* ENC28J60 Ethernet Module (ENC28J60) [S058] : http://rdiot.tistory.com/159 [RDIoT Demo] */

#include <EtherCard.h>
#define REQUEST_RATE 5000 // milliseconds

// ethernet interface mac address
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
// remote website name
const char website[] PROGMEM = "sports.news.naver.com";

byte Ethernet::buffer[700];
static long timer;

  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
  
  ether.printIp("My IP: ", ether.myip);
  // ether.printIp("Netmask: ", ether.mymask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);

  timer = - REQUEST_RATE; // start timing out right away

// called when the client request is complete
static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  int val = millis() - timer;
  Serial.print(val);
  Serial.println(" ms");
  Serial.println((const char*) Ethernet::buffer + off);

  lcd.setCursor(0,3);
  lcd.print("reply=" + (String)val + " ms   ");
}
