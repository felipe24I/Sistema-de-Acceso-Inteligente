# Diagrama de Contenedor

## Descripción
Detalla los componentes físicos del sistema y sus interconexiones:

### Componentes Principales
- **STM32 - HAL**: Microcontrolador central que ejecuta el firmware
- **Periféricos de Salida**:
  - **Display OLED SSD1306**: Interfaz visual de información
  - **LEDs Indicadores**: Rojo (cerrado), Verde (abierto), Amarillo (heartbeat)
  - **Servomotor**: Actuador físico para abrir/cerrar la puerta
- **Periféricos de Entrada**:
  - **Keypad Matricial**: Entrada local de comandos
  - **UART2**: Comunicación con PC Host
  - **UART3**: Comunicación con ESP01 (Internet)

### Interfaces de Hardware
- **I2C1**: Para el display OLED
- **GPIO**: Control de LEDs y lectura de keypad
- **USART2/3**: Comunicaciones seriales
- **TIM2 (PWM)**: Control del servomotor

### Comandos
El sistema responde a cuatro comandos principales:
- **#*A*#**: Abrir puerta (mueve servomotor a posición abierta)
- **#*C*#**: Cerrar puerta (mueve servomotor a posición cerrada)
- **#*1*#**: Consultar estado actual
- **B**: Limpiar buffer de entrada
