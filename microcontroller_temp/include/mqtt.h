#ifndef MQTT_H
#define MQTT_H

void setupMQTT(Client& networkClient);
void mqttLoop();
void mqttPublish(const char* topic, const char* message);

#endif