FROM homeassistant/home-assistant:latest

RUN mkdir -p /config/blueprints/automation/

COPY mqtt_temp_alert.yaml /config/blueprints/automation/

ENV TZ=Europe/Berlin

EXPOSE 8123