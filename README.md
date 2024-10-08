# ArduinoBeacons

Este proyecto implementa un medidor de calidad del aire utilizando un sensor de CO2 y un módulo Bluetooth Low Energy (BLE) para la transmisión de datos. Las lecturas de CO2 y temperatura se publican de forma inalámbrica, permitiendo monitorizar la calidad del aire en tiempo real.

## Requisitos

- Arduino IDE
- Biblioteca BLE para Arduino (instalar desde el gestor de bibliotecas del IDE)
- Sensor de CO2 compatible
- Placa Arduino (ej. Arduino Uno, Nano, etc.)

## Estructura del Proyecto

El proyecto está dividido en varias clases que manejan diferentes aspectos del sistema:

### Clases Principales

- **Medidor**
  - Se encarga de leer las señales analógicas de los sensores (CO2 y temperatura).
  - **Métodos Importantes:**
    - `iniciarMedidor()`: Inicializa el medidor y realiza configuraciones necesarias.
    - `medirCO2()`: Lee el nivel de CO2 y lo convierte en una concentración en ppm.
    - `medirTemperatura()`: Simula la medición de la temperatura (actualmente devuelve un valor fijo).

- **Publicador**
  - Maneja la emisión de datos a través de Bluetooth.
  - **Métodos Importantes:**
    - `encenderEmisora()`: Activa el emisor BLE.
    - `publicarCO2(valorCO2, contador, tiempoEspera)`: Publica el valor de CO2.
    - `publicarTemperatura(valorTemperatura, contador, tiempoEspera)`: Publica el valor de temperatura.

- **PuertoSerie**
  - Facilita la comunicación serie entre la placa Arduino y el entorno de desarrollo.
  - **Métodos Importantes:**
    - `esperarDisponible()`: Espera hasta que la comunicación serie esté disponible.
    - `escribir(mensaje)`: Escribe un mensaje en la consola serie.

- **ServicioEnEmisora**
  - Maneja los servicios y características del emisor BLE.
  - **Métodos Importantes:**
    - `anyadirCaracteristica(car)`: Añade características al servicio BLE.
    - `activarServicio()`: Activa el servicio BLE y sus características.

### Utilidad de las Clases

1. **Medidor**: Proporciona la funcionalidad para medir la calidad del aire y la temperatura.
2. **Publicador**: Encargado de la comunicación Bluetooth, permite transmitir los datos recolectados.
3. **PuertoSerie**: Facilita la depuración y comunicación en el entorno de desarrollo.
4. **ServicioEnEmisora**: Configura y activa el servicio BLE y sus características, permitiendo la comunicación con dispositivos externos.

## Instrucciones de Uso

1. Conecta el sensor de CO2 y la placa Arduino.
2. Abre el proyecto en el Arduino IDE.
3. Configura los pines del sensor en la clase `Medidor` según tu conexión.
4. Carga el código en la placa Arduino.
5. Utiliza una aplicación compatible con BLE para monitorizar los datos transmitidos.

