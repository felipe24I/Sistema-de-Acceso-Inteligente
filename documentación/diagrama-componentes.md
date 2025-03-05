# Diagrama de Componentes

![Imagen de WhatsApp 2025-03-05 a las 16 52 03_93df8b8a](https://github.com/user-attachments/assets/c2521d75-60b2-4d90-9912-ab7dcbd3f118)

## Descripción
Muestra la arquitectura interna del software:

### Capas de Software
- **Core ARM Cortex-M**: Procesador principal
- **HAL Drivers**:
  - GPIO HAL: Control de pines digitales
  - I2C HAL: Comunicación con display
  - UART HAL: Comunicación serie
  - SysTick HAL: Temporización
  - **TIM2 PWM HAL**: Control de servomotor

### Librerías Desarrolladas
- **keypad.h**: Gestión del teclado matricial
- **ring_buffer.h**: Implementación de buffer circular
- **keypad_control.h**: Procesamiento de comandos y control de acceso
- **display_control.h**: Gestión del display OLED
- **heartbeat.h**: Control del LED de actividad

### Componentes Funcionales
- **Manejo del Keypad**: Detección y procesamiento de teclas
- **Control de Acceso**: Gestión de estado de puerta
- **Procesamiento de Comandos**: Validación y ejecución
- **Display Manager**: Gestión de interfaz visual
- **Buffer Circular**: Almacenamiento temporal de comandos
- **Heartbeat Monitor**: Indicación de sistema activo
- **Control Servomotor**: Posicionamiento físico de la puerta

### Estados del Sistema
- **Puerta**: Abierta (servo en 500) o Cerrada (servo en 2000)
- **Display**: IDLE, WAIT
