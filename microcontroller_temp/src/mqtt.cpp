#include <PubSubClient.h>
#include "mqtt.h"
#include "secrets.h"

PubSubClient mqtt;

String id;
char dataTopic[50];
char statusTopic[50];

void reconnect() {
    // Loop until we're reconnected
    int attempt = 1;

    while (!mqtt.connected()) {
        Serial.print("Attempting MQTT connection...");

        // Attempt to connect
        if (mqtt.connect(id.c_str(), MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("connected");

            // Once connected, publish an announcement
            mqtt.publish(statusTopic, "online");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqtt.state());
            Serial.println(" try again in 5 seconds");

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
    snprintf(dataTopic, sizeof(dataTopic), "IoTDevice/%s/sensor0", id.c_str());
    snprintf(statusTopic, sizeof(statusTopic), "IoTDevice/%s/status", id.c_str());
}

void mqttLoop() {
    if (!mqtt.connected()) {
        reconnect();
    }

    mqtt.loop();
}

void mqttPublish(const char* message) {
    if (mqtt.connected()) {
        mqtt.publish(dataTopic, message);
    } else {
        Serial.println("MQTT not connected, cannot publish message");
    }
}