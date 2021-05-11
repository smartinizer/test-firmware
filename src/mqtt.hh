WiFiClient espClient;
PubSubClient client(espClient);

class MQTT_handler {
  private:
    // ip or hostname of mqtt broker
    const char* mqtt_server = "pi-docker";
    long lastMsg = 0;
    void reconnect();
    void callback_decode(char* topic, byte* message, unsigned int length);
  public:
    void (*usecase_callback)(char*, String);
    void loop();
    MQTT_handler(void (*callback_func)(char*, String));
};

MQTT_handler::MQTT_handler(void (*callback_func)(char*, String)) {
    usecase_callback = callback_func; 
    client.setServer(mqtt_server, 1883);

    // to make non-static function static... i know it doesnt look nice :( but it works
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    client.setCallback(std::bind(&MQTT_handler::callback_decode, this, _1,_2,_3));
}

void MQTT_handler::reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP32")) {
        Serial.println("connected");
        // Subscribe
        client.subscribe("command");
        } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
        }
    }
}

void MQTT_handler::loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > 10*1000) {
        lastMsg = now;
        client.publish("alive_check", "Hello");
    }
}

void MQTT_handler::callback_decode(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageString;
    
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageString += (char)message[i];
    }
    Serial.println();
    MQTT_handler::usecase_callback(topic,messageString);
}
