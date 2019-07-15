
char val = 101;    //    HEX/Char/DEC    0x65 / 'e' / 101 .  (ASCII table) 
char lock = 102; //0x66 'f'
char unlock = 103; //0x67 'g'
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

String html_1 = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>IoT SmartLock</title>
</head>

<body>

<h1> IoT SmartLock </h1>

<form id="F1" action="lockStatus">
  <label for="pin">Enter 4 digit pin:</label>
    <input type="password" id="pin" name="password"
           maxlength="4" inputmode = "numeric" required>
  <input type = "submit" value="Unlock">
</form>
)=====";

String html_2 = "";

String html_4 = R"=====(
</body>
</html>
)=====";


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

char ssid[] = "embedTest";       //  your network SSID (name)
char pass[] = "test1234";                //  your network password
 
WiFiServer server(80);           //Port 80 is one of the most commonly used port numbers in the Transmission Control Protocol (TCP) suite. Any Web/HTTP client, such as a Web browser, uses port 80 to send and receive requested Web pages from a HTTP server.
 
String request = "";            // http://yourIPadress/request/?  this request can be LEDON or LEDOFF
int LED_Pin = 16;                // Builtin nodemcu LED
String password = "1234";
String input = "";
bool Locked = true;
 
void setup() 
{
    pinMode(LED_Pin, OUTPUT);     
    
    Serial.begin(9600);        // baudrate of PIC and nodemcu should be same
    Serial.println();
    Serial.println("Serial started at 9600");
    Serial.println("Nodemcu");
    Serial.println();
 
    // Connecting to a WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
      
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server started");
 
} 
 
 
 
void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');

    //Serial.print("request: "); 
    //Serial.println(request);
    if(Locked){ 
      if(request.indexOf(password) > 0 )  { 
        digitalWrite(LED_Pin, HIGH);
        
        Serial.println(unlock);
        Locked = false;
        }
        else{
          Serial.println(val);
        }
    }
    else {
      digitalWrite(LED_Pin, LOW); 
      Serial.println(lock);
      Locked = true;
      }
 
 /*
    // Get the LED pin status and create the LED status message
    if (digitalRead(LED_Pin) == HIGH) 
    {
        // the LED is on so the button needs to say turn it off
       html_2 = "<input type = 'submit' value='Unlock' onclick='checkPin()'></form><br>\r\n";
    }
    else                              
    {
        // the LED is off so the button needs to say turn it on
        html_2 = "<input type = 'submit' value='Lock' onclick='checkPin()'></form><br>\r\n";
    }
 */
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );    
    client.print( html_2 );
    client.print( html_4);
 
    delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} 
