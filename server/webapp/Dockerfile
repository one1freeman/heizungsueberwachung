FROM python:3.10.19-slim-trixie

WORKDIR /app

COPY ./app .

RUN pip install --no-cache-dir -r requirements

EXPOSE 6767

RUN python app.py