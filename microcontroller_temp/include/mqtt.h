#ifndef MQTT_H
#define MQTT_H

void setupMQTT(Client& networkClient, String clientId);
void mqttLoop();
void mqttPublish(const char* message);

#endif