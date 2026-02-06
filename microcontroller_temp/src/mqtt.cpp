#include <PubSubClient.h>
#include "mqtt.h"
#include "secrets.h"

PubSubClient mqtt;

void reconnect() {
    // Loop until we're reconnected
    while (!mqtt.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (mqtt.connect(MQTT_USER, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            mqtt.publish("outTopic","hello world");
            // ... and resubscribe
            mqtt.subscribe("inTopic");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqtt.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
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

void setupMQTT(Client& networkClient) {
    mqtt.setClient(networkClient);
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt.setCallback(callback);
}

void mqttLoop() {
    if (!mqtt.connected()) {
        reconnect();
    }

    mqtt.loop();
}

void mqttPublish(const char* topic, const char* message) {
    if (mqtt.connected()) {
        mqtt.publish(topic, message);
    } else {
        Serial.println("MQTT not connected, cannot publish message");
    }
}