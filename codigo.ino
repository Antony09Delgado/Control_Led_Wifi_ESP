#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Tiktok";
const char* password = "12345678";

const int LED_AZUL = D0;   // GPIO16
const int LED_VERDE = D1;  // GPIO5
const int LED_ROJO = D2;   // GPIO4

ESP8266WebServer server(80);

void manejarRaiz() {
  String html = "<!DOCTYPE html>";
  html += "<html lang='es'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Control de LEDs</title>";
  html += "<style>";
  html += "body{margin:0;min-height:100vh;display:flex;justify-content:center;align-items:center;background:#101726;color:#eef;font-family:Arial,sans-serif;}";
  html += ".panel{width:min(92%,480px);padding:24px;border-radius:20px;background:#14203a;box-shadow:0 18px 40px rgba(0,0,0,0.25);text-align:center;}";
  html += "h1{margin:0 0 18px;font-size:2rem;}";
  html += ".buttons{display:grid;gap:14px;grid-template-columns:repeat(3,1fr);}";
  html += "button{border:none;border-radius:16px;padding:16px 12px;background:#1f2f4b;color:#eef;cursor:pointer;transition:background 0.2s ease;display:flex;flex-direction:column;gap:10px;align-items:center;justify-content:center;min-height:110px;font-size:0.95rem;}";
  html += "button.on{background:#3f6b98;box-shadow:0 8px 18px rgba(0,0,0,0.2);}";
  html += ".icon{font-size:2.4rem;line-height:1;}";
  html += ".label{font-weight:700;}";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<div class='panel'>";
  html += "<h1>Control de LEDs</h1>";
  html += "<p>Conecta a tu red Wi-Fi y accede a esta IP local.</p>";
  html += "<div class='buttons'>";
  html += "<button id='btnAzul' data-pin='" + String(LED_AZUL) + "'><span class='icon'>🔵</span><span class='label'>Azul</span></button>";
  html += "<button id='btnVerde' data-pin='" + String(LED_VERDE) + "'><span class='icon'>🟢</span><span class='label'>Verde</span></button>";
  html += "<button id='btnRojo' data-pin='" + String(LED_ROJO) + "'><span class='icon'>🔴</span><span class='label'>Rojo</span></button>";
  html += "</div>";
  html += "</div>";
  html += "<script>";
  html += "document.querySelectorAll('button[data-pin]').forEach(function(button){";
  html += "  button.addEventListener('click', function(){";
  html += "    var pin = button.dataset.pin;";
  html += "    fetch('/toggle?pin=' + pin).then(function(response){";
  html += "      if(!response.ok) throw new Error('Error en el servidor');";
  html += "      button.classList.toggle('on');";
  html += "    }).catch(function(){";
  html += "      alert('No se pudo cambiar el estado. Verifica la conexión.');";
  html += "    });";
  html += "  });";
  html += "});";
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void manejarToggle() {
  if (!server.hasArg("pin")) {
    server.send(400, "text/plain", "Falta pin");
    return;
  }

  int pin = server.arg("pin").toInt();
  if (pin != LED_AZUL && pin != LED_VERDE && pin != LED_ROJO) {
    server.send(400, "text/plain", "Pin no permitido");
    return;
  }

  digitalWrite(pin, !digitalRead(pin));
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println();
  Serial.print("Conectado. IP local: ");
  Serial.println(WiFi.localIP());

  server.on("/", manejarRaiz);
  server.on("/toggle", manejarToggle);
  server.begin();
}

void loop() {
  server.handleClient();
}
