# ENVOI DE DONNEES EN WIFI ESP32 
# Étape 1 : Connecter l’ESP32 sur le réseau du lycée
- lancer le logiciel Arduino
- Choisir le type de carte ESP32 Dev module
- Choisir le PORT COM associé à l’Arduino
 - recuperer l'adresse ip de la carte esp32
  # Programme Arduino Adresse IP ESP32

Copiez ce code dans votre Arduino IDE :

```cpp
#include <WiFi.h>

const char* ssid = "yourNetworkName";
const char* password = "yourNetworkPassword";

void setup(){
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}
```

