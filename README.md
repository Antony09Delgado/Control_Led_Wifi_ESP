# Control de LEDs con ESP8266

Este proyecto permite encender y apagar tres LEDs desde una página web sencilla, usando un ESP8266.

## ¿Qué hace?

Tu ESP8266 se conecta a una red Wi-Fi y crea una pequeña página web local. Desde esa página puedes presionar botones para controlar:

- LED azul
- LED verde
- LED rojo

## ¿Qué necesitas?

- Un ESP8266
- 3 LEDs
- 3 resistencias de $220\Omega$ (recomendado)
- Cables y una placa de pruebas

## Conexión de los pines

El código usa estos pines del ESP8266:

- D0 → LED azul
- D1 → LED verde
- D2 → LED rojo

## Configuración de Wi-Fi

Antes de subir el código, cambia estos datos en el archivo `codigo.ino`:

```cpp
const char* ssid = "nombre de wifi";
const char* password = "clave del wifi";
```

Asegúrate de reemplazarlos por el nombre y la contraseña de tu red Wi-Fi.

## Cómo usarlo

1. Abre el archivo `codigo.ino` en Arduino IDE.
2. Sube el código al ESP8266.
3. Espera a que se conecte a la red Wi-Fi.
4. Abre el Serial Monitor para ver la IP asignada.
5. Entra a esa IP desde tu navegador.

## ¿Qué verás?

Verás una página con tres botones grandes, uno para cada color. Al presionarlos, el LED correspondiente se enciende o se apaga.

## Nota importante

Este proyecto está pensado para aprender y probar de forma sencilla. Si quieres, luego puedes expandirlo para agregar:

- más botones
- modos de brillo
- temporizadores
- control desde el celular

## Ejemplo rápido

Si tu ESP8266 muestra una IP como esta:

```txt
192.168.1.20
```

Entonces en tu navegador debes abrir:

```txt
http://192.168.1.20
```
