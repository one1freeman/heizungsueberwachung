#include "setup_webpage.h"
#include <Arduino.h>
#include <DNSServer.h>
#include <WebServer.h>

DNSServer dnsServer;
WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", "<h1>Heizungsueberwachung</h1>");
}

bool serverSetup()
{
    // Start DNS server for captive portal
    if (dnsServer.start(53, "*", WiFi.softAPIP())) {
        Serial.println("Started DNS server in captive portal-mode");
    } else {
        Serial.println("Err: Can't start DNS server!");
        return false;
    }

    // Setup web server routes for captive portal
    server.on("/", HTTP_GET, []() {
        handleRoot();
    });

    server.on("/hotspot-detect.html", HTTP_GET, []() {
        handleRoot();
    });

    server.onNotFound([]() {
        server.sendHeader("Location", "http://192.168.4.1/", true);
        server.send(302, "text/plain", "");
    });

    server.begin();
    return true;
}

void serverHandleClient()
{
    dnsServer.processNextRequest();
    server.handleClient();
}

void shutdownServer()
{
    dnsServer.stop();
    server.close();
}
