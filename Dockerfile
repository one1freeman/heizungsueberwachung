FROM homeassistant/home-assistant:latest

ENV TZ=Europe/Berlin

EXPOSE 8123

VOLUME ["/config"]