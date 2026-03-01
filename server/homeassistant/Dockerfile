FROM homeassistant/home-assistant:latest

COPY configuration.yaml homeassistant/
COPY mqtt_temp_alert.yaml homeassistant/blueprints/automation/

ENV TZ=Europe/Berlin

EXPOSE 8123