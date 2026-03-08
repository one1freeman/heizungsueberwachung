#include <PubSubClient.h>
#include "mqtt.h"
#include "secrets.h"

PubSubClient mqtt;

String id;
String dataTopic;
String statusTopic;
String discovery_topic;
String discovery_payload;

void reconnect() {
    // Loop until we're reconnected
    int attempt = 1;

    while (!mqtt.connected()) {
        Serial.print("Attempting MQTT connection...");

        // Attempt to connect
        if (mqtt.connect(id.c_str(), MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("connected!");

            // Once connected, publish mqtt discovery payload
            mqtt.publish(discovery_topic.c_str(), discovery_payload.c_str(), true);
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

void setupMQTT(Client& networkClient, String uniqueId) {
    mqtt.setClient(networkClient);
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt.setCallback(callback);

    id = uniqueId;
    dataTopic = "sensor/" + id + "/state";
    statusTopic = "sensor/" + id + "/status";
    discovery_topic = "homeassistant/sensor/" + id + "/config";
    discovery_payload = "{\
        \"name\": \"" + id + "\",\
        \"device_class\": \"temperature\",\
        \"state_topic\": \"" + dataTopic + "\",\
        \"unique_id\": \"" + id + "\",\
        \"unit_of_measurement\": \"°C\"\
    }";
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