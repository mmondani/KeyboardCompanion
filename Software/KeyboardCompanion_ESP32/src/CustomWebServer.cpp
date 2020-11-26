#include "CustomWebServer.h"




CustomWebServer::CustomWebServer () : server(80) {
  
  setRoutes();
}


void CustomWebServer::begin () {
  server.begin();
}

void CustomWebServer::end () {
  server.end();
}


void CustomWebServer::setRoutes () {
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
}