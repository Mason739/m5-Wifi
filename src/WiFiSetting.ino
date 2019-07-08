#include <M5Stack.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include "WebServer.h"

const IPAddress apIP(192, 168, 4, 1);
const char* apSSID = "MY_WIFI_TEST";
const char* apPASSWORD = "Mypassword";

// DNSServer dnsServer;
WebServer webServer(80);

void setup() {
  m5.begin();
  Serial2.begin(115200, SERIAL_8N1, 16, 17);


  delay(10);

  setupMode();
}

void loop() {

  webServer.handleClient();
}


void startWebServer() {

    M5.Lcd.print("Starting Web Server at ");
    M5.Lcd.println(WiFi.softAPIP());
    webServer.on("/", []() {
      // String s = "<h1>Wi-Fi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
      // s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      // s += ssidList;
      // s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";

      String s = "<h1>Testing my m5Stack wifi network</h1>";

      webServer.send(200, "text/html", makePage("Wi-Fi Settings", s));
    });

    webServer.on("/go", []() {
      // String s = "<h1>Wi-Fi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
      // s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      // s += ssidList;
      // s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";

      String s = "<a href=\"/stop\">STOP</a>";

      Serial2.printf("SS %6d %6d\r", 8000, 8000);
      M5.Lcd.println("Going now!!!");


      webServer.send(200, "text/html", makePage("Wi-Fi Settings", s));

    });

    webServer.on("/button", []() {
      // String s = "<h1>Wi-Fi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
      // s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      // s += ssidList;
      // s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";
      String s = "";
      s += "<script>\n";
      s += "const url='http://192.168.4.1/go';\n";
      s += "const url2='http://192.168.4.1/stop';\n";
      s += "const url3='http://192.168.4.1/reverse';\n";
      s += "const url4='http://192.168.4.1/left';\n";
      s += "const url5='http://192.168.4.1/right';\n";
      s += "window.onkeydown = function(event) {\n";
      s += "console.log(\"Key pressed\");\n";
      s += "var Http = new XMLHttpRequest();\n";
      s += "if (event.keyCode == 87) {\n";
      s += "Http.open(\"GET\", url);\n";
      s += "} else  if (event.keyCode == 83) {\n";
      s += "Http.open(\"GET\", url3);\n";
      s += "} else if (event.keyCode == 65) {\n";
      s += "Http.open(\"GET\", url4);\n";
      s += "} else  if (event.keyCode == 68) {\n";
      s += "Http.open(\"GET\", url5);\n";
      s += "}\n";
      s += "Http.send();\n";
      s += "}\n";
      s += "\n";
      s += "window.onkeyup = function(event) {\n";
      s += "var Http2 = new XMLHttpRequest();\n";
      s += "Http2.open(\"GET\", url2);\n";
      s += "Http2.send();\n";
      s += "}\n";
      s += "\n";
      s += "</script>\n";

s += "<button onclick=\"Http.send();\">Click me</button>";




      webServer.send(200, "text/html", makePage("Wi-Fi Settings", s));

    });



    webServer.on("/stop", []() {
      // String s = "<h1>Wi-Fi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
      // s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
      // s += ssidList;
      // s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";



      Serial2.printf("SS %6d %6d\r", 0, 0);
    });


    webServer.on("/reverse", []() {
      Serial2.printf("SS %6d %6d\r", -8000, -8000);
    });

    webServer.on("/left", []() {
      Serial2.printf("SS %6d %6d\r", -8000, 8000);
    });

    webServer.on("/right", []() {
      Serial2.printf("SS %6d %6d\r", 8000, -8000);
    });




    webServer.onNotFound([]() {
      String s = "<h1>Not found</h1>";
      webServer.send(200, "text/html", makePage("AP mode", s));
    });


  webServer.begin();
}

void setupMode() {

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID, apPASSWORD);
  WiFi.mode(WIFI_MODE_AP);
  // WiFi.softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
  // WiFi.softAP(const char* ssid, const char* passphrase = NULL, int channel = 1, int ssid_hidden = 0);
  // dnsServer.start(53, "*", apIP);
  startWebServer();
  Serial.print("Starting Access Point at \"");
  M5.Lcd.print("Starting Access Point at \"");
  Serial.print(apSSID);
  M5.Lcd.print(apSSID);
  Serial.println("\"");
  M5.Lcd.println("\"");
}



String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}

String urlDecode(String input) {
  String s = input;
  s.replace("%20", " ");
  s.replace("+", " ");
  s.replace("%21", "!");
  s.replace("%22", "\"");
  s.replace("%23", "#");
  s.replace("%24", "$");
  s.replace("%25", "%");
  s.replace("%26", "&");
  s.replace("%27", "\'");
  s.replace("%28", "(");
  s.replace("%29", ")");
  s.replace("%30", "*");
  s.replace("%31", "+");
  s.replace("%2C", ",");
  s.replace("%2E", ".");
  s.replace("%2F", "/");
  s.replace("%2C", ",");
  s.replace("%3A", ":");
  s.replace("%3A", ";");
  s.replace("%3C", "<");
  s.replace("%3D", "=");
  s.replace("%3E", ">");
  s.replace("%3F", "?");
  s.replace("%40", "@");
  s.replace("%5B", "[");
  s.replace("%5C", "\\");
  s.replace("%5D", "]");
  s.replace("%5E", "^");
  s.replace("%5F", "-");
  s.replace("%60", "`");
  return s;
}
