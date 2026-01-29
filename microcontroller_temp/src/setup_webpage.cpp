#include "setup_webpage.h"
#include <Arduino.h>
#include <DNSServer.h>
#include <WebServer.h>

#include "html_pages.h"
#include "network.h"
#include "NVS_handling.h"

DNSServer dnsServer;
WebServer server(80);

bool setupFinished = false;

void handleRoot(bool connectFailed = false) {
    char pageBuffer[1024];
    snprintf(pageBuffer, sizeof(pageBuffer), SETUP_PAGE, connectFailed ? "<p style=\"color:red;\">Fehlgeschlagen. Bitte erneut versuchen.</p>" : "");
    server.send(200, "text/html", pageBuffer);
}

void serverHandleClient()
{
    dnsServer.processNextRequest();
    server.handleClient();
}

void shutdownServer()
{
    Serial.print("Shutting down configuration server...");
    dnsServer.stop();
    server.close();
    shutdownAP();
    Serial.println("done.");
}

void setupServerRoutes()
{
    server.on("/", HTTP_GET, []() {
        handleRoot();
    });

    server.on("/submit", HTTP_POST, []() {
        String ssid = server.arg("ssid");
        String pass = server.arg("pass");

        Serial.print("Received SSID: ");
        Serial.println(ssid);
        Serial.print("Received Password: ");
        Serial.println(pass);

        if (ssid.length() > 0 && pass.length() > 0) 
        {
            if (connectToWiFi(ssid.c_str(), pass.c_str()))
            {
                setupFinished = true;
                saveCredentials(ssid.c_str(), pass.c_str());
            }

        } else {
            Serial.println("SSID or Password is empty.");
        }
        
        if (setupFinished)
        {
            server.send(200, "text/html", "<h1>Configuration Successful</h1><p>The device is now connected to the WiFi network.</p>");
        } else {
            handleRoot(true);
        }
    });
    
    server.on("/favicon.ico", HTTP_GET, []() {
        server.send(204); // No Content
    });
    
    // necessary for captive portal redirection
    server.onNotFound([]() {
        server.sendHeader("Location", "http://192.168.4.1/", true);
        server.send(302, "text/plain", "");
    });
}

bool setupWebpage(const char* ssid, const char* pass)
{
    startAP(ssid, pass);

    // Start DNS server for captive portal
    if (dnsServer.start(53, "*", WiFi.softAPIP())) {
        Serial.println("Started DNS server in captive portal-mode");
    } else {
        Serial.println("Can't start DNS server!");
        return false;
    }

    setupServerRoutes();
    
    server.begin();
    
    while (!setupFinished)
    {
        serverHandleClient();
        delay(5);
    }

    Serial.println("Configuration finished");

    delay(500);
    
    shutdownServer();

    return true;
}

