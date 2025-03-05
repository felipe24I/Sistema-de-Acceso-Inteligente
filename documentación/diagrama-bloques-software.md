# Diagrama de Bloques Software

## Descripción
Detalla el flujo de ejecución del software y sus módulos principales, incluyendo el control del servomotor:

### Inicialización
1. Configuración de hardware (HAL, Periféricos, Reloj)
2. Inicialización de periféricos:
   - GPIO: Pines para LEDs, keypad y señales de control
   - UART2/3: Comunicación con host y ESP01
   - I2C1: Interfaz para display OLED
   - TIM2: Configuración de PWM para el servomotor
3. Inicialización de subsistemas:
   - keypad_init: Configura el teclado matricial
   - display_init: Inicializa OLED y muestra "Sistema Listo"
   - heartbeat_init: Configura LED de actividad
   - ring_buffer_init: Prepara buffer circular de 5 bytes
   - init_door_state: Estado inicial cerrado (LED rojo ON)
4. Inicio del control del servomotor:
   - HAL_TIM_PWM_Start: Activa la señal PWM
   - move_servo(2000): Posiciona el servo en cierre (180°)
5. Activación de interrupciones UART

### Loop Principal
- *heartbeat_update*: Actualiza LED de actividad
- *check_keypad*: Procesa entradas del teclado
- *process_command*: Verifica y ejecuta comandos
- *display_update*: Gestiona estados de la pantalla

### Control de Puerta (control_action)
- *Comando A* (Abrir):
  - Enciende LED verde, apaga LED rojo
  - Posiciona servomotor en apertura (move_servo(500))
  - Actualiza display con estado "Puerta Abierta"
- *Comando C* (Cerrar):
  - Enciende LED rojo, apaga LED verde
  - Posiciona servomotor en cierre (move_servo(2000))
  - Actualiza display con estado "Puerta Cerrada"
- *Comando 1* (Estado):
  - Muestra el estado actual de la puerta

### Control del Servomotor
- Función *move_servo(position)*:
  - Configura ciclo de trabajo del PWM según posición deseada
  - 500: Posición 0° (abierto)
  - 2000: Posición 180° (cerrado)
