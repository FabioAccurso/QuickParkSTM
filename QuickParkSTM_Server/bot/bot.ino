#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "Home&Life SuperWiFi-2D55";
const char* password = "FH7GBQFP8XPKEXY3";
const char* botToken = "7593165618:AAEXKfGBs6feieRBebRZMTaB9gXNqacIPJM";  
// const char* chatID = "YYY";       // <- lo uso solo se voglio un unico utilizzatore

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

String serialBuffer = "";
int postiLiberi = -1;

void setup() {
  Serial.begin(38400);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setInsecure();  // Disattiva SSL cert check (più facile)
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      parseMsg(serialBuffer);
      serialBuffer = "";
    } else {
      serialBuffer += c;
    }
  }

  // Poll ogni secondo
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 1000) {
    int newMsg = bot.getUpdates(bot.last_message_received + 1);
    while (newMsg) {
      for (int i = 0; i < newMsg; i++) {
        String text = bot.messages[i].text;
        String chat_id = bot.messages[i].chat_id;

        if (text == "/posti") {
          bot.sendMessage(chat_id, "🚘 Posti disponibili: " + String(postiLiberi), "");
        } else {
          bot.sendMessage(chat_id, "❌ Comando non valido. Usa /posti", "");
        }
      }
      newMsg = bot.getUpdates(bot.last_message_received + 1);
    }
    lastCheck = millis();
  }
}

void parseMsg(String msg) {
  int index = msg.indexOf("POSTI:");
  if (index != -1) {
    int posti = msg.substring(index + 6).toInt();
    if (posti >= 0 && posti <= 100) { // supponiamo massimo 100 posti
      postiLiberi = posti;
      Serial.println("📥 STM32 → Posti liberi aggiornati: " + String(postiLiberi));
    }
  }
}
