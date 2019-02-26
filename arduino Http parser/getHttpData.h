
#include <ESP8266WiFi.h>
#include <string.h>
#include "pswrd.h"

//const char* ssid     = "xxxxxxxxx";
//const char* password = "xxxxxxxxx";

const char* host = "10.10.0.1";
char inputStr[100];
char delim0[] = ">";
char delim[] = " ";
char delim2[] = "<";
char *ptr;

void setup_wifi() {
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
   would try to act as both a client and an access-point and could cause
   network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;
int nb;

int get_tempArray(float* temps) {
  int indx1=0;
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return 0;
  }
  
  // We now create a URI for the request
  //  String url = "/input/";
  //  url += streamId;
  //  url += "?private_key=";
  //  url += privateKey;
  //  url += "&value=";
  //  url += value;

  String url = "http://10.10.0.1";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" + 
         "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return 0;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    nb = client.readBytesUntil('\n', inputStr, 100);
    inputStr[nb]='\0';
    if (strstr(inputStr,"<br><body>")!=NULL){
      //char delim0[] = ">";
      //char delim[] = " ";
      //char delim2[] = "<";
  
      ptr = strtok(inputStr, delim0);
      ptr = strtok(NULL, delim0);
      ptr = strtok(NULL, delim);
      //Serial.print(ptr);
      ptr = strtok(NULL, delim);
      //Serial.print(ptr);
      ptr = strtok(NULL, delim2);
      temps[indx1] = atof(ptr);
      //Serial.println(temps[indx1]);
      indx1++;
    }
  }
  
  Serial.println("closing connection");
  return indx1;
}


