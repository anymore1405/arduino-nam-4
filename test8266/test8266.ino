#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);
String a = {"test\n"};
char* ssid = "";
char* password = "";

String webPage()
 { 
  String html = {
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "   <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
  "  <title>Chọn kết nối wifi</title>"
  "  <meta name='viewport' content='width=device-width, initial-scale=1'>"
  "  <style>"
  "    .b{width: 100px;height: 40px;font-size: 21px;color: #FFF;background-color:#4caf50;border-radius: 10px;}"
  "    .t{width: 100px;height: 40px;font-size: 21px;color: #FFF;background-color:#f44336;border-radius: 10px;}"
  "  </style>"
  "</head>"
  "<body>"
  "<div style='width: 330px;height: auto;margin: 0 auto;margin-top: 70px'>"
  "<h1 align='center'>Chọn kết nối WIFI</h1>"
  "<form action='setup' method='POST'>"
  "<select name='ssid' required>"
  };
  html.concat(a);
  html.concat({
    "</select>"
    "<input type='text' name='password'>"
    "<input type='submit'>"
  "</form>"
  "</div>"
  "</body>"
  "</html>"
});
return html;}
void TrangChu()
{
  server.send(200, "text/html", webPage());
}
void setupConnect(){
  Serial.printf("pre name: %s, value: %s\n", server.arg("password"), server.arg("ssid"));
  String s = server.arg("ssid");
  String p = server.arg("password");
  p.toCharArray(password, 20);
       Serial.printf("name: %s, value: %s\n", password, WiFi.SSID(s.toInt()).c_str());
    WiFi.begin(WiFi.SSID(s.toInt()).c_str(), password);
    Serial.printf("connect name: %s, value: %s\n", WiFi.SSID(s.toInt()).c_str(), password);
    if (WiFi.status() != WL_CONNECTED){
        server.send(200, "text/html", "<html>Kết nối thất bại</html>");
      }
      server.send(200, "text/html", "<html>Kết nối thành công</html>");
  }
void setup()
{
  Serial.begin(115200);
  int count = WiFi.scanNetworks();
    for(int i = 0; i<count;i++){
      a.concat("<option value='");
      a.concat(i);
      a.concat("'>");
      a.concat(WiFi.SSID(i).c_str());
      a.concat("</option>");
      Serial.printf("SSID: %s\n", WiFi.SSID(i).c_str());
    };
    Serial.printf("start\n");
  while (WiFi.softAP("ESP8266 WiFI", "12345678") == false) 
   {
     Serial.print(".");
     delay(300);
   }
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", TrangChu);
  server.on("/setup", setupConnect);
  server.begin();

}
void loop()
{
  server.handleClient();
}
