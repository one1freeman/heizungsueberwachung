#include <PubSubClient.h>
#include "mqtt.h"
#include "secrets.h"

PubSubClient mqtt;

String id;
String dataTopic;
String statusTopic;

void reconnect() {
    // Loop until we're reconnected
    int attempt = 1;

    while (!mqtt.connected()) {
        Serial.print("Attempting MQTT connection...");

        // Attempt to connect
        if (mqtt.connect(id.c_str(), MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("connected!");

            // Once connected, publish an announcement
            mqtt.publish(statusTopic.c_str(), "online");
        } else {
            Serial.print("failed, mqtt state: ");
            Serial.println(mqtt.state());
            Serial.println(" try again in " + String(5000*attempt/1000) + " seconds");

            // Wait 5 seconds before retrying
            delay(5000*attempt);

            // exponential backoff with a maximum delay of 100 seconds
            attempt = (attempt < 20) ? attempt + 1 : 20;
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setupMQTT(Client& networkClient, String clientId) {
    mqtt.setClient(networkClient);
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt.setCallback(callback);

    id = clientId;
    dataTopic = "IoTDevice/" + id + "/sensor0";
    statusTopic = "IoTDevice/" + id + "/status";
}

void mqttLoop() {
    if (!mqtt.connected()) {
        reconnect();
    }

    mqtt.loop();
}

void mqttPublish(const char* message) {
    if (mqtt.connected()) {
        mqtt.publish(dataTopic.c_str(), message);
    } else {
        Serial.println("MQTT not connected, cannot publish message");
    }
}