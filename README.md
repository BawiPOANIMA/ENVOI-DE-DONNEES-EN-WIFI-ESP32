# Étape 1 : Connecter l’ESP32 sur le réseau du lycée
- lancer le logiciel Arduino
- Choisir le type de carte ESP32 Dev module
- Choisir le PORT COM associé à l’Arduino
 - recuperer l'adresse ip de la carte esp32
  # Programme Arduino Adresse IP ESP32

Copiez ce code dans votre Arduino IDE :

```cpp
#include <WiFi.h>

const char* ssid = "Nom du réseau"; // parti a modifier
const char* password = "Mot de passe réseau"; //parti a madifier

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
- Récupérer l'IP de la va permetre de creer un bouton sur la page index.php pour allumer une led et buzer
# Étape 2 : Envoi de la donnée par l’ESP32 sur le serveur web
-  Pour envoyer une donner au serveur nous utilison la requête POST	qui permet d'envoyer une nouvelle donnée, GET	Lire	récupérer une valeur, PUT	Modifier	mettre à jour une donnée.
-  Le programme si-dessous permet denvoyer une donner aléatoire toute les 5 seconde  sur le serveur Ubuntu.

Copiez ce code dans votre Arduino IDE :
 ```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "####"; // parti a modifier
const char* password = "####"; //parti a madifier
const char* serverName = "http://Adresse IP UBUNTU/data.php"; //parti a modifier

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connexion au WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté au WiFi !");
  randomSeed(analogRead(0)); // initialise le générateur de nombres aléatoires
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int valeur = random(0, 100); // génère un nombre aléatoire entre 0 et 99

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String data = "valeur=" + String(valeur);
    int httpResponseCode = http.POST(data); // envoi POST

    Serial.print("Valeur aléatoire envoyée: ");
    Serial.println(valeur);

    if (httpResponseCode > 0) {
      String response = http.getString(); // récupère la réponse du serveur
    } else {
      Serial.print("Erreur lors de l'envoi POST, code: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // termine la connexion
  } else {
    Serial.println("WiFi non connecté !");
  }
  delay(5000); // attente de 5 secondes avant le prochain envoi
}
```
