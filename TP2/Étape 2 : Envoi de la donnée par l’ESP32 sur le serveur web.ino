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
