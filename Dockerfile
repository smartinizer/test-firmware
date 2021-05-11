FROM python:3.9 AS build
WORKDIR /usr/src/app
COPY /. .
RUN pip install -U platformio
RUN pio run -d .


FROM nginx:alpine
WORKDIR /usr/share/nginx/html
COPY --from=build /usr/src/app/.pio/build/esp32doit-devkit-v1/firmware.bin .
COPY /config.json .
