
namespace usecase{

    int ledPin = 2;
    char msg[50];
    int value = 0;
    String topic = "command";

    void loadConfig(String topicConfig, String ledPinConfig){
        topic = topicConfig;
        ledPin = ledPinConfig.toInt();
        Serial.println("Loading Config, topis is " + topic + ", LED-Pin is " + String(ledPin));
    }

    void callback(char* topic, String message) {
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");

        if (String(topic) == topic) {
             
            //Relais:
            Serial.print("Changing output to ");
            if(message == "on"){
                Serial.println("on");
                digitalWrite(ledPin, HIGH);
            }
            else if(message == "off"){
                Serial.println("off");
                digitalWrite(ledPin, LOW);
            } 
            // My PC-Switch use case ^^
            // if (message=="switch"){
            //     Serial.println("Switch!");
            //     digitalWrite(ledPin, HIGH);
            //     delay(1000);
            //     digitalWrite(ledPin, LOW);
            // }
        }
    }
}
