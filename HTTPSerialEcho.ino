#include <SPI.h>
#include <Ethernet.h>

int STATUS_LED = 13;
int BAUD = 9600;
int HTTP = 80;
int SERIAL_MAX = 1024;

byte mac[] = {0x90, 0x15, 0xa4, 0x88, 0x74, 0xb0};
EthernetServer server(HTTP);

String sbuf;

void setup() {  
  // Try to get an inetaddr from DHCP.
  Ethernet.begin(mac);
  
  // Initialize serial interface.
  Serial.begin(BAUD);
  
  // Initialize the web server.
  server.begin();
  
  Serial.println("Init complete.");
}

void loop() {
  // Read from the serial port if available.
  // '\n' character clears the buffer.
  // Truncating buffer: bytes received after the buffer is full are dropped.
  if (Serial.available() > 0) {
    char rcv = (char)Serial.read();
    Serial.write(rcv);
    if (rcv == '\n' || rcv == '\r') {
      sbuf = "";
    } else if (sbuf.length() < SERIAL_MAX) {
      sbuf += rcv;
    }
  }
  
  // Acquire a client if waiting.
  // Write the contents of the serial buffer to the client.
  EthernetClient client = server.available();
  if (client) {
    int len = sbuf.length();
    
    client.println("HTTP/1.1 200 OK");
    client.println("Server: Arduino/HTTPSerialEcho");
    client.println("Content-Type: text/html");
    client.print("Content-Length: ");
    client.println(len, 10);
    client.println("Connection: close");
    client.println();
    
    char *buf = (char*)malloc(len + 1);
    sbuf.toCharArray(buf, len + 1);
    int i;
    for (i = 0; i < len; i++) {
      client.print(buf[i]);
    }
    
    client.println();
    client.println();
    
    client.stop();
  }
}
