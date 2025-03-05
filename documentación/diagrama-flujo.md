# Diagrama de Flujo
![Imagen de WhatsApp 2025-03-05 a las 17 31 47_f73585c0](https://github.com/user-attachments/assets/f895963b-b241-4371-ae75-54af83c7f451)

## Descripción
Representa el flujo detallado de ejecución:

### Secuencia de Inicialización
- Configuración de hardware y periféricos (incluyendo TIM2 para PWM)
- Inicialización de subsistemas (keypad, display, heartbeat)
- Inicio del PWM para el servomotor (HAL_TIM_PWM_Start)
- Posicionamiento inicial del servo en posición cerrada (move_servo(2000))
- Activación de recepciones UART por interrupción

### Procesamiento de Comandos
- Verificación de buffer lleno (5 bytes)
- Validación de formato "#*X*#"
- Ejecución de acción correspondiente:
  - **A**: 
    - Abrir puerta (LED verde ON, rojo OFF)
    - Posicionar servo en apertura (move_servo(500))
    - Mostrar estado en display
  - **C**: 
    - Cerrar puerta (LED rojo ON, verde OFF)
    - Posicionar servo en cierre (move_servo(2000))
    - Mostrar estado en display
  - **1**: Mostrar estado actual
  - **B**: Limpiar buffer

### Control del Servomotor
La función move_servo(position) controla la posición del servomotor:
- **2000**: Posición de cierre (180 grados)
- **500**: Posición de apertura (0 grados)
